#include "P2P_FreeIp.h"


// ����TCP�ͻ���socket
int TcpClientCreate(void)
{
	struct sockaddr_in serAddr;
	int sock = -1;
	int SockOptVal = 1;

	memset(&serAddr, 0, sizeof(serAddr));
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(PORT);
	serAddr.sin_addr.s_addr = inet_addr (SERVER_IP);
	//����socket
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock < 0) 
	{
		printf("socket Error!");
		return -1;
	}
	// �˿ڸ���
	if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &SockOptVal, sizeof(int)) == -1)
	{
		return -1;
	}
	// ��������
	if (connect(sock, (struct sockaddr *) &serAddr, sizeof(serAddr)) < 0) 
	{
		printf("connect Error!!\n");
		return -1;
	}
	return sock;
}

// ������������
int SendStreamChn(int sock,int StreamChn)
{
	AV_CMD NxpAvCmd;
	int res = 0;
	// �趨ͨ����
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
// ��ȡ���к�
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
// ����NXP���û���¼��Ϣ
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

// �����������ݣ�������P2P�ӿڽ��������ݷ��͵��ͻ���
int RecvRealStream(int sock,int msessionid,int run)
{
	char RecvBuf[FRAME_BUF_SIZE] = {0};
	AV_VHD NxpAvVhd;
	int RecvBytes = 0;
	int res = 0;
	int TotalPackets = 0;
	while(run)
	{
		// ����AV_VHD
		memset(&NxpAvVhd, 0, AV_HEADER_LEN);
		RecvBytes = recv(sock, &NxpAvVhd,AV_HEADER_LEN, 0);
		if((RecvBytes <= 0)||(RecvBytes != AV_HEADER_LEN))
		{
			printf("Send Error!!\n");
			return -1;
		}
		// ����H.264֡����
		TotalPackets = 0;
		while(TotalPackets < NxpAvVhd.bSize)// ��ʱ��һ���Է��ͽ϶������ʱ��TCP�Ὣ�����ݰ��𿪷ֶ�η��͡�
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
		//P2P��������
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
		//P2P��������
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
	// ���յ�P2P�ͻ��˵Ĺر�������˳����߳�
	if(!pmediainfo->run)
	{
		close(sock);
		return NULL;
	}
	// ����socket
	sock = TcpClientCreate();
	if(sock == -1)
	{
		close(sock);
		return NULL;
	}
	// ������������(ͨ��)
	if(SendStreamChn(sock,StreamChn) == -1)
	{
		close(sock);
		return NULL;
	}
	// ��ȡ��Ʒ���к�
	if(RecvSN(sock) == -1)
	{
		close(sock);
		return NULL;
	}
	// �����û���Ϣ
	if(SendUsrInfo(sock,Usr,Pwd) == -1)
	{
		close(sock);
		return NULL;
	}
	// �����������ݣ�������P2P�ӿڷ��͵�P2P�ͻ���
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

	if(mediainfo->streamType == 1)  //����������
	{
		printf("play main stream!\n");
	}
	else if(mediainfo->streamType == 2) //����������
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

int ClientDisconnect(char *data) //�Զ������ر�����
{
	struct  m_mediainfo *mediainfo = (struct  m_mediainfo *)data;
	mediainfo->run = 0;  //ֹͣ������Ƶ�߳�
	
	int result = P2pStopService(mediainfo->msessionid);  //�ر�p2p����
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

	
	if(mediainfo->streamType == 1)  //����������
	{
		printf("play main stream!\n");
	}
	else if(mediainfo->streamType == 2) //����������
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
        mediainfo->run = 0; //ֹͣ������Ƶ
        return 0;
		
}
int RelayClientDisconnect(char *data)   //�Զ������ر�����
{
	struct  m_mediainfo *mediainfo = (struct  m_mediainfo *)data;
	mediainfo->run = 0;
	
	int result = P2pStopRelayService(mediainfo->msessionid);  //�ر�p2p����
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
		case  P2P_PLAY_REAL_STREAM:  //ʵʱ��
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
		case  P2P_PLAY_RELAY_STREAM: //ʵʱ��(����ת��ʽ)
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
	    if(SQLITE_OK != sqlite3_open(DATABASE_FILE, &db))//���ݿ��ʧ��,�ָ����ݿ⡣
	    {
	        break;
	    }
	    result = sqlite3_get_table(db, sqlcmd[0], &dbResult, &nRow, &nColumn, NULL);
	    if(SQLITE_OK != result)//��ѯĳ����ʧ�ܣ��ָ����ݿⲢ�˳���
	    {
	        break;
	    }
	    sqlite3_free_table(dbResult);
	    strcpy(UserInfo->ucPassWord, dbResult[nColumn + 1]);
	    result = sqlite3_get_table(db, sqlcmd[1], &dbResult, &nRow, &nColumn, NULL);
	    if(SQLITE_OK != result)//��ѯĳ����ʧ�ܣ��ָ����ݿⲢ�˳���
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

	int result =P2P_InitService(FREE_IP_ADDR, UserInfo.ucSerialNum,"admin",UserInfo.ucPassWord);   //arg[1]ΪP2P��������ַ��ĿǰΪwww.freeipc.com   arm[2]Ϊ�豸�����к�    "admin"��"admin"Ϊ�豸���û���������
	if(result<0)
	{
		printf("P2P_InitService erro!\n");
	}

	while(1)
	{
		sleep(30);
	}
	
}




