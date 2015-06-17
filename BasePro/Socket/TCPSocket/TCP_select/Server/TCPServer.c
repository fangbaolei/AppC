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

// �����߳�
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
	//htonl:��һ��32λ���������ֽ�˳��ת���������ֽ�˳��
	//INADDR_ANY:0.0.0.0����ʾ����IP��ַ���ڶ�IP����������豸�У�
	//                   �����ó���INADDR_ANYʱ����ôϵͳ����Ĭ�ϵ�����
	server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	// ���������޷��Ŷ�������ת���������ֽ�˳��
	server_sockaddr.sin_port = htons(PORT);
	server_len = sizeof(server_sockaddr);

	//����socket������ΪTCP��
	ServerFd = socket(AF_INET, SOCK_STREAM, 0);
	if (ServerFd == -1) 
	{
		printf("create server_socket error!\n");
		return (-1);
	}

	//fcntl:���ļ��������ṩ����,�˴���Ϊ������
	if (fcntl(ServerFd, F_SETFL, O_NONBLOCK) == -1) 
	{
		printf("Set server socket nonblock failed\n");
		MAC_CLOSE_SOCK(ServerFd);
		return (-1);
	}

	//��
	if (bind(ServerFd, (struct sockaddr *) &server_sockaddr, server_len) == -1) 
	{
		printf("bind PORT %d error!\n", ntohs(server_sockaddr.sin_port));
		MAC_CLOSE_SOCK(ServerFd);
		return (-1);
	}
	//����
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
	//����ÿ�����ù��ļ���Ԫ��
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
		//����
		len = recv(Msg_Connet[ConnectNum], buffer, BUF_LEN, 0);
		if(len == 0)// �յ���FIN�ֽڣ���ʾ�Է������ر�����
		{
			MAC_CLOSE_SOCK(Msg_Connet[ConnectNum]);
			FD_CLR(Msg_Connet[ConnectNum], &ConnectSet);
			continue;
		}
		if (len < 0) // ���մ���
		{
			usleep(10*1000);
			continue;
		}	
		//��ÿͻ��˵�IP��ַ
		getpeername(Msg_Connet[ConnectNum], (struct sockaddr*) &sockaddr,&SockAddrLen);
		printf("read data [%s] from Client %s on socket %d\n",buffer,inet_ntoa(sockaddr.sin_addr),Msg_Connet[ConnectNum]);
		//���ؽ��յ���������
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
	struct timeval Timeout; /* ����һ��ʱ�����������ʱ�� */

	MaxFd = ServerFd;
	
	while (1) 
	{

			Timeout.tv_sec = 3;
			Timeout.tv_usec = 0; /* ����select�ȴ������ʱ��Ϊ20��*/
			//ÿ�ζ�Ҫ�������ü��ϲ��ܼ����¼�
			FD_ZERO(&ConnectSet);
			FD_SET(ServerFd, &ConnectSet);
			//���Ѵ��ڵ�socket��������
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
					//��ʱ����������м���Ԫ�ز��ر�������ͻ��˵�socket
					FD_ZERO(&ConnectSet);
					for (ConnectNum = 0; ConnectNum < BACKLOG; ConnectNum++)
					{
						MAC_CLOSE_SOCK(Msg_Connet[ConnectNum]);
					}
					//�������ü���socket���ȴ�����
					FD_CLR(ServerFd, &ConnectSet);
					FD_SET(ServerFd, &ConnectSet);
					continue;
				}
				break;
				default:
				{
					//����Ƿ��������ӽ���
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
					{//�������ӵ�����ͨ��
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
