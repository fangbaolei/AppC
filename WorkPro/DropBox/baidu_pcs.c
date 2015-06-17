/*
 * Copyright (c) 2013 emptyhua@gmail.com
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <time.h>
#include <dirent.h>
#include <libgen.h>
#include <stdarg.h>
#include "smtp.h"
#include "pcs.h"

static const char *option_api_key	  = NULL;
static const char *option_api_secret  = NULL;
static BaiduPCS *api = NULL;

typedef struct st_Upload
{
	char *remote_path;			 /* 远程目录 */
	char *local_path;			 /* 本地目录 */
	int option_overwrite;		 /* 覆盖同名文件    				  */
	int option_new;				 /* 创建新文件       			  */
	int option_follow_link; 	 /* 复制链接源文件  				  */
}st_up;

typedef struct st_DownLoad
{
	char *remote_path;			 /* 远程目录 */
	char *local_path;			 /* 本地目录 */
	int option_overwrite;		 /* 覆盖同名文件    				  */
	int option_new;				 /* 创建新文件       			  */
}st_down;

/* 释放API */
void BaiduPCS_Free()
{
    if (api == NULL) 
	{
		return;
	}
	printf("now free api ! ,<func:%s>,<line:%d>\n",__FUNCTION__,__LINE__);
	HttpClient_Free(api->client);	
	free(api);
	api = NULL;
}

int Get_Access_Token(char *oauth_token_secret,char *oauth_token,char *sandbox)
{
	if(oauth_token_secret == NULL || oauth_token == NULL)
	{
		printf("error:device code empty!\n");
		return -1;
	}
    if (api != NULL)
    {
    	printf("api not empty! ,<func:%s>,<line:%d>\n",__FUNCTION__,__LINE__);
		return -1;
    }
	api	= calloc(sizeof(BaiduPCS), 1);
	api->client = calloc(sizeof(HttpClient), 1);
    sprintf(api->key, "%s", option_api_key);
    sprintf(api->secret, "%s", option_api_secret);
	
    cJSON *json             = NULL;
    cJSON *item             = NULL;
	FILE *fp;	
    struct passwd *pw;
    const char *homedir;	
    char config[1024];
    pw = getpwuid(getuid());
    homedir = pw->pw_dir;
    snprintf(config, 1023, "%s/.dropbox_uploader",  homedir);

    HttpClient *client  	= api->client;
    char *url_buffer    	= api->util_buffer0;
    const char *error   	= NULL;
    const char *response    = NULL;

	sprintf(url_buffer, "https://api.dropbox.com/1/oauth/access_token?oauth_consumer_key=%s"
		"&oauth_token=%s&oauth_signature_method=PLAINTEXT&oauth_signature=%s%%26%s"
		,api->key,oauth_token,api->secret,oauth_token_secret);

	printf("Waiting for validation....\n");
	HttpClient_Init(client);
	HttpClient_Get(client, url_buffer);
	error = HttpClient_GetError(client);
	if (error != NULL)
	{
		BaiduPCS_ThrowError(api, "http request failed: %s", error);		
		BaiduPCS_Free();
		return -1;
	}
	response = HttpClient_ResponseText(client);
#if 1
	//debug
	printf("http response:%s\n",response);
#endif
	if(strncmp(response,"oauth_token_secret",18) == 0)
	{
		char *p1 = strstr(response,"oauth_token_secret=");
		strncpy(oauth_token_secret,p1 + 19,15);
		p1 = strstr(response,"oauth_token=");
		strncpy(oauth_token,p1 + 12,16);	
		
		char write[128];
		memset(write,0,sizeof(write));
		fp = fopen(config, "wb");
		if (fp != NULL)
		{
			sprintf(write,"APPKEY=%s\n",api->key);		
			fwrite(write, 1, strlen(write), fp);		
			sprintf(write,"APPSECRET=%s\n",api->secret);		
			fwrite(write, 1, strlen(write), fp);		
			sprintf(write,"ACCESS_LEVEL=%s\n",sandbox); 	
			fwrite(write, 1, strlen(write), fp);		
			sprintf(write,"OAUTH_ACCESS_TOKEN=%s\n",oauth_token);		
			fwrite(write, 1, strlen(write), fp);		
			sprintf(write,"OAUTH_ACCESS_TOKEN_SECRET=%s",oauth_token_secret); 	
			fwrite(write, 1, strlen(write), fp);		
			fclose(fp);
			fp = NULL;
			/* 确保只有自己读写 */
			chmod(config, 0600);				
			BaiduPCS_Free();
			return 1;
		}
		else
		{
			printf("ERROR: %s Unable to write , <func:%s>,<line:%d>\n", config,__FUNCTION__, __LINE__); 				
			BaiduPCS_Free();
			return -1;
		}	
	}	
	BaiduPCS_Free();
	return -1;
}


/* 初始化API */
int init_api()
{
    int ret = 1;
    struct passwd *pw;
    const char *homedir;
    char config[1024];
    char buf[1024];
    FILE *fp;
    char *p1 = NULL;
    if (api != NULL)
    {
    	printf("api not empty! ,<func:%s>,<line:%d>\n",__FUNCTION__,__LINE__);
		return 1;
    }
   api = calloc(sizeof(BaiduPCS), 1);
   api->client = calloc(sizeof(HttpClient), 1);
    sprintf(api->key, "%s", option_api_key);
    sprintf(api->secret, "%s", option_api_secret);

    /* 读取已存的token */
    pw = getpwuid(getuid());
    homedir = pw->pw_dir;
    snprintf(config, 1023, "%s/.dropbox_uploader",  homedir);

    fp = fopen(config, "rb");
    if (fp != NULL)
	{
		fseek(fp,0,SEEK_SET);
		fgets(buf, 128, fp );
		p1 = strstr(buf,"APPKEY=");			
		strncpy(api->key,p1 + 7,15);
		
		fgets(buf, 128, fp );
		p1 = strstr(buf,"APPSECRET=");
		strncpy(api->access_token,p1 + 10,15);

		fgets(buf, 128, fp );
		p1 = strstr(buf,"ACCESS_LEVEL=");
		strncpy(api->level,p1 + 13,1);

		fgets(buf, 128, fp );
		p1 = strstr(buf,"OAUTH_ACCESS_TOKEN=");
		strncpy(api->access_token,p1 + 19,16);

		fgets(buf, 128, fp );
		p1 = strstr(buf,"OAUTH_ACCESS_TOKEN_SECRET=");
		strncpy(api->access_token_secret,p1 + 26,15);

        fclose(fp);
        fp = NULL;
        /* 确保只有自己读写 */
        chmod(config, 0600);
    }
	else
	{
		fprintf(stderr, "not existing token %s\n", config);
		printf("ERROR: init api device code is empty , <func:%s>,<line:%d>\n",__FUNCTION__, __LINE__);  
		ret = 0;
	}
    return ret;
}

/* 显示云盘信息 */
int Baidu_PCS_GetInfo(BaiduPCSInfo *pInfo)
{
	if(pInfo == NULL)
	{
        printf("ERROR: No BaiduPCSInfo ,<func:%s><line:%d>\n",__FUNCTION__,__LINE__);
        return -1;
	}
	printf("Getting information ...\n");
	if (!init_api())
	{
		BaiduPCS_Free();
		return -1;
	}
	const char *error = NULL;

	BaiduPCS_Info(api, pInfo);
	error = BaiduPCS_GetError(api);
	if (error != NULL)
	{
		printf("ERROR: Failed to get information: %s ,<func:%s>,<line:%d> \n", error,__FUNCTION__,__LINE__);
		BaiduPCS_Free();
		return -1;
	}
	
	BaiduPCS_Free();
	return 0;
}


int do_upload(const char *local_path,const char *remote_path,int overwrite,int create_new,int follow_link)
{ 
    int ret                 = 0;
	int back				= 0;
    int is_first            = 1;
    PCSFile *new_file       = NULL;
    PCSFile *t_file         = NULL;
    struct dirent *item     = NULL;
    const char *error       = NULL;

    char t_path[PATH_MAX + 1];         /* 临时路径       */
    char t_remote_path[PATH_MAX + 1];  /* 临时路径       */

    /* 需要释放 */
    PCSFile *c_file         = NULL;
    PCSFileList *stack      = NULL;
    PCSFile *remote_file    = NULL;
    PCSFileList *r_list     = NULL;
    DIR *dir                = NULL;
    
    /* 遍历栈 */
    stack   = PCSFileList_New();
    c_file  = BaiduPCS_NewLocalFile(api, local_path);

    /* 当前要上传的远程路径 */
    c_file->userdata = strdup(remote_path);
    
    while(c_file != NULL)
	{
        remote_path = (char *)c_file->userdata;
        /* 普通文件 */
        if (!c_file->is_dir && !c_file->is_link)
		{
            if (is_first)
			{
                remote_file = BaiduPCS_NewRemoteFile(api, remote_path); 				
                if (remote_file != NULL) 
				{
                    /*  upload xx.txt /apps/xx/ 
                     		*  对于这种情况,远端路径修正为/apps/xx/xx.txt
                     		*/
                    if (remote_file->is_dir)
					{
                        t_remote_path[0] = '\0';
                        strcat(t_remote_path, remote_path);
                        strcat(t_remote_path, "/");
                        strcat(t_remote_path, basename(c_file->path));
                        fprintf(stderr, "Upload path %s Revised to %s\n", remote_path, t_remote_path);
                        free(c_file->userdata);
                        c_file->userdata = strdup(t_remote_path);
                        remote_path = c_file->userdata;
                        PCSFile_Free(remote_file);
                        remote_file = NULL;
                    /* upload xx.txt /apps/xx/xx.txt */
                    }
					else if (!overwrite && !create_new) 
					{
                        printf("IGNORE: %s -> %s remote files existing\n", c_file->path, remote_file->path);
                        goto free; 
                    }
					else
					{
						printf("ERROR:The remote path is not a directory,  <func:%s><line:%d> \n",__FUNCTION__,__LINE__);
						ret = 1;
						goto free;
					}
                    PCSFile_Free(remote_file);
                    remote_file = NULL;
                }
            }
           // remote_file = PCS_Upload(api, c_file, remote_path);
           back = PCS_Upload(api, c_file, remote_path);
            error = BaiduPCS_GetError(api);
            /* 上传失败 */
           // if (error != NULL || remote_file == NULL)
            if (error != NULL)
			{
                printf("ERROR: <func:%s><line:%d> <%s> -> <%s> %s\n",__FUNCTION__, __LINE__, c_file->path, remote_path, error);
                /* 如果上传单个文件，失败后会返回error code */
                if (is_first) 
				{
                    ret = 1;
                    goto free;
                }
            /* 上传成功 */
            } 
			else
			{
             //   printf("OK: %s -> %s\n", c_file->path, remote_file->path);
                printf("OK: %s\n", c_file->path);
                PCSFile_Free(remote_file);
                remote_file = NULL;
            }

            free(c_file->userdata);
            PCSFile_Free(c_file);

            c_file = PCSFileList_Shift(stack);
            is_first = 0;
        }
		else if (c_file->is_dir)  //如果是目录
		{
            /* 遍历目录 */
            dir = opendir(c_file->path);  
            /* 读取目录失败 */
            if (dir == NULL)
			{
                printf("ERROR: <func:%s><line:%d> %s -> %s Directory reading failure\n",__FUNCTION__,__LINE__, c_file->path, remote_path);
                /* 如果当前为用户指定的根目录，直接返回错误 */
                if (is_first) 
				{
                    ret = 1;
                    goto free;
                }
            } 
			else 
			{
                /* 进行目录修正 */
                if (is_first)
				{
                    remote_file = BaiduPCS_NewRemoteFile(api, remote_path); 
                    if (remote_file != NULL) 
					{
                        /*  upload ./dir/ /apps/xx/ 
                       		  *  对于这种情况,远端路径修正为/apps/xx/dir
                        		 */
                        if (remote_file->is_dir)
						{
                            t_remote_path[0] = '\0';
                            strcat(t_remote_path, remote_file->path);
                            strcat(t_remote_path, "/");
                            strcat(t_remote_path, basename(c_file->path));
                            printf("Upload directory %s Revised to %s\n", remote_path, t_remote_path);
                            free(c_file->userdata);
                            c_file->userdata = strdup(t_remote_path);
                            remote_path = c_file->userdata;

                        } 
						else if (!remote_file->is_dir) 
						{
                            printf("ERROR: <func:%s><line:%d> %s -> %s The remote path is not a directory\n",__FUNCTION__,__LINE__, c_file->path, remote_file->path);
                            ret = 1;
                            goto free;
                        }
                        PCSFile_Free(remote_file);
                        remote_file = NULL;
                    }
                }

                /* 获取远程目录列表,用于排除远端已存在的文件 */
                remote_file = BaiduPCS_NewRemoteFile(api, remote_path);
                if (remote_file != NULL)
				{
                    /* 远端已存在同名文件 */
                    if (!remote_file->is_dir) 
					{
                        printf("ERROR: <func:%s><line:%d> %s -> %s remote files existing\n",__FUNCTION__,__LINE__, c_file->path, remote_file->path);
                        if (is_first) 
						{
                            ret = 1;
                            goto free;
                        }
                    }
					else 
                    {
                        /* 获取远端目录文件列表,用于对比本地目录列表 */
                        r_list = BaiduPCS_ListRemoteDir(api, remote_path);
                    }
                    PCSFile_Free(remote_file);
                    remote_file = NULL;
                }
                
                while ((item = readdir(dir)) != NULL) 
				{
                    if (strcmp(item->d_name, ".") == 0|| strcmp(item->d_name, "..") == 0)
					{
                        continue;
                    }

                    /* 构建本地文件完整路径 */
                    t_path[0] = '\0';
                    strcat(t_path, c_file->path);
                    strcat(t_path, "/");
                    strcat(t_path, item->d_name);

                    /* 构建上传路径 */
                    t_remote_path[0] = '\0';
                    strcat(t_remote_path, remote_path);
                    strcat(t_remote_path, "/");
                    strcat(t_remote_path, item->d_name);

                    new_file = BaiduPCS_NewLocalFile(api, t_path);
                    error = BaiduPCS_GetError(api);
                    if (error != NULL || new_file == NULL)
					{
                        printf("ERROR: <func:%s><line:%d> %s -> %s %s\n",__FUNCTION__,__LINE__, t_path, t_remote_path, error);
                    } 
					else
					{
                        if (r_list != NULL)
						{
                            t_file = PCSFileList_Find(r_list, t_remote_path);
                            /* 远程已存在同名文件 */
                            if (t_file != NULL)
							{
                                if (new_file->is_dir && !t_file->is_dir)
								{
                                    printf("ERROR: <func:%s><line:%d> %s -> %s Remote existence for directory\n",__FUNCTION__,__LINE__, t_path, t_remote_path);
                                    PCSFile_Free(new_file);
                                    new_file = NULL;
                                    continue;
                                }
								else if (!new_file->is_dir && t_file->is_dir)
								{
                                    printf("ERROR: <func:%s><line:%d> %s -> %s Remote existence for file\n",__FUNCTION__,__LINE__, t_path, t_remote_path);
                                    PCSFile_Free(new_file);
                                    new_file = NULL;
                                    continue;
                                } 
								else if (!new_file->is_dir && !new_file->is_link && !overwrite && !create_new) 
								{
                                    printf("IGNORE: %s -> %s Remote existence for file\n", t_path, t_remote_path);
                                    PCSFile_Free(new_file);
                                    new_file = NULL;
                                    continue;
                                }
                            }
                        }
                       
                        new_file->userdata = strdup(t_remote_path);
                        //放入栈中
                        PCSFileList_Prepend(stack, new_file);
                        new_file = NULL;
                    }
                }
                if (r_list != NULL)
				{
                    PCSFileList_Free(r_list);
                    r_list = NULL;
                }
                closedir(dir);
                dir = NULL;
            }

            free(c_file->userdata);
            PCSFile_Free(c_file);
            c_file = PCSFileList_Shift(stack);
            is_first = 0;
        /* 软链接 */
        } 
		else if (c_file->is_link) 
        { 
            if (follow_link)
			{
                realpath(c_file->path, t_path);
                fprintf(stderr, "Follow the soft chain %s -> %s\n", c_file->path, t_path);
                new_file = BaiduPCS_NewLocalFile(api, t_path);
                new_file->userdata = c_file->userdata;
                PCSFile_Free(c_file);
                c_file = new_file;
            }
			else
			{
                printf("IGNORE: Ignore the soft links %s\n", c_file->path);
                free(c_file->userdata);
                PCSFile_Free(c_file);
                c_file = PCSFileList_Shift(stack);
                is_first = 0;
            }
        /* 忽略其他类型 */
        }
		else
		{
            printf("ERROR: <func:%s><line:%d> Does not support the file type %s\n",__FUNCTION__,__LINE__, c_file->path);
            free(c_file->userdata);
            PCSFile_Free(c_file);
            c_file = PCSFileList_Shift(stack);
            is_first = 0;
        }
    }
free:
    PCSFileList_Free(stack);

    if (dir != NULL) 
	{
        closedir(dir);
    }

    if (c_file != NULL)
	{
        free(c_file->userdata);
        PCSFile_Free(c_file);
    }

    if (remote_file != NULL)
	{
        PCSFile_Free(remote_file);
		remote_file = NULL;
    }

    if (r_list != NULL)
	{
        PCSFileList_Free(r_list);
    }
    return ret;
}


/* 上传文件或目录 */
int Baidu_PCS_Upload(st_up *pUp)
{
	printf("Uploading ...\n");
	int ret = 0; 

	char local_path[strlen(pUp->local_path)];
	char remote_path[strlen(pUp->remote_path)];
	if (pUp == NULL || pUp->local_path == NULL || pUp->remote_path == NULL)
	{
	        printf("ERROR: <func:%s><line:%d> Please specify the path\n",__FUNCTION__,__LINE__);
	        return -1;
    	}	
    	if (pUp->option_overwrite && pUp->option_new)
	{
	        printf("ERROR: <func:%s><line:%d> Please do not specify at the same time...\n",__FUNCTION__,__LINE__);
	        return -1;
    	}
	memset(local_path,0,sizeof(local_path));
	memset(remote_path,0,sizeof(remote_path));
	strcpy(local_path,pUp->local_path);
	strcpy(remote_path,pUp->remote_path);
	

    	if (local_path[strlen(local_path) - 1] == '/')
	{
       	 local_path[strlen(local_path) - 1] = '\0';
    	}

    	if (remote_path[strlen(remote_path) - 1] == '/')
	{
     	   	remote_path[strlen(remote_path) - 1] = '\0';
   	 }

    if (!init_api())
	{
		printf("upload :init api err!\n");
		BaiduPCS_Free();
        return -1;
    }

    printf("Upload %s to %s\n", local_path, remote_path);   
    if (stat(local_path, &(api->file_st)) == -1)
	{
        printf("ERROR: %s not exit ,<func:%s><line:%d>\n",local_path,__FUNCTION__,__LINE__);
		BaiduPCS_Free();
        return -1;
    }

    ret = do_upload(local_path, remote_path, pUp->option_overwrite, pUp->option_new, pUp->option_follow_link);
	if(ret)
	{
        printf("ERROR: upload err ,<func:%s><line:%d>\n",__FUNCTION__,__LINE__);
		BaiduPCS_Free();
        return -1;
	}

	BaiduPCS_Free();
	return 0;
} 

int _do_download(const char *remote_path,const char *local_path,int overwrite,int create_new)
{
    int ret             = 0; 
    int local_exist     = 0;
    int stdout_output   = 0;
    const char *error   = NULL;
    FILE *fp            = NULL;
    char *buf           = api->util_buffer0;

    time_t rawtime;
    struct tm * timeinfo;
    char t_local_file[PATH_MAX + 1];

	printf("##<%s>##\n",local_path);
    sprintf(t_local_file, "%s", local_path);
	
    if (strcmp(local_path, "-") == 0)
	{
        fp = stdout;
        stdout_output = 1;
    } 
	else
	{
        if (stat(local_path, &(api->file_st)) != -1)
		{
            local_exist = 1;
            if (S_ISDIR(api->file_st.st_mode))
			{
                printf("ERROR: <func:%s><line:%d> %s -> %s Local existing dir\n",__FUNCTION__,__LINE__, remote_path, local_path);
                if (!create_new || overwrite)
				{
                    ret = 1;
                    goto free;
                }
            } 
			else if (!overwrite && !create_new)
			{
                printf("IGNORE: %s -> %s Local existing files\n", remote_path, local_path);
                goto free;
            }
        }

        if (local_exist && create_new)
		{
            time(&rawtime);
            timeinfo = localtime(&rawtime);
            strftime(buf, 80, ".%Y%m%d%H%M%S", timeinfo);
            strcat(t_local_file, buf);
        }

        fp = fopen(t_local_file, "wb");
        if (fp == NULL)
		{
            printf("ERROR: <func:%s><line:%d> %s -> %s local file write err\n",__FUNCTION__,__LINE__, remote_path, t_local_file);
            ret = 1;
            goto free;
        }
    }

    BaiduPCS_Download(api, remote_path, fp);
    error = BaiduPCS_GetError(api);
    if (error != NULL)
	{
        printf("ERROR: <func:%s><line:%d> %s -> %s download failed:%s\n",__FUNCTION__,__LINE__, remote_path, t_local_file, error);
        ret = 1;
    }
	else 
	{
        printf("OK: %s -> %s\n", remote_path, t_local_file);
    }

free:
    if (!stdout_output && fp != NULL) 
	{
        fclose(fp);
    }
    return ret;
}

int do_download(const char *remote_path,const char *local_path,int overwrite,int create_new)
{ 
    int ret                 = 0;
    int stdout_output       = 0;
    PCSFile *file           = NULL;  /* 需要释放 */
    PCSFile *t_file         = NULL; 
    const char *error       = NULL;

    int remote_root_offset  = 0;
    char *tmp;
    char t_local_root[PATH_MAX + 1];
    char t_local_file[PATH_MAX + 1];

    PCSFileList *stack      = NULL; /* 需要释放 */
    PCSFileList *list       = NULL; /* 需要释放 */

    /* 获取远程路径信息 */
    file = BaiduPCS_NewRemoteFile(api, remote_path);
    error = BaiduPCS_GetError(api);
    if (error != NULL || file == NULL) 
	{
        printf("ERROR: <func:%s><line:%d> %s Failed to get file information:%s\n",__FUNCTION__,__LINE__, remote_path, error);
        ret = 1;
        goto free;
    }
    sprintf(t_local_file, "%s", local_path);
	
        /* 远端为目录 */
    if (file->is_dir)
	{	
		printf("##<%s><%d>##\n",__FUNCTION__,__LINE__);
        sprintf(t_local_root, "%s", local_path);
        remote_root_offset = strlen(file->path);		
        if (stat(local_path, &(api->file_st)) != -1)
		{
            if (S_ISDIR(api->file_st.st_mode))
			{				
                sprintf(t_local_root, "%s/%s", local_path, basename(file->path));					
                fprintf(stderr, "Revised to local root directory:%s\n", t_local_root);
            }
			else
			{
                printf("ERROR: <func:%s><line:%d> %s -> %s existing directory\n",__FUNCTION__,__LINE__, file->path, local_path);
                ret = 1;
                goto free;
            }
			printf("##<%s><%d>##\n",__FUNCTION__,__LINE__);
        }		
		
        stack = PCSFileList_New();
        while(file != NULL)
		{
            tmp = file->path + remote_root_offset;
            sprintf(t_local_file, "%s%s", t_local_root, tmp);

            /* 如果是普通文件 */
            if (!file->is_dir)
			{
				printf("##normal  local file <%s> remote:<%s>##\n",t_local_file,file->path);
                _do_download(file->path, t_local_file, overwrite, create_new);
                PCSFile_Free(file);
                file = PCSFileList_Shift(stack);
            /* 如果是目录 */
            } 
			else
			{
				printf("## dir local file <%s>##\n",t_local_file);
                /* 创建本地目录 */
                if (stat(t_local_file, &(api->file_st)) != -1)
				{
					if (!S_ISDIR(api->file_st.st_mode))
					{				
                        printf("ERROR: <func:%s><line:%d> %s -> %s  local existing directory \n",__FUNCTION__,__LINE__, file->path, t_local_file);
                        ret = 1;
                        goto free;
                    }
                }
				else
				{
					printf("now mkdir %s\n",t_local_file);
                    if (0 != mkdir(t_local_file, 0755))
					{
                        printf("ERROR: <func:%s><line:%d> %s -> %s Local directory creation fails\n",__FUNCTION__,__LINE__, file->path, t_local_file);
                        ret = 1;
                        goto free;
                    }
                }
                list = BaiduPCS_ListRemoteDir(api, file->path);
                error = BaiduPCS_GetError(api);
                if (error != NULL || list == NULL)
				{
                    printf("ERROR: <func:%s><line:%d> %s Failed to get directory listing:%s\n",__FUNCTION__,__LINE__, file->path, error);
                }
                /* 列出目录 */
                if (list != NULL)
				{
                    t_file  = PCSFileList_Shift(list);
                    while(t_file != NULL)
					{
                        PCSFileList_Prepend(stack, t_file);
                        t_file = PCSFileList_Shift(list);
                    }
                    PCSFileList_Free(list);
                    list = NULL;
                }
                PCSFile_Free(file);
                file = PCSFileList_Shift(stack);
            }
        }
    } 
	else
	{
		printf("##<%s><%d>##\n",__FUNCTION__,__LINE__);
        if (stat(local_path, &(api->file_st)) != -1)
		{
            if (S_ISDIR(api->file_st.st_mode))
			{				
                sprintf(t_local_file, "%s/%s", local_path, basename(file->path));					
            }
        }		
        ret = _do_download(remote_path, t_local_file, overwrite, create_new);
    }

free:
    if (file != NULL)
	{
        PCSFile_Free(file);
    }
    if (stack != NULL)
	{
        PCSFileList_Free(stack);
    }
    if (list != NULL)
	{
        PCSFileList_Free(list);
    }
    return ret;
}


/* 下载文件或目录 */
int Baidu_PCS_DownLoad(st_down *pDown)
{	
    if (pDown == NULL || pDown->local_path == NULL || pDown->remote_path == NULL)
	{
        printf("ERROR: <func:%s><line:%d> Please specify the path\n",__FUNCTION__,__LINE__);
        return -1;
    }
	int ret = 0;
	char local_path[strlen(pDown->local_path)];
	char remote_path[strlen(pDown->remote_path)];
	memset(local_path,0,sizeof(local_path));
	memset(remote_path,0,sizeof(remote_path));
	strcpy(local_path,pDown->local_path);
	strcpy(remote_path,pDown->remote_path);
 
    if (pDown->option_overwrite && pDown->option_new)
	{
        printf("ERROR: <func:%s><line:%d> Please do not specify at the same time:-n -o\n",__FUNCTION__,__LINE__);
        return -1;
    }

    if (local_path[strlen(local_path) - 1] == '/')
	{
        local_path[strlen(local_path) - 1] = '\0';
    }

    if (remote_path[strlen(remote_path) - 1] == '/')
	{
        remote_path[strlen(remote_path) - 1] = '\0';
    }
	
    printf("Download %s to %s\n",remote_path, local_path);
    if (!init_api())
	{
		printf("err: download init api err!\n");
		BaiduPCS_Free();
        return -1;
    }
	
    ret = do_download(remote_path, local_path, pDown->option_overwrite, pDown->option_new);
	if(ret)
	{
		printf("err: download err!\n");
		BaiduPCS_Free();
		return -1;
	}

	BaiduPCS_Free();
	return 0;
} 

int Get_User_Code(char *oauth_token,char *url,char *oauth_token_secret)
{
	if(url == NULL || oauth_token_secret ==NULL)
	{
		return -1;
	}
    if (api != NULL)
    {
    	printf("api not empty! ,<func:%s>,<line:%d>\n",__FUNCTION__,__LINE__);
		return -1;
    }
	char temp[32];
	memset(temp,0,sizeof(temp));
	api	= calloc(sizeof(BaiduPCS), 1);
	api->client = calloc(sizeof(HttpClient), 1);
	api->error[0] = '\0';
	api->error_code = 0;
    sprintf(api->key, "%s", option_api_key);
    sprintf(api->secret, "%s", option_api_secret);

	HttpClient *client 		= api->client;
	char *url_buffer		= api->util_buffer0;
	const char *error		= NULL;
	const char *response	= NULL;

/* get 请求 发送 */
	sprintf(url_buffer, "https://api.dropbox.com/1/oauth/request_token?"
		"oauth_consumer_key=%s"
		"&oauth_signature_method=PLAINTEXT"
		"&oauth_signature=%s%%26",api->key,api->secret);
	printf("<%s>\n",url_buffer);

	HttpClient_Init(client);
	HttpClient_Get(client, url_buffer);
	error = HttpClient_GetError(client);
	if (error != NULL)
	 {
		 BaiduPCS_ThrowError(api, "http request failed: %s", error);
		 goto free;
	 }
 
	response = HttpClient_ResponseText(client);
	printf("###<%s>###\n",response);
	if(response != NULL)
	{
		char *p1 = strstr(response,"oauth_token_secret=");
		strncpy(oauth_token_secret,p1 + 19,16);
		p1 = strstr(response,"oauth_token=");
		strncpy(oauth_token,p1 + 12,16);	
		sprintf(url,"https://www2.dropbox.com/1/oauth/authorize?oauth_token=%s",oauth_token);
	}
	 printf("oauth_token_secret:<%s>\n oauth_token:<%s> url:%s\n",oauth_token_secret,oauth_token,url);
	 BaiduPCS_Free();
  	 return 0;
 free:
	 BaiduPCS_Free();
	 return -1;
}


int main(int argc, char **argv)
{    
	option_api_key	  = "xs4dbfapgqiszay";  // 账号
	option_api_secret  = "8zsuyk02h2g7irg"; // 密码
	int ret = 0;

/* 第一次使用需要通过授权后才可进行上传，下载文件，授权成功则该步骤不需要 */
/* 1,向邮箱发送验证码和验证的 URL 地址 */
#if 0
	char message[512];
	char oauth_token[32];
	char url[128];	
	char oauth_token_secret[128];
	memset(message,0,sizeof(message));
	memset(oauth_token,0,sizeof(oauth_token));
	memset(url,0,sizeof(url));
	memset(oauth_token_secret,0,sizeof(oauth_token_secret));
	
	ret = Get_User_Code(oauth_token,url,oauth_token_secret);	
	if(ret == -1)
	{
		printf("get user code err!\n");
		return -1;
	}
	sprintf(message,"URL:%s",url);

	st_smtp s;
	memset(&s,0,sizeof(s));
	/*  填充 SMTP 结构体  */
	s.pHost      	= "smtp.exmail.qq.com";  /* 服务器域名 */
	s.pLoginName  	= "1398142976@qq.com";   /* 发送 账号 */
	s.pLoginPassword= "sb5201314";   		/* 登陆密码 */
	s.pSendFrom     = "1398142976@qq.com";  /*  发送 账号 */ 
	s.pSendTo      	= "254961379@qq.com";   /* 接收账号 */
	s.pDate    		= "2014-04-03 12:00:00 +800";   /*  发送时间，时区+800 表示北京时间 */
	s.pEmailSubject = "Baidu PCS!"; /*  邮件名  */
 	s.port 			= 25;	
	s.pMessage 		= message;
	
//	ret = Smtp_SendEmail(&s);
//	if(ret == -1)
	{
//		printf("Smtp_SendEmail error!\n");
//		return -1;
	}
#endif
	
/* 2，查询 本机获取API的token并且写入/root/.baidu_pcs_token 文件中
 *   如果没有成功建立 /root/.baidu_pcs_token 该文件，则不能上传，下载文件，
 *
*/	
#if 0
	while(1)
	{
		sleep(5);
		ret = Get_Access_Token(oauth_token_secret,oauth_token,"sandbox");
		if(ret == 1)
		{
			printf("Get Access Token succ, now you can upload or download file! \n");
			break;
		}
	}
#endif


/* 上面 1 ，2 步骤完成后就不需要再做，下次可直接进行上传，下载文件*/
/* 3,获取网盘容量， 上传，下载文件 */

/*	get info */
#if 0
	BaiduPCSInfo info;
	memset(&info,0,sizeof(info));
	ret = Baidu_PCS_GetInfo(&info);
	if(ret == -1)
	{
		printf("Get info err!\n");
	}
	printf("info  quota:%lld,used:%lld\n",info.quota,info.used);
#endif	

/*  Upload ..... */
#if 1
	st_up Upload;
	memset(&Upload,0,sizeof(Upload));
	Upload.local_path 			= "./123.avi";
	Upload.remote_path 			= "/up";
	Upload.option_follow_link 	= 0;
	Upload.option_new		 	= 0;
	Upload.option_overwrite 	= 0;
	ret = Baidu_PCS_Upload(&Upload);
	if(ret == -1)
	{
		printf("upload err!\n");
	}

#endif
#if 0
/* download..... */
	st_down Down;
	memset(&Down,0,sizeof(Down));
	Down.local_path 			= "./";
	Down.remote_path 			= "/app";
	Down.option_new		 		= 0;
	Down.option_overwrite 		= 0;
	ret = Baidu_PCS_DownLoad(&Down);
	if(ret == -1)
	{
		printf("download err!\n");
	}
#endif
    return 0;
}

