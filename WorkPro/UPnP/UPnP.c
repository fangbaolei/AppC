#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>  
#include <net/if.h>  
#include <arpa/inet.h> 
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#define  MAXINTERFACES  16
#define  RECV_LEN       2048
/******************
函数功能：SOAP消息体格式--新增自动映射端口


******************/
int SOAPMsgBodyAddMap(char *HostAddr, int PortNum, char *MsgBody)
{
	char SOAPBody[20][100] = {{0}};
    int i = 0, j = 0;
    int BodySize = 0;
	strcpy(SOAPBody[i++], "<?xml version=\"1.0\"?>\r\n");
	strcpy(SOAPBody[i++], "<s:Envelope\r\n");
        strcpy(SOAPBody[i++], "xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\"\r\n");
	strcpy(SOAPBody[i++], "s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\">");
	strcpy(SOAPBody[i++], "<s:Body>\r\n");
	strcpy(SOAPBody[i++], "<u:AddPortMapping xmlns:u=\"urn:schemas-upnp-org:service:WANIPConnection:1\">\r\n");
	strcpy(SOAPBody[i++], "<NewRemoteHost></NewRemoteHost>\r\n");
	sprintf(SOAPBody[i++], "<NewExternalPort>%d</NewExternalPort>\r\n", PortNum);
	strcpy(SOAPBody[i++], "<NewProtocol>TCP</NewProtocol>\r\n");
        sprintf(SOAPBody[i++], "<NewInternalPort>%d</NewInternalPort>\r\n", PortNum);
        sprintf(SOAPBody[i++], "<NewInternalClient>%s</NewInternalClient>\r\n", HostAddr);
	strcpy(SOAPBody[i++], "<NewEnabled>1</NewEnabled>\r\n");
	strcpy(SOAPBody[i++], "<NewPortMappingDescription>[IMAGIATEKIPCAM]</NewPortMappingDescription>\r\n");
	strcpy(SOAPBody[i++], "<NewLeaseDuration>0</NewLeaseDuration>\r\n");
        strcpy(SOAPBody[i++], "</u:AddPortMapping>\r\n");
	strcpy(SOAPBody[i++], "</s:Body>\r\n");
	strcpy(SOAPBody[i++], "</s:Envelope>\r\n");
        for(j = 0; j < i; j++)
        {
           strcat(MsgBody, SOAPBody[j]);
        }
        BodySize = strlen(MsgBody);
        return BodySize;
}

/***********************
函数功能： SOAP消息体格式--删除自动端口映射


***********************/
int SOAPMsgBodyRmMap(char *HostAddr, int PortNum, char *MsgBody)
{
	char SOAPBody[20][100] = {{0}};
    int i = 0, j = 0;
    int BodySize = 0;
	strcpy(SOAPBody[i++], "<?xml version=\"1.0\"?>\r\n");
	strcpy(SOAPBody[i++], "<s:Envelope\r\n");
        strcpy(SOAPBody[i++], "xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\"\r\n");
	strcpy(SOAPBody[i++], "s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\">");
	strcpy(SOAPBody[i++], "<s:Body>\r\n");
	strcpy(SOAPBody[i++], "<u:DeletePortMapping xmlns:u=\"urn:schemas-upnp-org:service:WANIPConnection:1\">\r\n");
	strcpy(SOAPBody[i++], "<NewRemoteHost></NewRemoteHost>\r\n");
	sprintf(SOAPBody[i++], "<NewExternalPort>%d</NewExternalPort>\r\n", PortNum);
	strcpy(SOAPBody[i++], "<NewProtocol>TCP</NewProtocol>\r\n");
        strcpy(SOAPBody[i++], "</u:DeletePortMapping>\r\n");
	strcpy(SOAPBody[i++], "</s:Body>\r\n");
	strcpy(SOAPBody[i++], "</s:Envelope>\r\n");
        for(j = 0; j < i; j++)
        {
           strcat(MsgBody, SOAPBody[j]);
        }
        BodySize = strlen(MsgBody);
        return BodySize;
}

/*********************
函数功能：HTTP POST数据包，不带M-/Mani头。添加映射端口号。




***********************/
void HttpPOSTAddMap(char *HostAddr, char *RouteAddr, int PortNum, char *POSTMsg)
{
    char SOAPMsg[800] = {0};
    char POSTHead[8][100] = {{0}};
    int SOAPBodySize = 0;
    int i = 0, j = 0;
    SOAPBodySize = SOAPMsgBodyAddMap(HostAddr, PortNum, SOAPMsg);
    printf("SOAPBodySize:%d\n", SOAPBodySize);
    strcpy(POSTHead[i++], "POST /ipc HTTP/1.1\r\n"); 
    sprintf(POSTHead[i++], "HOST: %s:1900\r\n", RouteAddr);
    sprintf(POSTHead[i++], "CONTENT-LENGTH: %d\r\n", SOAPBodySize);
    strcpy(POSTHead[i++], "Content-Type: text/xml; charset=\"utf-8\"\r\n");
    strcpy(POSTHead[i++], "SOAPACTION: \"urn:schemas-upnp-org:service:WANIPConnection:1#AddPortMapping\"\r\n\r\n");
    for(j = 0; j < i; j++)
    {
        strcat(POSTMsg, POSTHead[j]);
    }
    printf("sizeof(POSTMsg):%d\n", strlen(POSTMsg));
    
    strcat(POSTMsg, SOAPMsg);
    printf("POSGMsg:\n%s", POSTMsg);
}

/************************
函数功能：HTTP POST数据包，不带M-/Man头。删除映射的端口号



***************************/
void HttpPOSTDelMap(char *HostAddr, char *RouteAddr, int PortNum, char *POSTMsg)
{
    char SOAPMsg[800] = {0};
    char POSTHead[8][100] = {{0}};
    int SOAPBodySize = 0;
    int i = 0, j = 0;

    SOAPBodySize = SOAPMsgBodyRmMap(HostAddr, PortNum, SOAPMsg);
    printf("SOAPBodySize:%d\n", SOAPBodySize);
    strcpy(POSTHead[i++], "POST /ipc HTTP/1.1\r\n");
    sprintf(POSTHead[i++], "HOST: %s:1900\r\n", RouteAddr);
    sprintf(POSTHead[i++], "CONTENT-LENGTH: %d\r\n", SOAPBodySize);
    strcpy(POSTHead[i++], "Content-Type: text/xml; charset=\"utf-8\"\r\n");
    strcpy(POSTHead[i++], "SOAPACTION: \"urn:schemas-upnp-org:service:WANIPConnection:1#DeletePortMapping\"\r\n\r\n");
    
    for(j = 0; j < i; j++)
    {
        strcat(POSTMsg, POSTHead[j]);
    }
    printf("sizeof(POSTMsg):%d\n", strlen(POSTMsg));
   
    strcat(POSTMsg, SOAPMsg);
    printf("POSGMsg:\n%s", POSTMsg);
}

/*************************
函数功能：获取本地IP地址


**************************/
char* GetLocalIp()    
{          
    char *ip = NULL;    
    int fd, intrface;      
    struct ifreq buf[MAXINTERFACES];      
    struct ifconf ifc;      
  
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) >= 0)      
    {      
        ifc.ifc_len = sizeof(buf);      
        ifc.ifc_buf = (caddr_t)buf;      
        if (!ioctl(fd, SIOCGIFCONF, (char *)&ifc))      
        {      
            intrface = ifc.ifc_len / sizeof(struct ifreq);      
  
            while (intrface-- > 0)      
            {      
                if (!(ioctl (fd, SIOCGIFADDR, (char *) &buf[intrface])))      
                {      
                    ip=(inet_ntoa(((struct sockaddr_in*)(&buf[intrface].ifr_addr))->sin_addr));      
                    break;    
                }                          
            }    
        }      
        close (fd);  
        printf("local ipaddr:%s\n", ip);
        return ip;      
    }    
        return ip;      
}

/************************
函数功能： UDP通信



*************************/
char UDPCommunicate(char *HostIP, char *DstIP, int HostPort, int DstPort, char *UDPData)
{
    int Sockfd;
    int set;
    struct sockaddr_in SrcAddr, DstAddr;
    int RecvNum = 0;
    socklen_t DstLen = 0;
    char RecvBuf[RECV_LEN] = {0};
    struct timeval outtime = {2, 0};
    //初始化网络参数 -- 本地
    bzero(&SrcAddr, sizeof(SrcAddr));
    SrcAddr.sin_family = AF_INET;
    SrcAddr.sin_addr.s_addr = inet_addr(HostIP);
    SrcAddr.sin_port = htons(1234);
    // 初始化网络参数--路由器
    bzero(&DstAddr, sizeof(DstAddr));
    DstAddr.sin_family = AF_INET;
    DstAddr.sin_addr.s_addr = inet_addr(DstIP);
    DstAddr.sin_port = htons(1900);
    // 创建一个UDP Socket 
    if((Sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        printf("Creat socke error!\n");
        close(Sockfd);
        return -1;
    }
    //x=fcntl(Sockfd,F_GETFL,0);
    //fcntl(Sockfd,F_SETFL,x | O_NONBLOCK);
    set=setsockopt(Sockfd,SOL_SOCKET,SO_RCVTIMEO,&outtime,sizeof(outtime));
	if(set!=0)
	{
        close(Sockfd);
	    return -1;
	}
    // bind
    if(bind(Sockfd, (struct sockaddr *)&SrcAddr, sizeof(SrcAddr)) == -1)
    {
		printf("UDP bind Error!\n");
        close(Sockfd);
        return -1;
    }
    // sendto
    printf("Message sending to route:\n%s",UDPData);
    sendto(Sockfd, UDPData, strlen(UDPData), 0, (struct sockaddr *)&DstAddr, sizeof(DstAddr));
    // recvfrom
    DstLen = sizeof(DstAddr);
    RecvNum = recvfrom(Sockfd, RecvBuf, sizeof(RecvBuf), 0, (struct sockaddr *)&DstAddr, &DstLen);
    printf("RecvNum:%d\n",RecvNum);
   
    RecvBuf[RecvNum] = '\0';
    printf("Recv data are :\n%s", RecvBuf);
    // close
    close(Sockfd);   
    return RecvNum; 
}

/********************
函数功能：发现, 基于SSDP协议，UDP实现



***********************/
int  SearchReq(char *HostIP, char *DstIP, int SearchPort)
{
    char SearchMsg[]=
		"M-SEARCH * HTTP/1.1\r\n"
		"HOST:239.255.255.250:1900\r\n"
		"MAN:\"ssdp:discover\"\r\n"
		"MX:3\r\n"
		"ST:ssdp:all\r\n"
		"\r\n";
    int SSDPPort = 1900;
    return(UDPCommunicate(HostIP, DstIP, SearchPort, SSDPPort, SearchMsg));
} 
/**********************
函数功能：TCP通信




**********************/
char TCPCommunicate(char *RouteAddr, int Port, char *POSTMsg)
{
    int Sockfd;
    int RecvLen;
    struct sockaddr_in DstAddr;
    char RecvBuf[RECV_LEN] = {0};
    
    // 网络参数初始化
    bzero(&DstAddr, sizeof (DstAddr));
    DstAddr.sin_family = AF_INET;
    DstAddr.sin_addr.s_addr = inet_addr (RouteAddr);
    DstAddr.sin_port = htons (Port); 
    // socket
    if ((Sockfd = socket (PF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror ("socket");
        close(Sockfd);
        return -1;
    }
    // connet
    if (connect (Sockfd, (struct sockaddr *) &DstAddr, sizeof (struct sockaddr)) == -1)
    {
        perror ("connect");
        close(Sockfd);
        return -1;
    }
    printf ("Connected to server\n");
    // send	
    if(send(Sockfd, POSTMsg, strlen(POSTMsg), 0) == -1)
    {
        perror("send");
        close(Sockfd);
        return -1;
    }
    printf("send ok\n");
    // recv
    RecvLen = recv(Sockfd, RecvBuf, RECV_LEN, 0);
    printf("RecvLen:%d\n", RecvLen);
    if(RecvLen == -1)
    {
        perror("recv");
        close(Sockfd);
        return -1;
    }
    RecvBuf[RecvLen] = '\0';
    printf("RecvBuf:\n%s", RecvBuf);
    close(Sockfd);
	return 0;
}
/*******************
函数功能：控制--增加自动端口映射



********************/
void CtrlAddPortMap(char *RouteAddr,char *LocalAddr, int PortSetArr[3][2])
{
    char POSTMsg[1024] = {0};
    int  SSDPPort = 1900;
    int i;
    static int  OldPort[3] = {0};
    static char MapFlg[3] = {0};
    for(i = 0; i < 3; i++)
    {
        if(PortSetArr[i][1]) // 添加端口号映射
        {
               
             if(MapFlg[i] == 0) // 第一次新增映射端口时，直接映射。
             {
                 MapFlg[i] = 1;
                 OldPort[i] = PortSetArr[i][0];  // 保存新的端口号
                 HttpPOSTAddMap(LocalAddr, RouteAddr, PortSetArr[i][0], POSTMsg);
                 TCPCommunicate(RouteAddr, SSDPPort, POSTMsg); // TCP发送数据
                 memset(POSTMsg, 0, sizeof(POSTMsg));
                 continue; // 退出本次循环
             }
             else if(MapFlg[i] == 1)// 不是第一次映射，先删除原来已经映射的端口号后再重新映射
             {
                 // 删除掉原来的端口号
                 HttpPOSTDelMap(LocalAddr, RouteAddr, OldPort[i], POSTMsg);
                 TCPCommunicate(RouteAddr, SSDPPort, POSTMsg);
                 memset(POSTMsg, 0, sizeof(POSTMsg));
                 // 映射新的端口号
                 OldPort[i] = PortSetArr[i][0];
                 HttpPOSTAddMap(LocalAddr, RouteAddr, PortSetArr[i][0], POSTMsg);
                 TCPCommunicate(RouteAddr, SSDPPort, POSTMsg);
                 memset(POSTMsg, 0, sizeof(POSTMsg));
             }
        }
        else // 删除端口号映射
        {
             HttpPOSTDelMap(LocalAddr, RouteAddr, OldPort[i], POSTMsg);
             TCPCommunicate(RouteAddr, SSDPPort, POSTMsg);
             memset(POSTMsg, 0, sizeof(POSTMsg));
        }
    }
}
/*********************
函数功能：添加端口映射的逻辑处理



***********************/
char AddPortMap_TCP(char *RouteAddr, int PortSetArr[3][2])
{
    char *LocalAddr = NULL;
    int RecvNum = 0;
    static char ChkCnt = 0;
    int SearchPort = PortSetArr[2][0];
    while(1)
    {
		// 第0步，寻址
		LocalAddr = GetLocalIp();
		// 第一步，发现--搜索请求，基于SSDP协议
		// 此处的SearchPort可为其他可用的端口号
		RecvNum = SearchReq(LocalAddr, RouteAddr, SearchPort);
		printf("RecvNum:%d\n",RecvNum);
		if(RecvNum <= 0)
		{
		    printf("Trying to connect UPnP host again: %d\n", ChkCnt);
		    sleep(2);
		    if(ChkCnt++ >= 2)// 超过3次查询失败，退出
		    {
		        printf("Recieve No Data!!\n\n");
		        ChkCnt = 0;
		        return -1;
		    }
		    continue;
		}
		ChkCnt = 0;
		// 第三步，控制--新增映射端口，基于SOAP协议
		CtrlAddPortMap(RouteAddr, LocalAddr, PortSetArr);
        return 0;
    }
}
/********************
函数功能：控制--删除自动端口映射



***********************/
void CtrDelPort(char *RouteAddr,char *LocalAddr, int PortSetArr[3][2])
{
    int  SSDPPort = 1900;
    char POSTMsg[1024] = {0};
    int i;
    for(i = 0; i < 3; i++)
    {
        HttpPOSTDelMap(LocalAddr, RouteAddr, PortSetArr[i][0], POSTMsg);
        TCPCommunicate(RouteAddr, SSDPPort, POSTMsg);
        memset(POSTMsg, 0, sizeof(POSTMsg));
    }
}
/*******************
函数功能：删除端口映射的逻辑处理



**********************/
char DelPortMap_TCP( char *RouteAddr, int PortSetArr[3][2])
{
    char *LocalAddr = NULL;
    int RecvNum = 0;
    static char ChkCnt = 0;
    int SearchPort = PortSetArr[2][0];
    while(1)
    {
		// 第0步，寻址
		LocalAddr = GetLocalIp();
		// 第一步，发现--搜索请求，基于SSDP协议
		// 此处的SearchPort可为其他可用的端口号
		RecvNum = SearchReq(LocalAddr, RouteAddr, SearchPort);
		printf("RecvNum:%d\n",RecvNum);
		if(RecvNum <= 0)
		{
		    printf("Trying to connect UPnP host again: %d\n", ChkCnt);
		    sleep(2);
		    if(ChkCnt++ >= 2)// 超过3次查询失败，退出
		    {
		        printf("Recieve No Data!!\n\n");
		        ChkCnt = 0;
		        return -1;
		    }
		    continue;
		}
		ChkCnt = 0;
		// 第二步，描述（不需要）
		// 第三步，控制--删除映射端口，基于SOAP协议
		// 视频监控中，需要映射三个端口   	
		CtrDelPort(RouteAddr, LocalAddr, PortSetArr);
		// 第四步和第五步（不需要）
		return 0;// 退出while循环
    }
}

/**********************
函数功能：基于UPnP协议的自动端口映射实现过程。



************************/
char RoutePortMapping(char *RouteAddr, int PortSetArr[3][2], char UPnPEnFlg)
{

    static char MapFlg;
    switch(UPnPEnFlg)
    {
        case 0:// 不激活自动端口映射
        if(MapFlg == 0)// 如果NVR做过端口映射或已经删除了端口映射，则直接退出
        {
            printf("No need to mapping\n");
            break;
        }
        printf("Delete mapping!\n");
        // 否则，删除已映射的端口
        DelPortMap_TCP(RouteAddr, PortSetArr);
        MapFlg = 0;// 
        break;
        case 1:// 激活端口映射
        MapFlg = 1;
        printf("Need mapping!\n");
        AddPortMap_TCP(RouteAddr, PortSetArr);
        break;
        default: 
            printf("Please enter the right number!\n");
        break;
   }
	return 0;
}
/*************************
函数功能：模拟网页设置，从标准输入输出获取输入信息，设置UPnP使能，端口号和单个端口使能等。
说明： 由于下面的输入仅作为测试之用，所以没有对输入的内容做严格的限定，请依照提示输入相关信息。
       在实际使用过程中，RouteAddr,PortSetArr和UPnPEnFlg等变量的值都需要从网页中获取。 



*****************************/
char PortSetting(int PortSetArr[3][2])
{
    int i;
    char GetStrBuf[10];
    char StrPort[3][10] = {
     "TCPPort",
     "RtspPort",
     "HttpPort"
    };
    char UPnPEn = 0;

    printf("Please enter a num like '1' means add mapping or '0' means delete mapping:\n");

    gets(GetStrBuf);
    UPnPEn = atoi(GetStrBuf);
    printf("UPnPEn:%d\n", UPnPEn);
    if(UPnPEn)
    {
        for(i = 0; i < 3; i++)
        {
            printf("Please Enter %s :", StrPort[i]);
            gets(GetStrBuf);
            PortSetArr[i][0] = atoi(GetStrBuf);
            printf("Please Enter a number '1' which means enable %s, or '0' which means disable %s :", StrPort[i], StrPort[i]);
            gets(GetStrBuf);
            PortSetArr[i][1] = atoi(GetStrBuf);
        }
   
    }   
    for(i = 0; i < 3; i++)
    {   
        if(PortSetArr[i][1])
        {
            printf("%s:%d  Enabled\n", StrPort[i], PortSetArr[i][0]);
        }
        else
        {
            printf("%s:%d  Disabled\n", StrPort[i], PortSetArr[i][0]);
        }
    }
    return UPnPEn;
}


int main(int argc, char *argv[])
{
    char UPnPEnFlg = 0; // UPnP使能标识
    char RouteAddr[32] = "192.168.1.1";// 路由器IP地址
    int  PortSetArr[3][2] = {         // 端口号和端口使能
     {0, 0},  //PortSetArr[0][0]: TCPPort;  PortSetArr[0][1]: TCPPortMapEnFlg
     {0, 0},  //PortSetArr[1][0]: RtspPort; PortSetArr[1][1]: MapEnFlg
     {0, 0}   //PortSetArr[2][0]: HttpPort; PortSetArr[2][1]: MapEnFlg
    };
    while(1)
    {   
        UPnPEnFlg = PortSetting(PortSetArr);// 标准输入输出模拟网页获取设置信息
        RoutePortMapping(RouteAddr, PortSetArr, UPnPEnFlg);// UPnP自动端口映射的实现
    }  
    return 0;
}
