#include "fwserver.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>


char g_buff[1024];
FILE *g_outFile=0;

// ����һ��ʵ��
FWServer *FW_CreateNew()
{
    FWServer *server = 0;

    do{
        server = (FWServer*)malloc(sizeof(FWServer));//�����ֲ����������ݾͲ��ᱻ�ͷ��ˡ�
        if(0==server) break;
        memset(server,0,sizeof(FWServer));

        server->pool = TP_CreateThreadPool(FW_MAX_THREAD_NUM+5); // �����̳߳�
        if(0==server->pool) break;
        server->list_worker = List_CreateNew(0);// ������������
        if(0==server->list_worker) break;
        server->list_listen = List_CreateNew(0);// ������������
        if(0==server->list_listen) break;
        if(0!=pipe(server->pipe_listen)) break;

        server->isRegister = 0;

        if(0==g_outFile){
            g_outFile = fopen("log.txt","wb+");
        }

        return server;
    }while(0);

    if(0!=server){
        if(0!=server->list_worker){
            List_Delete(server->list_worker);
        }
        if(0!=server->list_listen){
            List_Delete(server->list_listen);
        }
        if(0!=server->pool){
            TP_DeleteThreadPool(server->pool);
        }
        close(server->pipe_listen[0]);
        close(server->pipe_listen[1]);

        FW_Delete(server);
    }
    return 0;
}

void FW_Delete(FWServer* server)
{
    if(0!=server){
        if(0!=server->p2pSocket){
            FW_DeleteSokcet(server->p2pSocket);
        }
        if(0!=server->list_worker){
            List_Delete(server->list_worker);
        }
        if(0!=server->list_listen){
            List_Delete(server->list_listen);
        }
        if(0!=server->pool){
            TP_DeleteThreadPool(server->pool);
        }
        FW_Delete(server);
    }
}

FWSocket * FW_CreateNewSocket()
{
    FWSocket *socket = 0;

    do{
        socket = (FWSocket*)malloc(sizeof(FWSocket));
        if(0==socket) break;
        memset(socket,0,sizeof(FWSocket));
        socket->fd = -1;
        return socket;
    }while(0);

    return 0;
}

void FW_DeleteSokcet(FWSocket *socket)
{
    if(0!=socket){
        FW_CLOSE_SOCK(socket->fd);
        FW_FREE(socket->buff);
        FW_FREE(socket);
    }
}

FWSession* FW_CreateNewSession()
{
    FWSession *session;

    do{
        session = (FWSession *)malloc(sizeof(FWSession));
        if(0==session) {break;}
        memset(session,0,sizeof(FWSession));
        time(&session->time);
        return session;
    }while(0);
    if(0!=session){
        FW_FREE(session);
    }
    return 0;
}

void FW_DeleteSession(FWSession *session)
{
    if(0!=session){
        FW_DeleteSokcet(session->listenSocket);
        FW_DeleteSokcet(session->terminal[0].socket);
        FW_DeleteSokcet(session->terminal[1].socket);
        FW_FREE(session);
    }
}

FWWorker* FW_CreateWorker()
{
    FWWorker* pWorker;
    int rsl;

    do{
        pWorker = (FWWorker*)malloc(sizeof(FWWorker));
        if(0==pWorker) break;
        memset(pWorker,0,sizeof(pWorker));
        pWorker->list_session = List_CreateNew(0);
        if(0==pWorker->list_session) break;
        rsl = pipe(pWorker->pipe_newSession);
        if(0!=rsl) break;

        return pWorker;
    }while(0);

    if(0!=pWorker){
        if(0!=pWorker->list_session) List_Delete(pWorker->list_session);
        close(pWorker->pipe_newSession[0]);
        close(pWorker->pipe_newSession[1]);
        FW_FREE(pWorker);
    }
    return 0;
}

void FW_DeleteWorker(FWWorker *pWorker)
{
    if(0==pWorker) return;

    if(0!=pWorker->list_session) List_Delete(pWorker->list_session);
    close(pWorker->pipe_newSession[0]);
    close(pWorker->pipe_newSession[1]);
    FW_FREE(pWorker);
}



int FW_RecvCmd(FWSocket *socket,char *buff, unsigned long sec, unsigned long usec)
{
    NET_MSG *netMsg;
    char *pBuff;
    unsigned int totleSize;
    unsigned int offset;
    int rsl;

    if(0==socket || 0==buff) return -1;

    if(0!=socket->buff){
        pBuff = socket->buff;
        offset = socket->buffoffset;
    }else{
        pBuff = buff;
        offset = 0;
    }
    netMsg = (NET_MSG *)pBuff;

    while(1){
        totleSize = (offset<sizeof(NET_MSG))?(sizeof(NET_MSG)):(sizeof(NET_MSG)+netMsg->msgDataLen);
        if(offset == totleSize){
            rsl =  0;
            break;
        }
        rsl = FW_Select(socket->fd,sec,usec);
        if(0!=rsl){
            rsl = offset;
            break;
        }
        rsl = recv(socket->fd,(void*)(pBuff+offset),totleSize-offset,0);
        if(0==rsl){
            rsl = -1;
            break;
        }else if(0<rsl){
            offset += rsl;
        }
    }

    if(0==rsl){
        if(pBuff!=buff){
            /*本次接受 cmd 完成,释放空间*/
            memcpy(buff,pBuff,offset);
            FW_FREE(socket->buff);
            socket->buffsize = 0;
            socket->buffoffset = 0;
        }
    }else if(-1==rsl){
        /*socket 已经正常关闭,释放分配的空间*/
        FW_FREE(socket->buff);
        socket->buffsize = 0;
        socket->buffoffset = 0;
    }else{
        if(pBuff==buff){
            if(0==socket->buff){
                socket->buffsize = 200;
                socket->buff = (char*)malloc(socket->buffsize);
            }
            memcpy(socket->buff,pBuff,offset);
            socket->buffoffset = offset;
        }
    }
    return rsl;
}

int FW_SendCmd(FWSocket *socket,char *buff)
{
    NET_MSG *netMsg;
    int rsl;

    if(0==socket || 0==buff) return -1;
    netMsg = (NET_MSG*)buff;

    rsl = send(socket->fd,buff,sizeof(NET_MSG)+netMsg->msgDataLen,0);
    if(rsl != (int)(sizeof(NET_MSG)+netMsg->msgDataLen)){
        return -1;
    }
    return 0;
}


int FW_Select(int fd, unsigned long sec, unsigned long usec)
{
    struct timeval timeout;
    fd_set fds;
    int rsl;

    timeout.tv_sec = sec;
    timeout.tv_usec = usec;
    FD_ZERO(&fds);
    FD_SET(fd,&fds);

    rsl = select(fd+1,&fds,0,0,&timeout);
    if(0<rsl && 0!=FD_ISSET(fd,&fds)){
        return 0;
    }
    return -1;
}

int FW_Start(FWServer* server)
{
    char buff[BUFF_LEN];
    NET_MSG *netMsg = (NET_MSG *)buff;
    char *data = buff+sizeof(NET_MSG);

    int haveResponse;
    int rsl;

    int maxfd;
    fd_set fds;
    struct timeval timeout;

    if(0==server) return -1;

    while(1){

        do{
            while(0==server->p2pSocket){
                FW_ECHO("connect to p2p server...");
                server->isRegister = 0;
                server->p2pSocket = FW_ConnectTo(inet_addr(FW_SERVER_IP),FW_SERVER_PORT);
                if(0!=server->p2pSocket) break;
                sleep(5);
            }
            if(0==server->isRegister){
                rsl = FW_Register(server);
                if(0!=rsl){
                    break;
                }
            }
            /*select*/
            FD_ZERO(&fds);
            FD_SET(server->p2pSocket->fd,&fds);
            maxfd = server->p2pSocket->fd;
            timeout.tv_sec = 4;
            timeout.tv_usec = 0;
            rsl = select(maxfd+1,&fds,0,0,&timeout);

            if(0==rsl){
                FW_HeartBeat(server);
            }else if(FD_ISSET(server->p2pSocket->fd,&fds)){
                /*read cmd*/
                rsl = FW_RecvCmd(server->p2pSocket,buff,10,0);
                if(0!=rsl){
                    FW_ERRO("read cmd failed!\n");
                    break;
                }
                haveResponse = 0;
                FW_DEBUG("netMsg->msgType is OX%x len is %d-------",netMsg->msgType,netMsg->msgDataLen);
                switch(netMsg->msgType){
                case RELAY_REGISTER_SUC_MSG:{
                    FW_DEBUG("register success!");
                    server->isRegister = 1;
                }break;
                case RELAY_REGISTER_ERROR_MSG:{
                    FW_DEBUG("register failed!");
                    server->isRegister = 0;
                    sleep(5);
                }break;
                case RELAY_CONNECT_REQUEST_MSG:{
                    RELAY_CONN_REQUEST *portReq= (RELAY_CONN_REQUEST*)data;
                    RELAY_CONNECT_RESPONSE_CODE *response = (RELAY_CONNECT_RESPONSE_CODE *)data;
                    rsl = FW_AddSessionToListen(server,portReq->port,portReq->SN);
                    netMsg->msgType = RELAY_CONNECT_RESPONSE_CODE_MSG;
                    netMsg->msgDataLen = sizeof(RELAY_CONNECT_RESPONSE_CODE);
                    response->statusCode = rsl;
                    haveResponse = 1;
                }break;


                default:{
                    FW_ERRO("p2p server unknow cmd!");
                }break;
                }
                if(0!=haveResponse){
                    /*answer cmd*/
                    rsl = FW_SendCmd(server->p2pSocket,buff);
                    if(0!=rsl){
                        FW_ERRO("send cmd failed!\n");
                        break;
                    }
                }
            }
        }while(1);

        FW_DeleteSokcet(server->p2pSocket);
        server->p2pSocket = 0;
    }

    FW_ERRO("###########################################################\n");
    FW_ERRO("##############        server quit         #################\n");
    FW_ERRO("###########################################################\n");

    return 0;
}


int FW_StartListen(FWServer *server)
{
    List_Foreach_Variable;
    struct timeval timeout;
    time_t now;
    FWSession *pSession;
    FWSocket *socket;
    fd_set fds;
    int maxFd;
    int rsl;
    int ifRemoveSession;

    if(0==server) return -1;

    while(1){
        FD_ZERO(&fds);

        /*添加新会话*/
        FD_SET(server->pipe_listen[0],&fds);
        maxFd = server->pipe_listen[0];

        List_Foreach(server->list_listen){
            pSession = (FWSession*)List_Foreach_Value;
            /*会话个两终端还没有连接完成*/
            if(0==pSession->terminal[0].socket || 0==pSession->terminal[1].socket){
                FD_SET(pSession->listenSocket->fd,&fds);
                maxFd = FW_MAX(pSession->listenSocket->fd,maxFd);
            }
            /*终端连接还没有进过校验*/
            if(0!=pSession->terminal[0].socket && 0==pSession->terminal[0].isSnCkecked){
                FD_SET(pSession->terminal[0].socket->fd,&fds);
                maxFd = FW_MAX(pSession->terminal[0].socket->fd,maxFd);
            }else if(0!=pSession->terminal[1].socket && 0==pSession->terminal[1].isSnCkecked){
                FD_SET(pSession->terminal[1].socket->fd,&fds);
                maxFd = FW_MAX(pSession->terminal[1].socket->fd,maxFd);
            }
        }

        maxFd ++;
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;
        rsl = select(maxFd,&fds,0,0,&timeout);
        switch(rsl){
        case -1:{
            FW_DEBUG("select socket error!\n");
        }break;
        default:{
            if(0<rsl){
                if(FD_ISSET(server->pipe_listen[0],&fds)){
                    rsl = read(server->pipe_listen[0],&pSession,sizeof(FWSession*));
                    if(sizeof(FWSession*) == rsl){
                        time(&pSession->time);
                        List_PushBack(server->list_listen,(void*)pSession);
                        FW_ECHO("listen session on port %d",pSession->listenSocket->port);
                    }
                }
            }

            List_Foreach(server->list_listen){
                ifRemoveSession = 0;

                pSession = (FWSession*)List_Foreach_Value;
                if(FD_ISSET(pSession->listenSocket->fd,&fds)){
                    socket = FW_Accept(pSession->listenSocket);
                    if(0!=socket){
                        if(0==pSession->terminal[0].socket){
                            pSession->terminal[0].socket = socket;
                            FW_DEBUG("connect one: ip=%d,port=%d",socket->ip,socket->port);
                        }else if(0==pSession->terminal[1].socket){
                            pSession->terminal[1].socket = socket;
                            FW_DEBUG("connect two: ip=%d,port=%d",socket->ip,socket->port);
                        }
                    }
                    /*重置 session 时间重新获得 20 秒超时时间*/
                    time(&pSession->time);
                }
                if(0!=pSession->terminal[0].socket && FD_ISSET(pSession->terminal[0].socket->fd,&fds)){
                    rsl = FW_CheckConnect(pSession->terminal[0].socket,pSession->sn);
                    if(-1==rsl){
                        /*sn 校验失败 或 socket 已经断开*/
                        ifRemoveSession = 1;
                    }else if(0==rsl){
                        /*sn 校验成功*/
                        pSession->terminal[0].isSnCkecked = 1;
                    }
                    /*如果 rsl 大于0 表示 cmd 接受还没完成继续下一次的selct等待接受完成*/
                    time(&pSession->time);
                }
                if(0!=pSession->terminal[1].socket && FD_ISSET(pSession->terminal[1].socket->fd,&fds)){
                    rsl = FW_CheckConnect(pSession->terminal[1].socket,pSession->sn);
                    if(-1==rsl){
                        /*sn 校验失败 或 socket 已经断开*/
                        ifRemoveSession = 1;
                    }else if(0==rsl){
                        /*sn 校验成功*/
                        pSession->terminal[1].isSnCkecked = 1;
                    }
                    /*如果 rsl 大于0 表示 cmd 接受还没完成继续下一次的selct等待接受完成*/
                    time(&pSession->time);
                }
                /*判断连接与sn校验是否完成*/
                if((0!=pSession->terminal[0].socket && 1==pSession->terminal[0].isSnCkecked)
                        && (0!=pSession->terminal[1].socket && 1==pSession->terminal[1].isSnCkecked)){
                    FW_AddSession(server,pSession);
                    List_Foreach_RmCurNode;
                    continue;
                }
                /*判断是否超时*/
                time(&now);
                if(now-pSession->time > FW_SESSION_TIMEOUT){
                    ifRemoveSession = 1;
                }

                /*移除会话*/
                if(1 == ifRemoveSession){
                    FW_DEBUG("remvoe session listen port %d",pSession->listenSocket->port);
                    FW_DeleteSession(pSession);
                    List_Foreach_RmCurNode;
                }
            }
        }break;
        }
    }
    return 0;
}

int FW_Register(FWServer* server)
{
    NET_MSG netMsg;
    int rsl;

    if(0==server) return -1;
    if(-1==server->p2pSocket->fd) return -1;
    FW_ECHO("p2p server: register!");

    /*register to p2p server*/
    netMsg.msgType = RELAY_REGISTER_MSG;
    netMsg.msgDataLen = 0;
    rsl = send(server->p2pSocket->fd,&netMsg,sizeof(NET_MSG),0);
    if(sizeof(NET_MSG) != rsl){
        FW_ERRO("send cmd error!\n");
        return -1;
    }
    return 0;
}

inline int FW_HeartBeat(FWServer* server)
{
    NET_MSG netMsg;
    int rsl;

    if(0==server) return -1;
    if(-1==server->p2pSocket->fd) return -1;

    /*心跳*/
    netMsg.msgType = RELAY_CONNECT_HEART_BEAT_MSG;
    netMsg.msgDataLen = 0;
    rsl = send(server->p2pSocket->fd,&netMsg,sizeof(NET_MSG),0);
    if(sizeof(NET_MSG) != rsl){
        FW_ERRO("send cmd error!\n");
        FW_CLOSE_SOCK(server->p2pSocket->fd);
        return -1;
    }
    return 0;
}

inline int FW_FreePort(FWServer* server, int port)
{
    if(0==server) return -1;

    int rsl;
    char buff[100];
    memset(buff,0,sizeof(buff));
    NET_MSG *netMsg = (NET_MSG *)buff;
    RELAY_CONN_RESPONSE *response = (RELAY_CONN_RESPONSE*)(buff+sizeof(NET_MSG));

    netMsg->msgType = RELAY_CONNECT_RESPONSE_MSG;
    netMsg->msgDataLen = sizeof(RELAY_CONN_RESPONSE);
    response->port = port;
    response->portStatus = 0;

    rsl = FW_SendCmd(server->p2pSocket,buff);
    if(0!=rsl){
        FW_DEBUG("send free port send error!");
    }
    return 0;
}


int FW_AddSessionToListen(FWServer *server, int port, unsigned int sn)
{
    FWSession *session;
    FWSocket *socket;
    int rsl;

    if(0==server) return -1;

    do{
        socket = FW_ListenPort(port);
        if(0==socket){ break; }
        session = FW_CreateNewSession();
        if(0==session) {break;}
        time(&session->time);
        session->listenSocket = socket;
        session->sn = sn;
        rsl = write(server->pipe_listen[1],(void*)&session,sizeof(FWSession *));
        if(sizeof(FWSession*)!=rsl){break;}
        return 0;
    }while(0);
    FW_DeleteSession(session);
    FW_ERRO("listen port %d failed!",port);
    return -1;
}

int FW_AddSession(FWServer *server, FWSession *session)
{
    List_Foreach_Variable;
    int rsl;

    if(0==server || 0==session) return -1;

    FWWorker *pWorker = (FWWorker *)List_Frist(server->list_worker);
    FWWorker *pWorkerIter;
    List_Foreach(server->list_worker){
        pWorkerIter = (FWWorker *)List_Foreach_Value;
        if(List_Count(pWorker->list_session) > List_Count(pWorkerIter->list_session)){
            pWorker = pWorkerIter;
        }
    }

    if((0==pWorker) || ((List_Count(pWorker->list_session)>FW_SUITABLE_SESSION_NUM) &&
                        (List_Count(server->list_worker)<FW_MAX_THREAD_NUM)) ){
        pWorker = FW_CreateWorker();
        if(0==pWorker){ return -1; }
        pWorker->server = server;
        List_PushBack(server->list_worker,(void*)pWorker);
        TP_PushTaskEx(server->pool,(TP_FUN)FW_DoWork,(void*)pWorker,0);

        //        FW_AddWorker(server);
        //        pWorker = List_Last(server->list_worker);
        //        FW_DEBUG("create worker!-----------");
    }
    if(0==pWorker) return -1;

    time(&session->time);

    rsl = write(pWorker->pipe_newSession[1],&session,sizeof(FWSession*));
    if(rsl != sizeof(FWSession*)){
        FW_ERRO("write worker session failed!-----------");
    }
    return 0;
}

//int FW_AddWorker(FWServer *server)
//{
//    int iRsl;
//    FWWorker *pWorker;
//    if(0==server) return -1;

//    do{
//        pWorker = (FWWorker*)malloc(sizeof(FWWorker));
//        if(0==pWorker){
//            FW_ERRO("create worker failed!");
//            break;
//        }
//        memset(pWorker,0,sizeof(FWWorker));
//        pWorker->list_session = List_CreateNew(sizeof(FWSession));
//        if(0==pWorker->list_session){
//            FW_ERRO("create list failed!");
//            break;
//        }
//        iRsl = pipe(pWorker->pipe_newSession);
//        if(0!=iRsl){
//            FW_ERRO("create pipe failed!");
//            break;
//        }
//        pWorker->server = server;
//        List_PushBack(server->list_worker,(void*)pWorker);
//        TP_PushTaskEx(server->pool,(TP_FUN)FW_DoWork,(void*)pWorker,0);
//        return 0;
//    }while(0);

//    close(pWorker->pipe_newSession[0]);
//    close(pWorker->pipe_newSession[1]);
//    List_Delete(pWorker->list_session);
//    FW_FREE(pWorker);

//    return -1;
//}

void FW_DoWork(FWWorker * worker)
{
    List_Foreach_Variable;
    int rsl;
    int isRemoveSession;
    int maxfd;
    fd_set readFds;
    fd_set writeFds;
    FWSession *pSession;
    //    char buff[BUFF_LEN];
    time_t now;
    struct timeval timeout;


    if(0==worker) return;

    while(1){
        FD_ZERO(&readFds);
        FD_ZERO(&writeFds);
        FD_SET(worker->pipe_newSession[0],&readFds);
        maxfd = worker->pipe_newSession[0];

        List_Foreach(worker->list_session){
            pSession = (FWSession*)List_Foreach_Value;
            if(pSession->terminal[0].socket->buff != 0){
                FD_SET(pSession->terminal[1].socket->fd,&writeFds);
            }else{
                FD_SET(pSession->terminal[0].socket->fd,&readFds);
            }
            if(pSession->terminal[1].socket->buff != 0){
                FD_SET(pSession->terminal[0].socket->fd,&writeFds);
            }else{
                FD_SET(pSession->terminal[1].socket->fd,&readFds);
            }
            maxfd = FW_MAX(pSession->terminal[0].socket->fd,maxfd);
            maxfd = FW_MAX(pSession->terminal[1].socket->fd,maxfd);
        }
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;
        rsl = select(maxfd+1,&readFds,&writeFds,0,&timeout);
        switch(rsl){
        case -1:{
            printf("error!\n");
        }break;
        default:{
            if(FD_ISSET(worker->pipe_newSession[0],&readFds)){
                rsl = read(worker->pipe_newSession[0],&pSession,sizeof(FWSession*));
                if(sizeof(FWSession*) == rsl){
                    printf("this is %x worker add session lport %d!\n",
                           (unsigned int) pthread_self(),pSession->listenSocket->port);
                    List_PushBack(worker->list_session,(void*)pSession);
                }
            }
            time(&now);
            List_Foreach(worker->list_session){

                pSession = (FWSession*)List_Foreach_Value;
                isRemoveSession = 0;
                do{
                    if(FD_ISSET(pSession->terminal[0].socket->fd,&readFds) ||
                            FD_ISSET(pSession->terminal[1].socket->fd,&writeFds)){
                        rsl = FW_ExchangeData(pSession->terminal[0].socket,pSession->terminal[1].socket);
                        if(-1==rsl){
                            isRemoveSession = 1;
                            FW_DEBUG("--------------------------b3");
                            break;
                        }
                        time(&pSession->time);
//                        FW_DEBUG("exchange port %d data len is %d",pSession->listenSocket->port, rsl);
                    }
                    if(FD_ISSET(pSession->terminal[1].socket->fd,&readFds) ||
                            FD_ISSET(pSession->terminal[0].socket->fd,&writeFds)){
                        rsl = FW_ExchangeData(pSession->terminal[1].socket,pSession->terminal[0].socket);
                        if(-1==rsl){
                            isRemoveSession = 1;
                            FW_DEBUG("--------------------------b5");
                            break;
                        }
                        time(&pSession->time);
//                        FW_DEBUG("exchange port %d data len is %d",pSession->listenSocket->port, rsl);
                    }
                    if(now - pSession->time > 10){
                        FW_DEBUG("--------------------------btimeout");
                        FW_DEBUG("%ud %ud\n",(int)now,(int)pSession->time);
                        isRemoveSession = 1;
                        break;
                    }
                }while(0);
                if(1==isRemoveSession){
                    FW_DEBUG("this is %0xx worker remove session lport %d!",
                             (unsigned int) pthread_self(),pSession->listenSocket->port);
                    FW_FreePort(worker->server,pSession->listenSocket->port);
                    FW_DeleteSession(pSession);
                    List_Foreach_RmCurNode;
                }
            }
        }
        }
    }
}


int FW_CheckConnect(FWSocket *socket,unsigned int sn)
{
    char buff[BUFF_LEN];
    NET_MSG *netMsg = (NET_MSG *)buff;
    CLIENT_CONNECT_REQUEST *request = (CLIENT_CONNECT_REQUEST *)(buff+sizeof(NET_MSG));
    CLIENT_CONNECT_RESPONSE *response = (CLIENT_CONNECT_RESPONSE *)(buff+sizeof(NET_MSG));
    int rsl;

    if(0==socket) return -1;
    rsl = FW_RecvCmd(socket,buff,0,10*1000);


    if(0==rsl){
        netMsg->msgType = CLIENT_CONNECT_RESPONSE_MSG;
        netMsg->msgDataLen = sizeof(CLIENT_CONNECT_RESPONSE);
        response->statusCode = (request->SN == sn)?0:-1;
        rsl = FW_SendCmd(socket,buff);
        if(response->statusCode){
            FW_DEBUG("error sn: %d",response->statusCode);
        }
        FW_FREE(socket->buff);
        socket->buffoffset = 0;
        socket->buffsize = 0;
        return response->statusCode;
    }else{
        return rsl;
    }
}


int FW_ExchangeData(FWSocket *sendSocket, FWSocket *recvSocket)
{
    int rsl;
    int rlen,wlen;
    int num = 0;
    char buff[BUFF_LEN];

    if(0==sendSocket || 0==recvSocket) return -1;

    if(sendSocket->buffsize > 0){
        rsl = send(recvSocket->fd,sendSocket->buff+sendSocket->buffoffset,sendSocket->buffsize-sendSocket->buffoffset,0);
        if(0==rsl){ /*会话关闭或不可写*/
            return -1;
        }else if(-1==rsl){
            return 0;
        }else {
            num += rsl;
            sendSocket->buffoffset += rsl;
            FW_DEBUG("send len %d\n",rsl);
            if(sendSocket->buffoffset == sendSocket->buffsize){
                FW_FREE(sendSocket->buff);
                sendSocket->buffoffset = 0;
                sendSocket->buffsize = 0;
            }else{
                return num;
            }
        }
    }

    while(1){
        rlen = 0;
        wlen = 0;
        rlen = recv(sendSocket->fd,buff,BUFF_LEN,0);

        if(0==rlen){ /*会话关闭或不可读*/
            return -1;
        }else if(-1==rlen){
            return num;
        }

        wlen = send(recvSocket->fd,buff,rlen,0);
        if(0==wlen){
            return -1;
        }else if(wlen != rlen){
            break;
        }
        num += wlen;
    }

    /*发送缓冲区已满*/
    if(-1==wlen) wlen = 0;
    sendSocket->buffsize = rlen - wlen;
    sendSocket->buffoffset = 0;
    sendSocket->buff = (char*)malloc(sendSocket->buffsize);
    if(0==sendSocket->buff){
        printf("lose data size is %d\n",sendSocket->buffsize);
        sendSocket->buffsize = 0;
        sendSocket->buffoffset = 0;
        return num;
    }
    memcpy(sendSocket->buff,buff+wlen,sendSocket->buffsize);
    FW_DEBUG("save len %d  %p\n",sendSocket->buffsize,sendSocket->buff);
    return num;
}


void FW_CheckLogFileSize()
{
    long int size;
    if(0==g_outFile) return;

    size = ftell(g_outFile);
    if(size > 4*1024*1024){ /*4M*/
        fclose(g_outFile);
        rename("log.txt","log_old.txt");
        g_outFile = fopen("log.txt","wb+");
    }
}

FWSocket* FW_ListenPort(int port)
{
    int fd;
    FWSocket* socket;

    do{
        fd = SK_ListenPort(port);
        if(-1 == fd){ break; }
        socket = FW_CreateNewSocket();
        if(0==socket){ break; }

        socket->fd = fd;
        socket->port = port;
        SK_SetSocketUB(fd);

        return socket;
    }while(0);

    if(-1!=fd){
        FW_CLOSE_SOCK(fd);
    }
    if(0!=socket){
        FW_DeleteSokcet(socket);
    }
    return 0;
}

FWSocket* FW_ConnectTo( unsigned int ip, int port)
{
    FWSocket* socket;

    do{
        socket = FW_CreateNewSocket();
        if(0==socket){ break;}
        socket->fd = SK_ConnectTo(ip,port);
        if(-1 == socket->fd){ break; }
        SK_SetSocketUB(socket->fd);

        socket->ip = ip;
        socket->port = port;

        return socket;
    }while(0);

    if(0!=socket){
        FW_DeleteSokcet(socket);
    }
    return 0;
}

FWSocket* FW_Accept(FWSocket *listenSocket)
{
    int fd;
    FWSocket* socket;

    if(0==listenSocket) return 0;
    struct sockaddr addr;
    struct sockaddr_in *addr_in =(struct sockaddr_in *)(&addr);
    socklen_t len = sizeof(struct sockaddr);

    do{
        fd = accept(listenSocket->fd,&addr,&len);
        if(-1 == fd){ break; }
        socket = FW_CreateNewSocket();
        if(0==socket){ break; }
        SK_SetSocketUB(fd);

        socket->fd = fd;
        socket->ip = addr_in->sin_addr.s_addr;
        socket->port = addr_in->sin_port;
        return socket;
    }while(0);

    if(-1!=fd){
        FW_CLOSE_SOCK(fd);
    }
    if(0!=socket){
        FW_DeleteSokcet(socket);
    }
    return 0;
}


/*listen port*/
int SK_ListenPort(int port)
{
    int sockfd = -1;
    struct sockaddr_in address;
    int on=1;
    int rsl;

    if(0 > port) return -1;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1==sockfd){
        printf("Create socket failed!\n");
        return -1;
    }
    /*set socket*/
    rsl = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int));
    if(-1==rsl){
        printf("set socket failed!\n");
        FW_CLOSE_SOCK(sockfd);
        return -1;
    }
    /*bind*/
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    memset(&(address.sin_zero), '\0', 8);
    rsl = bind(sockfd, (struct sockaddr *)&address, sizeof(address));
    if(0 != rsl){
        printf("bind socket failed!\n");
        FW_CLOSE_SOCK(sockfd);
        return -1;
    }
    /* listen */
    rsl = listen(sockfd, 10);
    if(0!=rsl){
        printf("listen socket failed!\n");
        FW_CLOSE_SOCK(sockfd);
        return -1;
    }
    return sockfd;
}



/*socket*/
int SK_ConnectTo(unsigned int ip,int port)
{
    int sockfd;
    int rsl;
    struct sockaddr_in address;

    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(-1==sockfd) return -1;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = ip;
    address.sin_port = htons(port);
    rsl = connect(sockfd,(const struct sockaddr *)&address,sizeof(struct sockaddr_in));
    if(-1==rsl){
        FW_CLOSE_SOCK(sockfd);
        return -1;
    }
    return sockfd;
}


int SK_SetSocketUB(int sockfd)
{
    int flags;
    int rsl;
    flags=fcntl(sockfd,F_GETFL,0);
    rsl = fcntl(sockfd,F_SETFL,flags|O_NONBLOCK);

    //    setsockopt(s, SOL_SOCKET, SO_RCVBUF, &rcv_size, &optlen);
    int size;
    socklen_t len = sizeof(size);


    rsl = getsockopt(sockfd,SOL_SOCKET,SO_RCVBUF,&size,&len);
    if(0!=rsl){
        printf("%s: get socket opt failed!\n",__FUNCTION__);
    }/*else{
        printf("%s: sokcet recv buff size is %d\n",__FUNCTION__,size);
    }*/

    rsl = getsockopt(sockfd,SOL_SOCKET,SO_SNDBUF,&size,&len);
    if(0!=rsl){
        printf("%s: get socket opt failed!\n",__FUNCTION__);
    }/*else{
        printf("%s: sokcet send buff size is %d\n",__FUNCTION__,size);
    }*/

    size = 64 * 1024;
    rsl = setsockopt(sockfd,SOL_SOCKET,SO_SNDBUF,&size,len);
    if(0!=rsl){
        printf("%s: set socket opt failed!\n",__FUNCTION__);
    }

    rsl = getsockopt(sockfd,SOL_SOCKET,SO_SNDBUF,&size,&len);
    if(0!=rsl){
        printf("%s: get socket opt failed!\n",__FUNCTION__);
    }/*else{
        printf("%s: sokcet send buff size is %d\n",__FUNCTION__,size);
    }*/


    //    size = 8;
    //    rsl = setsockopt(sockfd,SOL_SOCKET,SO_RCVLOWAT,&size,len);
    //    if(0!=rsl){
    //        printf("%s: set socket opt failed!\n",__FUNCTION__);
    //    }
    //    rsl = getsockopt(sockfd,SOL_SOCKET,SO_RCVLOWAT,&size,&len);
    //    if(0!=rsl){
    //        printf("%s: get socket SO_RCVLOWAT failed!\n",__FUNCTION__);
    //    }else{
    //        printf("%s: sokcet SO_RCVLOWAT size is %d\n",__FUNCTION__,size);
    //    }


    //    printf("set socket no block success!\n");
    return rsl;
}




