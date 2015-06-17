
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <net/if.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "DevDiscovery.h"
static pthread_t Discoveryid;

int StartDiscoveryThread()
{
    struct sockaddr_in addrto;
    struct sockaddr_in from;

    int rsockfd = -1;
    int wsockfd = -1;
    int rsl;
    char buff[DD_BUFF_LEN];
    const int opt = 1;
    const int len = sizeof(struct sockaddr_in);

    struct NET_CONFIG ncNetConfig;
    struct in_addr iaAddr;
    nettype response;

    unsigned int uiRtspPort;
    unsigned int uiHttpPort;
    unsigned int remotePort;
    sdk_comm_cfg_t	commInfo;
    do{
        //创建 UDP socket
        rsockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if(-1==rsockfd){
            Printf("Create rsockfd failed!");
            break;
        }
        wsockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if(-1==wsockfd)
        {
            Printf("Create wsockfd failed!");
            break;
        }
        //设置该套接字为广播类型，
        rsl = setsockopt(rsockfd, SOL_SOCKET, SO_BROADCAST, (char *)&opt, sizeof(opt));
        if(-1 == rsl)
        {
            Printf("set rsockfd SO_BROADCAST failed!");
            break;
        }
        rsl = setsockopt(wsockfd, SOL_SOCKET, SO_BROADCAST, (char *)&opt, sizeof(opt));
        if(-1 == rsl)
        {
            Printf("set wsockfd SO_BROADCAST failed!");
            break;
        }
        // 绑定地址
        memset(&addrto,0,sizeof(struct sockaddr_in));
        addrto.sin_family = AF_INET;
        addrto.sin_addr.s_addr = htonl(INADDR_ANY);
        addrto.sin_port = htons(BROADCAST_PORT);
        rsl = bind(rsockfd,(struct sockaddr *)&(addrto), sizeof(struct sockaddr_in));
        if(-1 == rsl)
        {
            Printf("bind rsockfd failed!");
            break;
        }
        addrto.sin_port = htons(0);
        rsl = bind(wsockfd,(struct sockaddr *)&(addrto), sizeof(struct sockaddr_in));
        if(-1 == rsl)
        {
            Printf("bind wsockfd failed!");
            break;
        }
        char* __restrict__ msg = CONST_MESSAGE;
        Printf("Start DevDescovery success!");
        while(1)
        {
            rsl = recvfrom(rsockfd, buff, DD_BUFF_LEN, 0, (struct sockaddr*)&from,(socklen_t*)&len);
            if(rsl<=0)
            {
                Printf("recv failed! skip, continue ...");
                usleep(10*1000);
                continue;
            }
            //fprintf(stderr,"ip:%s, prot:%d, %s\n",inet_ntoa(from.sin_addr),ntohs(from.sin_port),buff);
            rsl = memcmp(buff,msg,strlen(msg));
            if(0!=rsl) continue;

            /*reponse*/
            memset(&response,0,sizeof(nettype));
            sprintf((char*)response.message,"%s",msg);
            response.msg_type = 1;
            sprintf((char*)response.dev_type,"%s","HS_NVR");
            /*net config*/
            memset(&ncNetConfig,0,sizeof(struct NET_CONFIG));
            rsl = net_get_info(DD_IFace,&ncNetConfig);
            if(0!=rsl)
            {
                Printf("get net config failed!");
                break;
            }
            iaAddr.s_addr = ncNetConfig.ifaddr;
            sprintf((char*)response.ip_value,"%s",inet_ntoa(iaAddr));
            iaAddr.s_addr = ncNetConfig.netmask;
            sprintf((char*)response.netmask_value,"%s",inet_ntoa(iaAddr));
            response.mac_value[0] = ncNetConfig.mac[0];
            response.mac_value[1] = ncNetConfig.mac[1];
            response.mac_value[2] = ncNetConfig.mac[2];
            response.mac_value[3] = ncNetConfig.mac[3];
            response.mac_value[4] = ncNetConfig.mac[4];
            response.mac_value[5] = ncNetConfig.mac[5];
            /*dev name*/
            sprintf((char*)response.devname,"NVR111");
            response.uc_chs = configGetDisplayNum();
            /*port*/
            rsl = GetPort(&uiRtspPort,&uiHttpPort,&remotePort);
            if(0!=rsl)
            {
                Printf("get port failed!\n");
                break;
            }
            response.http_port = htonl(uiHttpPort);
            response.rtsp_port = htonl(uiRtspPort);
            response.remote_port = htonl(remotePort);
            from.sin_addr.s_addr = inet_addr("255.255.255.255");
            rsl = sendto(wsockfd,&response,sizeof(nettype),0,(struct sockaddr*)&from,len);
            if(rsl < 0)
            {
                Printf("send failed!");
            }
            usleep(40*1000);
        }
        DD_CLOSE_SOCK(rsockfd);
        DD_CLOSE_SOCK(wsockfd);
        DD_DEBUG("quit\n");
        return 0;
    }while(0);

    DD_CLOSE_SOCK(rsockfd);
    DD_CLOSE_SOCK(wsockfd);
    Printf("quit\n");
    return -1;
}

int discovery(void)
{
    int rsl;
    if(0!=Discoveryid) return -1;
    rsl = pthread_create(&Discoveryid,0,(void*(*)(void*))StartDiscoveryThread,0);
    return rsl;
}
