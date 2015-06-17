#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <unistd.h>
int ConnectServer(int connectFd, struct sockaddr *pServerSockAddr ,int sockAddrLen, unsigned long timeOut)
{
	int iSave = fcntl(connectFd,F_GETFL);
	fcntl(connectFd, F_SETFL, iSave | O_NONBLOCK);


	if( 0 != connect( connectFd, pServerSockAddr, sockAddrLen) )
	{
// 使用select设置超时时间
		struct timeval timeOutVal;
		timeOutVal.tv_sec = timeOut;
		timeOutVal.tv_usec = 0;

		fd_set readdSet;
		fd_set writeSet;
		FD_ZERO(&readdSet);
		FD_ZERO(&writeSet);
		FD_SET(connectFd, &readdSet);
		FD_SET(connectFd, &writeSet);
		if(0 < select(connectFd+1, &readdSet, &writeSet, NULL, &timeOutVal))
		{
			//要重新设置为阻塞模式
			fcntl(connectFd, F_SETFL, iSave );

			return 0;
		}
		perror("connect() to the dyndns server");

		return -1;
	}
	return 0;
	
}

int GetMessageFromServer(int sockfd, char *pbuf, int *plen )
{
	int i = 0,  retval = 0;
	int recvLen = 0;
	struct timeval timeout;
	int *len = plen;
	fd_set ReadSet;

	for( i=0; i<10; i++ )
	{
		// FD_SET()应该在每次循环时都被调用， select()超时readSet会被清空
		// 初始化套接字
		FD_ZERO(&ReadSet);
		FD_SET( sockfd, &ReadSet );

		//把超时时间改为1秒， 防止网络太慢时服务端返回的应答抓不到。
		//在公司服务器(www.dvrdydns.com)上遇到过这种情况：超时时间设置为10000微妙，通过外网一致得不到服务器响应，内网却可以
		//当延长超时时间后就正常了。
		timeout.tv_sec  = 3;
		timeout.tv_usec = 0;

		retval = select(sockfd+1, &ReadSet, NULL, NULL, &timeout );
		if(retval == -1)//错误，退出程序
		{
			return -1;
		}
		else if( retval == 0 )//再次轮询
		{
			continue;
		}

		if( FD_ISSET( sockfd, &ReadSet ) )// 测试是否有网络数据
		{
			if ( recvLen > *len)// 数据过多
			{
				printf("%s:%s:%d, recvLen=%d, len=%d", __FUNCTION__, __FILE__ ,__LINE__, recvLen, *len);
				return -1;
			}

			retval = recv( sockfd, pbuf + recvLen, *len - recvLen, 0 );// 接收数据
			if(retval== -1 )
			{
				return -1;
			}
			if( strstr(pbuf, "\r\n\r\n"))// 搜索接收的数据中是否有"\r\n\r\n"字符串
			{
				recvLen += retval;
				pbuf[recvLen] = '\0';
				*len = recvLen;
				return 0;
			}

			recvLen += retval;

		}
	}
	return -1;
}


int  GetExternalIp(char *pIPAddr )
{
	struct sockaddr_in Server;
	int serverfd;
	struct hostent *pServerhe = NULL;
	char package[100]={0};
	char *pReceiveBuf = malloc(4096);
	int recvLen = 4096;

	pServerhe = gethostbyname("checkip.dyndns.org");
	if( NULL == pServerhe )
	{
		printf("gethostbyname() error\n");
		printf("%s:%s:%d, 不能解析域名:%s\n", __FUNCTION__, __FILE__, __LINE__,"checkip.dyndns.org");
		return -1;
	}

	memset(&Server, 0, sizeof(struct sockaddr_in));
	Server.sin_family = AF_INET;
	Server.sin_port =  htons(80);
	memcpy(&(Server.sin_addr), *((struct in_addr **)pServerhe->h_addr_list), sizeof(struct in_addr));

	serverfd = socket(AF_INET, SOCK_STREAM, 0);
	if(serverfd== -1 )
	{
		perror("socket()");
		return -1;
	}
	if(ConnectServer(serverfd, (struct sockaddr*)&Server, sizeof(struct sockaddr), 3) != 0)
	{
		close(serverfd);
		perror("connect():");
		return -1;
	}	

	strcpy(package,"GET http://checkip.dyndns.org/HTTP/1.0\r\n\r\n");

	//send Http request
	if ( -1 == send(serverfd,(char*)package,strlen(package),0))
	{
		close(serverfd);
		perror("send():");
		return -1;
	}

	memset(pReceiveBuf, 0, 4096);

	//接收从服务器发来的IP信息
	if( 0 != GetMessageFromServer(serverfd, pReceiveBuf, &recvLen) )
 	{
 		close(serverfd);
 		if ( NULL != pReceiveBuf)
 		{
 			free(pReceiveBuf);
 			pReceiveBuf = NULL;
 		}
 		return -1;
 	}


	if ( 0 < recvLen ) 
	{
		char *pIP = strstr(pReceiveBuf ,"Current IP Address:");
		if(pIP != NULL)
		{
			pIP += 19;
			int a=0, b=0, c=0, d=0;
			sscanf(pIP, "%d.%d.%d.%d", &a, &b,&c,&d);
			snprintf(pIPAddr, 16,"%d.%d.%d.%d", a, b, c, d);
		}	
	}	

//	printf("外网IP地址:pIPAddr ===%s\n", pIPAddr);	//外网IP地址::pIPAddr ===121.35.197.233
	
	if ( NULL != pReceiveBuf)
	{
		free(pReceiveBuf);
		pReceiveBuf = NULL;
	}
	close( serverfd );
	return 0;

}

int main(void)
{
	char ExIp[16] = {0};
	GetExternalIp(ExIp);
	printf("ipaddr:%s\n" ,ExIp);
	return 0;
}
