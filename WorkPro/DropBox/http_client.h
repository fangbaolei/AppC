/*
 * Copyright (c) 2013 emptyhua@gmail.com
 */

#ifndef _HTTP_CLIENT_H
#define _HTTP_CLIENT_H

#include <curl/curl.h>
#include <curl/curlbuild.h>
#include <curl/curlrules.h>
#include <curl/curlver.h>
#include <curl/easy.h>
#include <curl/mprintf.h>
#include <curl/multi.h>
#include <curl/stdcheaders.h>
#include <curl/typecheck-gcc.h>

//#include "curl.h"
typedef struct HttpBuffer_s HttpBuffer;

struct HttpBuffer_s {
    char *content;
    size_t size;            /*buffer�ߴ�*/
    size_t used;            /*��ʹ���ֽ���*/
    HttpBuffer *next;       /*����*/
};

typedef struct HttpClient_s {
    CURL *curl;                 /*CURL          */
    
    int retry_times;            /*ʧ�����Դ���  */
    int retry_interval;         /*����Ƶ��,��   */
    int fail_times;             /*ʧ�ܴ���      */

    HttpBuffer *responseText;   /*body������    */
    HttpBuffer *responseHeader; /*header������  */
    char *c_responseText;
    char *c_responseHeader;

    void *fail_reset_callback;  /*ʧ�����ûص�  */
    void *fail_reset_context;   /*ʧ������������*/
    size_t fail_reset_context2;   /*ʧ������������*/

    CURLcode resultCode;

    int trace_ascii;
} HttpClient;


HttpBuffer* HttpBuffer_New();
void   HttpBuffer_Free(HttpBuffer *buffer);
void   HttpBuffer_Append(HttpBuffer *buffer, const char *input, size_t size); 
size_t HttpBuffer_Length(HttpBuffer *buffer);
void   HttpBuffer_Empty(HttpBuffer *buffer);
size_t HttpBuffer_ToChar(HttpBuffer *buffer, char *content);
void   HttpBuffer_Dump(HttpBuffer *buffer);

HttpClient* HttpClient_New();
void HttpClient_Free(HttpClient *client);

void  HttpClient_Init(HttpClient *client);

void  HttpClient_SetFailRetryCallback(HttpClient *client, void *callback, void *context, size_t context2);
//void  HttpClient_SetFailRetryCallback(HttpClient *client, void *callback, void *context);

void  HttpClient_SetFailRetry(HttpClient *client, int retry_times, int retry_interval);
void  HttpClient_SetWillGetHeader(HttpClient *client);
void  HttpClient_SetDebug(HttpClient *client, int trace_ascii);

CURLcode HttpClient_Get(HttpClient *client, const char *url);

CURLcode HttpClient_PostHttpData(HttpClient *client, const char *url, struct curl_httppost *data);

const char *HttpClient_GetError(HttpClient *client);
const char *HttpClient_ResponseText(HttpClient *client);
long HttpClient_ResponseCode(HttpClient *client);

#endif
