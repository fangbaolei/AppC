#ifdef __cplusplus
extern "C" {
#endif


#ifndef _HEROSPEED_P2P_APP_MSG_DEF_H_
#define _HEROSPEED_P2P_APP_MSG_DEF_H_

#include "P2PSDK.h"

typedef enum
{
    P2P_PLAY_REAL_STREAM = 0,
    P2P_STOP_REAL_STREAM = 1,
    P2P_PLAY_RELAY_STREAM = 2 ,
    P2P_STOP_RELAY_STREAM = 3,
    P2P_CLIENT_DISCONNECT = 4,
    P2P_RELAYCLIENT_DISCONNECT = 5,
}P2pCmdType;
typedef enum
{
   Msg_Data,  // ��Ϣ���� 
   RealStream_Data, // ʵʱ������
   RecordStream_Data, // ¼��������
   // any else .... 
}StreamType;

typedef struct  m_mediainfo
{
    int    run;
    int    msessionid;	
    short streamType;  // 1:������ 2:������
    short channelNo;  // ͨ����(��1��ʼ)	
}P2pMediainfo,*MP2pMediainfo;

typedef int (*HandleCommandCallback)(P2pCmdType cmd,char* data,int len);


int   P2P_InitService(char* serverIp, char* myId,const char*username,const char* password);
int   P2p_RegisterCommandHandle(HandleCommandCallback handlecommand);


int P2pStartSendData(int sessionid,char* data, int len,StreamType mstreamtype);
int P2pStopService(int sessionid);

int P2pStartSendRelayData(int sessionid,char* data, int len,StreamType mstreamtype);
int P2pStopRelayService(int sessionid);


#ifdef __cplusplus
}
#endif

#endif



