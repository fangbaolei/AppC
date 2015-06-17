#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include "TCPServer.h"

#define BACKLOG   3
#define PORT  2456
#define BUF_LEN  128

typedef void *(*CallBackTread)(void*);

// 创建线程
int P2P_CreatThread(CallBackTread func)
{
	int iRet=0;
       pthread_t		 threadID;
    	pthread_attr_t   attr;	
	pthread_attr_init(&attr);	
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	iRet=pthread_create(&threadID,&attr,func,NULL);
	if(iRet != 0)
	{
		(void)pthread_attr_destroy(&attr);
		return -1;
	}
	return 0;
}
int TCP_Create(void)
{
	struct sockaddr_in server_sockaddr;
	int server_len;
	int ServerFd;

	memset(&server_sockaddr, 0, sizeof(server_sockaddr));
	server_sockaddr.sin_family = AF_INET;
	//htonl:将一个32位数从主机字节顺序转换成网络字节顺序
	//INADDR_ANY:0.0.0.0，表示任意IP地址。在多IP或多网卡的设备中，
	//                   当设置成了INADDR_ANY时，那么系统将绑定默认的网卡
	server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	// 将主机的无符号短整形数转换成网络字节顺序
	server_sockaddr.sin_port = htons(PORT);
	server_len = sizeof(server_sockaddr);

	//建立socket，类型为TCP流
	ServerFd = socket(AF_INET, SOCK_STREAM, 0);
	if (ServerFd == -1) 
	{
		printf("create server_socket error!\n");
		return (-1);
	}

	//fcntl:对文件描述符提供控制,此处设为非阻塞
	if (fcntl(ServerFd, F_SETFL, O_NONBLOCK) == -1) 
	{
		printf("Set server socket nonblock failed\n");
		MAC_CLOSE_SOCK(ServerFd);
		return (-1);
	}

	//绑定
	if (bind(ServerFd, (struct sockaddr *) &server_sockaddr, server_len) == -1) 
	{
		printf("bind PORT %d error!\n", ntohs(server_sockaddr.sin_port));
		MAC_CLOSE_SOCK(ServerFd);
		return (-1);
	}
	//监听
	if (listen(ServerFd, BACKLOG) == -1) 
	{
		printf("listen error!\n");
		MAC_CLOSE_SOCK(ServerFd);
		return (-1);
	}
	return ServerFd;
	
}
int NewConnection(int ServerFd,int Msg_Connet[BACKLOG])
{	
	int new_cli_fd;
	int ConnectNum;
	socklen_t  socklen;
	struct sockaddr_in cli_sockaddr;
	socklen = sizeof(cli_sockaddr);
	new_cli_fd = accept(ServerFd,(struct sockaddr *) &cli_sockaddr, &socklen);
	if (new_cli_fd < 0) 
	{
		printf("Accept error\n");
		return -1;
	}
	printf("open communication with  Client %s on socket %d\n",inet_ntoa(cli_sockaddr.sin_addr), new_cli_fd);
	for (ConnectNum = 0; ConnectNum < BACKLOG; ConnectNum++) 
	{
		if (Msg_Connet[ConnectNum] == -1) 
		{
			Msg_Connet[ConnectNum] = new_cli_fd;
			break;
		}
	}
	return new_cli_fd;
}

int KeepConnection(int Msg_Connet[BACKLOG],	fd_set ConnectSet)
{
	int ConnectNum;
	int len = 0;
	char buffer[BUF_LEN];
	struct sockaddr_in sockaddr;
	socklen_t SockAddrLen = sizeof(sockaddr);
	//遍历每个设置过的集合元素
	for (ConnectNum = 0; ConnectNum < BACKLOG; ConnectNum++) 
	{ 	
		if (Msg_Connet[ConnectNum] == -1)
		{
			continue;
		}
		if (!FD_ISSET(Msg_Connet[ConnectNum], &ConnectSet)) 
		{
			continue;
		}
		//接收
		len = recv(Msg_Connet[ConnectNum], buffer, BUF_LEN, 0);
		if(len == 0)// 收到了FIN分节，表示对方主动关闭连接
		{
			MAC_CLOSE_SOCK(Msg_Connet[ConnectNum]);
			FD_CLR(Msg_Connet[ConnectNum], &ConnectSet);
			continue;
		}
		if (len < 0) // 接收错误
		{
			usleep(10*1000);
			continue;
		}	
		//获得客户端的IP地址
		getpeername(Msg_Connet[ConnectNum], (struct sockaddr*) &sockaddr,&SockAddrLen);
		printf("read data [%s] from Client %s on socket %d\n",buffer,inet_ntoa(sockaddr.sin_addr),Msg_Connet[ConnectNum]);
		//返回接收到到的数据
		len = send(Msg_Connet[ConnectNum], buffer, strlen(buffer), 0);
		if (len < 0) 
		{
			printf("Send error\n");
			return -1;
		}
		printf("write data [%s] to Client %s on socket %d\n",buffer, inet_ntoa(sockaddr.sin_addr),Msg_Connet[ConnectNum]);
	}
	return 0;

}
int TCP_Select(int ServerFd)
{
	int Ret = 0;
	int MaxFd = 0;
	int ConnectNum = 0;
	fd_set ConnectSet;
	int Msg_Connet[BACKLOG] = {-1};
	int NewFd = 0;
	struct timeval Timeout; /* 声明一个时间变量来保存时间 */

	MaxFd = ServerFd;
	
	while (1) 
	{

			Timeout.tv_sec = 3;
			Timeout.tv_usec = 0; /* 设置select等待的最大时间为20秒*/
			//每次都要重新设置集合才能激发事件
			FD_ZERO(&ConnectSet);
			FD_SET(ServerFd, &ConnectSet);
			//对已存在到socket重新设置
			for (ConnectNum = 0; ConnectNum < BACKLOG; ConnectNum++)
			{
				if (Msg_Connet[ConnectNum] != -1) 
				{
					FD_SET(Msg_Connet[ConnectNum], &ConnectSet);
				}
			}
			Ret = select(MaxFd + 1, &ConnectSet, NULL, NULL, &Timeout);
			switch (Ret) 
			{
				case -1:
				{
					printf("Select error\n");
					return -1;
				}
				break;
				case 0:
				{
					printf("Select time_out\n");
					//超时则清理掉所有集合元素并关闭所有与客户端的socket
					FD_ZERO(&ConnectSet);
					for (ConnectNum = 0; ConnectNum < BACKLOG; ConnectNum++)
					{
						MAC_CLOSE_SOCK(Msg_Connet[ConnectNum]);
					}
					//重新设置监听socket，等待链接
					FD_CLR(ServerFd, &ConnectSet);
					FD_SET(ServerFd, &ConnectSet);
					continue;
				}
				break;
				default:
				{
					//检测是否有新连接建立
					if (FD_ISSET(ServerFd, &ConnectSet)) 
					{ //new connection
						NewFd =NewConnection(ServerFd,Msg_Connet);
						FD_SET(NewFd, &ConnectSet);
						if (MaxFd < NewFd) 
						{
							MaxFd = NewFd;
						}
						continue;
					} 
					else 
					{//已有连接的数据通信
						KeepConnection(Msg_Connet, ConnectSet);
					}
				}
				break;
			}
		}

}
void * TcpServer(void *param) 
{
	int ServerFd = 0;
	ServerFd = TCP_Create();
	if(ServerFd == -1)
	{
		return NULL;
	}
	TCP_Select(ServerFd);
	return NULL;
}

int main(void) 
{
	if(P2P_CreatThread(TcpServer)<0)
	{
		printf("PlayRealStream P2P_CReatThread erro!\n");
		return -1;
	}
	while(1)
	{
		sleep(10);
	}
	return 0;
}
