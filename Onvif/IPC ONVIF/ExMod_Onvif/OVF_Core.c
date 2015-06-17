//OVF_Core.c

#include "soapH.h"
#include "soapStub.h"
#include "OVF_Export.h"
#include "OVF_Core.h"
#include "OVF_Discovery.h"
#include "OVF_Discovery_Client.h"
SOAP_NMAC struct Namespace namespacesI[] =
{
 	{"SOAP-ENV", "http://www.w3.org/2003/05/soap-envelope", "http://schemas.xmlsoap.org/soap/envelope/", NULL},
 	{"SOAP-ENC", "http://www.w3.org/2003/05/soap-encoding", "http://schemas.xmlsoap.org/soap/encoding/", NULL},
	{"xsi","http://www.w3.org/2001/XMLSchema-instance", NULL, NULL},
	{"xsd","http://www.w3.org/2001/XMLSchema", NULL, NULL},
	{"wsa5","http://www.w3.org/2005/08/addressing", NULL, NULL},
	{"c14n","http://www.w3.org/2001/10/xml-exc-c14n#", NULL, NULL},
	{"wsu","http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-utility-1.0.xsd", NULL, NULL},
	{"xenc","http://www.w3.org/2001/04/xmlenc#", NULL, NULL},
	{"ds","http://www.w3.org/2000/09/xmldsig#", NULL, NULL},
	{"wsse","http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-secext-1.0.xsd", NULL, NULL},
	{"xmime","http://tempuri.org/xmime.xsd", NULL, NULL},
	{"xop","http://www.w3.org/2004/08/xop/include", NULL, NULL},
	{"ns5","http://www.placeholder.org/ver10/tmp/schema", NULL, NULL}, 
	{"tt","http://www.onvif.org/ver10/schema", NULL, NULL}, 
	{"wsbf2","http://docs.oasis-open.org/wsrf/bf-2", NULL, NULL}, 
	{"wstop","http://docs.oasis-open.org/wsn/t-1", NULL, NULL},
	{"wsr2","http://docs.oasis-open.org/wsrf/r-2", NULL, NULL},
	{"daae","http://www.onvif.org/ver20/analytics/wsdl/AnalyticsEngineBinding", NULL, NULL}, 
	{"dare","http://www.onvif.org/ver20/analytics/wsdl/RuleEngineBinding", NULL, NULL},
	{"tan","http://www.onvif.org/ver20/analytics/wsdl", NULL, NULL},
	{"decpp","http://www.onvif.org/ver10/events/wsdl/CreatePullPointBinding", NULL, NULL},
	{"dee","http://www.onvif.org/ver10/events/wsdl/EventBinding", NULL, NULL},
	{"denc","http://www.onvif.org/ver10/events/wsdl/NotificationConsumerBinding", NULL, NULL}, 
	{"denf","http://www.onvif.org/ver10/events/wsdl/NotificationProducerBinding", NULL, NULL}, 
	{"depp","http://www.onvif.org/ver10/events/wsdl/PullPointBinding", NULL, NULL}, 
	{"depps","http://www.onvif.org/ver10/events/wsdl/PullPointSubscriptionBinding", NULL, NULL},
	{"tev","http://www.onvif.org/ver10/events/wsdl", NULL, NULL},
	{"depsm","http://www.onvif.org/ver10/events/wsdl/PausableSubscriptionManagerBinding", NULL, NULL},
	{"wsnt","http://docs.oasis-open.org/wsn/b-2", NULL, NULL}, 
	{"desm","http://www.onvif.org/ver10/events/wsdl/SubscriptionManagerBinding", NULL, NULL}, 
	{"ns1","http://www.onvif.org/ver10/actionengine/wsdl", NULL, NULL}, 
	{"ns2","http://www.onvif.org/ver10/deviceIO/wsdl", NULL, NULL},
	{"ns4","http://www.placeholder.org/ver10/tmp/wsdl", NULL, NULL},
	{"tad","http://www.onvif.org/ver10/analyticsdevice/wsdl", NULL, NULL},
	{"tdis","http://www.onvif.org/ver10/display/wsdl", NULL, NULL},
	{"tds","http://www.onvif.org/ver10/device/wsdl", NULL, NULL}, 
	{"timg","http://www.onvif.org/ver20/imaging/wsdl", NULL, NULL}, 
	{"tptz","http://www.onvif.org/ver20/ptz/wsdl", NULL, NULL}, 
	{"trcv","http://www.onvif.org/ver10/receiver/wsdl", NULL, NULL}, 
	{"trec","http://www.onvif.org/ver10/recording/wsdl", NULL, NULL},
	{"trp","http://www.onvif.org/ver10/replay/wsdl", NULL, NULL}, 
	{"trt","http://www.onvif.org/ver10/media/wsdl", NULL, NULL}, 
	{"tse","http://www.onvif.org/ver10/search/wsdl", NULL, NULL}, 
	{"tns1","http://www.onvif.org/ver10/topics", NULL, NULL}, 
	{"ter","http://www.onvif.org/ver10/error", NULL, NULL},
	{"snl","onvif/extend/snl/ver10/schema", NULL, NULL},
	{NULL,NULL,NULL,NULL}
};

SOAP_NMAC struct Namespace namespacesII[] =
{
	{"SOAP-ENV", "http://www.w3.org/2003/05/soap-envelope", "http://schemas.xmlsoap.org/soap/envelope/", NULL},
	{"SOAP-ENC", "http://www.w3.org/2003/05/soap-encoding", "http://schemas.xmlsoap.org/soap/encoding/", NULL},
//	{"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
//	{"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
	{"wsa", "http://schemas.xmlsoap.org/ws/2004/08/addressing", NULL, NULL},
//	{"dndl", "http://www.onvif.org/ver10/network/wsdl/DiscoveryLookupBinding", NULL, NULL},
//	{"dnrd", "http://www.onvif.org/ver10/network/wsdl/RemoteDiscoveryBinding", NULL, NULL},
	{"d", "http://schemas.xmlsoap.org/ws/2005/04/discovery", NULL, NULL},
	{"dn", "http://www.onvif.org/ver10/network/wsdl", NULL, NULL},
	{NULL, NULL, NULL, NULL}
};
SOAP_NMAC struct Namespace namespacesIII[] =
{
	{"SOAP-ENV", "http://www.w3.org/2003/05/soap-envelope", "http://schemas.xmlsoap.org/soap/envelope/", NULL},
	{"SOAP-ENC", "http://www.w3.org/2003/05/soap-encoding", "http://schemas.xmlsoap.org/soap/encoding/", NULL},
	{"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
	{"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
	{"wsa", "http://schemas.xmlsoap.org/ws/2004/08/addressing", NULL, NULL},
	{"dndl", "http://www.onvif.org/ver10/network/wsdl/DiscoveryLookupBinding", NULL, NULL},
	{"dnrd", "http://www.onvif.org/ver10/network/wsdl/RemoteDiscoveryBinding", NULL, NULL},
	{"d", "http://schemas.xmlsoap.org/ws/2005/04/discovery", NULL, NULL},
	{"dn", "http://www.onvif.org/ver10/network/wsdl", NULL, NULL},
	{NULL, NULL, NULL, NULL}
};
static VOID* TheadSvUDP(VOID *lParam)
{
	pthread_detach(pthread_self());
	BOOL bRet				= FALSE;
	ONVIF*    Ovf			= (ONVIF *)lParam;
	Ovf->soapUDP->hdOnvif	= (VOID  *)Ovf;
	IPCAM_setTskName("TheadSvUDP");
	while(Ovf->IsKeepAliveUDP)
  { 			

		soap_serve   (Ovf->soapUDP);
		soap_destroy    (Ovf->soapUDP);
		soap_end        (Ovf->soapUDP);
		soap_done   ((struct soap*)Ovf);     //分离soap结构
  
	//	printf("1111111111111111111111111111111111111111111111111111111111111111\n");
		//OVF_Sleep(1);
	}
  if(Ovf)
  {
  	free(Ovf);
  	Ovf =NULL;
  }
  pthread_exit(0);
	return NULL;
}

static VOID* ThreadSvTCP_Work(void *soap)
{	
   pthread_detach(pthread_self());
   soap_serve  ((struct soap*)soap);
  // printf(" soap serve process finsh date close client\n");
   soap_destroy((struct soap*)soap);     //删除C++结构数据
   soap_end    ((struct soap*)soap);     //删除数据
   soap_done   ((struct soap*)soap);     //分离soap结构
   free(soap);soap =NULL;
   pthread_exit(0);
   return NULL; 
}

static VOID* ThreadSvTCP(VOID *lParam)
{

  pthread_t   threadID;
	ONVIF*      Ovf =       (ONVIF*)lParam;
	SOAP_SOCKET Client; // master and slave sockets //	
	Ovf->soapTCP->hdOnvif=(VOID *)Ovf;
	//IPCAM_setTskName("ThreadSvTCP");
	while(Ovf->IsKeepAliveTCP)
	{ 
      Client = soap_accept(Ovf->soapTCP);
     
      if (!soap_valid_socket(Client))
      { 
          soap_print_fault(Ovf->soapTCP, stderr);
       //   printf("============sssssssssssssssssssss==========ThreadSvTCP===================\n");
         //  printf("onvifonvif11111111111111111111111111111111111111111111111111111111111nvifonvifonvif\n");
          continue;
      }
      else
      {
       //printf("onvifonvif222222222222222222222222222222222222222222222222nvifonvifonvif\n");
		   struct soap *tsoap;
		    MyOnvifInfo pInfo;
		   if (!(tsoap = soap_copy(Ovf->soapTCP)))continue;
            tsoap->recv_timeout  = 1;
		       tsoap->send_timeout  = 1;
		 //     pInfo.soap_info = tsoap;
      //     pInfo.client  = Client;
           pthread_create(&threadID, NULL,ThreadSvTCP_Work,(VOID*)tsoap);
          //   pthread_create(&threadID, NULL,ThreadSvTCP_Work,(VOID*)&pInfo);
           // printf("onvifonvif333333333333333333333333333333333333333nvifonvifonvif\n");
      }
    //printf("222222222222222222222222222222222222222222222222222222222222222222222222222\n");
   }

   return NULL;
}

BOOL  OVF_StartSvUDP(ONVIF* Ovf,USHORT TimeOut)
{
	struct ip_mreq  mcast ;
	if(TimeOut<=5)TimeOut=5;
    if(NULL!=Ovf->soapUDP) return FALSE;
	Ovf->soapUDP=(struct soap*)calloc(sizeof(CHAR),sizeof(struct soap));
	soap_init2(Ovf->soapUDP, SOAP_IO_UDP|SOAP_IO_FLUSH, SOAP_IO_UDP|SOAP_IO_FLUSH);
	soap_set_namespaces(Ovf->soapUDP, namespacesIII); 

	if(!soap_valid_socket(soap_bind(Ovf->soapUDP, NULL, 3702, 10))){ 
		soap_print_fault(Ovf->soapUDP, stderr);
	//	printf("=================================OVF_StartSvUDP fail======================\n");
		return FALSE;
	}
	
	mcast.imr_multiaddr.s_addr = inet_addr("239.255.255.250");
	//mcast.imr_interface.s_addr = inet_addr("172.16.1.78");//htonl(INADDR_ANY);
	//mcast.imr_interface.s_addr = htonl(Ovf->LocalIpaddr);
	mcast.imr_interface.s_addr = htonl(INADDR_ANY);
	//组播
	if(setsockopt(Ovf->soapUDP->master, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mcast, sizeof(mcast)) < 0){
	//	printf("[UDP]:setsockopt error!\n");
	//	printf("=================================OVF_StartSvUDP  muitip fail======================\n");
		return FALSE;
	}	
	Ovf->IsKeepAliveUDP =TRUE;
    pthread_create(&Ovf->threadUDP, NULL,TheadSvUDP,(VOID*)Ovf);
	//printf("=================================OVF_StartSvUDP  muitip suceess======================\n");
    return TRUE;
}

BOOL  OVF_StopSvUDP(ONVIF* Ovf)
{
    if(NULL==Ovf->soapUDP) return FALSE;
	Ovf->IsKeepAliveUDP=FALSE;
    pthread_join(Ovf->threadUDP, NULL);
	if(Ovf->soapUDP){
		soap_done(Ovf->soapUDP);
		free     (Ovf->soapUDP);
	          	  Ovf->soapUDP=NULL;	
		
	}
	return TRUE;
}
BOOL OVF_EnableDiscovery (HDOVF  hOVF ,BOOL IsEnable)
{
    ONVIF* Ovf = (ONVIF* )hOVF;
    if(IsEnable)return OVF_StartSvUDP(Ovf,0);
    else        return OVF_StopSvUDP (Ovf);
}

BOOL  OVF_StartSvTCP(ONVIF* Ovf,USHORT TimeOut)
{

	SOAP_SOCKET Server;
	if(TimeOut<=5)TimeOut=5;
    if(NULL!=Ovf->soapTCP) return FALSE;
	Ovf->soapTCP=(struct soap*)calloc(sizeof(CHAR),sizeof(struct soap)); 
	soap_init(Ovf->soapTCP);
	soap_set_namespaces(Ovf->soapTCP, namespacesI); 
  
      Ovf->soapTCP->send_timeout   = 5;       //5 seconds
      Ovf->soapTCP->recv_timeout   = TimeOut; //5 seconds
      Ovf->soapTCP->accept_timeout = 1;       //秒
	    Ovf->soapTCP->hdOnvif        = Ovf;
//    Ovf->soapTCP->max_keep_alive = 100;     // max keep-alive sequence 
    if(0!=Ovf->PortTcpServer){//端口为0不启动主动服务
    //	  printf("===============================OVF_StartSvTCP=%d\n",Ovf->PortTcpServer);
        Server = soap_bind(Ovf->soapTCP, NULL, Ovf->PortTcpServer, 100);
        if (!soap_valid_socket(Server)){ 
            soap_print_fault(Ovf->soapTCP, stderr);
        //    printf("====================================OVF_StartSvTCP  is fail==========================\n");
            return FALSE;
        }
    	Ovf->IsKeepAliveTCP =TRUE;
        pthread_create(&Ovf->threadTCP, NULL,ThreadSvTCP,(VOID*)Ovf);
    }
 // printf("====================================OVF_StartSvTCP  is suceess==========================\n");
	return TRUE;
}
BOOL  OVF_StopSvTCP(ONVIF* Ovf)
{

	Ovf->IsKeepAliveTCP=FALSE;
    pthread_join(Ovf->threadTCP, NULL);
	if(Ovf->soapTCP){
		soap_done(Ovf->soapTCP);
		free     (Ovf->soapTCP);
	          	  Ovf->soapTCP=NULL;
	}
	return TRUE;
}

BOOL  OVF_InitDeFaultVal(ONVIF *pOnvif )
{
	OVFDISCONVERYINFO *OVFDiscoveryInfo  = (OVFDISCONVERYINFO    *) calloc(sizeof(CHAR),sizeof(OVFDISCONVERYINFO));
  ONVIF             *Onvif             = (ONVIF*)pOnvif;
	BOOL               nRet              = TRUE;
	
	
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDiscovery,GetDiscoveryInfo);
    if(FALSE==Onvif->CallBackOvf->CallBackDiscovery->GetDiscoveryInfo(OVFDiscoveryInfo)){nRet = FALSE; goto  END_INITDEFAULTVAL;}
    sprintf(Onvif->xAddr            , "%s/onvif/device_service", OVFDiscoveryInfo->DevRootUrl);
	sprintf(Onvif->EndpointReference, "%s","soap.udp://239.255.255.250:3702");
	
END_INITDEFAULTVAL:
    free(OVFDiscoveryInfo);OVFDiscoveryInfo=NULL;
	return nRet;
}

HDOVF OVF_Init(UINT usIP,USHORT usPort,USHORT TimeOut, CALLBACKOVF* lpCallBack )
{

   
	 INT     Ret;
     ONVIF  *pOnvif		 = (ONVIF*)calloc(sizeof(CHAR),sizeof(ONVIF));
	 ONVIF  *POnvifSer	 = (ONVIF*)calloc(sizeof(CHAR),sizeof(ONVIF));
#ifdef WIN32
	 WSADATA wsaData;
     if ((Ret = WSAStartup(MAKEWORD(2,2), &wsaData)) != 0) return NULL;
#endif  

     pOnvif->Ver           = 2;
	 POnvifSer->Ver		   = 2;
     pOnvif->SubVer        = 1;
	 POnvifSer->SubVer     = 1;
	 pOnvif->PortTcpServer = usPort;
	 pOnvif->LocalIpaddr    = usIP;
	 pOnvif->CallBackOvf   = lpCallBack;
	 POnvifSer->CallBackOvf= lpCallBack;
	 //ONVIF HELLO 协议
	 OVF_InitDeFaultVal(POnvifSer);
	 POnvifSer->hOnvifCln = ONVIF_ClnInit(0,usPort);
	 ((PONVIFCLIENT)(POnvifSer->hOnvifCln))->OnvifServer=POnvifSer;
//	 printf("aaaaaaaaaaaaaaaaaaaaaa==========================bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb\n");
		 Ret=ONVIF_ClnSendHello( POnvifSer->hOnvifCln,POnvifSer->EndpointReference,POnvifSer->xAddr,IPCAMWSDEVICETYPE);
	 ONVIF_ClnDeinit(POnvifSer->hOnvifCln);
	 free(POnvifSer);
	 POnvifSer=NULL;
	//  printf("cccccccccccccccccccccccccccc==========================dddddddddddddddddddddddddddddddddddddddddd\n");
	 if(!OVF_StartSvUDP(pOnvif,TimeOut)  ||
 		!OVF_StartSvTCP(pOnvif,TimeOut))
	 {     
	 	//     printf("eeeeeeeeeeeeeeeeeeeeeee==========================ffffffffffffffffffffffffffffffffffff\n");
	 	     free(pOnvif); 
		     pOnvif=NULL;
        return NULL;
   }
//	printf("ggggggggggggggggggggggggggggg==========================hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh\n");
	return (HDOVF )pOnvif;
}

VOID  OVF_DeInit(HDOVF  hOVF)
{
	 ONVIF *pOnvif  = (ONVIF*)hOVF;
	 ONVIF  *POnvifSer	 = (ONVIF*)calloc(sizeof(CHAR),sizeof(ONVIF));
	 POnvifSer->CallBackOvf = pOnvif->CallBackOvf;
	 POnvifSer->Ver			= pOnvif->Ver;
	 POnvifSer->SubVer     = pOnvif->SubVer;
	 POnvifSer->PortTcpServer=pOnvif->PortTcpServer;
	 if(!hOVF ||
		!OVF_StopSvUDP(pOnvif) ||
		!OVF_StopSvTCP(pOnvif))
	 free(pOnvif);
	 pOnvif=NULL;
	 //Onvif Byte 协议
	 OVF_InitDeFaultVal(POnvifSer);
	 POnvifSer->hOnvifCln = ONVIF_ClnInit(0,POnvifSer->PortTcpServer);
	 ((PONVIFCLIENT)(POnvifSer->hOnvifCln))->OnvifServer=POnvifSer;
	 ONVIF_ClnSendBye(POnvifSer->hOnvifCln,POnvifSer->EndpointReference,POnvifSer->xAddr,IPCAMWSDEVICETYPE);
	 if(POnvifSer->hOnvifCln)
		 ONVIF_ClnDeinit(POnvifSer->hOnvifCln);
	 free(POnvifSer); POnvifSer=NULL;
	 
}
VOID OVF_Sleep(UINT Seconds)
{
#ifndef _WIN32
	sleep(Seconds);
#else
	//Sleep(1000*Seconds);
	Sleep(Seconds);
#endif
}
VOID OVF_MSleep(UINT Milliseconds)
{
#ifndef _WIN32
	usleep(Milliseconds*1000);
#else
	//Sleep(Milliseconds);
	
#endif
}
BOOL OVF_CreateUUIDS(CHAR *sUUID)
{
#ifndef _WIN32
        UINT uuid;
        uuid_generate(uuid);
        uuid_unparse (uuid, sUUID);
#else
		UUID  uuid;
		UuidCreate(&uuid);
        UuidToString(&uuid, (CHAR**)&sUUID);
#endif
return TRUE;
}
BOOL OVF_IsONVIF(HDOVF  hOVF ,CHAR*Buff,USHORT BufLenth)
{
    //printf(Buff);
	if(//strstr(Buff,"text/xml")&&
	   strstr(Buff,"soap")&&
	   strstr(Buff,"onvif"))        return TRUE;

	return FALSE;
}
BOOL OVF_StartONVIF(HDOVF  hOVF ,CHAR*Buff,USHORT BufLenth,INT nSocket,SOCKETIN *SocketIn)
{
    pthread_t     threadID;
	ONVIF        *pOnvif  = (ONVIF*)hOVF;
   struct soap   *tsoap;

   	printf("OVF_StartONVIF  start");
   if (!(tsoap = soap_copy(pOnvif->soapTCP)))return FALSE;
    tsoap->buflen  = BufLenth;
	tsoap->socket  = nSocket;
	strncpy(tsoap->buf,Buff,BufLenth);
	
   if(0!=pthread_create(&threadID, NULL,ThreadSvTCP_Work,(VOID*)tsoap)) return FALSE;

	return TRUE;
}
/*
BOOL OVF_InitSoapHead(struct soap* soap)
{  
    wsa__Relationship *wsa_RelatesTo     = (struct wsa__Relationship*)  soap_malloc(soap,sizeof(struct wsa__Relationship));
    CHAR *MessageID                      = (CHAR    *) soap_malloc(soap,64); 
    sta
    if (soap->header){
        strcpy(MessageID, "urn:uuid:");
        OVF_CreateUUIDS(&(MessageID[9]));

		if(soap->header->wsa__MessageID)
		{
			printf("remote wsa__MessageID : %s\n",soap->header->wsa__MessageID);
 			soap->header->wsa__RelatesTo =wsa_RelatesTo;
			soap_default__wsa__RelatesTo(soap, soap->header->wsa__RelatesTo);
			soap->header->wsa__RelatesTo->__item = soap->header->wsa__MessageID;

			soap->header->wsa__MessageID = MessageID;
			soap->header->wsa__To     = "http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous";
			soap->header->wsa__Action = "http://schemas.xmlsoap.org/ws/2005/04/discovery/ProbeMatches";
		}
	}

	scopes->__item =  "onvif://www.onvif.org/type/video_encoder \
                       onvif://www.onvif.org/type/audio_encoder \ 
                       onvif://www.onvif.org/location/%s \
                       onvif://www.onvif.org/hardware/IPC-model \ 
                       onvif://www.onvif.org/name/IPC-model";  //位置;型号;设备名称
    return TRUE;
}
*/
