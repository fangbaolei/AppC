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

const static char table64[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
void Base64Encode(const char *InStr, char *OutStr)
{
    unsigned char ibuf[3] = {0};
    unsigned char obuf[4] = {0};
    int i = 0;
    int inputparts = 0;

    while(*InStr) 
    {   
        for (i =  0; i < 3; i++) 
        {   
            if(*InStr) 
            {   
                inputparts++;
                ibuf[i] = *InStr;
                InStr++;
            }   
            else
            {
                ibuf[i] = 0;
            }
        }

        obuf [0] = (ibuf [0] & 0xFC) >> 2;
        obuf [1] = ((ibuf [0] & 0x03) << 4) | ((ibuf [1] & 0xF0) >> 4);
        obuf [2] = ((ibuf [1] & 0x0F) << 2) | ((ibuf [2] & 0xC0) >> 6);
        obuf [3] = ibuf [2] & 0x3F;

          switch(inputparts)
          {
              case 1: /* only one byte read */
                  sprintf(OutStr, "%c%c==",
                      table64[obuf[0]],
                      table64[obuf[1]]);
                  break;
              case 2: /* two bytes read */
                  sprintf(OutStr, "%c%c%c=",
                      table64[obuf[0]],
                      table64[obuf[1]],
                      table64[obuf[2]]);
                  break;
              default:
                  sprintf(OutStr, "%c%c%c%c",
                      table64[obuf[0]],
                      table64[obuf[1]],
                      table64[obuf[2]],
                      table64[obuf[3]] );
              break;
        }
        OutStr += 4;
    }
    *OutStr=0;
}

int ConnectServer(int connectFd, struct sockaddr *pServerSockAddr ,int sockAddrLen, unsigned long timeOut)
{
	int iSave = fcntl(connectFd,F_GETFL);
	fcntl(connectFd, F_SETFL, iSave | O_NONBLOCK);


	if( 0 != connect( connectFd, pServerSockAddr, sockAddrLen) )
	{
// ʹ��select���ó�ʱʱ��
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
			//Ҫ��������Ϊ����ģʽ
			fcntl(connectFd, F_SETFL, iSave );

			return 0;
		}
		perror("connect() to the ddns server");

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
		// FD_SET()Ӧ����ÿ��ѭ��ʱ�������ã� select()��ʱreadSet�ᱻ���
		// ��ʼ���׽���
		FD_ZERO(&ReadSet);
		FD_SET( sockfd, &ReadSet );

		//�ѳ�ʱʱ���Ϊ1�룬 ��ֹ����̫��ʱ����˷��ص�Ӧ��ץ������
		//�ڹ�˾������(www.dvrdydns.com)�������������������ʱʱ������Ϊ10000΢�ͨ������һ�µò�����������Ӧ������ȴ����
		//���ӳ���ʱʱ���������ˡ�
		timeout.tv_sec  = 3;
		timeout.tv_usec = 0;

		retval = select(sockfd+1, &ReadSet, NULL, NULL, &timeout );
		if(retval == -1)//�����˳�����
		{
			return -1;
		}
		else if( retval == 0 )//�ٴ���ѯ
		{
			continue;
		}

		if( FD_ISSET( sockfd, &ReadSet ) )// �����Ƿ�����������
		{
			if ( recvLen > *len)// ���ݹ���
			{
				printf("%s:%s:%d, recvLen=%d, len=%d", __FUNCTION__, __FILE__ ,__LINE__, recvLen, *len);
				return -1;
			}

			retval = recv( sockfd, pbuf + recvLen, *len - recvLen, 0 );// ��������
			if(retval== -1 )
			{
				return -1;
			}
			if( strstr(pbuf, "\r\n\r\n"))// �������յ��������Ƿ���"\r\n\r\n"�ַ���
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
		printf("%s:%s:%d, ���ܽ�������:%s\n", __FUNCTION__, __FILE__, __LINE__,"checkip.dyndns.org");
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

	//���մӷ�����������IP��Ϣ
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

//	printf("����IP��ַ:pIPAddr ===%s\n", pIPAddr);	//����IP��ַ::pIPAddr ===121.35.197.233
	
	if ( NULL != pReceiveBuf)
	{
		free(pReceiveBuf);
		pReceiveBuf = NULL;
	}
	close( serverfd );
	return 0;

}
// DDNS��socketͨ��
int DdnsSocketCom(const char *DdnsCmdBuf,const char *DomainName)
{
	struct sockaddr_in ser_addr;
	int sockfd = 0;
	char ReceiveBuf[1024] = {0};
	int  len = 0,ret = 0;
       struct hostent *phstt;

	phstt = gethostbyname(DomainName);
       if (NULL == phstt)
	{
	    printf("gethostbyname() error\n");
		printf("%s:%s:%d, ���ܽ�������:%s\n", __FUNCTION__, __FILE__, __LINE__,"members.dyndns.org");
		return -1;//�޷������õ�ServerIP
	}
	else
	{
		printf("gethostbyname() sucssess!\n");
	}

	 // ��ʼ��socket
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port =  htons(80);
	memcpy(&(ser_addr.sin_addr), *((struct in_addr **)phstt->h_addr_list), sizeof(struct in_addr));
	memset(ser_addr.sin_zero,0, sizeof(ser_addr.sin_zero));
    // ����socket
       sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if( -1 == sockfd )
	{
		perror(" socket() error\n");
		return -1;
	}	 
    // ����DNS������
    // ����DNS
	if(ConnectServer(sockfd, (struct sockaddr*)&ser_addr, sizeof(struct sockaddr), 10) != 0)
	{
		perror("connect()");		
		close(sockfd);
		return -1;
	}
	// ��������
	if(send(sockfd, DdnsCmdBuf, strlen(DdnsCmdBuf), 0) == -1)
	{
		perror("send() data to server");
		close(sockfd);
		return -1;
	}
	// ����
	len=sizeof(ReceiveBuf);
	ret=GetMessageFromServer(sockfd,ReceiveBuf,&len);
	close(sockfd);
	if(ret != 0)
	{
		return ret;
	}
	printf("return:\n%s\n",ReceiveBuf);
	return 0;
}
int DdnsInfo(char *DdnsCmdBuf,  int Cmdlen)
{
	char ExIp[16] = {0};
	//char Src[512] = "HrSpdSV:xc12345";
	char Src[512] = {0};
    char Dst[512] = {0};
	sprintf(Src,"%s:%s","HrSpdSV","xc12345");
	printf("Src:%s\n",Src);
	Base64Encode(Src,Dst);
	printf("Base64 encode :%s\n", Dst);
    // ��ȡ����IP
	if(GetExternalIp(ExIp) == -1)
	{
		printf("Get external IP fail!\n");
		return -1;
	}
	printf("ipaddr:%s\n" ,ExIp);
	snprintf(DdnsCmdBuf,Cmdlen-1,"GET /ph/update?myip=%s HTTP/1.0\r\n""Host: ddns.oray.com\r\n""Authorization: Basic %s\r\n""User-Agent: Oray""\r\n\r\n",ExIp,Dst);
	printf("DDNS_CMD:\n%s",DdnsCmdBuf);
}

int main(void)
{
	char DdnsCmdBuf[1024] = {0};
	char *DomainName = "ddns.oray.com";
	DdnsInfo(DdnsCmdBuf,sizeof(DdnsCmdBuf));
	DdnsSocketCom(DdnsCmdBuf,DomainName);
   
	return 0;
}
