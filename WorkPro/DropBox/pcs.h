/*
 * Copyright (c) 2013 emptyhua@gmail.com
 */

#ifndef _BAIDU_PCS_H
#define _BAIDU_PCS_H

#include "http_client.h"
#include "cJSON.h"
#include <sys/types.h>
#include <sys/stat.h>


/* 文件对象 */
typedef struct PCSFile_s PCSFile;

struct PCSFile_s {
    char *path;             /*文件路径              */
    char is_link;           /*是否为链接            */
    char is_dir;            /*是否为目录            */
    size_t size;            /*文件大小              */
    unsigned int ctime;     /*创建时间              */
    unsigned int mtime;     /*修改时间              */

    PCSFile *next;          /*链表用                */
    void *userdata;         /*对象多用。。          */
};

typedef struct PCSFileList_s {
    PCSFile *first;
} PCSFileList;

/* 空间信息 */
typedef struct BaiduPCSInfo_s {
    long long quota;
    long long used;
} BaiduPCSInfo;

/* API 对象 */
typedef struct BaiduPCS_s {
    HttpClient *client;         /*Curl          */
    char access_token_secret[1024];           /*api_token secret    */	
    char access_token[1024];           /*api_token     */	
    char level[16];           /*ACCESS_LEVEL     */
    char key[1024];             /*api_key       */
    char secret[1024];          /*api_secret    */
    char error[4096];           /*错误信息      */
    int error_code;             /*错误码        */

    char util_buffer0[4096];
    char util_buffer1[4096];
    struct stat file_st;        /*文件信息缓冲  */
} BaiduPCS;


#define BaiduPCS_ThrowError(api, format, ...) snprintf(api->error, 4096, format, ##__VA_ARGS__)

const char *BaiduPCS_GetError(BaiduPCS *api);

/* 获取空间信息 */
void BaiduPCS_Info(BaiduPCS *api, BaiduPCSInfo *info); 
/* 上传单个文件 */
int PCS_Upload(BaiduPCS *api, PCSFile *local_file, const char *remote_file); 
/* 下载单个文件 */
void BaiduPCS_Download(BaiduPCS *api, const char *remote_file, FILE *local_fp); 

/* 列出远程目录的文件 */
PCSFileList *BaiduPCS_ListRemoteDir(BaiduPCS *api, const char *path); 
/* 从远程路径创建文件对象 */
PCSFile *BaiduPCS_NewRemoteFile(BaiduPCS *api, const char *path); 
/* 从本地路径创建文件对象 */
PCSFile *BaiduPCS_NewLocalFile(BaiduPCS *api, const char *path);


/* 文件对象 */
PCSFile *PCSFile_New();
/* 修改路径 */
void PCSFile_SetPath(PCSFile *file, const char *path);
void PCSFile_Free(PCSFile *file);

/* 文件列表 */
PCSFileList *PCSFileList_New();
void PCSFileList_Free(PCSFileList *file);

void PCSFileList_Prepend(PCSFileList *list, PCSFile *file);
PCSFile *PCSFileList_Find(PCSFileList *list, const char *path);
PCSFile *PCSFileList_Shift(PCSFileList *list);

#endif
