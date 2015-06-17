/*
 * pubFun.c
 *
 *  Created on: Apr 15, 2014
 *      Author: root
 */

#include "pubFun.h"
#include <sys/socket.h>
#include <netinet/if_ether.h>
#include <net/if.h>
#include <linux/sockios.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>

int g_GetMAC(char *pMAC, const UINT uMACLen)			//get MAC address;
{
	int nReturn = RET_FAILED;
	char *device = "eth0";
	unsigned char macaddr[ETH_ALEN];
	struct ifreq req;
	int err,i;
	int s = socket(AF_INET,SOCK_DGRAM,0);
	strcpy(req.ifr_name,device);
	err = ioctl(s,SIOCGIFHWADDR,&req);
	close(s);
	if( err != -1)
	{
		memcpy(macaddr,req.ifr_hwaddr.sa_data,ETH_ALEN);
		for( i = 0; i < ETH_ALEN; i++)
		{
			printf("%02x:",macaddr[i]);
		}
		nReturn = RET_SUC;
	}
	return nReturn;
}

int g_GetGateway(char *pGateway,const UINT uGatewayLen)
{
	int nReturn = RET_FAILED;
	strcpy( pGateway,"192.168.0.99");
	nReturn = RET_SUC;
	return nReturn;
}

int g_SetGateway(const char *pGateway)
{
	int nReturn = RET_FAILED;
	return nReturn;
}

int g_GetIP(char *pIP,const UINT uIPLen)
{
	int nReturn = RET_FAILED;
	strcpy( pIP,"192.168.0.48");
	nReturn = RET_SUC;
	return nReturn;
}

int g_SetIP(const char *pIP)
{
	int nReturn = RET_FAILED;
	return nReturn;
}


int g_GetMediaURI(char *pURI, const UINT uURILen)
{
	int nReturn = RET_FAILED;
	if( pURI != NULL)
	{
		strncpy(pURI,"rtsp://192.168.0.48/media",uURILen);
		nReturn = RET_SUC;
	}
	return nReturn;
}
