#ifndef FWSERVER_H
#define FWSERVER_H

#include "linklist.h"
#include "threadpool.h"
#include "relaymanage/relayManage.h"
#include "stdio.h"


#ifdef __cplusplus
extern "C" {
#endif

#define BUFF_LEN 10*1024
#define FW_FREE(P) if(0!=P){free(P); P=0;}
#define FW_CLOSE_SOCK(sock) if(-1!=sock){shutdown(sock,2); close(sock); sock = -1;}
#define FW_MAX(one,two) (one>two)?(one):(two)


#define _FW_DEBUG_ 1
#if _FW_DEBUG_
//#define FW_DEBUG(fmt,args...) printf("DEBUG %s-%d: "fmt"\n",__FUNCTION__,__LINE__,## args);
#define FW_DEBUG(fmt,args...) \
{ \
   printf("DEBUG %s-%d: "fmt"\n",__FUNCTION__,__LINE__,## args); \
   fprintf(g_outFile,"ERRO %s-%d: "fmt"\n",__FUNCTION__,__LINE__,## args); \
   fflush(g_outFile); \
    FW_CheckLogFileSize(); \
}
#else
#define FW_DEBUG(fmt,args...)
#endif

//#define FW_ERRO(fmt,args...) printf("ERRO %s-%d: "fmt"\n",__FUNCTION__,__LINE__,## args);
//#define FW_ECHO(fmt,args...) printf("ECHO %s-%d: "fmt"\n",__FUNCTION__,__LINE__,## args);
#define FW_ERRO(fmt,args...)  \
{ \
    printf("ERRO %s-%d: "fmt"\n",__FUNCTION__,__LINE__,## args); \
    fprintf(g_outFile,"ERRO %s-%d: "fmt"\n",__FUNCTION__,__LINE__,## args); \
    fflush(g_outFile); \
    FW_CheckLogFileSize(); \
}
#define FW_ECHO(fmt,args...) \
{ \
    printf("ECHO %s-%d: "fmt"\n",__FUNCTION__,__LINE__,## args); \
    fprintf(g_outFile,"ERRO %s-%d: "fmt"\n",__FUNCTION__,__LINE__,## args); \
    fflush(g_outFile);\
    FW_CheckLogFileSize(); \
}


//#define FW_SERVER_IP "183.57.82.43"
#define FW_SERVER_IP "58.96.171.231"
#define FW_SERVER_PORT 8888

#define FW_MAX_THREAD_NUM 20
#define FW_SUITABLE_SESSION_NUM 10

#define FW_SESSION_TIMEOUT 10


struct FWServer;

typedef struct FWSocket{
    int fd;
    int ip;
    int port;

    char* buff;
    unsigned int buffsize;
    unsigned int buffoffset;
}FWSocket;

typedef struct FWTerminal{
    int isSnCkecked;
    FWSocket *socket;
}FWTerminal;

typedef struct FWSession{
    unsigned int sn;
    time_t time;
    FWSocket *listenSocket;
    FWTerminal terminal[2];
}FWSession;

typedef struct FWWorker{
    List *list_session;
    int pipe_newSession[2];
    struct FWServer *server;
}FWWorker;


typedef struct FWServer{
    ThreadPool *pool;
    FWSocket *p2pSocket;

    int isRegister;

    List *list_worker;
    List *list_listen;
    int pipe_listen[2];
}FWServer;


FWServer* FW_CreateNew();
void FW_Delete(FWServer* server);

FWSocket *FW_CreateNewSocket();
void FW_DeleteSokcet(FWSocket *socket);

FWSession *FW_CreateNewSession();
void FW_DeleteSession(FWSession *session);

FWWorker *FW_CreateWorker();
void FW_DeleteWorker(FWWorker* worker);

int FW_Select(int fd, unsigned long sec, unsigned long usec);
int FW_RecvCmd(FWSocket *socket, char* buff, unsigned long sec, unsigned long usec);
int FW_SendCmd(FWSocket *socket, char* buff);

int FW_Start(FWServer* server);
int FW_StartListen(FWServer* server);

inline int FW_Register(FWServer* server);
inline int FW_HeartBeat(FWServer* server);
inline int FW_FreePort(FWServer* server, int port);

int FW_AddSession(FWServer* server, FWSession* session);
int FW_AddSessionToListen(FWServer* server, int port, unsigned int sn);
int FW_CheckConnect(FWSocket *socket, unsigned int sn);

//int FW_AddWorker(FWServer* server);
void FW_DoWork(FWWorker * worker);

/*返回值为发送的数据量. -1:会话关闭 0:不可写或不可读.*/
inline int FW_ExchangeData(FWSocket *sendSock, FWSocket *recvSock);

void FW_CheckLogFileSize();

FWSocket* FW_ListenPort(int port);
FWSocket* FW_ConnectTo(unsigned int ip, int port);
FWSocket* FW_Accept(FWSocket *listenSocket);

int SK_ListenPort(int port);
int SK_ConnectTo(unsigned int ip,int port);
int SK_SetSocketUB(int sockfd);


#ifdef __cplusplus
}
#endif
#endif
