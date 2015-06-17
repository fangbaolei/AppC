#include <netdb.h>
#include <linux/rtnetlink.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <fcntl.h>

#include <sys/socket.h>
#include <linux/if.h>
#include <linux/route.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

#define PROCNET_ROUTE_PATH		"/proc/net/route"
int net_search_gateway(char *buf, in_addr_t *gate_addr)
{
	char iface[16];
	unsigned long dest, gate;
	int iflags;

	sscanf(buf, "%s\t%08lX\t%08lX\t%8X\t", iface, &dest, &gate, &iflags);
	printf("net_search_gateway:%s, %lX, %lX, %X\n", iface, dest, gate, iflags);
	if ( (iflags & (RTF_UP | RTF_GATEWAY)) == (RTF_UP | RTF_GATEWAY) ) {
		*gate_addr = gate;
		return 0;
	}
	return -1;
}

in_addr_t net_get_gateway(void)
{
	in_addr_t gate_addr;
	char buff[132];
	FILE *fp = fopen(PROCNET_ROUTE_PATH, "r");

	if (!fp) {
		//DBG_ERR(PROCNET_ROUTE_PATH);
		printf("INET (IPv4) not configured in this system.\n");
		return (INADDR_ANY);
	}
	fgets(buff, 130, fp);
	while (fgets(buff, 130, fp) != NULL) {
		if (net_search_gateway(buff, &gate_addr) == 0) {
			fclose(fp);
			return gate_addr;
		}
	}
	fclose(fp);
	return (INADDR_ANY);
}

int main(void)
{
	in_addr_t GateWay;
	GateWay = net_get_gateway();
    printf("get ip(%d.%d.%d.%d) success!\r\n", (GateWay)&0xff, (GateWay>>8)&0xff, (GateWay>>16)&0xff, (GateWay>>24)&0xff);
	return 0;
}
