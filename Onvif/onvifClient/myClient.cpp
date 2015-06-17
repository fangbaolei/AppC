#include "soapStub.h"
#include "wsddapi.h"
#include "RemoteDiscoveryBinding.nsmap"

// SOAP消息体的初始化，主要是超时时间和头部的初始化
static struct soap* ONVIF_Initsoap(struct SOAP_ENV__Header *header, const char *was_To, const char *was_Action, int timeout)  
{  
    struct soap *soap = NULL;   
    unsigned char macaddr[6];  
    char _HwId[1024];  
    unsigned int Flagrand;  
    soap = soap_new();  //初始化环境变量
    if(soap == NULL)  
    {     
        printf("[%d]soap = NULL\n", __LINE__);  
        return NULL;  
    }     
     soap_set_namespaces( soap, namespaces);  //设置命名空间
    //超过5秒钟没有数据就退出
    if (timeout > 0)  
    {     
        soap->recv_timeout = timeout;  
        soap->send_timeout = timeout;  
        soap->connect_timeout = timeout;  
    }     
    else  
    {     
       //如果外部接口没有设备默认超时时间的话，我这里给了一个默认值10s
        soap->recv_timeout    = 10;   
        soap->send_timeout    = 10;   
        soap->connect_timeout = 10;   
    }     
   soap_default_SOAP_ENV__Header(soap, header);//添加SOAPHeader的in函数处理：
  
// 为了保证每次搜索的时候MessageID都是不相同的！因为简单，直接取了随机值    srand((int)time(0));  
    Flagrand = rand()%9000 + 1000; //淇濊瘉鍥涗綅鏁存暟  
    macaddr[0] = 0x1; macaddr[1] = 0x2; macaddr[2] = 0x3; macaddr[3] = 0x4; macaddr[4] = 0x5; macaddr[5] = 0x6;  
    sprintf(_HwId,"urn:uuid:%ud68a-1dd2-11b2-a105-%02X%02X%02X%02X%02X%02X",  
            Flagrand, macaddr[0], macaddr[1], macaddr[2], macaddr[3], macaddr[4], macaddr[5]);  
    header->wsa__MessageID =(char *)malloc( 100);  
    memset(header->wsa__MessageID, 0, 100);  
    strncpy(header->wsa__MessageID, _HwId, strlen(_HwId));  // 给头赋值
  
    if (was_Action != NULL)  
    {  
        header->wsa__Action =(char *)malloc(1024);  
        memset(header->wsa__Action, '\0', 1024);  
        strncpy(header->wsa__Action, was_Action, 1024);// 给头赋值"http://schemas.xmlsoap.org/ws/2005/04/discovery/Probe";  
    }  
    if (was_To != NULL)  
    {  
        header->wsa__To =(char *)malloc(1024);  
        memset(header->wsa__To, '\0', 1024);  
        strncpy(header->wsa__To,  was_To, 1024);// 给头赋值"urn:schemas-xmlsoap-org:ws:2005:04:discovery";     
    }  
    soap->header = header;  // 给头赋值
    return soap;  
}  


int ONVIF_ClientDiscovery( )  
{  
    int HasDev = 0;  // 探测到的设备数量
    int retval = SOAP_OK;  // 返回值
    wsdd__ProbeType req;  //客户端发送的probe
    struct __wsdd__ProbeMatches resp;  //服务端回的probematchs
    wsdd__ScopesType sScope;  // Probe里面的范围
    struct SOAP_ENV__Header header;  // SOAP的头
    struct soap* soap;  // SOAP环境变量
  
  
    const char *was_To = "urn:schemas-xmlsoap-org:ws:2005:04:discovery";  
    const char *was_Action = "http://schemas.xmlsoap.org/ws/2005/04/discovery/Probe";  
    //这个就是传递过去的组播的ip地址和对应的端口发送广播信息    
    const char *soap_endpoint = "soap.udp://239.255.255.250:3702/";  
  
      //这个接口填充一些信息并new返回一个soap对象，本来可以不用额外接口，  
    // 但是后期会作其他操作，此部分剔除出来后面的操作就相对简单了,只是调用接口就好
    soap = ONVIF_Initsoap(&header, was_To, was_Action, 20);  
  
    soap_default_SOAP_ENV__Header(soap, &header);  //将header设置为soap消息默认的头属性
    soap->header = &header;  // 给头赋值
  
    soap_default_wsdd__ScopesType(soap, &sScope);   /*设置所需寻找设备的类型和范围,二者至少设定一个,否则可能收到非ONVIF设备,出现异常*/
    sScope.__item = (char*)"";//设置所需设备的sScope
    soap_default_wsdd__ProbeType(soap, &req);  
    req.Scopes = &sScope;  
    req.Types = (char*)""; //"dn:NetworkVideoTransmitter";  
  
    retval = soap_send___wsdd__Probe(soap, soap_endpoint, NULL, &req);   //通过组播发送Probe探针,发送成功返回0,否则-1
   //发送组播消息成功后，开始循环接收各位设备发送过来的消息 
    while (retval == SOAP_OK)  
    {  
        retval = soap_recv___wsdd__ProbeMatches(soap, &resp);  //接收ProbeMatches,成功返回0,否则-1 
        if (retval == SOAP_OK)  
        {  
            if (soap->error)  
            {  
                printf("[%d]: recv error:%d,%s,%s\n", __LINE__, soap->error, *soap_faultcode(soap), *soap_faultstring(soap));  
                retval = soap->error;  
            }  
            else //成功接收某一个设备的消息 
            {
                HasDev ++; 
				 
                if(NULL!= resp.wsdd__ProbeMatches && resp.wsdd__ProbeMatches->ProbeMatch != NULL && resp.wsdd__ProbeMatches->ProbeMatch->XAddrs != NULL)  
                {  
                    printf(" ################  recv  %d devices info #### %d\n", HasDev, resp.wsdd__ProbeMatches->__sizeProbeMatch);  
                    printf("Target Service Address  : %s\r\n", resp.wsdd__ProbeMatches->ProbeMatch->XAddrs);  
                    printf("Target EP Address       : %s\r\n", resp.wsdd__ProbeMatches->ProbeMatch->wsa__EndpointReference.Address);  
                    printf("Target Type             : %s\r\n", resp.wsdd__ProbeMatches->ProbeMatch->Types);  
                    printf("Target Metadata Version : %d\r\n", resp.wsdd__ProbeMatches->ProbeMatch->MetadataVersion);  
//                    sleep(1);  
                }  
            }  
        }  
        else if (soap->error)  
        {  
            if (HasDev == 0)  
            {  
                printf("[%s][%d] Thers Device discovery or soap error: %d, %s, %s \n", __func__, __LINE__, soap->error, *soap_faultcode(soap), *soap_faultstring(soap)); 
                retval = soap->error;  
            }  
            else  
            {  
                printf(" [%s]-[%d] Search end! It has Searched %d devices! \n", __func__, __LINE__, HasDev);  
                retval = 0;  
            }  
            break;  
        }  
    }  
  /********清除变量************/
    soap_destroy(soap);  
    soap_end(soap);  
    soap_free(soap);  
  
    return retval;  
}


int main(int arge,char **argv)
{
	if (ONVIF_ClientDiscovery() != 0 )  
	{  
	printf("discovery failed!\n");  
	return -1;  
	}  

	printf("I love you zaiwei!\n");
	return 0;
}
