// TCP select客户端
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<time.h>

#define PORT 2456
#define SERVER_IP "127.0.0.1"

int main(void)
{
	int sock = 0;
	int res;
	int SockOptVal = 1;
	char StrCmd[20] = "hello!!";
	struct sockaddr_in serAddr;
	//填充sockaddr_in
	memset(&serAddr, 0, sizeof(serAddr));
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(PORT);
	serAddr.sin_addr.s_addr = inet_addr (SERVER_IP);
	//创建socket
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock < 0) 
	{
		printf("socket Error!");
		close(sock);
		return -1;
	}
	if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &SockOptVal, sizeof(int)) == -1)
	{
		close(sock);
		sock = -1;
		return -1;
	}
	if (connect(sock, (struct sockaddr *) &serAddr, sizeof(serAddr)) == -1) 
	{
		printf("connect Error!!\n");
		close(sock);
		return -1;
	}
	while(1)
	{
		res = send(sock, StrCmd,strlen(StrCmd)+1, 0);
		if (res <= 0) 
		{
			printf("Send Error!!\n");
			close(sock);
			return -1;
		}
		printf("Send:%s\n",StrCmd);
		memset(StrCmd,0,sizeof(StrCmd));
		res = recv(sock, StrCmd,sizeof(StrCmd), 0);
		if (res <= 0) 
		{
			printf("Send Error!!\n");
			close(sock);
			return -1;
		}
		printf("recv:%s\n",StrCmd);
		sleep(1);
	}
	return 0;
}
