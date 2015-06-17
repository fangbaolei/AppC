#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "net/if.h"
#include <sys/ioctl.h>

#include "arpa/inet.h"
#include "linux/sockios.h"
int main(int argc,char *argv[])
{
struct sockaddr_in *addr;
struct ifreq ifr;
char*address;
int sockfd;
#if 1
char *name = "eth0";
if( strlen(name) >= IFNAMSIZ)
{
    printf("device name is error.\n"), exit(0);
}
strcpy( ifr.ifr_name, name);
#endif
 sockfd = socket(AF_INET,SOCK_DGRAM,0);
//get Mask
if( ioctl( sockfd, SIOCGIFNETMASK, &ifr) == -1)
printf("ioctl error.\n"), exit(0);
addr = (struct sockaddr_in *)&ifr.ifr_addr;
address = inet_ntoa(addr->sin_addr);
printf("Mask: %s\n",address);
}
