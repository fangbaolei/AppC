//////////////////////////////////////////////////////////////////////////
#include "soapH.h"
#include "OVF_Export.h"
#include "soapStub.h"
#include "OVF_Core.h"
#include "OVF_Discovery_Client.h"

SOAP_NMAC struct Namespace namespacesIIII[] =
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



BOOL  OVF_InitDeFaultValCLN(ONVIF	*pOnvif,struct d__HelloType *pHellope)
{
	OVFDISCONVERYINFO *OVFDiscoveryInfo				= (OVFDISCONVERYINFO    *) calloc(sizeof(CHAR),sizeof(OVFDISCONVERYINFO));
      struct d__HelloType           *Hellope  = (struct d__HelloType*)pHellope;
	ONVIF            *Onvif           = (ONVIF*)pOnvif;
	BOOL               nRet					= TRUE;
	
	
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDiscovery,GetDiscoveryInfo);
    if(FALSE==Onvif->CallBackOvf->CallBackDiscovery->GetDiscoveryInfo(OVFDiscoveryInfo)){nRet = FALSE; goto  END_INITDEFAULTVALCLN;}
	sprintf(Hellope->wsa__EndpointReference.Address, "um:uuid:%s", OVFDiscoveryInfo->DevGuid);      
END_INITDEFAULTVALCLN:
    free(OVFDiscoveryInfo); OVFDiscoveryInfo=NULL;
	return nRet;
}
BOOL OVF_InitDeFaultValCLNBye(ONVIF	*pOnvif,struct d__ByeType *pByepe)
{
	OVFDISCONVERYINFO *OVFDiscoveryInfo				= (OVFDISCONVERYINFO    *) calloc(sizeof(CHAR),sizeof(OVFDISCONVERYINFO));
      struct d__ByeType           *Byepe  = (struct d__ByeType*)pByepe;
	ONVIF            *Onvif           = (ONVIF*)pOnvif;
	BOOL               nRet					= TRUE;
	
	
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDiscovery,GetDiscoveryInfo);
    if(FALSE==Onvif->CallBackOvf->CallBackDiscovery->GetDiscoveryInfo(OVFDiscoveryInfo)){nRet = FALSE; goto  END_INITDEFAULTVALCLN;}
	sprintf(Byepe->wsa__EndpointReference.Address, "um:uuid:%s", OVFDiscoveryInfo->DevGuid);      
END_INITDEFAULTVALCLN:
    free(OVFDiscoveryInfo); OVFDiscoveryInfo=NULL;
	return nRet;
}
BOOL ONVIF_ClnInitUDPSoap(ONVIFCLIENT* OnvifC,USHORT TimeOut)
{
	
	struct ip_mreq  mcast ;
	ONVIFCLIENT * OnvifCln =(ONVIFCLIENT*)OnvifC;
	if(NULL!=OnvifCln->soapUDP) return FALSE;
	OnvifCln->soapUDP=(struct soap*)calloc(sizeof(CHAR),sizeof(struct soap));
	soap_init2(OnvifCln->soapUDP, SOAP_IO_UDP|SOAP_IO_FLUSH, SOAP_IO_UDP|SOAP_IO_FLUSH);
	soap_set_namespaces(OnvifCln->soapUDP, namespacesIIII); 
	TimeOut =5;
	OnvifCln->soapUDP->recv_timeout = TimeOut;
	OnvifCln->soapUDP->send_timeout   = 5;       //5 seconds
	OnvifCln->soapUDP->accept_timeout = 1;       //秒
	OnvifCln->soapUDP->hdOnvif        = OnvifC;
	if(!soap_valid_socket(soap_bind(OnvifCln->soapUDP, NULL, 3702, 10))){ 
		soap_print_fault(OnvifCln->soapUDP, stderr);
		return FALSE;
	}
	
	mcast.imr_multiaddr.s_addr = inet_addr("239.255.255.250");
	//mcast.imr_interface.s_addr = inet_addr("172.16.1.78");//htonl(INADDR_ANY);
	mcast.imr_interface.s_addr = htonl(INADDR_ANY);
	
	//组播
	if(setsockopt(OnvifCln->soapUDP->master, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mcast, sizeof(mcast)) < 0)
	{
		printf("===============================maliang=============================\n");
		return FALSE;
	}
	return TRUE;
}
HONVIFCLN ONVIF_ClnInit(ULONG ulIP,USHORT usPort)
{
	PONVIFCLIENT OnvifCln = (PONVIFCLIENT) calloc(sizeof(CHAR),sizeof(ONVIFCLIENT));
    
 //	if(NULL!=OnvifSev){
// 		OnvifCln->soapUDP = OnvifSev->soapUDP;
 //	}else{
	//独立创建客户端监听及主播端口
	ONVIF_ClnInitUDPSoap(OnvifCln,5);
	
	return (HONVIFCLN)OnvifCln;
}
BOOL ONVIF_ClnDeinit(HONVIFCLN hOnvifCln)
{
	ONVIFCLIENT *pOnvifClient =(ONVIFCLIENT*)hOnvifCln;
// 	if(!pOnvifClient->IsCopyByServer){
// 		//自行创建的套接字自行释放
// 		if (NULL!=pOnvifClient->soapUDP){
// 		}
// 	}
	if(NULL==pOnvifClient->soapUDP) return FALSE;
	if(pOnvifClient->soapUDP){
		if(soap_serve   (pOnvifClient->soapUDP))
			soap_destroy    (pOnvifClient->soapUDP);
		soap_end        (pOnvifClient->soapUDP);
		soap_done(pOnvifClient->soapUDP);
		free     (pOnvifClient->soapUDP);
		pOnvifClient->soapUDP=NULL;			
	}
    free(pOnvifClient); pOnvifClient=NULL;
	return TRUE;
}

BOOL ONVIF_ClnSendHello(HONVIFCLN hOnvifCln,CHAR * EndPoint,CHAR * ServAddr,CHAR* DeviceType)
{
		ONVIFCLIENT *pOnvifClient						=(ONVIFCLIENT*)hOnvifCln;
		//NEWCLN   (HelloResp,pOnvifClient->soapUDP,struct d__ResolveType);
		struct d__ResolveType HelloResp;
		NEWCLN   (HelloReq ,pOnvifClient->soapUDP,struct d__HelloType);	
		NEWCLNIII(addr,pOnvifClient->soapUDP,CHAR,OVFCHARLENTH);

		HelloReq->Types									= DeviceType;
		HelloReq->XAddrs								= ServAddr;
		HelloReq->wsa__EndpointReference.Address		= addr;
		OVF_InitDeFaultValCLN((LPONVIF)pOnvifClient->OnvifServer,HelloReq);
		printf("==============================ONVIF_ClnSendHello========================\n");
	return !soap_call___dnrd__Hello(pOnvifClient->soapUDP,EndPoint,NULL,HelloReq,&HelloResp);

}
BOOL ONVIF_ClnSendBye(HONVIFCLN hOnvifCln,CHAR * EndPoint,CHAR * ServAddr,CHAR *DeviceType)
{
	    ONVIFCLIENT *pOnvifClient                  =(ONVIFCLIENT*)hOnvifCln;
	   	NEWCLN   (BypeReq ,pOnvifClient->soapUDP,struct d__ByeType);
		//	NEWCLN   (BypeResp,pOnvifClient->soapUDP,struct d__ResolveType);
		struct d__ResolveType BypeResp;
		NEWCLNIII(addr,pOnvifClient->soapUDP,CHAR,OVFCHARLENTH);

	    BypeReq->Types								= DeviceType;
		BypeReq->XAddrs								= ServAddr;
		BypeReq->wsa__EndpointReference.Address		= addr;
		OVF_InitDeFaultValCLNBye((LPONVIF)pOnvifClient->OnvifServer,BypeReq);
	return !soap_call___dnrd__Bye(pOnvifClient->soapUDP,EndPoint,NULL,BypeReq,&BypeResp);
}
