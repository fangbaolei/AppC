#ifndef DEVDISCOVERY_H
#define DEVDISCOVERY_H

#ifdef __cplusplus
extern "C"
{
#endif
#define _DD_DEBUG_ 1

#if _DD_DEBUG_
#define DD_DEBUG(fmt,args...) printf("DEBUG %s-%d: " fmt "\n",__FUNCTION__,__LINE__,## args);
#else
#define DD_DEBUG(fmt,args...)
#endif

#define DD_CLOSE_SOCK(sock) \
    shutdown(sock,2); \
    close(sock); \
    sock = -1;

#define DD_BUFF_LEN 500
#define DD_IFace "eth0"
#define CONST_MESSAGE "search....."
#define BROADCAST_PORT 6789


typedef struct netparam {
    unsigned char  message[12];
    unsigned char  msg_type;
    unsigned char  dev_type[10];
    unsigned char  mac_value[7];
    unsigned char  netmask_value[30];
    unsigned char  ip_value[30];
    unsigned char  devname[64];
    unsigned int   http_port;
    unsigned int   rtsp_port;
    unsigned char  uc_chs;         //      //111209
    unsigned char  uc_subType;     //  device  type     //111209     1:IPNC  0:ethers
    unsigned char  reserve[9];
    unsigned char  devMode[32];
    unsigned int   remote_port;
} nettype;
//
typedef struct broadparam {
 unsigned char message[12];
 unsigned char msg_type;   //  BROAD_MODIFY_PARAM   3  //IP
 unsigned char ipaddress[48];
 unsigned char ipaddress_new[48];
 unsigned char subnetmask[48];
 unsigned char gateway[48];
 unsigned char dns[48];
 unsigned char useDHCP;   // 1DHCP 0
 unsigned char useDNSfromDHCP; //  1DNS DHCP 0
 unsigned char res;
//}BroadParam, *pBroadParam;
}broadcasttype;


int discovery(void);



#ifdef __cplusplus
}
#endif
#endif
