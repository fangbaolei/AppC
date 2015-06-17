//OVF_DeviceManager.c
#include<stdio.h>
#include "stdsoap2.h"
#include "soapH.h"
#include "soapStub.h"
#include "OVF_Export.h"
#include "OVF_Core.h"
#include "OVF_Discovery.h"

 char pbuf_addr[128] = {0};
//ONVIF相关
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetServices(struct soap* hSoap, struct _tds__GetServices *tds__GetServices, struct _tds__GetServicesResponse *tds__GetServicesResponse)
{
	// printf("===============================================__tds__GetServices=================================\n");
    ONVIF                   *pOnvif  =   (ONVIF*)hSoap->hdOnvif;
    struct tt__OnvifVersion *Version =   (struct tt__OnvifVersion*)soap_malloc(hSoap,sizeof(struct tt__OnvifVersion));
     if(FALSE==pOnvif->CallBackOvf->CallBackDevManage->GetImg(pbuf_addr))return SOAP_FAULT;
	NEWMIII(tds__GetServicesResponse->Service,struct tds__Service,1);
	if(NULL != pOnvif){
		Version->Major = pOnvif->Ver;
		Version->Minor = pOnvif->SubVer;
		tds__GetServicesResponse->Service->Namespace=pOnvif->Namespace;
		tds__GetServicesResponse->Service->XAddr    =pOnvif->xAddr;
		//(tds__GetServicesResponse->Service+sizeof(struct tds__Service))->Namespace = pOnvif->Namespace;
		//(tds__GetServicesResponse->Service+sizeof(struct tds__Service))->XAddr = pbuf_addr;
	}	
    tds__GetServicesResponse->__sizeService     =1;
 //   (tds__GetServicesResponse->Service+sizeof(struct tds__Service))->Version  =Version;
  //  (tds__GetServicesResponse->Service+sizeof(struct tds__Service))->__size   =0;
    
    tds__GetServicesResponse->Service->Version  =Version;
    tds__GetServicesResponse->Service->__size   =0;
    if(tds__GetServices->IncludeCapability){//包含GetServiceCapabilities,这部分需要手工制作XML脚本
		// tds__GetServicesResponse.Service.Capabilities.
    }   
	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetCapabilities(struct soap* hSoap, struct _tds__GetCapabilities *tds__GetCapabilities, struct _tds__GetCapabilitiesResponse *tds__GetCapabilitiesResponse)
{ 
	 //printf("===============================================__tds__GetCapabilities=================================\n");
    NEW(DevmSvCap ,DEVMSVCAP);

    //子结构DEVICE
    NEW(DevCap   ,struct tt__Capabilities);

  	NEW(Device   ,struct tt__DeviceCapabilities );  
	NEW(Network ,struct tt__NetworkCapabilities ); 
    NEW(Extension,struct tt__NetworkCapabilitiesExtension);
    NEW(System  ,struct tt__SystemCapabilities );
    NEW(SupportedVersions,struct tt__OnvifVersion);
    NEW(SysExtension, struct tt__SystemCapabilitiesExtension);
    NEW(IO      ,struct tt__IOCapabilities );	 
    NEW(Security,struct tt__SecurityCapabilities );
    NEW(Imaging ,struct tt__ImagingCapabilities);
    NEW(Ptz,     struct tt__PTZCapabilities);
    NEW(Media   ,struct tt__MediaCapabilities);
	NEW(Events, struct tt__EventCapabilities);
	NEW(StreamingCapabilities,struct tt__RealTimeStreamingCapabilities);
    INT Category =0;
    ONVIF        *Onvif      = (ONVIF*)hSoap->hdOnvif;  
    NEWMIII(Media->Extension,struct tt__MediaCapabilitiesExtension,1);
	NEWMIII(Media->Extension->ProfileCapabilities,struct tt__ProfileCapabilities,1);

    Device->IO =IO;
	Device->Network=Network;
//	Device->Network->Extension=Extension;//(V2.1)
	Device->Security = Security;
	Device->System   = System;
	Device->System->SupportedVersions=SupportedVersions;
//	Device->System->Extension=SysExtension;
	if (NULL!= tds__GetCapabilities->Category)
		Category = *tds__GetCapabilities->Category;
    
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,GetDevServerCap);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->GetDevServerCap(DevmSvCap))return SOAP_FAULT;

	Device->Network->DynDNS                          =&DevmSvCap->CapDevice.Network.SupDynDNS;
	Device->Network->IPFilter                        =&DevmSvCap->CapDevice.Network.SupIPFilter;  
	Device->Network->IPVersion6                      =&DevmSvCap->CapDevice.Network.SupIPVersion6;
	Device->Network->ZeroConfiguration               =&DevmSvCap->CapDevice.Network.SupZeroConfiguration;
//	Device->Network->Extension->Dot11Configuration   =&DevmSvCap->CapDevice.Network.SupDot11Configuration; //(V2.1)

	Device->System->DiscoveryBye      =  DevmSvCap->CapDevice.System.SupDiscoveryBye;
	Device->System->DiscoveryResolve  =  DevmSvCap->CapDevice.System.SupDiscoveryResolve;
	Device->System->FirmwareUpgrade   =  DevmSvCap->CapDevice.System.SupFirmwareUpgrade;
	Device->System->RemoteDiscovery   =  DevmSvCap->CapDevice.System.SupRemoteDiscovery;
	Device->System->SystemBackup      =  DevmSvCap->CapDevice.System.SupHttpSystemBackup;
	Device->System->SystemLogging     =  DevmSvCap->CapDevice.System.SupSystemLogging;
	Device->System->__sizeSupportedVersions=1;
	Device->System->SupportedVersions->Major =1;
	Device->System->SupportedVersions->Minor =0;
	
	// Device->System->Extension->HttpFirmwareUpgrade    =&DevmSvCap->CapDevice.System.SupHttpFirmwareUpgrade;
	//  Device->System->Extension->HttpSupportInformation =&DevmSvCap->CapDevice.System.SupHttpSupportInformation;
	// Device->System->Extension->HttpSystemBackup       =&DevmSvCap->CapDevice.System.SupHttpSystemBackup;
	//  Device->System->Extension->HttpSystemLogging      =&DevmSvCap->CapDevice.System.SupHttpSystemLogging;
	StreamingCapabilities->RTP_USCORERTSP_USCORETCP=&DevmSvCap->CapMedia.Streaming.SupRTP_USCORERTSP_USCORETCP;
	StreamingCapabilities->RTP_USCORETCP           =&DevmSvCap->CapMedia.Streaming.SupRTP_USCORETCP;
	StreamingCapabilities->RTPMulticast            =&DevmSvCap->CapMedia.Streaming.SupRTPMulticast;
	Device->IO->InputConnectors					   =&DevmSvCap->CapDevice.IO.InputConnectors;
	Device->IO->RelayOutputs                       =&DevmSvCap->CapDevice.IO.RelayOutputs;

	if (tt__CapabilityCategory__Analytics==Category || tt__CapabilityCategory__All==Category){
		DevCap->Analytics   = NULL;//(struct tt__AnalyticsCapabilities *)&DevmSvCap->CapAnalytics;
	}
	if (tt__CapabilityCategory__Device==Category || tt__CapabilityCategory__All==Category){
		DevCap->Device				 = Device; 
		DevCap->Device->XAddr		 = DevmSvCap->CapDevice.XAddr ;
	}
	if (tt__CapabilityCategory__Events==Category || tt__CapabilityCategory__All==Category){
		DevCap->Events			     =Events;
		DevCap->Events->XAddr		 =DevmSvCap->CapEvent.SupXAddr;
		DevCap->Events->WSPausableSubscriptionManagerInterfaceSupport	= DevmSvCap->CapEvent.SupWSPausableSubscriptionManagerInterfaceSupport;
		DevCap->Events->WSPullPointSupport								= DevmSvCap->CapEvent.SupWSPullPointSupport;
		DevCap->Events->WSSubscriptionPolicySupport						= DevmSvCap->CapEvent.SupWSSubscriptionPolicySupport;

	}
	if (tt__CapabilityCategory__Imaging==Category|| tt__CapabilityCategory__All==Category){
		DevCap->Imaging     = Imaging;
		DevCap->Imaging->XAddr     = DevmSvCap->CapImag.SupXAddr;
	}
	if (tt__CapabilityCategory__Media==Category || tt__CapabilityCategory__All==Category){
		DevCap->Media       = Media;
		DevCap->Media->StreamingCapabilities						   = StreamingCapabilities;
		DevCap->Media->XAddr										   = DevmSvCap->CapMedia.SupXAddr;
		DevCap->Media->Extension->ProfileCapabilities->MaximumNumberOfProfiles =2;
	}
	if (tt__CapabilityCategory__PTZ==Category || tt__CapabilityCategory__All==Category){
		DevCap->PTZ         = Ptz;
		DevCap->PTZ->XAddr  = DevmSvCap->CapPTZ.SupXAddr;
	}
	
    tds__GetCapabilitiesResponse->Capabilities=DevCap;    
    return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetServiceCapabilities(struct soap*  hSoap, struct _tds__GetServiceCapabilities *tds__GetServiceCapabilities, struct _tds__GetServiceCapabilitiesResponse *tds__GetServiceCapabilitiesResponse)
{
	//printf("===============================================__tds__GetServiceCapabilities=================================\n");
	NEW(DevmSvCap ,DEVMSVCAP);
	ONVIF   * Onvif      = (ONVIF*)hSoap->hdOnvif;
	
    NEW(DevSvCap  ,struct tds__DeviceServiceCapabilities);
	NEWMIII(DevSvCap->Network,struct tds__NetworkCapabilities,1);
	NEWMIII(DevSvCap->System  ,struct tds__SystemCapabilities,1);
	NEWMIII(DevSvCap->Security,struct tds__SecurityCapabilities,1);

   
     
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,GetDevServerCap);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->GetDevServerCap(DevmSvCap))return SOAP_FAULT;
	DevSvCap->Security->UsernameToken				   =&DevmSvCap->CapDevice.Security.SupUsernameToken;
	DevSvCap->Network->DynDNS                          =&DevmSvCap->CapDevice.Network.SupDynDNS;
	DevSvCap->Network->IPFilter                        =&DevmSvCap->CapDevice.Network.SupIPFilter;      
	DevSvCap->Network->IPVersion6                      =&DevmSvCap->CapDevice.Network.SupIPVersion6;
	DevSvCap->Network->ZeroConfiguration               =&DevmSvCap->CapDevice.Network.SupZeroConfiguration;
	
    DevSvCap->System->DiscoveryBye      =  &DevmSvCap->CapDevice.System.SupDiscoveryBye;
    DevSvCap->System->DiscoveryResolve  =  &DevmSvCap->CapDevice.System.SupDiscoveryResolve;
    DevSvCap->System->FirmwareUpgrade   =  &DevmSvCap->CapDevice.System.SupFirmwareUpgrade;
    DevSvCap->System->RemoteDiscovery   =  &DevmSvCap->CapDevice.System.SupRemoteDiscovery;
    DevSvCap->System->SystemBackup      =  &DevmSvCap->CapDevice.System.SupHttpSystemBackup;
    DevSvCap->System->SystemLogging     =  &DevmSvCap->CapDevice.System.SupSystemLogging;

	
    DevSvCap->__size   =0;
    tds__GetServiceCapabilitiesResponse->Capabilities=DevSvCap;
	return SOAP_OK;
}
//WDS 命名范围(用于添加删除或获取WDS命名范围的定义网络文档，可以不予支持)
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetScopes(struct soap* hSoap, struct _tds__GetScopes *tds__GetScopes, struct _tds__GetScopesResponse *tds__GetScopesResponse){
	//printf("===============================================__tds__GetScopes=================================\n");
	CHAR * SoapItem                      = (CHAR    *) soap_malloc(hSoap,1024);
	OVFDISCONVERYINFO *OVFDiscoveryInfo  = (OVFDISCONVERYINFO    *) soap_malloc(hSoap,sizeof(OVFDISCONVERYINFO));
    ONVIF             *Onvif             = (ONVIF*)hSoap->hdOnvif;
	NEW(scopes,struct tt__Scope);	
	
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDiscovery,GetDiscoveryInfo);
    if(FALSE==Onvif->CallBackOvf->CallBackDiscovery->GetDiscoveryInfo(OVFDiscoveryInfo))return SOAP_FAULT;
	sprintf(SoapItem,"onvif://www.onvif.org/hardware "
		"onvif://www.onvif.org/type/avencoder "
		"onvif://www.onvif.org/location/%s " 
		"onvif://www.onvif.org/name/%s ",
		OVFDiscoveryInfo->DevLocation,
					   OVFDiscoveryInfo->DevName); 
	scopes->ScopeItem = SoapItem;
	tds__GetScopesResponse->__sizeScopes =1;

	tds__GetScopesResponse->Scopes =scopes;
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetScopes(struct soap* hSoap, struct _tds__SetScopes *tds__SetScopes, struct _tds__SetScopesResponse *tds__SetScopesResponse)
{//printf("===============================================__tds__SetScopes=================================\n");
	return SOAP_OK;}

SOAP_FMAC5 int SOAP_FMAC6 __tds__AddScopes(struct soap* hSoap, struct _tds__AddScopes *tds__AddScopes, struct _tds__AddScopesResponse *tds__AddScopesResponse)
{
	//printf("===============================================__tds__AddScopes=================================\n");
	return SOAP_OK;}

SOAP_FMAC5 int SOAP_FMAC6 __tds__RemoveScopes(struct soap* hSoap, struct _tds__RemoveScopes *tds__RemoveScopes, struct _tds__RemoveScopesResponse *tds__RemoveScopesResponse)
{printf("===============================================__tds__RemoveScopes=================================\n");
	return SOAP_OK;}
/////////////////网络发现的相关配置操作函数////////////////////////////
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDiscoveryMode(struct soap* hSoap, struct _tds__GetDiscoveryMode *tds__GetDiscoveryMode, struct _tds__GetDiscoveryModeResponse *tds__GetDiscoveryModeResponse)
{
	 //printf("===============================================__tds__GetDiscoveryMode=================================\n");
    ONVIF             *Onvif      = (ONVIF*)hSoap->hdOnvif; 
    if(NULL!=Onvif->soapUDP)
		 tds__GetDiscoveryModeResponse->DiscoveryMode=tt__DiscoveryMode__Discoverable;
    else
		tds__GetDiscoveryModeResponse->DiscoveryMode=tt__DiscoveryMode__NonDiscoverable;
    return SOAP_OK;
 }

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetDiscoveryMode(struct soap* hSoap, struct _tds__SetDiscoveryMode *tds__SetDiscoveryMode, struct _tds__SetDiscoveryModeResponse *tds__SetDiscoveryModeResponse)
{ 
	// printf("===============================================__tds__SetDiscoveryMode=================================\n");
    ONVIF             *Onvif      = (ONVIF*)hSoap->hdOnvif; 

    if(tds__SetDiscoveryMode->DiscoveryMode==tt__DiscoveryMode__Discoverable)
        OVF_EnableDiscovery(hSoap->hdOnvif,TRUE);
    if(tds__SetDiscoveryMode->DiscoveryMode==tt__DiscoveryMode__NonDiscoverable)
        OVF_EnableDiscovery(hSoap->hdOnvif,FALSE);
    return SOAP_OK;
 }

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetRemoteDiscoveryMode(struct soap* hSoap, struct _tds__GetRemoteDiscoveryMode *tds__GetRemoteDiscoveryMode, struct _tds__GetRemoteDiscoveryModeResponse *tds__GetRemoteDiscoveryModeResponse)
{
	// printf("===============================================__tds__GetRemoteDiscoveryMode=================================\n");
    ONVIF             *Onvif      = (ONVIF*)hSoap->hdOnvif; 
    if(NULL!=Onvif->soapUDP)
    tds__GetRemoteDiscoveryModeResponse->RemoteDiscoveryMode=tt__DiscoveryMode__Discoverable;
       else
    tds__GetRemoteDiscoveryModeResponse->RemoteDiscoveryMode=tt__DiscoveryMode__NonDiscoverable;
    return SOAP_OK;
 }

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetRemoteDiscoveryMode(struct soap* hSoap, struct _tds__SetRemoteDiscoveryMode *tds__SetRemoteDiscoveryMode, struct _tds__SetRemoteDiscoveryModeResponse *tds__SetRemoteDiscoveryModeResponse)
{
	  //printf("===============================================__tds__SetRemoteDiscoveryMode=================================\n");
    ONVIF             *Onvif      = (ONVIF*)hSoap->hdOnvif; 

    if(tds__SetRemoteDiscoveryMode->RemoteDiscoveryMode==tt__DiscoveryMode__Discoverable)
        OVF_EnableDiscovery(hSoap->hdOnvif,TRUE);
    if(tds__SetRemoteDiscoveryMode->RemoteDiscoveryMode==tt__DiscoveryMode__NonDiscoverable)
        OVF_EnableDiscovery(hSoap->hdOnvif,FALSE);
    return SOAP_OK;
}
//网络发现之代理网关
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDPAddresses(struct soap* hSoap, struct _tds__GetDPAddresses *tds__GetDPAddresses, struct _tds__GetDPAddressesResponse *tds__GetDPAddressesResponse)
{//printf("===============================================__tds__GetDPAddresses=================================\n");
	return SOAP_OK;}
SOAP_FMAC5 int SOAP_FMAC6 __tds__SetDPAddresses(struct soap* hSoap, struct _tds__SetDPAddresses *tds__SetDPAddresses, struct _tds__SetDPAddressesResponse *tds__SetDPAddressesResponse)
{//printf("===============================================__tds__SetDPAddresses=================================\n");
	return SOAP_OK;}
/////////////////////////设备的命名端点.GUID//////////////////////
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetEndpointReference(struct soap* hSoap, struct _tds__GetEndpointReference *tds__GetEndpointReference, struct _tds__GetEndpointReferenceResponse *tds__GetEndpointReferenceResponse)
{
	 // printf("===============================================__tds__GetEndpointReference=================================\n");
	  ONVIF             *Onvif      = (ONVIF*)hSoap->hdOnvif;   
	  tds__GetEndpointReferenceResponse->GUID  =Onvif->EndpointReference;
	  tds__GetEndpointReferenceResponse->__size=0;
	return SOAP_OK;
}

/////////////////////////客户端可用的WSDL and schema 链接,可不予支持////////
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetWsdlUrl(struct soap* hSoap, struct _tds__GetWsdlUrl *tds__GetWsdlUrl, struct _tds__GetWsdlUrlResponse *tds__GetWsdlUrlResponse)
{
	//printf("===============================================__tds__GetWsdlUrl=================================\n");
    NEW(DevmSvCap ,DEVMSVCAP);
	int i= sizeof(DEVMSVCAP);
	ONVIF             *Onvif      = (ONVIF*)hSoap->hdOnvif;    
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,GetDevServerCap);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->GetDevServerCap(DevmSvCap))return SOAP_FAULT;
	if(NULL != DevmSvCap){	
		tds__GetWsdlUrlResponse->WsdlUrl	= DevmSvCap->CapDevice.XAddr;
	}

	return SOAP_OK;
}

////////////////////////获取系统相关信息的URL链接////////////////
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetSystemUris(struct soap* hSoap, struct _tds__GetSystemUris *tds__GetSystemUris, struct _tds__GetSystemUrisResponse *tds__GetSystemUrisResponse)
{
  // printf("===============================================__tds__GetSystemUris=================================\n");
    NEW(LogList   ,struct tt__SystemLogUriList);
    NEW(SysUrl    ,SYSTEMURL);

    ONVIF             *Onvif      = (ONVIF*)hSoap->hdOnvif;    
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,GetSystemUrl);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->GetSystemUrl(SysUrl))return SOAP_FAULT;
    LogList->__sizeSystemLog                     =SysUrl->urlSystemLogSize;
  //  LogList->SystemLog                           =(struct tt__SystemLogUri *)SysUrl->urlSystemLog;
	LogList->SystemLog->Type					 =SysUrl->urlSystemLog->LogType;
    tds__GetSystemUrisResponse->SupportInfoUri   =SysUrl->urlSupportInfo;
    tds__GetSystemUrisResponse->SystemBackupUri  =SysUrl->urlSystemBackup;
    tds__GetSystemUrisResponse->SystemLogUris    =LogList;
    
	return SOAP_OK;
}

