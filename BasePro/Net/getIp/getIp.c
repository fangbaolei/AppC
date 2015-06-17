#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include <sys/socket.h>
#include <net/if.h>
#include <net/route.h>
#include <netinet/in.h>

#include <asm/types.h>
#include <netinet/ether.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
/* Ip */
int netGetIp(char *pInterface, unsigned int *ip)
{
	int sock = 0;
	struct ifreq ifr;

	if((pInterface == NULL) || (*pInterface == '\0'))
	{
		printf("get ip: pInterface == NULL\r\n");
		return -1;
	}

	memset(&ifr, 0, sizeof(ifr));
	strncpy(ifr.ifr_name, pInterface, IFNAMSIZ);
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock <= 0)
	{
		printf("get ip: sock error, %s\r\n", strerror(errno));
		return -1;
	}

#if 0
	((struct sockaddr_in*)&ifr.ifr_addr)->sin_family = PF_INET;
#else
	struct sockaddr_in si;

	memset(&si, 0, sizeof(struct sockaddr_in));
	si.sin_family = PF_INET;
	memcpy(&ifr.ifr_addr, &si, sizeof(struct sockaddr_in));
#endif
//	((struct sockaddr_in*)&ifr.ifr_addr)->sin_addr.s_addr = ip;
	if(ioctl(sock, SIOCGIFADDR, &ifr) < 0)
	{
		printf("get ip error: %s\r\n", strerror(errno));
		close(sock);
		return -1;
	}
	else
	{
		*ip = ((struct sockaddr_in*)&ifr.ifr_addr)->sin_addr.s_addr;
		printf("get ip(%d.%d.%d.%d) success!\r\n", (*ip)&0xff, (*ip>>8)&0xff, (*ip>>16)&0xff, (*ip>>24)&0xff);
	}
	close(sock);
	return 0;
}
int main(void)
{
    char *EtheName = "eth0";
    unsigned int Ip[40] = {0};
    netGetIp("eth0", Ip);
    if()
    printf("=========get Ip(%d.%d.%d.%d) success!\r\n", (*Ip)&0xff, (*Ip>>    8)&0xff, (*Ip>>16)&0xff, (*Ip>>24)&0xff);

}
