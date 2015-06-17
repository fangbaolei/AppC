/*
 * Copyright (c) 2013 emptyhua@gmail.com
 */

#ifndef _BAIDU_PCS_H
#define _BAIDU_PCS_H

#include "http_client.h"
#include "cJSON.h"
#include <sys/types.h>
#include <sys/stat.h>


/* �ļ����� */
typedef struct PCSFile_s PCSFile;

struct PCSFile_s {
    char *path;             /*�ļ�·��              */
    char is_link;           /*�Ƿ�Ϊ����            */
    char is_dir;            /*�Ƿ�ΪĿ¼            */
    size_t size;            /*�ļ���С              */
    unsigned int ctime;     /*����ʱ��              */
    unsigned int mtime;     /*�޸�ʱ��              */

    PCSFile *next;          /*������                */
    void *userdata;         /*������á���          */
};

typedef struct PCSFileList_s {
    PCSFile *first;
} PCSFileList;

/* �ռ���Ϣ */
typedef struct BaiduPCSInfo_s {
    long long quota;
    long long used;
} BaiduPCSInfo;

/* API ���� */
typedef struct BaiduPCS_s {
    HttpClient *client;         /*Curl          */
    char access_token_secret[1024];           /*api_token secret    */	
    char access_token[1024];           /*api_token     */	
    char level[16];           /*ACCESS_LEVEL     */
    char key[1024];             /*api_key       */
    char secret[1024];          /*api_secret    */
    char error[4096];           /*������Ϣ      */
    int error_code;             /*������        */

    char util_buffer0[4096];
    char util_buffer1[4096];
    struct stat file_st;        /*�ļ���Ϣ����  */
} BaiduPCS;


#define BaiduPCS_ThrowError(api, format, ...) snprintf(api->error, 4096, format, ##__VA_ARGS__)

const char *BaiduPCS_GetError(BaiduPCS *api);

/* ��ȡ�ռ���Ϣ */
void BaiduPCS_Info(BaiduPCS *api, BaiduPCSInfo *info); 
/* �ϴ������ļ� */
int PCS_Upload(BaiduPCS *api, PCSFile *local_file, const char *remote_file); 
/* ���ص����ļ� */
void BaiduPCS_Download(BaiduPCS *api, const char *remote_file, FILE *local_fp); 

/* �г�Զ��Ŀ¼���ļ� */
PCSFileList *BaiduPCS_ListRemoteDir(BaiduPCS *api, const char *path); 
/* ��Զ��·�������ļ����� */
PCSFile *BaiduPCS_NewRemoteFile(BaiduPCS *api, const char *path); 
/* �ӱ���·�������ļ����� */
PCSFile *BaiduPCS_NewLocalFile(BaiduPCS *api, const char *path);


/* �ļ����� */
PCSFile *PCSFile_New();
/* �޸�·�� */
void PCSFile_SetPath(PCSFile *file, const char *path);
void PCSFile_Free(PCSFile *file);

/* �ļ��б� */
PCSFileList *PCSFileList_New();
void PCSFileList_Free(PCSFileList *file);

void PCSFileList_Prepend(PCSFileList *list, PCSFile *file);
PCSFile *PCSFileList_Find(PCSFileList *list, const char *path);
PCSFile *PCSFileList_Shift(PCSFileList *list);

#endif
