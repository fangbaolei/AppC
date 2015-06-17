//OVF_DeviceManager_NetWork.c
#include<stdio.h>
#include "stdsoap2.h"
#include "soapH.h"
#include "soapStub.h"
#include "OVF_Export.h"
#include "OVF_Core.h"
#include "OVF_Discovery.h"

///////////////////////////////网络配置////////////////////////////////////////////////////

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetHostname(struct soap* hSoap, struct _tds__GetHostname *tds__GetHostname, struct _tds__GetHostnameResponse *tds__GetHostnameResponse)
{
	
    NEW(HostName    ,struct tt__HostnameInformation);
    NEW(NetExtConfig,NETEXTCONFIG);

    ONVIF             *Onvif      = (ONVIF*)hSoap->hdOnvif;    
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,GetNetConfigExt);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->GetNetConfigExt(NetExtConfig))return SOAP_FAULT;

    HostName->FromDHCP =NetExtConfig->NetHostNameFormDHCP;
 	HostName->Name     =NetExtConfig->NetHostName;
    tds__GetHostnameResponse->HostnameInformation=HostName;
    printf("===============================================__tds__GetHostname=================================\n");
    return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetHostname(struct soap* hSoap, struct _tds__SetHostname *tds__SetHostname, struct _tds__SetHostnameResponse *tds__SetHostnameResponse)
{
	 printf("===============================================__tds__SetHostname=================================\n");
	 ONVIF             *Onvif      = (ONVIF*)hSoap->hdOnvif;
    NEW(NetExtConfig,NETEXTCONFIG);
	NEWMIII(hSoap->fault ,struct SOAP_ENV__Fault,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code,struct SOAP_ENV__Code ,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode,struct SOAP_ENV__Code,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode,struct SOAP_ENV__Code ,1);
		NEWMIII(hSoap->fault->SOAP_ENV__Reason,struct SOAP_ENV__Reason,1);

   
	if (NULL != tds__SetHostname)
		STRNCPY(NetExtConfig->NetHostName ,tds__SetHostname->Name,OVFCHARLENTH);
  
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,SetNetConfigExt);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->SetNetConfigExt(NetExtConfig,NETCFG_CMD_SETHOSTNAME)){

		hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode->SOAP_ENV__Value ="ter:InvalidHostname" ;
		hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Value ="ter:InvalidArgVal";
 		hSoap->fault->SOAP_ENV__Reason->SOAP_ENV__Text="The requested hostname cannot be accepted by the NVT.";

		return SOAP_FAULT;
	}

	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __tds__SetHostnameFromDHCP(struct soap* hSoap, struct _tds__SetHostnameFromDHCP *tds__SetHostnameFromDHCP, struct _tds__SetHostnameFromDHCPResponse *tds__SetHostnameFromDHCPResponse)
{
	printf("===============================================__tds__SetHostnameFromDHCP=================================\n");
	NEW(NetExtConfig,NETEXTCONFIG);
	
    ONVIF             *Onvif      = (ONVIF*)hSoap->hdOnvif;
	if((NULL != tds__SetHostnameFromDHCP) && (NULL !=&tds__SetHostnameFromDHCP->FromDHCP))
		NetExtConfig->NetHostNameFormDHCP=tds__SetHostnameFromDHCP->FromDHCP;
  
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,SetNetConfigExt);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->SetNetConfigExt(NetExtConfig,NETCFG_CMD_SETHOSTNAMEDHCP))return SOAP_FAULT;

	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDNS(struct soap* hSoap, struct _tds__GetDNS *tds__GetDNS, struct _tds__GetDNSResponse *tds__GetDNSResponse)
{
	 printf("===============================================__tds__GetDNS=================================\n");
    INT  i =0;
    NEW(Dns         ,struct tt__DNSInformation);
    NEW(NetExtConfig,NETEXTCONFIG);
    ONVIF             *Onvif      = (ONVIF*)hSoap->hdOnvif; 

    NEWMII (sIPAddr,CHAR*,2);
	NEWMII (sDomain,CHAR*,2);
    NEWMIII(Dns->DNSFromDHCP,struct tt__IPAddress,2);
    NEWMIII(Dns->DNSManual,struct tt__IPAddress,2);
	 
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,GetNetConfigExt);
   if(FALSE==Onvif->CallBackOvf->CallBackDevManage->GetNetConfigExt(NetExtConfig))return SOAP_FAULT;
	Dns->__sizeSearchDomain		   = NetExtConfig->NetsizeSearchDomain;
	for (i=0;i<NetExtConfig->NetsizeSearchDomain;i++)
	{
		sDomain[i]                 = NetExtConfig->NetSearchDomain[i];
		Dns->SearchDomain		   = &sDomain[i];
	}
    Dns->FromDHCP                  = NetExtConfig->NetDnsFromDHCP;
    if(!Dns->FromDHCP ){
		for(i=0;i<NetExtConfig->NetDnsIPV4Size;i++){
			sIPAddr[i]                    = NetExtConfig->NetDnsIPV4[0];
			Dns->DNSManual[i].IPv4Address = &sIPAddr[i];
		}
   		Dns->__sizeDNSManual           =NetExtConfig->NetDnsIPV4Size;
		Dns->DNSFromDHCP               =NULL;

    }else{
		for(i=0;i<NetExtConfig->NetDnsIPV4Size;i++){
			sIPAddr[i]                      = NetExtConfig->NetDnsIPV4[0];
			Dns->DNSFromDHCP[i].IPv4Address = &sIPAddr[i];
		}
   		Dns->__sizeDNSManual           =NetExtConfig->NetDnsIPV4Size;
		Dns->DNSManual                 =NULL;
	}
	tds__GetDNSResponse->DNSInformation=Dns;
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetDNS(struct soap* hSoap, struct _tds__SetDNS *tds__SetDNS, struct _tds__SetDNSResponse *tds__SetDNSResponse)
{
	  printf("===============================================__tds__SetDNS=================================\n");
    NEW(NetExtConfig,NETEXTCONFIG);
    INT i;
    ONVIF             *Onvif      = (ONVIF*)hSoap->hdOnvif;
	NEWMIII(hSoap->fault ,struct SOAP_ENV__Fault,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code,struct SOAP_ENV__Code ,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode,struct SOAP_ENV__Code,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode,struct SOAP_ENV__Code ,1);
		NEWMIII(hSoap->fault->SOAP_ENV__Reason,struct SOAP_ENV__Reason,1);
	if(NULL != tds__SetDNS){
		for(i=0;i<2&&i<tds__SetDNS->__sizeDNSManual;i++) 
		{
			if( NULL != tds__SetDNS->DNSManual)
			{
				STRNCPY(NetExtConfig->NetDnsIPV4[i],*tds__SetDNS->DNSManual->IPv4Address+i,OVFCHARLENTH);
			//	printf("=================================ip_addr=%s=====================================\n",NetExtConfig->NetDnsIPV4[0]);
			}
		}
	} 	
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,SetNetConfigExt);
	if(FALSE==Onvif->CallBackOvf->CallBackDevManage->SetNetConfigExt(NetExtConfig,NETCFG_CMD_SETDNS)){

		hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode->SOAP_ENV__Value ="ter:InvalidIPv4Address" ;
		hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Value ="ter:InvalidArgVal";
 		hSoap->fault->SOAP_ENV__Reason->SOAP_ENV__Text="The suggested IPv4 address is invalid.";

		return SOAP_FAULT;
	}
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetNTP(struct soap* hSoap, struct _tds__GetNTP *tds__GetNTP, struct _tds__GetNTPResponse *tds__GetNTPResponse)
{
	 printf("===============================================__tds__GetNTP=================================\n");
  
    NEW(Ntp         ,struct tt__NTPInformation);
    NEW(NetExtConfig,NETEXTCONFIG);
	INT i;
    ONVIF             *Onvif      = (ONVIF*)hSoap->hdOnvif; 
    NEWMII (sIPAddr,CHAR*,2);
    NEWMIII(Ntp->NTPManual         ,struct tt__NetworkHost,2);
    NEWMIII(Ntp->NTPFromDHCP       ,struct tt__NetworkHost,2);




    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,GetNetConfigExt);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->GetNetConfigExt(NetExtConfig))return SOAP_FAULT;
    if(NetExtConfig->NetNtpFromDHCP){
		Ntp->__sizeNTPFromDHCP=NetExtConfig->NetNtpSize;
		Ntp->FromDHCP         = TRUE;
		Ntp->NTPFromDHCP->Type=NetExtConfig->NetNtpType;
		Ntp->NTPManual		  = NULL;
		if(NetExtConfig->NetNtpType==IPTYPE_DNS){
            for(i=0;i<2&&i<NetExtConfig->NetNtpSize;i++){
				sIPAddr[i]=NetExtConfig->NetNtpDns[i];
			    Ntp->NTPFromDHCP[i].DNSname= &sIPAddr[i];
            } 
		}else if(NetExtConfig->NetNtpType==IPTYPE_V4){
			for(i=0;i<2&&i<NetExtConfig->NetNtpSize;i++){
				sIPAddr[i]=NetExtConfig->NetNtpIPV4[i];
			    Ntp->NTPFromDHCP[i].DNSname= &sIPAddr[i];
            }
		}
    }else{
		Ntp->__sizeNTPManual  =NetExtConfig->NetNtpSize;
		Ntp->FromDHCP         = FALSE;
		Ntp->NTPFromDHCP	  = NULL;
		Ntp->NTPManual->Type  = NetExtConfig->NetNtpType;
// 		if(NetExtConfig->NetNtpType==IPTYPE_DNS){
//             for(i=0;i<2&&i<NetExtConfig->ntp;i++){
// 				sIPAddr[i]=NetExtConfig->NetNtpDns[i];
// 			    Ntp->NTPFromDHCP[i].DNSname= &sIPAddr[i];
//             }
// 		}else if(NetExtConfig->NetNtpType==IPTYPE_V4){
// 			for(i=0;i<2&&i<NetExtConfig->NetNtpSize;i++){
// 				sIPAddr[i]=NetExtConfig->NetNtpIPV4[i];
// 			    Ntp->NTPFromDHCP[i].DNSname =	&sIPAddr[i];
//             }	
// 		}
    }
	tds__GetNTPResponse->NTPInformation =Ntp;
    return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetNTP(struct soap* hSoap, struct _tds__SetNTP *tds__SetNTP, struct _tds__SetNTPResponse *tds__SetNTPResponse)
{
	 printf("===============================================__tds__SetNTP=================================\n");
    NEW(NetExtConfig,NETEXTCONFIG);

    ONVIF             *Onvif      = (ONVIF*)hSoap->hdOnvif;
	int                i;

	NetExtConfig->NetNtpFromDHCP  = FALSE;
	if(NULL != tds__SetNTP){
		NetExtConfig->NetNtpSize =tds__SetNTP->__sizeNTPManual;
		if(NULL != tds__SetNTP->NTPManual){

			if(tds__SetNTP->NTPManual->Type==IPTYPE_DNS){
				for(i=0;i<2&&i<tds__SetNTP->__sizeNTPManual;i++)
				{
					if( NULL != tds__SetNTP->NTPManual)
						STRNCPY(NetExtConfig->NetNtpDns[i],tds__SetNTP->NTPManual->DNSname[i],OVFCHARLENTH);
				}
			}else if(tds__SetNTP->NTPManual->Type==IPTYPE_V4){
				for(i=0;i<2&&i<tds__SetNTP->__sizeNTPManual;i++)
				{
					if(NULL != tds__SetNTP->NTPManual->IPv4Address)
						STRNCPY(NetExtConfig->NetNtpIPV4[i],tds__SetNTP->NTPManual->IPv4Address[i],OVFCHARLENTH);
				}
			}
		}
	
	}
	  CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,SetNetConfigExt);
	 if(FALSE==Onvif->CallBackOvf->CallBackDevManage->SetNetConfigExt(NetExtConfig,NETCFG_CMD_SETNTP))return SOAP_FAULT;
	
    return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDynamicDNS(struct soap* hSoap, struct _tds__GetDynamicDNS *tds__GetDynamicDNS, struct _tds__GetDynamicDNSResponse *tds__GetDynamicDNSResponse)
{
	   printf("===============================================__tds__GetDynamicDNS=================================\n");
    NEW(DynDNS      ,struct tt__DynamicDNSInformation);
    NEW(NetExtConfig,NETEXTCONFIG);

    ONVIF             *Onvif      = (ONVIF*)hSoap->hdOnvif; 

    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,GetNetConfigExt);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->GetNetConfigExt(NetExtConfig))return SOAP_FAULT;
    
	DynDNS->Type    =           NetExtConfig->NetDynamicDnsType;
	DynDNS->Name    = (CHAR**)&(NetExtConfig->NetDynamicDns[0]);
	DynDNS->TTL     =           NetExtConfig->NetDynamicDnsTTL;
	tds__GetDynamicDNSResponse->DynamicDNSInformation = DynDNS;
    return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetDynamicDNS(struct soap* hSoap, struct _tds__SetDynamicDNS *tds__SetDynamicDNS, struct _tds__SetDynamicDNSResponse *tds__SetDynamicDNSResponse)
{
	  printf("===============================================__tds__SetDynamicDNS=================================\n");
    NEW(NetExtConfig,NETEXTCONFIG);

    ONVIF             *Onvif      = (ONVIF*)hSoap->hdOnvif; 
	if(NULL !=tds__SetDynamicDNS){
		 NetExtConfig->NetDynamicDnsType=       tds__SetDynamicDNS->Type  ;
		 STRNCPY(NetExtConfig->NetDynamicDns  ,*tds__SetDynamicDNS->Name,OVFCHARLENTH)   ;
		 STRNCPY(NetExtConfig->NetDynamicDnsTTL,tds__SetDynamicDNS->TTL ,OVFCHARLENTH)     ;
	}
     CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,SetNetConfigExt);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->SetNetConfigExt(NetExtConfig,NETCFG_CMD_SETDNYDNS))return SOAP_FAULT;
          
	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetNetworkDefaultGateway(struct soap* hSoap, struct _tds__GetNetworkDefaultGateway *tds__GetNetworkDefaultGateway, struct _tds__GetNetworkDefaultGatewayResponse *tds__GetNetworkDefaultGatewayResponse)
{   
	  printf("===============================================__tds__GetNetworkDefaultGateway=================================\n");
    NEW( Gateway,struct tt__NetworkGateway);

    NEW(NetExtConfig,NETEXTCONFIG);
	INT		i =0;
    ONVIF             *Onvif      = (ONVIF*)hSoap->hdOnvif; 

	NEWMIII(Gateway->IPv4Address, CHAR* ,5);
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,GetNetConfigExt);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->GetNetConfigExt(NetExtConfig))return SOAP_FAULT;
    Gateway->__sizeIPv4Address = NetExtConfig->NetGatewaySize;
	for (; i<5 && i< (Gateway->__sizeIPv4Address) ; i++)
	{
		Gateway->IPv4Address[i]	= NetExtConfig->NetGateway[i];
	}
	
	tds__GetNetworkDefaultGatewayResponse->NetworkGateway =Gateway;
	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __tds__SetNetworkDefaultGateway(struct soap* hSoap, struct _tds__SetNetworkDefaultGateway *tds__SetNetworkDefaultGateway, struct _tds__SetNetworkDefaultGatewayResponse *tds__SetNetworkDefaultGatewayResponse)
{
	
	 printf("===============================================__tds__SetNetworkDefaultGateway=================================\n");
    NEW(NetExtConfig,NETEXTCONFIG);
    INT i;
    ONVIF             *Onvif      = (ONVIF*)hSoap->hdOnvif; 
	NEWMIII(hSoap->fault ,struct SOAP_ENV__Fault,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code,struct SOAP_ENV__Code ,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode,struct SOAP_ENV__Code,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode,struct SOAP_ENV__Code ,1);
		NEWMIII(hSoap->fault->SOAP_ENV__Reason,struct SOAP_ENV__Reason,1);
	if(NULL != tds__SetNetworkDefaultGateway)
	{
		NetExtConfig->NetGatewaySize  = tds__SetNetworkDefaultGateway->__sizeIPv4Address;
	//	printf("========================================Getway leng=%d==================",NetExtConfig->NetGatewaySize);
		for(i=0;i<5&&i<tds__SetNetworkDefaultGateway->__sizeIPv4Address;i++){
				STRNCPY(NetExtConfig->NetGateway[i],*tds__SetNetworkDefaultGateway->IPv4Address+i,OVFCHARLENTH);
			//	printf("========================================Getway ip=%s==================",NetExtConfig->NetGateway[i]);
		}

	}
	//printf("========================================Getway ip=%s==================",NetExtConfig->NetGateway[0]);
     CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,SetNetConfigExt);
	 if(FALSE==Onvif->CallBackOvf->CallBackDevManage->SetNetConfigExt(NetExtConfig,NETCFG_CMD_SETGATEWAY)){
		 
		 hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode->SOAP_ENV__Value ="ter:InvalidGatewayAddress" ;
		 hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Value ="ter:InvalidArgVal";
 		 hSoap->fault->SOAP_ENV__Reason->SOAP_ENV__Text="The supplied gateway address was invalid.";

		 return SOAP_FAULT;
	 }
  	
	return SOAP_OK;
}
//网络.设备.IP
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetNetworkInterfaces(struct soap* hSoap, struct _tds__GetNetworkInterfaces *tds__GetNetworkInterfaces, struct _tds__GetNetworkInterfacesResponse *tds__GetNetworkInterfacesResponse)
{//此函数或可分解为单一设备点的配置函数...
    printf("===============================================__tds__GetNetworkInterfaces=================================\n");
    NEW(Net,NETINTERFACES );
    ONVIF                        *Onvif      = (ONVIF*)hSoap->hdOnvif;
	INT                           i;
	NEWMII(Interface,struct tt__NetworkInterface,2);
	for(i=0;i<2;i++){
		NEWMIII(Interface[i].Info,struct tt__NetworkInterfaceInfo,1);
		NEWMIII(Interface[i].IPv4,struct tt__IPv4NetworkInterface,1);
		NEWMIII(Interface[i].IPv4->Config,struct tt__IPv4Configuration,1);
		NEWMIII(Interface[i].IPv4->Config->Manual,   struct tt__PrefixedIPv4Address,1);
		NEWMIII(Interface[i].IPv4->Config->FromDHCP ,struct tt__PrefixedIPv4Address,1);
		NEWMIII(Interface[i].IPv4->Config->LinkLocal,struct tt__PrefixedIPv4Address,1);
		NEWMIII(Interface[i].Extension,struct tt__NetworkInterfaceExtension,1);
		NEWMIII(Interface[i].Extension->Dot11,struct tt__Dot11Configuration,1);
		NEWMIII(Interface[i].Extension->Dot11->Security,struct tt__Dot11SecurityConfiguration,1);
		NEWMIII(Interface[i].Extension->Dot11->Security->PSK,struct tt__Dot11PSKSet,1);
	}

    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,GetNetInterface);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->GetNetInterface(Net))return SOAP_FAULT;
	for(i =0;i<2&&i<Net->NetInterfaceSize;i++){
		Interface[i].Enabled        = Net->NetInterfaces[i].NetEnabled;
		Interface[i].token          = Net->NetInterfaces[i].NetToken;
		Interface[i].Info->HwAddress= Net->NetInterfaces[i].NetInfo.InfoHwAddress;
		Interface[i].Info->Name     = Net->NetInterfaces[i].NetInfo.InfoName;
		Interface[i].Info->MTU      =&Net->NetInterfaces[i].NetInfo.InfoMTU;
		//ipv4
		Interface[i].IPv4->Enabled  =Net->NetInterfaces[i].NetEnabled;//设备点开启则配置开启
		Interface[i].IPv4->Config->DHCP         =Net->NetInterfaces[i].NetIPv4.ipv4DHCP;
		Interface[i].IPv4->Config->__sizeManual =Net->NetInterfaces[i].NetIPv4.ipv4SizeManual;
		Interface[i].IPv4->Config->Manual->Address          =Net->NetInterfaces[i].NetIPv4.ipv4Manual.ipv4Address;
		Interface[i].IPv4->Config->Manual->PrefixLength     =Net->NetInterfaces[i].NetIPv4.ipv4Manual.ipv4Length;
		Interface[i].IPv4->Config->FromDHCP ->Address       =Net->NetInterfaces[i].NetIPv4.ipv4FromDHCP .ipv4Address;
		Interface[i].IPv4->Config->FromDHCP->PrefixLength   =Net->NetInterfaces[i].NetIPv4.ipv4FromDHCP.ipv4Length;
		Interface[i].IPv4->Config->LinkLocal ->Address      =Net->NetInterfaces[i].NetIPv4.ipv4LinkLocal.ipv4Address;
		Interface[i].IPv4->Config->LinkLocal->PrefixLength  =Net->NetInterfaces[i].NetIPv4.ipv4LinkLocal.ipv4Length;
		//Dot11
		if(Net->NetInterfaces[i].NetIsWifi){
		Interface[i].Extension->__sizeDot11=1; //一个设备点对应一个WIFI配置表
		Interface[i].Extension->Dot11->Alias  =Net->NetInterfaces[i].NetWifiConfig.WifiAlias;
		Interface[i].Extension->Dot11->SSID.__ptr  = Net->NetInterfaces[i].NetWifiConfig.WifiSSID.BinData;
		Interface[i].Extension->Dot11->SSID.__size = Net->NetInterfaces[i].NetWifiConfig.WifiSSID.BinSize;
		Interface[i].Extension->Dot11->Mode         = Net->NetInterfaces[i].NetWifiConfig.WifiMode;
		//Dot11.Secu
		Interface[i].Extension->Dot11->Security->Algorithm=&Net->NetInterfaces[i].NetWifiConfig.WifiSecurity.WifiCipAlgorithm;
		Interface[i].Extension->Dot11->Security->Mode     = Net->NetInterfaces[i].NetWifiConfig.WifiSecurity.WifiSecMode;
		Interface[i].Extension->Dot11->Security->PSK->Key->__ptr = Net->NetInterfaces[i].NetWifiConfig.WifiSecurity.WifiSecPSK.PskBinKey.BinData;
		Interface[i].Extension->Dot11->Security->PSK->Key->__size= Net->NetInterfaces[i].NetWifiConfig.WifiSecurity.WifiSecPSK.PskBinKey.BinSize;
		Interface[i].Extension->Dot11->Security->PSK->Passphrase = Net->NetInterfaces[i].NetWifiConfig.WifiSecurity.WifiSecPSK.PskPassphrase;
		}else{
         Interface[i].Extension=NULL;
		}
	}
    tds__GetNetworkInterfacesResponse->__sizeNetworkInterfaces=Net->NetInterfaceSize; 
    tds__GetNetworkInterfacesResponse->NetworkInterfaces      =Interface;
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetNetworkInterfaces(struct soap* hSoap, struct _tds__SetNetworkInterfaces *tds__SetNetworkInterfaces, struct _tds__SetNetworkInterfacesResponse *tds__SetNetworkInterfacesResponse)
{
	 printf("===============================================__tds__SetNetworkInterfaces=================================\n");
	ONVIF                              *Onvif      = (ONVIF*)hSoap->hdOnvif;
	struct tt__NetworkInterfaceSetConfiguration * NetSet     = tds__SetNetworkInterfaces->NetworkInterface;
    NEW(Net,NETINTERFACE);
	NEWMIII(hSoap->fault ,struct SOAP_ENV__Fault,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code,struct SOAP_ENV__Code ,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode,struct SOAP_ENV__Code,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode,struct SOAP_ENV__Code ,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Reason,struct SOAP_ENV__Reason,1);

	if(NULL !=NetSet ){
		if(NULL !=NetSet->Enabled)
			Net->NetEnabled				  = *NetSet->Enabled;
		if(NULL != NetSet->IPv4){
			Net->NetIPv4.ipv4SizeManual   = NetSet->IPv4->__sizeManual;
//			printf ("File");
			if(NULL != NetSet->IPv4->DHCP){
			Net->NetIPv4.ipv4DHCP         = *NetSet->IPv4->DHCP;
			}
			if (NULL !=NetSet->IPv4->Manual)
			{
				STRNCPY(Net->NetIPv4.ipv4LinkLocal.ipv4Address,NetSet->IPv4->Manual->Address,OVFCHARLENTH);
				if(NULL != tds__SetNetworkInterfaces->NetworkInterface->IPv4->DHCP){
					if (*tds__SetNetworkInterfaces->NetworkInterface->IPv4->DHCP)//DHCP
				{
					STRNCPY(Net->NetIPv4.ipv4FromDHCP.ipv4Address,NetSet->IPv4->Manual->Address,OVFCHARLENTH);
					
				}
				else//MAUAL
				{
					STRNCPY(Net->NetIPv4.ipv4Manual.ipv4Address,NetSet->IPv4->Manual->Address,OVFCHARLENTH);
					//	printf ("File [%s] maual ip [%s]\n", __FILE__, NetSet->IPv4->Manual->Address);
					}	
				}		

			}
		}
	}
//	printf("NetSet\n");
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,SetNetInterface);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->SetNetInterface(tds__SetNetworkInterfaces->InterfaceToken,Net)){
		
		hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode->SOAP_ENV__Value ="ter:InvalidIPv4Address" ;
		hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Value ="ter:InvalidArgVal";
 		hSoap->fault->SOAP_ENV__Reason->SOAP_ENV__Text="The suggested IPv4 address is invalid.";

		return SOAP_FAULT;
	}
 //	tds__SetNetworkInterfacesResponse->RebootNeeded = *tds__SetNetworkInterfaces->NetworkInterface->Enabled;
	return SOAP_OK;
}
//网络.协议
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetNetworkProtocols(struct soap* hSoap, struct _tds__GetNetworkProtocols *tds__GetNetworkProtocols, struct _tds__GetNetworkProtocolsResponse *tds__GetNetworkProtocolsResponse)
{
	 printf("===============================================__tds__GetNetworkProtocols=================================\n");
	INT                         i;
    ONVIF                      *Onvif      = (ONVIF*)hSoap->hdOnvif;
    NEW(NetPS,NETPROTOCALS );
    NEWMII(NetP,struct tt__NetworkProtocol,3);
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,GetNetProtocols);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->GetNetProtocols(NetPS))return SOAP_FAULT; 
	for(i=0;i<3&&i<NetPS->NetProtocalTypeSize;i++){
		NetP[i].Enabled= NetPS->NetProtocals[i].NetProtocalEnabled;
		NetP[i].Name   = NetPS->NetProtocals[i].NetProtocalType;
		NetP[i].Port   =&NetPS->NetProtocals[i].NetProtocalPort;
		NetP[i].__sizePort=1;//一个端口
	}
	tds__GetNetworkProtocolsResponse->NetworkProtocols =NetP ;
		
	
	return SOAP_OK;

}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetNetworkProtocols(struct soap* hSoap, struct _tds__SetNetworkProtocols *tds__SetNetworkProtocols, struct _tds__SetNetworkProtocolsResponse *tds__SetNetworkProtocolsResponse)
{
	printf("===============================================__tds__SetNetworkProtocols=================================\n");
	INT i;
    ONVIF                      *Onvif      = (ONVIF*)hSoap->hdOnvif;
    NEW(NetPS,NETPROTOCALS );
	NEWMIII(hSoap->fault ,struct SOAP_ENV__Fault,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code,struct SOAP_ENV__Code ,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode,struct SOAP_ENV__Code,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode,struct SOAP_ENV__Code ,1);
		NEWMIII(hSoap->fault->SOAP_ENV__Reason,struct SOAP_ENV__Reason,1);
	if(NULL != tds__SetNetworkProtocols){
		NetPS->NetProtocalTypeSize=tds__SetNetworkProtocols->__sizeNetworkProtocols;
		for(i=0;i<3&&i<tds__SetNetworkProtocols->__sizeNetworkProtocols;i++){
			NetPS->NetProtocals[i].NetProtocalEnabled= tds__SetNetworkProtocols->NetworkProtocols[i].Enabled;
			NetPS->NetProtocals[i].NetProtocalPort   =*tds__SetNetworkProtocols->NetworkProtocols[i].Port;
			NetPS->NetProtocals[i].NetProtocalType   = tds__SetNetworkProtocols->NetworkProtocols[i].Name;
		}
	}
			
	CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,SetNetProtocols);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->SetNetProtocols(NetPS)){

		hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode->SOAP_ENV__Value ="ter:ServiceNotSupported" ;
		hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Value ="ter:InvalidArgVal";
 		hSoap->fault->SOAP_ENV__Reason->SOAP_ENV__Text="The supplied network service is not supported. ";

		return SOAP_FAULT; 
	}
	return SOAP_OK;
}
//零配置
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetZeroConfiguration(struct soap* hSoap, struct _tds__GetZeroConfiguration *tds__GetZeroConfiguration, struct _tds__GetZeroConfigurationResponse *tds__GetZeroConfigurationResponse)
{
	
	printf("===============================================__tds__GetZeroConfiguration=================================\n");
	NEW(  NetZero,NETZEROCONFIG);
    NEW(lpNetZero,struct tt__NetworkZeroConfiguration) ;
	ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
	NEWMIII(lpNetZero->Addresses,CHAR*,1);
	NEWMIII(*lpNetZero->Addresses,CHAR,OVFCHARLENTH);
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,GetNetZeroConfig);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->GetNetZeroConfig(NetZero))return SOAP_FAULT; 
    lpNetZero->Enabled       = NetZero->NetZeroEnabled;
	lpNetZero->InterfaceToken= NetZero->NetInterfaceToken;
	lpNetZero->__sizeAddresses=NetZero->NetSizeAddresses;
	*lpNetZero->Addresses      =NetZero->NetAddresses;

	tds__GetZeroConfigurationResponse->ZeroConfiguration=lpNetZero;
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetZeroConfiguration(struct soap* hSoap, struct _tds__SetZeroConfiguration *tds__SetZeroConfiguration, struct _tds__SetZeroConfigurationResponse *tds__SetZeroConfigurationResponse)
{
	printf("===============================================__tds__SetZeroConfiguration=================================\n");
    NEW(  NetZero,NETZEROCONFIG);
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
	if(NULL != tds__SetZeroConfiguration){
		NetZero->NetZeroEnabled   =  tds__SetZeroConfiguration->Enabled;
		STRNCPY(NetZero->NetInterfaceToken,tds__SetZeroConfiguration->InterfaceToken,OVFCHARLENTH);
	}	
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,SetNetZeroConfig);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->SetNetZeroConfig(NetZero))return SOAP_FAULT; 
	return SOAP_OK;
}
//IP过滤
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetIPAddressFilter(struct soap* hSoap, struct _tds__GetIPAddressFilter *tds__GetIPAddressFilter, struct _tds__GetIPAddressFilterResponse *tds__GetIPAddressFilterResponse)
{
	 printf("===============================================__tds__GetIPAddressFilter=================================\n");
    NEW(lpIPFilter,struct tt__IPAddressFilter) ;
    NEW(  IpFilter,IPADDRFILTER);
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,GetNetIPAddressFilter);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->GetNetIPAddressFilter(IpFilter))return SOAP_FAULT;
    lpIPFilter->Type= IpFilter->NetFilterType;
	lpIPFilter->__sizeIPv4Address=IpFilter->NetSizeIPv4Address;
	lpIPFilter->IPv4Address      =(struct tt__PrefixedIPv4Address*)IpFilter->NetIPv4Address;//结构定义相同，可强制转换

	tds__GetIPAddressFilterResponse->IPAddressFilter=lpIPFilter;
    return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetIPAddressFilter(struct soap* hSoap, struct _tds__SetIPAddressFilter *tds__SetIPAddressFilter, struct _tds__SetIPAddressFilterResponse *tds__SetIPAddressFilterResponse)
{
	  printf("===============================================__tds__SetIPAddressFilter=================================\n");
    NEW(  IpFilter,IPADDRFILTER);
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
	int     i;
    if(NULL != tds__SetIPAddressFilter && NULL != tds__SetIPAddressFilter->IPAddressFilter){
		IpFilter->NetFilterType     = tds__SetIPAddressFilter->IPAddressFilter->Type;
		IpFilter->NetSizeIPv4Address= tds__SetIPAddressFilter->IPAddressFilter->__sizeIPv6Address;
		for(i=0;i<OVFMAXCHANNEL&&i<IpFilter->NetSizeIPv4Address;i++){
			STRNCPY(IpFilter->NetIPv4Address[i]->ipv4Address    ,tds__SetIPAddressFilter->IPAddressFilter->IPv4Address[i].Address,OVFCHARLENTH);
			IpFilter->NetIPv4Address[i]->ipv4Length     = tds__SetIPAddressFilter->IPAddressFilter->IPv4Address[i].PrefixLength;
		 }
	} 
	CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,SetNetIPAddressFilter);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->SetNetIPAddressFilter(IpFilter))return SOAP_FAULT;

    return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__AddIPAddressFilter(struct soap* hSoap, struct _tds__AddIPAddressFilter *tds__AddIPAddressFilter, struct _tds__AddIPAddressFilterResponse *tds__AddIPAddressFilterResponse)
{
	 printf("===============================================__tds__AddIPAddressFilter=================================\n");
    NEW(  IpFilter,IPADDRFILTER);
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
	int     i;
    if(NULL != tds__AddIPAddressFilter && NULL != tds__AddIPAddressFilter->IPAddressFilter){
		IpFilter->NetFilterType     = tds__AddIPAddressFilter->IPAddressFilter->Type;
		IpFilter->NetSizeIPv4Address= tds__AddIPAddressFilter->IPAddressFilter->__sizeIPv6Address;
		for(i=0;i<OVFMAXCHANNEL&&i<IpFilter->NetSizeIPv4Address;i++){
			STRNCPY(IpFilter->NetIPv4Address[i]->ipv4Address    ,tds__AddIPAddressFilter->IPAddressFilter->IPv4Address[i].Address,OVFCHARLENTH);
			IpFilter->NetIPv4Address[i]->ipv4Length     = tds__AddIPAddressFilter->IPAddressFilter->IPv4Address[i].PrefixLength;
		}
	}
    
	 CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,AddNetIPAddressFilter);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->AddNetIPAddressFilter(IpFilter))return SOAP_FAULT;
    
    return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__RemoveIPAddressFilter(struct soap* hSoap, struct _tds__RemoveIPAddressFilter *tds__RemoveIPAddressFilter, struct _tds__RemoveIPAddressFilterResponse *tds__RemoveIPAddressFilterResponse)
{
	   printf("===============================================__tds__RemoveIPAddressFilter=================================\n");
     NEW(  IpFilter,IPADDRFILTER);
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
	int     i;
     if(NULL != tds__RemoveIPAddressFilter && NULL != tds__RemoveIPAddressFilter->IPAddressFilter){
		IpFilter->NetFilterType     = tds__RemoveIPAddressFilter->IPAddressFilter->Type;
		IpFilter->NetSizeIPv4Address= tds__RemoveIPAddressFilter->IPAddressFilter->__sizeIPv6Address;
		for(i=0;i<OVFMAXCHANNEL&&i<IpFilter->NetSizeIPv4Address;i++){
		 STRNCPY(IpFilter->NetIPv4Address[i]->ipv4Address    ,tds__RemoveIPAddressFilter->IPAddressFilter->IPv4Address[i].Address,OVFCHARLENTH);
				 IpFilter->NetIPv4Address[i]->ipv4Length     = tds__RemoveIPAddressFilter->IPAddressFilter->IPv4Address[i].PrefixLength;
		}
	 }
	 CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,RemNetIPAddressFilter);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->RemNetIPAddressFilter(IpFilter))return SOAP_FAULT;
     
    return SOAP_OK;
 }
//WIFI
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDot11Capabilities(struct soap* hSoap, struct _tds__GetDot11Capabilities *tds__GetDot11Capabilities, struct _tds__GetDot11CapabilitiesResponse *tds__GetDot11CapabilitiesResponse)
{
	 printf("===============================================__tds__GetDot11Capabilities=================================\n");
    NEW(lpDot11Cap,struct tt__Dot11Capabilities) ;
    NEW(  Dot11Cap,DOT11CAP);
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,WifiGetDot11Cap);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->WifiGetDot11Cap( Dot11Cap))return SOAP_FAULT;
    
	lpDot11Cap->AdHocStationMode      =Dot11Cap->NetIsAdHocStationMode;
	lpDot11Cap->MultipleConfiguration =Dot11Cap->NetIsMultipleConfig;
	lpDot11Cap->ScanAvailableNetworks =Dot11Cap->NetIsScanAvailable;
	lpDot11Cap->TKIP                  =Dot11Cap->NetIsTKIP;
	lpDot11Cap->WEP                   =Dot11Cap->NetIsWEP;
	
    tds__GetDot11CapabilitiesResponse->Capabilities=lpDot11Cap;
    return SOAP_OK;
 }
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDot11Status(struct soap* hSoap, struct _tds__GetDot11Status *tds__GetDot11Status, struct _tds__GetDot11StatusResponse *tds__GetDot11StatusResponse)
{
	   printf("===============================================__tds__GetDot11Status=================================\n");
    NEW(lpDot11Stus,struct tt__Dot11Status) ;
    NEW(  Dot11Stus,NETDOT11STATUS);
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,WifiGetDot11Status);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->WifiGetDot11Status( tds__GetDot11Status->InterfaceToken, Dot11Stus))return SOAP_FAULT;
    //提供下列两个参数即可
	lpDot11Stus->SignalStrength=& Dot11Stus->WifiSignalStrength;
	 lpDot11Stus->BSSID=Dot11Stus->WifiSSID,OVFCHARLENTH ;
	
	tds__GetDot11StatusResponse->Status=lpDot11Stus;
	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __tds__ScanAvailableDot11Networks(struct soap* hSoap, struct _tds__ScanAvailableDot11Networks *tds__ScanAvailableDot11Networks, struct _tds__ScanAvailableDot11NetworksResponse *tds__ScanAvailableDot11NetworksResponse)
{  
	 printf("===============================================__tds__ScanAvailableDot11Networks=================================\n");
    INT   i;
    NEW(  Dot11Point,DOT11HOTPOINTS);
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    struct tt__Dot11AvailableNetworks *lpDot11Point[OVFMAXCHANNEL];
	NEWM(lpDot11Point,struct tt__Dot11AvailableNetworks,16) ;
 
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,WifiScanHotPoint);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->WifiScanHotPoint( tds__ScanAvailableDot11Networks->InterfaceToken, Dot11Point))return SOAP_FAULT;

    for(i=0;i<OVFMAXCHANNEL&&i<Dot11Point->Dot11HotPointSize;i++){
		lpDot11Point[i]->SignalStrength=&Dot11Point->Dot11HotPoints[i].WifiSignalStrength;
		lpDot11Point[i]->BSSID         = Dot11Point->Dot11HotPoints[i].WifiSSID;
		lpDot11Point[i]->SSID.__ptr    = Dot11Point->Dot11HotPoints[i].WifiBinSSID.BinData;
		lpDot11Point[i]->SSID.__size   = Dot11Point->Dot11HotPoints[i].WifiBinSSID.BinSize;
		lpDot11Point[i]->AuthAndMangementSuite=&Dot11Point->Dot11HotPoints[i].WifiSecurity;
		lpDot11Point[i]->__sizeAuthAndMangementSuite=1;//仅提供一个授权模式
    
	 }
	return SOAP_OK;
}

