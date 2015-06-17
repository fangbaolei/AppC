#include "P2P_FreeIp.h"


// 创建TCP客户端socket
int TcpClientCreate(void)
{
	struct sockaddr_in serAddr;
	int sock = -1;
	int SockOptVal = 1;

	memset(&serAddr, 0, sizeof(serAddr));
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(PORT);
	serAddr.sin_addr.s_addr = inet_addr (SERVER_IP);
	//创建socket
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock < 0) 
	{
		printf("socket Error!");
		return -1;
	}
	// 端口复用
	if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &SockOptVal, sizeof(int)) == -1)
	{
		return -1;
	}
	// 连接请求
	if (connect(sock, (struct sockaddr *) &serAddr, sizeof(serAddr)) < 0) 
	{
		printf("connect Error!!\n");
		return -1;
	}
	return sock;
}

// 设置码流类型
int SendStreamChn(int sock,int StreamChn)
{
	AV_CMD NxpAvCmd;
	int res = 0;
	// 设定通道号
	memset(&NxpAvCmd,0,sizeof(NxpAvCmd));
	NxpAvCmd.bCH= StreamChn;
	res = send(sock, &NxpAvCmd,sizeof(NxpAvCmd), 0);
	if (res <= 0) 
	{
		printf("Send Error!!\n");
		return -1;
	}
	printf("Send channel:%d\n",NxpAvCmd.bCH);
	return 0;
}
// 获取序列号
int RecvSN(int sock)
{
	AV_CMD NxpAvCmd;
	int res = 0;
	char SN[32] = {0};
	memset(&NxpAvCmd, 0, sizeof(NxpAvCmd));
	res = recv(sock, &NxpAvCmd,sizeof(NxpAvCmd), 0);
	if ((res <= 0) ||(!NxpAvCmd.bBuffer))
	{
		printf("Send Error!!\n");
		return -1;
	}
	res = recv(sock, SN,NxpAvCmd.bBufferSize, 0);
	if (res <= 0) 
	{
		printf("Send Error!!\n");
		return -1;
	}
	printf("Recv SN:%s\n\n",SN);
	return 0;
}
// 发送NXP的用户登录信息
int SendUsrInfo(int sock,char *Usr,char *Pwd)
{
	AV_CMD NxpAvCmd;
	USER_INFO NxpUsrInfo;
	int res = 0;
	memset(&NxpUsrInfo, 0, sizeof(NxpUsrInfo));
	strcpy(NxpUsrInfo.ucUsername,Usr);
	strcpy(NxpUsrInfo.ucPassWord,Pwd);
	NxpAvCmd.bBuffer = 1;
	NxpAvCmd.bBufferSize = sizeof(NxpUsrInfo);
	res = send(sock, &NxpAvCmd,sizeof(NxpAvCmd), 0);
	if (res <= 0) 
	{
		printf("Send Error!!\n");
		return -1;
	}
	res = send(sock, &NxpUsrInfo,sizeof(NxpUsrInfo), 0);
	if (res <= 0) 
	{
		printf("Send Error!!\n");
		return -1;
	}
	printf("Client:   usr :%s   pwd:%s\n",NxpUsrInfo.ucUsername,NxpUsrInfo.ucPassWord);
	return 0;

}

// 接收码流数据，并调用P2P接口将码流数据发送到客户端
int RecvRealStream(int sock,int msessionid,int run)
{
	char RecvBuf[FRAME_BUF_SIZE] = {0};
	AV_VHD NxpAvVhd;
	int RecvBytes = 0;
	int res = 0;
	int TotalPackets = 0;
	while(run)
	{
		// 接收AV_VHD
		memset(&NxpAvVhd, 0, AV_HEADER_LEN);
		RecvBytes = recv(sock, &NxpAvVhd,AV_HEADER_LEN, 0);
		if((RecvBytes <= 0)||(RecvBytes != AV_HEADER_LEN))
		{
			printf("Send Error!!\n");
			return -1;
		}
		// 接收H.264帧数据
		TotalPackets = 0;
		while(TotalPackets < NxpAvVhd.bSize)// 有时候一次性发送较多的数据时，TCP会将该数据包拆开分多次发送。
		{
			RecvBytes = recv(sock, RecvBuf+TotalPackets, NxpAvVhd.bSize-TotalPackets, 0);
			if(RecvBytes != NxpAvVhd.bSize)
			{
				printf("*********  RecvBytes:%d,  NxpAvVhd.bSize:%d    recv next packet!!\n\n",RecvBytes,NxpAvVhd.bSize);
				if((TotalPackets+RecvBytes) == NxpAvVhd.bSize)
				{
					printf("*********  Recv packets currect!!:%d\n\n",TotalPackets + RecvBytes);
				}
			}
			if(RecvBytes == -1)
			{
				return -1;
			}
			TotalPackets += RecvBytes;
		}
		//P2P发送码流
		res = P2pStartSendData(msessionid,RecvBuf, NxpAvVhd.bSize, RealStream_Data);	
		if(res== -2)
		{
			return -1;
		}
	}
	return -1;
}
int RecvRelayStream(int sock,int msessionid,int run)
{
	char RecvBuf[FRAME_BUF_SIZE] = {0};
	AV_VHD NxpAvVhd;
	int RecvBytes = 0;
	int res = 0;
	int TotalPackets = 0;
	while(run)
	{
		memset(&NxpAvVhd, 0, AV_HEADER_LEN);
		RecvBytes = recv(sock, &NxpAvVhd,AV_HEADER_LEN, 0);
		if( (RecvBytes <= 0)||(RecvBytes != AV_HEADER_LEN) )
		{
			printf("Send Error!!\n");
			return -1;
		}
		TotalPackets = 0;
		while(TotalPackets < NxpAvVhd.bSize)
		{
			RecvBytes = recv(sock, RecvBuf+TotalPackets, NxpAvVhd.bSize-TotalPackets, 0);
			if(RecvBytes != NxpAvVhd.bSize)
			{
				printf("========  RecvBytes:%d,  NxpAvVhd.bSize:%d\n\n",RecvBytes,NxpAvVhd.bSize);
				if((TotalPackets+RecvBytes) == NxpAvVhd.bSize)
				{
					printf("========  Recv packets currect!!:%d\n\n",TotalPackets+RecvBytes);
				}
			}
			if(RecvBytes == -1)
			{
				return -1;
			}
			TotalPackets += RecvBytes;
		}
		//P2P发送码流
		res = P2pStartSendRelayData(msessionid,RecvBuf, NxpAvVhd.bSize, RealStream_Data);	
		if(res== -2)
		{
			return -1;
		}
	}
	return -1;
}

void *SendRealStream(void *mediainfo)
{
	struct  m_mediainfo* pmediainfo  = (struct  m_mediainfo *)(mediainfo);
	int sock = -1;
	int StreamChn = 0;
	char Usr[16] = "admin";
	char Pwd[16] = "admin";
	int MessionId = pmediainfo->msessionid;
	StreamChn = pmediainfo->channelNo;
	// 接收到P2P客户端的关闭命令后，退出该线程
	if(!pmediainfo->run)
	{
		close(sock);
		return NULL;
	}
	// 创建socket
	sock = TcpClientCreate();
	if(sock == -1)
	{
		close(sock);
		return NULL;
	}
	// 设置码流类型(通道)
	if(SendStreamChn(sock,StreamChn) == -1)
	{
		close(sock);
		return NULL;
	}
	// 获取产品序列号
	if(RecvSN(sock) == -1)
	{
		close(sock);
		return NULL;
	}
	// 发送用户信息
	if(SendUsrInfo(sock,Usr,Pwd) == -1)
	{
		close(sock);
		return NULL;
	}
	// 接收码流数据，并调用P2P接口发送到P2P客户端
	if(RecvRealStream(sock,MessionId,pmediainfo->run) == -1)
	{
		close(sock);
		return NULL;
	}
	return NULL;
}


void *SendRelayStream(void *mediainfo)
{
	struct  m_mediainfo* pmediainfo  = (struct  m_mediainfo *)(mediainfo);
	int sock = -1;
	int StreamChn = 0;
	char Usr[16] = "admin";
	char Pwd[16] = "admin";
	int MessionId = pmediainfo->msessionid;
	StreamChn = pmediainfo->channelNo;
	if(!pmediainfo->run)
	{
		close(sock);
		return NULL;
	}
	sock = TcpClientCreate();
	if(sock == -1)
	{
		close(sock);
		return NULL;
	}
	if(SendStreamChn(sock,StreamChn) == -1)
	{
		close(sock);
		return NULL;
	}
	if(RecvSN(sock) == -1)
	{
		close(sock);
		return NULL;
	}
	if(SendUsrInfo(sock,Usr,Pwd) == -1)
	{
		close(sock);
		return NULL;
	}
	if(RecvRelayStream(sock,MessionId,pmediainfo->run) == -1)
	{
		close(sock);
		return NULL;
	}
	return NULL;
}

int CreatThread(sthread func,void* param)
{
	int iRet=0;
       pthread_t		 threadID;
    	pthread_attr_t   attr;	
	pthread_attr_init(&attr);	
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	iRet=pthread_create(&threadID,&attr,func,param);
	if(iRet != 0)
	{
		(void)pthread_attr_destroy(&attr);
		return -1;
	}
	return 0;
}

int PlayRealStream(char *data)
{
	struct  m_mediainfo *mediainfo = (struct  m_mediainfo *)data;
	int ret = -1;

	if(mediainfo->streamType == 1)  //主码流请求
	{
		printf("play main stream!\n");
	}
	else if(mediainfo->streamType == 2) //辅码流请求
	{
		printf("play sub stream!\n");
	}
	//printf( "  file:%s   line:%d\n\n", __FILE__, __LINE__);
	mediainfo->run = 1;
	ret = CreatThread(SendRealStream,(void *)(mediainfo));
	if(ret <0)
	{
		printf("PlayRealStream CreatThread erro!\n");
		return -1;
	}
	return 0;
}

int StopRealStream(char *data)
{
	struct  m_mediainfo *mediainfo = (struct  m_mediainfo *)data;
	mediainfo->run = 0;
	return 0;
		
}

int ClientDisconnect(char *data) //对端主动关闭连接
{
	struct  m_mediainfo *mediainfo = (struct  m_mediainfo *)data;
	mediainfo->run = 0;  //停止发送视频线程
	
	int result = P2pStopService(mediainfo->msessionid);  //关闭p2p服务
	if(result<0)
	{
		printf("StopRealStream P2pStopSendData erro!\n");
		return -1;
	}
	
        return 0;
}

int PlayRelayStream(char *data)
{
	int ret = -1;
	
	struct  m_mediainfo *mediainfo = (struct  m_mediainfo *)data;
	printf("mediainfo->streamType :%d\n",mediainfo->streamType );

	
	if(mediainfo->streamType == 1)  //主码流请求
	{
		printf("play main stream!\n");
	}
	else if(mediainfo->streamType == 2) //辅码流请求
	{
		printf("play sub stream!\n");
	}
	//printf("111111111YYYYYYYY	channel is %d ",mediainfo->channelNo);
	//printf( "  file:%s   line:%d\n\n", __FILE__, __LINE__);

	mediainfo->run = 1;
	ret = CreatThread(SendRelayStream,(void *)(mediainfo));
	if(ret <0)
	{
		printf("PlayRelayStream CreatThread erro!\n");
		return -1;
	}
	
        return 0;
}
int StopRelayStream(char *data)  
{
	struct  m_mediainfo *mediainfo = (struct  m_mediainfo *)data;
        mediainfo->run = 0; //停止发送视频
        return 0;
		
}
int RelayClientDisconnect(char *data)   //对端主动关闭连接
{
	struct  m_mediainfo *mediainfo = (struct  m_mediainfo *)data;
	mediainfo->run = 0;
	
	int result = P2pStopRelayService(mediainfo->msessionid);  //关闭p2p服务
	if(result<0)
	{
		printf("StopRealStream P2pStopSendData erro!\n");
		return -1;
	}
	
        return 0;
}


int HandleCommand(P2pCmdType cmd,char* data,int len)
{
	int result = 0;	
	switch(cmd)
	{
		case  P2P_PLAY_REAL_STREAM:  //实时流
			result = PlayRealStream(data);
			if(result<0)
			{
				return -1;
			}
			break;
		case  P2P_STOP_REAL_STREAM:
			result = StopRealStream(data);
			if(result<0)
			{
				return -1;
			}
			break;
		case  P2P_PLAY_RELAY_STREAM: //实时流(走中转方式)
			result = PlayRelayStream(data);
			if(result<0)
			{
				return -1;
			}
			break;
		case  P2P_STOP_RELAY_STREAM:
			result = StopRelayStream(data);
			if(result<0)
			{
				return -1;
			}
			break;
		case  P2P_CLIENT_DISCONNECT:
			result = ClientDisconnect(data);
			if(result<0)
			{
				return -1;
			}
			break;	
		case  P2P_RELAYCLIENT_DISCONNECT:
			result = RelayClientDisconnect(data);
			if(result<0)
			{
				return -1;
			}
			break;	
		default:
			break;
	}

	return 0;	
}

int GetFreeIpInfo(USER_INFO *UserInfo)
{
    int result = 0;
    char **dbResult;
    int nRow = 0, nColumn = 0;
    char *sqlcmd[2] = {
	"select * from userInfo",
	"select * from p2pCfgTbl"
    };
    sqlite3 *db;
    do
    {
	    if(SQLITE_OK != sqlite3_open(DATABASE_FILE, &db))//数据库打开失败,恢复数据库。
	    {
	        break;
	    }
	    result = sqlite3_get_table(db, sqlcmd[0], &dbResult, &nRow, &nColumn, NULL);
	    if(SQLITE_OK != result)//查询某个表单失败，恢复数据库并退出。
	    {
	        break;
	    }
	    sqlite3_free_table(dbResult);
	    strcpy(UserInfo->ucPassWord, dbResult[nColumn + 1]);
	    result = sqlite3_get_table(db, sqlcmd[1], &dbResult, &nRow, &nColumn, NULL);
	    if(SQLITE_OK != result)//查询某个表单失败，恢复数据库并退出。
	    {
	        break;
	    } 
	    strcpy(UserInfo->ucSerialNum, dbResult[nColumn + 3]);
    }while(0);
	/*  */
	 sqlite3_free_table(dbResult);
	sqlite3_close(db);
    return 0;
}
int main(int argc, char** argv) 
{
	USER_INFO UserInfo;
	GetFreeIpInfo(&UserInfo);
	printf("Pwd:%s     sn:%s\n\n",UserInfo.ucPassWord,UserInfo.ucSerialNum);
	P2p_RegisterCommandHandle(HandleCommand);		

	int result =P2P_InitService(FREE_IP_ADDR, UserInfo.ucSerialNum,"admin",UserInfo.ucPassWord);   //arg[1]为P2P服务器地址，目前为www.freeipc.com   arm[2]为设备的序列号    "admin"、"admin"为设备的用户名和密码
	if(result<0)
	{
		printf("P2P_InitService erro!\n");
	}

	while(1)
	{
		sleep(30);
	}
	
}




