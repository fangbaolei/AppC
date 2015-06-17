#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "IPCAM_Export.h"

#ifdef __cplusplus
};
#endif



#define NET_TOKEN_FIRST   "ETH0"
#define NET_TOKEN_SECOND  "ETH1"

#define USER_LEVEL_ADMIN_CFG_PERM      (CFG_PERM_REC_CFG | CFG_PERM_UNIVERSAL_CFG | CFG_PERM_CHN_CFG | CFG_PERM_NET_CFG |\
                                        CFG_PERM_PTZ_CFG| CFG_PERM_ALARM_CFG | CFG_PERM_PREVIEW_CFG | CFG_PERM_EXCEPT_CFG | CFG_PERM_USER_CFG )
#define USER_LEVEL_OPERATOR_CFG_PERM    (CFG_PERM_REC_CFG | CFG_PERM_UNIVERSAL_CFG | CFG_PERM_CHN_CFG | CFG_PERM_PTZ_CFG| CFG_PERM_ALARM_CFG | CFG_PERM_PREVIEW_CFG  )
#define USER_LEVEL_USER_CFG_PERM        (CFG_PERM_REC_CFG | CFG_PERM_UNIVERSAL_CFG )
#define USER_LEVEL_ANONYMOUS_CFG_PERM   0x0
#define USER_LEVEL_EXTENDED_CFG_PERM    0x0


#define USER_LEVEL_ADMIN_OP_PERM       (OP_PERM_VER_UPGRADE | OP_PERM_CFG_OP | OP_PERM_DEFAULT_CFG | \
                                        OP_PERM_LOG_QUERY | OP_PERM_SYS_INFO | OP_PERM_HD_MGR | OP_PERM_POWEROFF | \
                                        OP_PERM_LIVE | OP_PERM_MAN_REC | OP_PERM_PLAYBACK | OP_PERM_PTZ | OP_PERM_BACKUP | OP_PERM_MAN_ALARM )
#define USER_LEVEL_OPERATOR_OP_PERM     (OP_PERM_CFG_OP | OP_PERM_LIVE | OP_PERM_MAN_REC | OP_PERM_PLAYBACK | OP_PERM_PTZ | OP_PERM_BACKUP | OP_PERM_MAN_ALARM )
#define USER_LEVEL_USER_OP_PERM         (OP_PERM_CFG_OP | OP_PERM_LIVE | OP_PERM_MAN_REC | OP_PERM_PLAYBACK  )
#define USER_LEVEL_ANONYMOUS_OP_PERM    (OP_PERM_LIVE )
#define USER_LEVEL_EXTENDED_OP_PERM     0x0

BOOL CheckIP(const char* szIP)
{
    int a = 0, b = 0, c = 0, d = 0;
    char szTemp[16] = {0};
    if ( szIP == NULL || strcmp("", szIP) == 0 )
    {
        return FALSE;
    }

    sscanf(szIP, "%d.%d.%d.%d", &a, &b, &c, &d);
    if ( a >= 0 && a <= 255 && b >= 0 && b <= 255 && c >= 0 && c <= 255 && d >= 0 && d <= 255 )
    {
        sprintf(szTemp, "%d.%d.%d.%d", a, b, c, d);
        if ( strcmp(szTemp, szIP) == 0 )
        {
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}

extern int IsValidVideoSrcToken(CHAR *pToken);
int IsValidToken(CHAR *token, int tokentype);


BOOL GetImg(char* lpDevSvCap)
{
	
	LPIPCAM_SYSCONTEXT SysContext = IPCAM_GetSystemContext();
	if(SysContext==NULL)		return FALSE;
	
	sprintf(lpDevSvCap,"http://%s:%d/Onvif/imaging_service",SysContext->ipcam_SysConfig->ConfigNet.NetIpAddr,NET_ONVIF_SERVER_PORT);
  return TRUE;
}


BOOL GetDevServerCap(LPDEVSVCAP lpDevSvCap)
{
	LPIPCAM_SYSCONTEXT SysContext = IPCAM_GetSystemContext();
	if(SysContext==NULL)		return FALSE;
	
	sprintf(lpDevSvCap->CapDevice.XAddr,"http://%s:%d/Onvif/device_service",SysContext->ipcam_SysConfig->ConfigNet.NetIpAddr,NET_ONVIF_SERVER_PORT);
	sprintf(lpDevSvCap->CapImag.SupXAddr,"http://%s:%d/Onvif/imaging_service",SysContext->ipcam_SysConfig->ConfigNet.NetIpAddr,NET_ONVIF_SERVER_PORT);
	sprintf(lpDevSvCap->CapMedia.SupXAddr,"http://%s:%d/Onvif/media_service",SysContext->ipcam_SysConfig->ConfigNet.NetIpAddr,NET_ONVIF_SERVER_PORT);
	sprintf(lpDevSvCap->CapPTZ.SupXAddr,"http://%s:%d/Onvif/Ptz",SysContext->ipcam_SysConfig->ConfigNet.NetIpAddr,NET_ONVIF_SERVER_PORT);
	IPCAM_DEBUG(SysContext->ipcam_SysConfig->ConfigNet.NetIpAddr);
	lpDevSvCap->CapDevice.System.SupDiscoveryBye 			   = TRUE;
	lpDevSvCap->CapDevice.Network.SupDynDNS                    = TRUE;
	lpDevSvCap->CapDevice.Network.SupIPFilter				   = TRUE;
	lpDevSvCap->CapDevice.Security.SupUsernameToken		   	   = TRUE;
	lpDevSvCap->CapDevice.System.SupSystemLogging			   = TRUE;
	lpDevSvCap->CapDevice.System.SupDiscoveryResolve		   = TRUE;
    lpDevSvCap->CapMedia.Streaming.SupRTP_USCORERTSP_USCORETCP = TRUE;
	lpDevSvCap->CapMedia.Streaming.SupRTP_USCORETCP			   = TRUE;
	lpDevSvCap->CapMedia.Streaming.SupRTPMulticast             = TRUE;
	sprintf(lpDevSvCap->CapEvent.SupXAddr,"http://%s:%d/onvif/Event",SysContext->ipcam_SysConfig->ConfigNet.NetIpAddr,NET_ONVIF_SERVER_PORT);
	lpDevSvCap->CapEvent.SupWSSubscriptionPolicySupport        = FALSE;
	lpDevSvCap->CapDevice.IO.InputConnectors				   = 1;	//SysContext->ipcam_SysConfig->ConfigAlarm.IoMap
	lpDevSvCap->CapDevice.IO.RelayOutputs					   = 1;


    return TRUE;
}

BOOL GetNetInterface(LPNETINTERFACES lpNetInterfaces)
{
	IPCAM_DEBUG("GetNetInterface.....................................................\n");
	LPIPCAM_SYSCONTEXT SysContext = IPCAM_GetSystemContext();
	if(SysContext == NULL) return FALSE;
	
    lpNetInterfaces->NetInterfaceSize = 1;
    lpNetInterfaces->NetInterfaces[0].NetEnabled= TRUE;

    strncpy(lpNetInterfaces->NetInterfaces[0].NetToken, DEV_NET_ETH0, OVFCHARLENTH);
    strncpy(lpNetInterfaces->NetInterfaces[0].NetInfo.InfoHwAddress,SysContext->ipcam_SysConfig->ConfigNet.NetMacAddr, 24);
  
	lpNetInterfaces->NetInterfaces[0].NetIPv4.ipv4DHCP = FALSE;
	strncpy(lpNetInterfaces->NetInterfaces[0].NetIPv4.ipv4FromDHCP.ipv4Address, SysContext->ipcam_SysConfig->ConfigNet.NetIpAddr, 16);
	lpNetInterfaces->NetInterfaces[0].NetIPv4.ipv4FromDHCP.ipv4Length = strlen(SysContext->ipcam_SysConfig->ConfigNet.NetIpAddr);

	lpNetInterfaces->NetInterfaces[0].NetIPv4.ipv4SizeManual = 1;
	strncpy(lpNetInterfaces->NetInterfaces[0].NetIPv4.ipv4Manual.ipv4Address,SysContext->ipcam_SysConfig->ConfigNet.NetIpAddr, 16);
	lpNetInterfaces->NetInterfaces[0].NetIPv4.ipv4Manual.ipv4Length = strlen(SysContext->ipcam_SysConfig->ConfigNet.NetIpAddr);
	strncpy(lpNetInterfaces->NetInterfaces[0].NetIPv4.ipv4LinkLocal.ipv4Address,SysContext->ipcam_SysConfig->ConfigNet.NetIpAddr,16);
	lpNetInterfaces->NetInterfaces[0].NetIPv4.ipv4LinkLocal.ipv4Length = strlen(SysContext->ipcam_SysConfig->ConfigNet.NetIpAddr);

    return TRUE;
}

BOOL GetNetConfigExt(LPNETEXTCONFIG lpNetExtConfig)
{
	IPCAM_DEBUG("GetNetConfigExt........................................................\n");
	LPIPCAM_SYSCONTEXT SysContext = IPCAM_GetSystemContext();
	if(SysContext==NULL)	return FALSE;
    lpNetExtConfig->NetDnsFromDHCP = FALSE;
	lpNetExtConfig->NetsizeSearchDomain = 1;
	strncpy(lpNetExtConfig->NetSearchDomain[0],"domain.name",OVFCHARLENTH);

    lpNetExtConfig->NetDnsIPV4Size = 2;
    strncpy(lpNetExtConfig->NetDnsIPV4[0], SysContext->ipcam_SysConfig->ConfigNet.NetDnsSvI, 16);
	strncpy(lpNetExtConfig->NetDnsIPV4[1], SysContext->ipcam_SysConfig->ConfigNet.NetDnsSvII, 16);

    lpNetExtConfig->NetGatewaySize = 1;
    strncpy(lpNetExtConfig->NetGateway[0], SysContext->ipcam_SysConfig->ConfigNet.NetGwAddr, 16);

	lpNetExtConfig->NetNtpSize = 1;
    strncpy(lpNetExtConfig->NetNtpDns[0], SysContext->ipcam_SysConfig->ConfigNet.NtpServer[0], 50);
	strncpy(lpNetExtConfig->NetNtpIPV4[0],SysContext->ipcam_SysConfig->ConfigNet.NetIpAddr,16);

    strncpy(lpNetExtConfig->NetDynamicDns,SysContext->ipcam_SysConfig->ConfigNet.DdnsServerList[0].SevName, OVFCHARLENTH);
    strcpy(lpNetExtConfig->NetHostName,"LHY");
	
    return TRUE;
}

BOOL  GetNetZeroConfig(LPNETZEROCONFIG lpNetZeroConfig)
{
	IPCAM_DEBUG("GetNetZeroConfig........................................................\n");
	LPIPCAM_SYSCONTEXT SysContext = IPCAM_GetSystemContext();
	if(SysContext==NULL)	return FALSE;

    strncpy(lpNetZeroConfig->NetInterfaceToken, DEV_NET_ETH0, OVFCHARLENTH);
    lpNetZeroConfig->NetZeroEnabled = TRUE;
    lpNetZeroConfig->NetSizeAddresses = 1;
    strncpy(lpNetZeroConfig->NetAddresses[0],SysContext->ipcam_SysConfig->ConfigNet.NetIpAddr, 16);

    return TRUE;
}

BOOL  SetNetZeroConfig(LPNETZEROCONFIG   NetZeroConfig)
{
    return TRUE;
}

BOOL  GetNetIPAddressFilter(LPIPADDRFILTER  lpNetAddrFilter)
{
    return TRUE;
}

BOOL SetNetIPAddressFilter(LPIPADDRFILTER  lpNetAddrFilter)
{
    return TRUE;
}

BOOL AddNetIPAddressFilter(LPIPADDRFILTER  lpNetAddrFilter)
{
    return  TRUE;
}

BOOL RemNetIPAddressFilter(LPIPADDRFILTER  lpNetAddrFilter)
{
    return TRUE;
}

BOOL GetRemoteUser(LPREMOTEUSER lpRemoteUser)
{
	LPIPCAM_SYSCONTEXT SysContext = IPCAM_GetSystemContext();
	if(SysContext==NULL)	return FALSE;

    strncpy(lpRemoteUser->UserName,SysContext->ipcam_SysConfig->ConfigUser.User[0].userName, 16);
    strncpy(lpRemoteUser->UserPwd, SysContext->ipcam_SysConfig->ConfigUser.User[0].userPassword, 16);

	lpRemoteUser->UserUseDerivedPwd = TRUE;
    return TRUE;
}

BOOL SetRemoteUser(LPREMOTEUSER lpRemoteUser)
{	
    if (lpRemoteUser == NULL)
    {
        return FALSE;
    }
    return TRUE;
}

BOOL GetUsers(LPUSERS lpUsers)
{
    if (lpUsers == NULL)
    {
        return FALSE;
    }
	INT i;
	LPIPCAM_SYSCONTEXT SysContext = IPCAM_GetSystemContext();
	for(i=0;i<SysContext->ipcam_SysConfig->ConfigUser.UserCount;i++)
	{
		strncpy(lpUsers->Users[i].UserName ,SysContext->ipcam_SysConfig->ConfigUser.User[i].userName, 16);
   		strncpy(lpUsers->Users[i].UserPwd  ,SysContext->ipcam_SysConfig->ConfigUser.User[i].userPassword, 16);
		lpUsers->Users[i].UserLevel		=	SysContext->ipcam_SysConfig->ConfigUser.User[i].Priority;
	}
   return TRUE;
}

BOOL SetUsers(LPUSERS lpUsers)
{
    int             i = 0;
    if (lpUsers == NULL)
    {
        return FALSE;
    }
	
    for (i = 0; i < lpUsers->UserSize; i++)
    {
		NetCfgUserModify(lpUsers->Users[i].UserName,lpUsers->Users[i].UserPwd);
    }
	CallBackNetConfig(0,MSG_USERMODIFY_REQ,NULL);
    return TRUE;
}

BOOL AddUsers(LPUSERS lpUsers)
{	
    int i = 0;
    if (lpUsers == NULL)
    {
        return FALSE;
    }
    if (lpUsers->UserSize == 0)
    {
        return TRUE;
    }
    for (i = 0; i < lpUsers->UserSize; i++)
    {
  	    NetCfgUserAdd(lpUsers->Users[i].UserName,lpUsers->Users[i].UserPwd,lpUsers->Users[i].UserLevel);
    }
	CallBackNetConfig(0,MSG_USERADD_REQ,NULL);
    return TRUE;
}

BOOL  DelUsers(LPUSERS lpUsers)
{
    int i = 0;
    if (lpUsers == NULL)
    {
        return FALSE;
    }
    if (lpUsers->UserSize == 0)
    {
        return TRUE;
    }
    for (i = 0; i < lpUsers->UserSize; i++)
    {
   		 NetCfgUserDel(lpUsers->Users[i].UserName);   
    }
    return TRUE;
}

BOOL SysReboot()
{
	IPCAM_DEBUG("SysReboot........................................................\n");
    CallBackNetConfig(0,MSG_REBOOT_REQ,NULL);
    return TRUE;
}

BOOL SysGetLog(LOGTYPE LogType, LPSYSTEMLOGS lpSystemLog)
{
    if(0 == LogType){
		strncpy(lpSystemLog->LogFile.fiName ,"system",OVFCHARLENTH);
		IPCAM_DEBUG(lpSystemLog->LogFile.fiName);
	}	
	else if(1 == LogType){
		strncpy(lpSystemLog->LogFile.fiName ,"access",OVFCHARLENTH);
		IPCAM_DEBUG("%d",LogType);
	}
	else {
		return FALSE;
	}
    return TRUE;
}

BOOL SysBackup(LPBACKUPFILES lpBackupFiles)
{
    if (lpBackupFiles == NULL)
    {
        return FALSE;
    }
	//?
    return TRUE;
}

BOOL SysGetSuportInfo(LPSUPORTINFO lpSuportInfo)
{
    if (lpSuportInfo == NULL)
    {
        return FALSE;
    }
	//?
    return TRUE;
}

BOOL SysGetDeviceInfo(LPDEVICEINFO lpDeviceInfo)
{
	LPIPCAM_SYSCONTEXT SysContext = IPCAM_GetSystemContext();
	printf("==================================SysGetDeviceInfo start==================================================\n");
    	strncpy(lpDeviceInfo->DevFirmwareVersion, SysContext->ipcam_SysConfig->ConfigFactory.strHardVer,OVFCHARLENTH);
	strncpy(lpDeviceInfo->DevHardwareId ,SysContext->ipcam_SysConfig->ConfigFactory.strDevRegcode,26);
    	strcpy(lpDeviceInfo->DevManufacturer,SysContext->ipcam_SysConfig->ConfigFactory.strFactoryName);
	strncpy(lpDeviceInfo->DevModel,SysContext->ipcam_SysConfig->ConfigFactory.strDevName,24);
	strncpy(lpDeviceInfo->DevSerialNumber,SysContext->ipcam_SysConfig->ConfigFactory.strDevSerialNumb,OVFCHARLENTH);
  	return TRUE;
}

BOOL SysSetFactoryDefault(ENU_FACTORYDEFFAULT FactoryDefaultType)
{
	CHAR	nowTime[64] = {0};
	LOG_Write(1,"Unkown",GetLocalTime(nowTime), "SysSetFactoryDefault重启系统");
	IPCAM_LoadDefaultCfg();
    return TRUE;
}

BOOL  SysGetDateTime(LPDATETIME lpGetDatetime)
{
	char timeTe[10];
	time_t timep;
	struct tm *p;

	LPIPCAM_SYSCONTEXT SysContext = IPCAM_GetSystemContext();
    if (lpGetDatetime == NULL || SysContext==NULL)
    {
        return FALSE;
    }
	
	time(&timep);
	p=gmtime(&timep);
	
	if(SysContext->ipcam_SysConfig->ConfigNet.NtpTimeZone>0)
		sprintf(timeTe,"GMT+%d",SysContext->ipcam_SysConfig->ConfigNet.NtpTimeZone);
	if(SysContext->ipcam_SysConfig->ConfigNet.NtpTimeZone==0)
		strncpy(timeTe,"GMT",OVFCHARLENTH);
	if(SysContext->ipcam_SysConfig->ConfigNet.NtpTimeZone<0)
		sprintf(timeTe,"GMT-%d",SysContext->ipcam_SysConfig->ConfigNet.NtpTimeZone);
	
	strncpy(lpGetDatetime->TimeZone,timeTe,10);//需要得到当前的时区
	lpGetDatetime->SetDateTimeType      = SysContext->ipcam_SysConfig->ConfigNet.NtpEnable;
	IPCAM_DEBUG("type%d",lpGetDatetime->SetDateTimeType);

	IPCAM_DEBUG("[SysGetDateTime]%4d-%2d-%2d %d:%d:%d" , 1900+p->tm_year, 1+p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);

	lpGetDatetime->IsDaylightSavings	= 0;
	lpGetDatetime->UTCDateTime.Year		= (1900+p->tm_year);	//p->tm_year;
	lpGetDatetime->UTCDateTime.Month    = 1+p->tm_mon;		//p->tm_mon;
	lpGetDatetime->UTCDateTime.Date     = p->tm_mday;
	lpGetDatetime->UTCDateTime.Hour		= p->tm_hour-8;
	lpGetDatetime->UTCDateTime.Minute   = p->tm_min;
	lpGetDatetime->UTCDateTime.Second	= p->tm_sec;
	
    return TRUE;
}


BOOL SysSetDateTime(LPDATETIME lpSetDatetime)
{
	struct tm Tm			= {0};
	struct tm TmTime		= {0};
	struct tm *pTmtime 	= NULL;
	time_t nTime;

	struct tm TmLocalTime = {0};

	if (lpSetDatetime == NULL)
	{
		return FALSE;
	}
	
	int nTimeZone = 0;
	LPIPCAM_SYSCONTEXT     gSystemText = IPCAM_GetSystemContext();
	LPCFG_NETINFO lpCfgNetInfo = &(gSystemText->ipcam_SysConfig->ConfigNet);

	if(0 == strcmp(lpSetDatetime->TimeZone,""))//安可NVR特别处理
	{
		IPCAM_DEBUG("1==========================================lpSetDatetime->TimeZone=%s===================\n", lpSetDatetime->TimeZone);
		nTimeZone = 0;
	}
	else
	{
		nTimeZone = lpCfgNetInfo->NtpTimeZone;
	}
	
	//IPCAM_DEBUG("1==========================================lpSetDatetime->TimeZone=%s===================\n", lpSetDatetime->TimeZone);

	Tm.tm_year = lpSetDatetime->UTCDateTime.Year-1900;
	Tm.tm_mon  = lpSetDatetime->UTCDateTime.Month-1;
	Tm.tm_mday = lpSetDatetime->UTCDateTime.Date;
	Tm.tm_hour = lpSetDatetime->UTCDateTime.Hour;
	Tm.tm_min  = lpSetDatetime->UTCDateTime.Minute;
	Tm.tm_sec  = lpSetDatetime->UTCDateTime.Second;

	nTime = mktime(&Tm);
	nTime += nTimeZone * 60 * 60;

	pTmtime = localtime_r (&nTime, &TmTime);
	if(pTmtime==NULL)
	{
		return FALSE;
	}

	TmTime.tm_year += 1900;
	TmTime.tm_mon += 1;

	IPCAM_DEBUG("[SysSetDateTime]%4d-%2d-%2d %d:%d:%d" , TmTime.tm_year, TmTime.tm_mon,TmTime.tm_mday, TmTime.tm_hour, TmTime.tm_min, TmTime.tm_sec);
	
	IPCAM_RtcWrite (&TmTime);

	return TRUE;
}


BOOL SysStartFirewareUpGrade(LPUPGRADE lpFirewareUpdate)//?
{
    if (lpFirewareUpdate == NULL)
    {
        return FALSE;
    }
    return TRUE;
}

BOOL SysUpGradeFireware(LPATTACHMENTDATA  lpDataFireware)//?
{
    if (lpDataFireware == NULL)
    {
        return FALSE;
    }
    if (lpDataFireware->Data == NULL)
    {
        return FALSE;
    }

    return TRUE;
}

BOOL  SysStartSystemRestore(LPRESTORESYSTEM  lpRestoreSystem)//?
{
	IPCAM_DEBUG("SysStartSystemRestore.............................................\n");
	CallBackNetConfig(0,MSG_SAVECFG_REQ,NULL);
	return TRUE;
}

BOOL  SysRestoreSystem(LPATTACHMENTDATA  DataRestore)//?
{
	IPCAM_DEBUG("SysRestoreSystem.............................................\n");
	CallBackNetConfig(0,MSG_LOADCFG_REQ,NULL);
	return TRUE;
}

BOOL  SetNetInterface(CHAR* InterfaceToken, LPNETINTERFACE NetInterface)//?
{
	IPCAM_DEBUG("SetNetInterface.............................................\n");
	char strIp[20] = {0};
	char strMask[20] = {0};
	char strGwaddr[20]={0};
	char strMac[20] = {0};
	char pipaddr[3]={0};
	char *paddr = pipaddr;
	get_net_env(DEV_NET_ETH0, strIp, strMask, strGwaddr,  strMac);
	char strGwaddr_ptem[3]={0};
	char *pGw = strGwaddr_ptem;
	int idnex = 8;
	while(strGwaddr[idnex]!='.')
  	{
  	  	*pGw++=strGwaddr[idnex];
  	  	idnex++;
  	}
	idnex =8;
	while(NetInterface->NetIPv4.ipv4Manual.ipv4Address[idnex]!='.')
	{
		  *paddr++=(NetInterface->NetIPv4.ipv4Manual.ipv4Address[idnex]);
		  idnex++;
	}
	
	printf("=============ip======%s=======strGwaddr_ptem=%s=============\n",pipaddr,strGwaddr_ptem);
	if (NULL == InterfaceToken )
	{
		return FALSE;
		
	}else{
		if (0 != strcmp(InterfaceToken,DEV_NET_ETH0))
		{
			return FALSE;
		}	
	}
	LPIPCAM_SYSCONTEXT SysContext = IPCAM_GetSystemContext();
	if(NULL != NetInterface->NetIPv4.ipv4LinkLocal.ipv4Address){
		printf("local%s\n",NetInterface->NetIPv4.ipv4LinkLocal.ipv4Address);
		if(0!=strcmp(NetInterface->NetIPv4.ipv4LinkLocal.ipv4Address,SysContext->ipcam_SysConfig->ConfigNet.NetIpAddr)){
		    if (1 == NetInterface->NetIPv4.ipv4DHCP)//DHCP
			{
				IPCAM_DEBUG("Set Net Env with DHCP");
				//strncpy(SysContext->ipcam_SysConfig->ConfigNet.NetIpAddr,NetInterface->NetIPv4.ipv4FromDHCP.ipv4Address,16);
				SysContext->ipcam_SysConfig->ConfigNet.NetIpFetchMode = NETPARAM_DHCP_MODE;
							
			}
			else//MANUAL
			{
				 printf("=============ip======%s=======strGwaddr_ptem=%s=============\n",pipaddr,strGwaddr_ptem);
				 if(strcmp(pipaddr,strGwaddr_ptem)==0)
				 {
						IPCAM_DEBUG("Set Net Env with ManUal and manual ip [%s]", NetInterface->NetIPv4.ipv4Manual.ipv4Address);
						strncpy(SysContext->ipcam_SysConfig->ConfigNet.NetIpAddr,NetInterface->NetIPv4.ipv4Manual.ipv4Address, 16);
						SysContext->ipcam_SysConfig->ConfigNet.NetIpFetchMode = NETPARAM_IP_MODE;
						printf("~~~~~~~~~~~~~sysmanual%s\n",SysContext->ipcam_SysConfig->ConfigNet.NetIpAddr);
				}
			}
			CallBackNetConfig(0,MSG_NETPARMSET_REQ,NULL);
		}
	}		
    return TRUE;
}


BOOL SetNetConfigExt(LPNETEXTCONFIG lpNetExtConfig, ENU_NETCFG_CMD SetCmd)//?
{
	IPCAM_DEBUG("SetNetConfigExt.............................................\n");
	INT i=0;
    if (lpNetExtConfig == NULL)
    {
        return FALSE;
    }
	char *ptr;
	INT irt;
	LPIPCAM_SYSCONTEXT SysContext = IPCAM_GetSystemContext();
    switch (SetCmd)
    {
	case NETCFG_CMD_SETHOSTNAME:
		if(0==strcmp(SysContext->ipcam_SysConfig->ConfigNet.NetHostName,lpNetExtConfig->NetHostName))
			return FALSE;
		strncpy(SysContext->ipcam_SysConfig->ConfigNet.NetHostName,lpNetExtConfig->NetHostName,24);
		break;
    case NETCFG_CMD_SETDNS:
		if(0==strcmp(lpNetExtConfig->NetDnsIPV4[0],""))return TRUE;
		ptr=strchr(lpNetExtConfig->NetDnsIPV4[0],'.');
		while(ptr){
			i++;
			irt =atoi(ptr);
			if(irt>255&&irt<0)return FALSE;
			ptr=strchr(ptr+1,'.');
		}
		if(3!=i)return FALSE;
		strncpy(SysContext->ipcam_SysConfig->ConfigNet.NetDnsSvI, lpNetExtConfig->NetDnsIPV4[0] ,16);
        strncpy(SysContext->ipcam_SysConfig->ConfigNet.NetDnsSvII, lpNetExtConfig->NetDnsIPV4[1],16);
        break;

    case NETCFG_CMD_SETGATEWAY:
		for (i=0;i<lpNetExtConfig->NetGatewaySize ;i++)
		{
			if(0==strcmp(lpNetExtConfig->NetGateway[i],""))return TRUE;
			ptr=strchr(lpNetExtConfig->NetGateway[i],'.');
			while(ptr){
				i++;
				irt =atoi(ptr);
				if(irt>255&&irt<0)return FALSE;
				ptr=strchr(ptr+1,'.');
			}
			if(3!=i)return FALSE;
		}
		strncpy(SysContext->ipcam_SysConfig->ConfigNet.NetGwAddr, lpNetExtConfig->NetGateway[0],16);
        
        break;

    case NETCFG_CMD_SETNTP:
        strncpy(SysContext->ipcam_SysConfig->ConfigNet.NtpServer[0], lpNetExtConfig->NetNtpDns[0],50);
        break;

    case NETCFG_CMD_SETDNYDNS:
		strncpy(SysContext->ipcam_SysConfig->ConfigNet.DdnsServerList[0].SevName, lpNetExtConfig->NetDynamicDns, 64);
		break;

    default:
        return FALSE;
    }


    return TRUE;
}

BOOL  GetNetProtocols(LPNETPROTOCALS lpNetProtocals)//?
{
	LPIPCAM_SYSCONTEXT SysContext = IPCAM_GetSystemContext();
	
    lpNetProtocals->NetProtocalTypeSize = 3;
    lpNetProtocals->NetProtocals[0].NetProtocalEnabled = TRUE;
    lpNetProtocals->NetProtocals[0].NetProtocalPort = NET_ONVIF_SERVER_PORT;
    lpNetProtocals->NetProtocals[0].NetProtocalType = NET_PROTOCOLTYPE_HTTP;

    lpNetProtocals->NetProtocals[1].NetProtocalEnabled = FALSE;
    lpNetProtocals->NetProtocals[1].NetProtocalPort = 443;
    lpNetProtocals->NetProtocals[1].NetProtocalType = NET_PROTOCOLTYPE_HTTPS;

    lpNetProtocals->NetProtocals[2].NetProtocalEnabled = TRUE;
    lpNetProtocals->NetProtocals[2].NetProtocalPort = NET_ONVIF_SERVER_PORT;
    lpNetProtocals->NetProtocals[2].NetProtocalType = NET_PROTOCOLTYPE_RTSP;

    return TRUE;
}

BOOL SetNetProtocols(LPNETPROTOCALS pNetProtocals)//?
{
    int i = 0;
    for (i = 0; i < pNetProtocals->NetProtocalTypeSize; i++)
    {
		if(NULL != &pNetProtocals->NetProtocals[i]){
			if(1== pNetProtocals->NetProtocals[i].NetProtocalType)
				return FALSE;
		}
        if (pNetProtocals->NetProtocals[i].NetProtocalEnabled)
        {
           
        }
    }

    return TRUE;
}
BOOL GetRelayOutputs(LPIORELAYOUTPUTS   lpIoRelayOutPuts)//?
{
	lpIoRelayOutPuts->IoRelayOutSize								= 1;
	strncpy(lpIoRelayOutPuts->IoRelayOutputs[0].IoRelayouttoken, "RelayOutputs0",OVFCHARLENTH);
	lpIoRelayOutPuts->IoRelayOutputs[0].IoRelayoutputSet.IoRelayMode	= IO_RELAYMODE_BIST;
	strncpy(lpIoRelayOutPuts->IoRelayOutputs[0].IoRelayoutputSet.IoDelayTime,"PT30S",OVFCHARLENTH);
	lpIoRelayOutPuts->IoRelayOutputs[0].IoRelayoutputSet.IoIdleState	= IO_RELAYSTATE_OPEN;

	return TRUE;
}

BOOL SetRelayOutput(CHAR *IoToken,LPIORELAYOUTSET   IoRelayOutSet)//?
{
	int ret=0;
	if (IoRelayOutSet==NULL || IoToken ==NULL)
	{
		return FALSE;
	}
	ret = IsValidToken(IoToken,7);
	if (ret<0)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL SetRelayActive(CHAR *IoToken,ENU_IORELAYLOGIC  IoRelayLogic)//?
{
	return TRUE;
}

CALLBACKDEVMS CallBackDevMs = {0};
VOID InitCallBackDevMs(VOID)
{
	  CallBackDevMs.GetImg =GetImg;
    CallBackDevMs.GetDevServerCap = GetDevServerCap;
    CallBackDevMs.GetNetInterface = GetNetInterface;
    CallBackDevMs.SetNetInterface = SetNetInterface;
    CallBackDevMs.GetNetConfigExt = GetNetConfigExt;
    CallBackDevMs.SetNetConfigExt = SetNetConfigExt;

    CallBackDevMs.GetNetProtocols = GetNetProtocols;
    CallBackDevMs.SetNetProtocols = SetNetProtocols;

    CallBackDevMs.GetNetZeroConfig = GetNetZeroConfig;
    CallBackDevMs.SetNetZeroConfig = SetNetZeroConfig;

    CallBackDevMs.GetNetIPAddressFilter = GetNetIPAddressFilter;
    CallBackDevMs.SetNetIPAddressFilter = SetNetIPAddressFilter;
    CallBackDevMs.AddNetIPAddressFilter = AddNetIPAddressFilter;
    CallBackDevMs.RemNetIPAddressFilter = RemNetIPAddressFilter;

	CallBackDevMs.GetRelayOutputs  = GetRelayOutputs;
	CallBackDevMs.SetRelayOutput   = SetRelayOutput;
	CallBackDevMs.SetRelayActive   = SetRelayActive;

    CallBackDevMs.GetRemoteUser = GetRemoteUser;
    CallBackDevMs.SetRemoteUser = SetRemoteUser;

    CallBackDevMs.GetUsers = GetUsers;
    CallBackDevMs.SetUsers = SetUsers;
    CallBackDevMs.AddUsers = AddUsers;
    CallBackDevMs.DelUsers = DelUsers;

    CallBackDevMs.SysReboot = SysReboot;
    CallBackDevMs.SysGetLog = SysGetLog;
    CallBackDevMs.SysBackup = SysBackup;
    CallBackDevMs.SysGetSuportInfo = SysGetSuportInfo;
    CallBackDevMs.SysGetDeviceInfo = SysGetDeviceInfo;
    CallBackDevMs.SysSetFactoryDefault = SysSetFactoryDefault;
    CallBackDevMs.SysGetDateTime = SysGetDateTime;
    CallBackDevMs.SysSetDateTime = SysSetDateTime;
    CallBackDevMs.SysStartFirewareUpGrade = SysStartFirewareUpGrade;
    CallBackDevMs.SysUpGradeFireware = SysUpGradeFireware;
    CallBackDevMs.SysStartSystemRestore = SysStartSystemRestore;
    CallBackDevMs.SysRestoreSystem = SysRestoreSystem;
}

