#include "soapH.h"
#include "soapStub.h"
#include "OVF_Export.h"
#include "OVF_Core.h"
#include "OVF_Discovery.h"

extern char g_myip[64];
SOAP_FMAC5 int SOAP_FMAC6 __dndl__Probe(struct soap* soap, struct d__ProbeType *d__Probe, struct d__ProbeMatchesType *d__ProbeMatches)
{
	
	struct d__ProbeMatchType * ProbeMatch= (struct d__ProbeMatchType *) soap_malloc(soap,sizeof(struct d__ProbeMatchType));
	struct d__ScopesType     * scopes    = (struct d__ScopesType     *) soap_malloc(soap,sizeof(struct d__ScopesType));
    CHAR *MessageID                      = (CHAR    *) soap_malloc(soap,64);
    CHAR * szXAddr                       = (CHAR    *) soap_malloc(soap,64);
    CHAR * szEndpointReference           = (CHAR    *) soap_malloc(soap,64);
	CHAR * SoapItem                      = (CHAR    *) soap_malloc(soap,1024);
	//char buf[]="464A4854-4656-5242-4530-313035394100";
//	char buf1[]="1319d68a-2192-11314-4121-313035394100";
    wsa__Relationship *wsa_RelatesTo     = (struct wsa__Relationship*)  soap_malloc(soap,sizeof(struct wsa__Relationship));
 
	OVFDISCONVERYINFO *OVFDiscoveryInfo  = (OVFDISCONVERYINFO    *) soap_malloc(soap,sizeof(OVFDISCONVERYINFO));
    ONVIF             *Onvif             = (ONVIF*)soap->hdOnvif;


    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDiscovery,GetDiscoveryInfo);
    if(FALSE==Onvif->CallBackOvf->CallBackDiscovery->GetDiscoveryInfo(OVFDiscoveryInfo))return SOAP_FAULT;
   // sprintf(szXAddr            , "%s/onvif/device_service", OVFDiscoveryInfo->DevRootUrl);
   sprintf(szXAddr            , "%s/onvif/device_service", OVFDiscoveryInfo->DevRootUrl);
	 sprintf(szEndpointReference, "um:uuid:%s", OVFDiscoveryInfo->DevGuid);
//	sprintf(szEndpointReference, "uuid:%s", buf);
	soap_default_d__ProbeMatchType(soap, ProbeMatch);
	soap_default_d__ScopesType    (soap, scopes);
	
	if (soap->header){
        strcpy(MessageID, "urn:uuid:");
    //    OVF_CreateUUIDS(&(MessageID[9]));
		strcpy(&(MessageID[9]),OVFDiscoveryInfo->DevGuid);
	//   strcpy(&(MessageID[9]),buf1);

		if(soap->header->wsa__MessageID)
		{
	//		printf("remote wsa__MessageID : %s\n",soap->header->wsa__MessageID);
 			soap->header->wsa__RelatesTo =wsa_RelatesTo;
			soap_default__wsa__RelatesTo(soap, soap->header->wsa__RelatesTo);
			soap->header->wsa__RelatesTo->__item = soap->header->wsa__MessageID;

			soap->header->wsa__MessageID = MessageID;
			soap->header->wsa__To     = "http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous";
			soap->header->wsa__Action = "http://schemas.xmlsoap.org/ws/2005/04/discovery/ProbeMatches";
		 
		}
	}
  /*  sprintf(SoapItem,"onvif://www.onvif.org/type/avencoder "
                     "onvif://www.onvif.org/location/%s " 
                     "onvif://www.onvif.org/name/%s ",
	                   OVFDiscoveryInfo->DevLocation,
					   OVFDiscoveryInfo->DevName);*/
	sprintf(SoapItem,"onvif://www.onvif.org/type/Network_Video_Transmitter "
	                 "onvif://www.onvif.org/type/ptz  "
	                 "onvif://www.onvif.org/type/video_encoder "
	                 "onvif://www.onvif.org/Hardware/maliang "
	                 "onvif://www.onvif.org/location/China  "
                     "onvif://www.onvif.org/location/%s " 
                     "onvif://www.onvif.org/name/%s "
                     "onvif://www.onvif.org/location/subaddress/%s",
	                   OVFDiscoveryInfo->DevLocation,
					           "LHY",
					           g_myip);
	
/*	sprintf(SoapItem,"onvif://www.onvif.org/type/Network_Video_Transmitter"
	                  "onvif://www.onvif.org/type/ptz"
	                  "onvif://www.onvif.org/type/video_encoder"
	                  "onvif://www.onvif .org/Hardware/%s"
                     "onvif://www.onvif.org/location/%s", 
                     "onvif://www.onvif.org/name/%s",
	                   OVFDiscoveryInfo->DevLocation,
	                   OVFDiscoveryInfo->DevLocation,
					   OVFDiscoveryInfo->DevName);*/
	
	scopes->__item =   SoapItem;  //位置;型号;设备名称
 	ProbeMatch->wsa__EndpointReference.Address = szEndpointReference;//"urn:uuid:464A4854-4656-5242-4530-313035394100";
	ProbeMatch->Types                          = OVFDiscoveryInfo->DevType;
	ProbeMatch->Scopes                         = scopes;
	ProbeMatch->XAddrs                         = szXAddr;
	ProbeMatch->MetadataVersion                = 1;

	d__ProbeMatches->__sizeProbeMatch         = 1;
	d__ProbeMatches->ProbeMatch               = ProbeMatch;

    STRNCPY(Onvif->xAddr,szXAddr,256);
    STRNCPY(Onvif->MessageID,MessageID,64);
    STRNCPY(Onvif->EndpointReference,szEndpointReference,64);
  //  STRNCPY(Onvif->Namespace,);
  
    return SOAP_OK;
}


SOAP_FMAC5 int SOAP_FMAC6 __dnrd__Hello(struct soap* soap, struct d__HelloType *d__Hello, struct d__ResolveType *dn__HelloResponse)
{
 	wsa__EndpointReferenceType *HelResp	 = (wsa__EndpointReferenceType *) soap_malloc(soap,sizeof(wsa__EndpointReferenceType));
 	wsa__ServiceNameType *SerName  =(wsa__ServiceNameType *)soap_malloc(soap,sizeof(wsa__ServiceNameType));
 	wsa__ReferenceParametersType *ReParameters	= (wsa__ReferenceParametersType *)soap_malloc(soap,sizeof(wsa__ReferenceParametersType));
 	wsa__ReferencePropertiesType *ReProperties	= (wsa__ReferencePropertiesType *)soap_malloc(soap,sizeof(wsa__ReferencePropertiesType));
 	char **Any ;
 	OVFDISCONVERYINFO *OVFDiscoveryInfo  = (OVFDISCONVERYINFO    *) soap_malloc(soap,sizeof(OVFDISCONVERYINFO));
 	CHAR * szXAddr                       = (CHAR    *) soap_malloc(soap,64);
 	CHAR * szEndpointReference           = (CHAR    *) soap_malloc(soap,64);
 	CHAR * SoapItem                      = (CHAR    *) soap_malloc(soap,1024);
 	ONVIF	*Onvif			= (ONVIF*)soap->hdOnvif;
     CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDiscovery,GetDiscoveryInfo);
 	if(FALSE==Onvif->CallBackOvf->CallBackDiscovery->GetDiscoveryInfo(OVFDiscoveryInfo))return SOAP_FAULT;
 	HelResp->ServiceName			= SerName;
 	HelResp->ReferenceParameters	= ReParameters;
 	HelResp->ReferenceProperties	= ReProperties;
 	Any=(char *)soap_malloc(soap,sizeof(char *));
 	*Any =(char)soap_malloc(soap,sizeof(char)*1024);
 	HelResp->ReferenceParameters->__any = Any;
 	sprintf(szXAddr  , "%s/onvif/device_service", OVFDiscoveryInfo->DevRootUrl);
 	sprintf(szEndpointReference, "um:uuid:%s", OVFDiscoveryInfo->DevGuid);
 	sprintf(SoapItem,"onvif://www.onvif.org/type/avencoder "
 		"onvif://www.onvif.org/location/%s " 
 		"onvif://www.onvif.org/name/%s ",
 		OVFDiscoveryInfo->DevLocation,
 		OVFDiscoveryInfo->DevName); 
 	HelResp->Address  = szXAddr;
 	HelResp->ServiceName->PortName = szEndpointReference;
 	*HelResp->ReferenceParameters->__any = SoapItem;
 	dn__HelloResponse->wsa__EndpointReference = *HelResp;
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __dnrd__Bye(struct soap* soap, struct d__ByeType *d__Bye, struct d__ResolveType *dn__ByeResponse)
{
// 	wsa__EndpointReferenceType *ByeResp	 = (wsa__EndpointReferenceType *) soap_malloc(soap,sizeof(wsa__EndpointReferenceType));
// 	wsa__ServiceNameType *SerName  =(wsa__ServiceNameType *)soap_malloc(soap,sizeof(wsa__ServiceNameType));
// 	wsa__ReferenceParametersType *ReParameters	= (wsa__ReferenceParametersType *)soap_malloc(soap,sizeof(wsa__ReferenceParametersType));
// 	wsa__ReferencePropertiesType *ReProperties	= (wsa__ReferencePropertiesType *)soap_malloc(soap,sizeof(wsa__ReferencePropertiesType));
// 	char **Any ;
// 	OVFDISCONVERYINFO *OVFDiscoveryInfo  = (OVFDISCONVERYINFO    *) soap_malloc(soap,sizeof(OVFDISCONVERYINFO));
// 	CHAR * szXAddr                       = (CHAR    *) soap_malloc(soap,64);
// 	CHAR * szEndpointReference           = (CHAR    *) soap_malloc(soap,64);
// 	CHAR * SoapItem                      = (CHAR    *) soap_malloc(soap,1024);
// 	ONVIF	*Onvif			= (ONVIF*)soap->hdOnvif;
//     CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDiscovery,GetDiscoveryInfo);
// 	if(FALSE==Onvif->CallBackOvf->CallBackDiscovery->GetDiscoveryInfo(OVFDiscoveryInfo))return SOAP_FAULT;
// 	ByeResp->ServiceName			= SerName;
// 	ByeResp->ReferenceParameters	= ReParameters;
// 	ByeResp->ReferenceProperties	= ReProperties;
// 	Any=(char *)soap_malloc(soap,sizeof(char *));
// 	*Any =(char)soap_malloc(soap,sizeof(char)*1024);
// 	ByeResp->ReferenceParameters->__any = Any;
// 	sprintf(szXAddr  , "%s/onvif/device_service", OVFDiscoveryInfo->DevRootUrl);
// 	sprintf(szEndpointReference, "uuid:%s", OVFDiscoveryInfo->DevGuid);
// 	sprintf(SoapItem,"onvif://www.onvif.org/type/avencoder "
// 		"onvif://www.onvif.org/location/%s " 
// 		"onvif://www.onvif.org/name/%s ",
// 		OVFDiscoveryInfo->DevLocation,
// 		OVFDiscoveryInfo->DevName); 
// 	ByeResp->Address  = szXAddr;
// 	ByeResp->ServiceName->PortName = szEndpointReference;
// 	*ByeResp->ReferenceParameters->__any = SoapItem;
// 	dn__ByeResponse->wsa__EndpointReference = *ByeResp;
   return SOAP_OK;
}

