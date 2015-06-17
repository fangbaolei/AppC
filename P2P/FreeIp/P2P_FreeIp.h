#ifndef __SEND_FILE_h__
#define __SEND_FILE_h__

#include <stdio.h>
#include <memory.h>
#include <pthread.h>
#include <unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include <sys/fcntl.h>
#include <sqlite3.h>
#include "P2psdkapp.h"

#define FRAME_BUF_SIZE (512*1024)
#define AV_HEADER_LEN  16
#define AV_FILE_PATH "./AVHeader_receiver"
#define BACKLOG   3
#define PORT  9395
#define SOL_SOCKET		1
#define SO_REUSEADDR		2
#define SERVER_IP "127.0.0.1"
#define DATABASE_FILE       "/data/system.db"
#define FREE_IP_ADDR       "www.freeipc.com"

typedef struct
{
	unsigned long ulFlag; //��־00 00 01 A5
	unsigned long bMediaType:1;//A/V
	unsigned long bFrameType:5;//֡���� 1��ʾΪP֡  5��ʾΪI֡
	unsigned long bSize:22; //֡����
	unsigned long bSubStream:2;//������
	unsigned long bFrameRate:2;//֡��
	unsigned short usCH;//ͨ����
	unsigned char ucI_SerialNum;//I֡���кţ���һ��I֡��һ
	unsigned char ucP_SerialNum;//p֡���кţ���һ��I֡����
	unsigned long ulTimeStamp;//ʱ���
}AV_VHD;

/*CMD16*/
    typedef struct
{   unsigned long ulFlag;                    //  00 00 01 A6

     unsigned long bCH:16;                 // 0
     unsigned long bBuffer:1;              //CMD               
     unsigned long bBufferSize:15;       //CMD

     unsigned short usCmd;                //
     unsigned char ucMessage;           //              
     unsigned char ucState;                //

     unsigned long ulData;                 //
   }AV_CMD ,  *PAV_CMD;


typedef struct
{
    unsigned char ucUsername[16];
    unsigned char ucPassWord[16];
    unsigned char ucSerialNum[16];
}USER_INFO;
// �̺߳���
typedef void *(*sthread)(void*);

#endif
