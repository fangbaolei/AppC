/*
 * Copyright (c) 2013 emptyhua@gmail.com
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <libgen.h>
#include "pcs.h"

#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define MAX(a, b) ((a) > (b) ? (a) : (b))


#define MAKE_JSON() \
error = HttpClient_GetError(client); \
if (error != NULL) { \
    BaiduPCS_ThrowError(api, "request failed: %s", error); \
    goto free; \
} \
response = HttpClient_ResponseText(client); \
json = cJSON_Parse(response); \
if (json == NULL) { \
    BaiduPCS_ThrowError(api, "JSON parse error"); \
    goto free; \
}\
item = cJSON_GetObjectItem(json, "error_code"); \
if (item != NULL && item->type == cJSON_Number) { \
    api->error_code = item->valueint; \
    item = cJSON_GetObjectItem(json, "error_msg"); \
    BaiduPCS_ThrowError(api, "%d-%s", api->error_code, item->valuestring); \
    goto free; \
} 

static void _BaiduPCS_Json2File(BaiduPCS *api, PCSFile *file, cJSON *array)
{
    cJSON *item;

    item = cJSON_GetObjectItem(array, "path");
    if (item == NULL || item->type != cJSON_String)
	{
        BaiduPCS_ThrowError(api, "json.list.path is not string");
        goto free;
    }
    PCSFile_SetPath(file, item->valuestring);


	item = cJSON_GetObjectItem(array, "is_dir");
	if (item != NULL && item->type == cJSON_True)
	{	
		file->is_dir = (char)item->valueint;
	}
	else if (item != NULL && item->type == cJSON_False)
	{
		file->is_dir = (char)item->valueint;
	}

#if 0	
    //获取尺寸
    item = cJSON_GetObjectItem(array, "size");
	printf("##size type<%d>##\n",item->type);
    if (item == NULL || item->type != cJSON_String)
	{
        BaiduPCS_ThrowError(api, "json.list.size is not number");
        goto free;
    }
    file->size = (size_t)item->valueint;

    //创建时间
    item = cJSON_GetObjectItem(array, "client_mtime");
	printf("##client_mtime type<%d>##\n",item->type);
    if (item == NULL || item->type != cJSON_Number)
	{
        BaiduPCS_ThrowError(api, "json.list.ctime is not number");
        goto free;
    }
    file->ctime = (unsigned int)item->valueint;
    
    //修改时间
    item = cJSON_GetObjectItem(array, "modified");
	printf("##modified type<%d>##\n",item->type);
    if (item == NULL || item->type != cJSON_Number)
	{
        BaiduPCS_ThrowError(api, "json.list.mtime is not number");
        goto free;
    }
    file->mtime = (unsigned int)item->valueint;
#endif

free:;
}


/* 获取API错误信息 */
const char *BaiduPCS_GetError(BaiduPCS *api)
{
    if (api->error[0] == '\0')
    {
		return NULL;
    }
    printf("Get API error information!\n");
    return api->error;
}

/* 获取空间的用量 */
void BaiduPCS_Info(BaiduPCS *api, BaiduPCSInfo *info)
{
    if (info == NULL || api == NULL) 
		return;
    HttpClient *client      = api->client;
    char *url_buffer        = api->util_buffer0;
    const char *token       = api->access_token;
    cJSON *json             = NULL;
    cJSON *item             = NULL;
    const char *error   	= NULL;
    const char *response    = NULL;
	api->error[0] = '\0';
	api->error_code = 0;

    sprintf(url_buffer, "https://pcs.baidu.com/rest/2.0/pcs/quota?"
           "access_token=%s"
           "&method=info", token);

    HttpClient_Init(client);
    HttpClient_Get(client, url_buffer);
    MAKE_JSON();/* 判断返回的错误信息 */

    item = cJSON_GetObjectItem(json, "quota");
    if (item == NULL || item->type != cJSON_Number)
	{
        BaiduPCS_ThrowError(api, "can't find json.quota");
        goto free;
    }
    info->quota = item->valueint;

    item = cJSON_GetObjectItem(json, "used");
    if (item == NULL || item->type != cJSON_Number)
	{
        BaiduPCS_ThrowError(api, "can't find json.used");
        goto free;
    }
    info->used = item->valueint;
free:
    if (json != NULL)
	{
        cJSON_Delete(json);
    }
}


static size_t _BaiduPCS_UploadReadCallback(void *ptr, size_t size, size_t nitems, void *userdata)
{
	return fread(ptr, size, nitems, (FILE *)userdata);	
}

static void _BaiduPCS_UploadResetCallback(FILE *fp,size_t offset)
{
    fseek(fp, offset, SEEK_SET);
}

static int _BaiduPCS_UploadBigFile(BaiduPCS *api,PCSFile *local_file,const char *remote_file)
{
    PCSFile *result     = NULL;
    HttpClient *client  = api->client;
    char *url_buffer    = api->util_buffer0;
    const char *token   = api->access_token;
    FILE *fp            = NULL;
    int i               = 0;
    int timeout         = 0;

    const char *error   = NULL;
    char *tmp           = NULL;
    const char *response      = NULL;
    char *remote_path_encode  = NULL;

    struct curl_httppost *post = NULL;
    struct curl_httppost *last = NULL;

    cJSON *json         = NULL;
    cJSON *item         = NULL;
    cJSON *array        = NULL;


    fp = fopen(local_file->path, "rb");
    if (fp == NULL)
	{
        BaiduPCS_ThrowError(api, "Local file cannot be read %s", local_file->path);
        goto free;
    }
	char level[16];
	memset(level,0,sizeof(level));
	if(api->level[0] == 's')
	{
		strcpy(level,"sandbox");
	}
	else if(api->level[0] == 'd')
	{
		strcpy(level,"dropbox");
	}
	
	size_t offset = 0;
	char id[32];
	memset(id,0,sizeof(id));
  	printf("size:<%d>\n",local_file->size);
	while(offset < local_file->size)
	{	
		printf("offset:<%d>\n",offset);
		if(offset == 0)	
		{
			sprintf(url_buffer,"https://api-content.dropbox.com/1/chunked_upload?"
						"oauth_consumer_key=%s"
						"&oauth_token=%s"
						"&oauth_signature_method=PLAINTEXT"
						"&oauth_signature=%s%%26%s",api->key,api->access_token,api->secret,api->access_token_secret);
		}
		else
		{
			sprintf(url_buffer,"https://api-content.dropbox.com/1/chunked_upload?"
						"upload_id=%s"
						"&offset=%d"
						"&oauth_consumer_key=%s"
						"&oauth_token=%s"
						"&oauth_signature_method=PLAINTEXT"
						"&oauth_signature=%s%%26%s",id,offset,api->key,api->access_token,api->secret,api->access_token_secret);
		}
		
		printf("\n upload spilt url:<%s>\n",url_buffer);
        fprintf(stderr, "uploading spilt...%d\n", i);
		
        HttpClient_Init(client);

		curl_easy_setopt(client->curl, CURLOPT_READFUNCTION, _BaiduPCS_UploadReadCallback);/* 读数据到 post */
		curl_easy_setopt(client->curl, CURLOPT_READDATA,fp);
		curl_easy_setopt(client->curl, CURLOPT_UPLOAD, 1);
		if((local_file->size - offset) > (5*1024*1024))
		{
			curl_easy_setopt(client->curl, CURLOPT_INFILESIZE, 5*1024*1024);
		}

		 /* 失败重试前，重置 */		 
		 HttpClient_SetFailRetryCallback(client, _BaiduPCS_UploadResetCallback, fp, offset);
		 /* 设置一个较为合理的超时时间 */		 
		 timeout = (local_file->size - offset) / (20 * 1024);
		 printf("timeout:%d\n",timeout);
		 curl_easy_setopt(client->curl, CURLOPT_TIMEOUT, timeout);


		HttpClient_PostHttpData(client, url_buffer, post);
		response = HttpClient_ResponseText(client);
		printf("\n##response spit:<%s>##\n",response);
		
        MAKE_JSON();

        item = cJSON_GetObjectItem(json, "upload_id");
        if (item == NULL || item->type != cJSON_String)
		{
            BaiduPCS_ThrowError(api, "can't find upload_id");
            goto free;
        }
		strcpy(id,item->valuestring);
		
        item = cJSON_GetObjectItem(json, "offset");
		offset = item->valueint;

        if (0) // (item == NULL || item->type != cJSON_String)
		{
            BaiduPCS_ThrowError(api, "can't find upload_id");
            goto free;
        }
		//strcpy(id,item->valuestring);

        cJSON_Delete(json);
        json = NULL;
        curl_formfree(post);
        post = NULL;
        last = NULL;
        i ++;
    }


	printf("upload end...wait for commit..\n");
    remote_path_encode = curl_easy_escape(client->curl, remote_file, 0);
    //合并文件分片
	sprintf(url_buffer, "https://api-content.dropbox.com/1/commit_chunked_upload/%s/%s?"
		"&oauth_consumer_key=%s"
		"&oauth_token=%s"
		"&oauth_signature_method=PLAINTEXT"
		"&oauth_signature=%s%%26%s",level,remote_path_encode,api->key,api->access_token,api->secret,api->access_token_secret);
    curl_free(remote_path_encode);
    remote_path_encode = NULL;

#if 0
    array = cJSON_CreateArray();
    block = local_file->block;
    while (block != NULL) 
	{
        cJSON_AddItemToArray(array, cJSON_CreateString(block->md5));
        block = block->next;
    }
    
    json = cJSON_CreateObject();
    cJSON_AddItemToObject(json, "block_list", array);
    tmp = cJSON_Print(json);

    curl_formadd(&post, &last,
                     CURLFORM_COPYNAME, "param",
                     CURLFORM_COPYCONTENTS, tmp,
                     CURLFORM_END);

    cJSON_Delete(json);
    json = NULL;
    free(tmp);
    tmp = NULL;
#endif

    HttpClient_Init(client);
	printf("\n commit url:<%s>\n",url_buffer);
	char para[64];
	memset(para,0,sizeof(para));
	sprintf(para,"upload_id=%s",id);
	curl_easy_setopt(client->curl, CURLOPT_POSTFIELDS, para);

    HttpClient_PostHttpData(client, url_buffer, post);	
	response = HttpClient_ResponseText(client);
	printf("commit response:<%s>\n",response);

#if 0
    MAKE_JSON();

     result = PCSFile_New();
    _BaiduPCS_Json2File(api, result, json);
#endif

    if (api->error[0] != '\0')
	{
        PCSFile_Free(result);        
        result = NULL;
    }

free:
    if (post != NULL)
	{
        curl_formfree(post);
    }

    if (fp != NULL)
	{
        fclose(fp);
    }

    if (json != NULL)
	{
        cJSON_Delete(json);
    }
    return result;
}

static PCSFile *_BaiduPCS_UploadSmallFile(BaiduPCS *api,PCSFile *local_file,const char *remote_file)	
{
    PCSFile *result     = NULL;
    HttpClient *client  = api->client;
    char *url_buffer    = api->util_buffer0;
    const char *token   = api->access_token;
    int timeout         = 0;

    const char *error   = NULL;
    const char *response      = NULL;
    char *remote_path_encode  = NULL;

    struct curl_httppost *post = NULL;
    struct curl_httppost *last = NULL;

    cJSON *json         = NULL;
    cJSON *item         = NULL;

    remote_path_encode = curl_easy_escape(client->curl, remote_file, 0);

	char level[16];
	memset(level,0,sizeof(level));
	if(api->level[0] == 's')
	{
		strcpy(level,"sandbox");
	}
	else if(api->level[0] == 'd')
	{
		strcpy(level,"dropbox");
	}

 	sprintf(url_buffer,"https://api-content.dropbox.com/1/files_put/%s/%s?"
		"oauth_consumer_key=%s"
		"&oauth_token=%s"
		"&oauth_signature_method=PLAINTEXT"
		"&oauth_signature=%s%%26%s",level,remote_path_encode,api->key,api->access_token,api->secret,api->access_token_secret);
	printf("##smallfile:<%s>##\n",url_buffer);

    curl_free(remote_path_encode);
    remote_path_encode = NULL;
    printf("uploading small file...\n"); 
	printf("path:<%s>...\n",local_file->path); 
    HttpClient_Init(client);

#if 1
	FILE *fp = fopen(local_file->path,"rb");
	if(fp == NULL)
	{
		printf("\nopen file err!\n");
		return NULL;
	}
	fseek(fp,0,SEEK_END);
	int len = ftell(fp);
	rewind(fp);
    curl_easy_setopt(client->curl, CURLOPT_READFUNCTION, _BaiduPCS_UploadReadCallback);/* 读数据到 post */
	curl_easy_setopt(client->curl, CURLOPT_READDATA,fp);
	curl_easy_setopt(client->curl, CURLOPT_UPLOAD, 1);
	curl_easy_setopt(client->curl, CURLOPT_POSTFIELDSIZE_LARGE, len);
    timeout = MAX(20, local_file->size / (10 * 1024));
    curl_easy_setopt(client->curl, CURLOPT_TIMEOUT, timeout);

	
	HttpClient_PostHttpData(client, url_buffer, post);
	response = HttpClient_ResponseText(client);
	printf("response small file:<%s>\n",response);
    curl_formfree(post);
    post = NULL;
    last = NULL;
    printf("!!!!!!<%s><%d>!!!!!!\n",__FUNCTION__,__LINE__);

#else
    curl_formadd(&post, &last,
                 CURLFORM_COPYNAME, "file",                 
                 CURLFORM_FILE, local_file->path,
                 CURLFORM_END);
	
    curl_easy_setopt(client->curl, CURLOPT_READFUNCTION, _BaiduPCS_UploadReadCallback);/* 读数据到 post */
    /* 设置一个较为合理的超时时间 */
    timeout = MAX(20, local_file->size / (10 * 1024));
    curl_easy_setopt(client->curl, CURLOPT_TIMEOUT, timeout);

    HttpClient_PostHttpData(client, url_buffer, post);

	response = HttpClient_ResponseText(client);
	printf("response small file:<%s>\n",response);
    curl_formfree(post);
    post = NULL;
    last = NULL;
#endif
#if 0	
    MAKE_JSON();
    result = PCSFile_New();
    _BaiduPCS_Json2File(api, result, json);

    if (api->error[0] != '\0')
	{
	    printf("upload small file error! now free it!\n");	
        PCSFile_Free(result);        
        result = NULL;
    }
#endif
free:
    if (post != NULL)
	{
        curl_formfree(post);
    }
    if (json != NULL)
	{
        cJSON_Delete(json);
    }	
    if (api->error[0] != '\0')
	{
	    printf("upload small file error! now free it!\n");	
        PCSFile_Free(result);        
        result = NULL;
    }
    return result;
}


/* 上传单个文件 */
int PCS_Upload(BaiduPCS *api,PCSFile *local_file,const char *remote_file)
{

	api->error[0] = '\0';
	api->error_code = 0;

    if (local_file == NULL)
	{
        BaiduPCS_ThrowError(api, "Please specify a local file");
        return NULL;
    }
	if(local_file->size > (10*1024*1024))
	{
        return _BaiduPCS_UploadBigFile(api, local_file, remote_file);
    }
	else
	{
       return _BaiduPCS_UploadSmallFile(api, local_file, remote_file);
    }
}


static size_t _BaiduPCS_Download_WriteData(void *ptr, size_t size, size_t nmemb, void *data)
{
    FILE *fp = (FILE *)data;
    int ret = fwrite(ptr, size, nmemb, fp);
    return ret;
}

/* 下载单个文件 */
void BaiduPCS_Download(BaiduPCS *api, const char *remote_file, FILE *local_fp)
{
    if (remote_file == NULL || local_fp == NULL) return;

    HttpClient *client          = api->client;
    char *url_buffer            = api->util_buffer0;
    const char *token           = api->access_token;
    const char *error           = NULL;
    char *remote_path_encode    = NULL;
	api->error[0] = '\0';
	api->error_code = 0;

    remote_path_encode = curl_easy_escape(client->curl, remote_file, 0);

	sprintf(url_buffer, "https://api-content.dropbox.com/1/files/sandbox/%s?"
		"oauth_consumer_key=%s"
		"&oauth_token=%s"
		"&oauth_signature_method=PLAINTEXT"
		"&oauth_signature=%s%%26%s",remote_path_encode,api->key,api->access_token,api->secret,api->access_token_secret);

	printf("download file <%s>, url:<%s>\n",remote_file,url_buffer);
    curl_free(remote_path_encode);
    remote_path_encode = NULL;
    
    HttpClient_Init(client);
    HttpClient_SetFailRetry(client, 0, 0);
    curl_easy_setopt(client->curl, CURLOPT_WRITEFUNCTION, _BaiduPCS_Download_WriteData);
    curl_easy_setopt(client->curl, CURLOPT_WRITEDATA, local_fp);
    /* 跟随重定向 */
    curl_easy_setopt(client->curl, CURLOPT_FOLLOWLOCATION, 1);
    /* 下载木有超时 */
    curl_easy_setopt(client->curl, CURLOPT_TIMEOUT, 0);
    HttpClient_Get(client, url_buffer);

    error = HttpClient_GetError(client);
    if (error != NULL)
	{
        BaiduPCS_ThrowError(api, "http request failed: %s", error);
    }
}


PCSFile *BaiduPCS_NewRemoteFile(BaiduPCS *api, const char *path)
{
    PCSFile *file           = NULL;
    HttpClient *client      = api->client;
    char *url_buffer        = api->util_buffer0;
    const char *token       = api->access_token;
    const char *error       = NULL;
    const char *response    = NULL;
    char *path_encode       = NULL;
    cJSON *json             = NULL;
    cJSON *array            = NULL;
    cJSON *item             = NULL;
	
	api->error[0] = '\0';
	api->error_code = 0;
	
    file = PCSFile_New();
    path_encode = curl_easy_escape(client->curl, path, 0);
	char level[16];
	memset(level,0,sizeof(level));
	if(api->level[0] == 's')
	{
		strcpy(level,"sandbox");
	}
	else if(api->level[0] == 'd')
	{
		strcpy(level,"dropbox");
	}
	sprintf(url_buffer,"https://api.dropbox.com/1/metadata/%s/%s?"
		"oauth_consumer_key=%s"
		"&oauth_token=%s"
		"&oauth_signature_method=PLAINTEXT"
		"&oauth_signature=%s%%26%s",level,path_encode,api->key,api->access_token,api->secret,api->access_token_secret);

	printf("##<%s>##\n",url_buffer);

    curl_free(path_encode);
    path_encode = NULL;

    HttpClient_Init(client);
    HttpClient_Get(client, url_buffer);
	error = HttpClient_GetError(client);
	if (error != NULL)
	{
		BaiduPCS_ThrowError(api, "request failed: %s", error);
		goto free;
	}
	response = HttpClient_ResponseText(client);	
	printf("response newremote:<%s>\n",response);
	json = cJSON_Parse(response);
	if (json == NULL)
	{
		BaiduPCS_ThrowError(api, "JSON parse error");
		goto free;
	}
	
	item = cJSON_GetObjectItem(json, "error");
	if (item != NULL && item->type == cJSON_String)
	{
		BaiduPCS_ThrowError(api, "%s", item->valuestring);
		goto free;
	}

    item = cJSON_GetObjectItem(json, "is_dir");
	printf("!!!!<%lld>,type:<%d>\n",item->valueint,item->type);
    if (item != NULL && item->type == cJSON_True)
	{	
        file->is_dir = (char)item->valueint;
    }
	else if (item != NULL && item->type == cJSON_False)
	{
		file->is_dir = (char)item->valueint;
	}
	
    item = cJSON_GetObjectItem(json, "path");
    if (item == NULL || item->type != cJSON_String)
	{
        BaiduPCS_ThrowError(api, "json.list.path is not string");
        goto free;
    }
    PCSFile_SetPath(file, item->valuestring);
	
free:

    if (json != NULL)
	{
        cJSON_Delete(json);
    }
    
    if (api->error[0] != '\0')
	{
		printf("has error ! <%s>\n",api->error);

		if (file != NULL)
		{
            PCSFile_Free(file);
        }
        return NULL;
    }

	if (file == NULL)
	{
		printf("file is null! \n");
	}
    return file;
} 


PCSFileList *BaiduPCS_ListRemoteDir(BaiduPCS *api, const char *path)
{
    PCSFileList *list       = NULL;
    PCSFile *file           = NULL;
    HttpClient *client      = api->client;
    char *url_buffer        = api->util_buffer0;
    const char *token       = api->access_token;
    const char *error       = NULL;
    const char *response    = NULL;
    char *path_encode       = NULL;
    cJSON *json             = NULL;
    cJSON *array            = NULL;
    cJSON *item             = NULL;
    int i                   = 0;
    int length              = 0;

	api->error[0] = '\0';
	api->error_code = 0;

    list = PCSFileList_New();
    path_encode = curl_easy_escape(client->curl, path, 0);

	char level[16];
	memset(level,0,sizeof(level));
	if(api->level[0] == 's')
	{
		strcpy(level,"sandbox");
	}
	else if(api->level[0] == 'd')
	{
		strcpy(level,"dropbox");
	}

	sprintf(url_buffer, "https://api.dropbox.com/1/metadata/%s/%s?"
		"oauth_consumer_key=%s"
		"&oauth_token=%s"
		"&oauth_signature_method=PLAINTEXT"
		"&oauth_signature=%s%%26%s",level,path_encode,api->key,api->access_token,api->secret,api->access_token_secret);

	printf("list:<%s>\n",url_buffer);
    curl_free(path_encode);

    HttpClient_Init(client);
    HttpClient_Get(client, url_buffer);
    MAKE_JSON();

	item = cJSON_GetObjectItem(json, "contents");
    if (item == NULL || item->type != cJSON_Array)
	{
        BaiduPCS_ThrowError(api, "can't find json.list");
        goto free;
    }

    array = item;
    length = cJSON_GetArraySize(array);
    
    for (i = 0; i < length; i ++)
	{
        item = cJSON_GetArrayItem(array, i);
        if (item == NULL || item->type != cJSON_Object)
		{
            BaiduPCS_ThrowError(api, "json.list.item is not object");
            goto free;
        }

        file = PCSFile_New();
        PCSFileList_Prepend(list, file);
        _BaiduPCS_Json2File(api, file, item);
        if (BaiduPCS_GetError(api) != NULL)
		{
			
		}
    }
       
free:
    if (json != NULL)
	{
        cJSON_Delete(json);
    }
    return list;
} 

