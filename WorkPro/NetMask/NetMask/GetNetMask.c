#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <linux/sockios.h>
#include <errno.h>
int GetNetMask(char *EthName, unsigned int *NetMask)
{
    /*socket参数设置*/  
    int sockfd = 0; 
    struct ifreq ifr; 
    struct sockaddr_in sin;
    if( strlen(EthName) >= IFNAMSIZ)
    {
        printf("device EthName is error.\n");
        return -1;
    }
    strcpy( ifr.ifr_name, EthName);
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);  
    if (sockfd == -1)  
    {  
        perror("socket");  
        return -1;       
    }
    if (ioctl(sockfd, SIOCGIFNETMASK, &ifr) == -1)   
    {  
        perror("ioctl");  
        return -1;  
    }  
    memcpy(&sin, &ifr.ifr_addr, sizeof(sin));    
    *NetMask = ((struct sockaddr_in*)&ifr.ifr_addr)->sin_addr.s_addr;
    printf("get NetMask(%d:%d:%d:%d) success!!\r\n", (*NetMask)&0xff, (*NetMask>>8)&0xff, (*NetMask>>16)&0xff, (*NetMask>>24)&0xff);
    //sprintf(NetMask,"%s",inet_ntoa(sin.sin_addr));      	
    //printf("mask:%d\n", inet_ntoa(sin.sin_addr));
    close(sockfd);
    return 0;
}

/*  */
int netSetMask(char *pInterface, unsigned int mask)
{
	int sock = 0;
	struct ifreq ifr;

	if((pInterface == NULL) || (*pInterface == '\0'))
	{
		printf("set mask: pInterface == NULL\r\n");
		return -1;
	}

	if(mask == 0)
	{
		printf("set mask: mask == 0\r\n");
		return -1;
	}

	memset(&ifr, 0, sizeof(ifr));
	strncpy(ifr.ifr_name, pInterface, IFNAMSIZ);
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock <= 0)
	{
		printf("set mask: sock error, %s\r\n", strerror(errno));
		return -1;
	}

#if 0
	((struct sockaddr_in*)&ifr.ifr_netmask)->sin_family = PF_INET;
	((struct sockaddr_in*)&ifr.ifr_netmask)->sin_addr.s_addr = mask;
#else
	struct sockaddr_in si;

	memset(&si, 0, sizeof(struct sockaddr_in));
	si.sin_family = PF_INET;
	si.sin_addr.s_addr = mask;
	memcpy(&ifr.ifr_netmask, &si, sizeof(struct sockaddr_in));
#endif
	if(ioctl(sock, SIOCSIFNETMASK, &ifr) < 0)
	{
		printf("set mask(%d:%d:%d:%d):%s\r\n",
				(mask)&0xff, (mask>>8)&0xff, (mask>>16)&0xff, (mask>>24)&0xff, strerror(errno));
		close(sock);
		return -1;
	}
	else
	{
		printf("set mask(%d:%d:%d:%d): success\r\n", (mask)&0xff, (mask>>8)&0xff, (mask>>16)&0xff, (mask>>24)&0xff);
	}
	close(sock);

	return 0;
}

int main(void)
{
    unsigned int  NetMask[2] = {0};
    struct sockaddr_in sin;
    unsigned char *EthName = "eth0";
    GetNetMask(EthName,NetMask);
    netSetMask(EthName,*NetMask);
    //printf("----------NetMask:%\n",NetMask);
    return 0;
}
