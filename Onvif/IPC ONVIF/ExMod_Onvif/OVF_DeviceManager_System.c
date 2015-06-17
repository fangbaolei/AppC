#include "stdsoap2.h"
#include "soapH.h"
#include "soapStub.h"
#include "OVF_Export.h"
#include "OVF_Core.h"
#include "OVF_Discovery.h"

//////////////////////////////////////////系统配置///////////////


SOAP_FMAC5 int SOAP_FMAC6 __tds__SystemReboot(struct soap* hSoap, struct _tds__SystemReboot *tds__SystemReboot, struct _tds__SystemRebootResponse *tds__SystemRebootResponse)
{
    printf("[__tds__SystemReboot]..................................................................\n");
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    NEWMIII(tds__SystemRebootResponse->Message,CHAR,OVFCHARLENTH);
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,SysReboot);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->SysReboot( ))return SOAP_FAULT;
    strncpy(tds__SystemRebootResponse->Message,"Device Reboot",OVFCHARLENTH);
    return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetSystemBackup(struct soap* hSoap, struct _tds__GetSystemBackup *tds__GetSystemBackup, struct _tds__GetSystemBackupResponse *tds__GetSystemBackupResponse)
{
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    struct tt__AttachmentData *Data[5];
    INT     i;
    
    NEW(Backfile,BACKUPFILES);
    NEWMII(BackfileRsp,struct tt__BackupFile,5);
    for(i=0;i<5&&i<Backfile->nFiles;i++)BackfileRsp[i].Data=Data[i];
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,SysBackup);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->SysBackup( Backfile))return SOAP_FAULT;
	for(i=0;i<5&&i<Backfile->nFiles;i++){
	    BackfileRsp[i].Name                    = Backfile->BackupFile[i].fiName;
		BackfileRsp[i].Data->xmime__contentType= Backfile->BackupFile[i].Data;
	}
     tds__GetSystemBackupResponse->__sizeBackupFiles =Backfile->nFiles;
	 tds__GetSystemBackupResponse->BackupFiles       =BackfileRsp;
    return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetSystemLog(struct soap* hSoap, struct _tds__GetSystemLog *tds__GetSystemLog, struct _tds__GetSystemLogResponse *tds__GetSystemLogResponse)
{
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    
    NEW(Logfile,SYSTEMLOGS);
    NEW(LogfileRsp,struct tt__SystemLog);
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,SysGetLog);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->SysGetLog(tds__GetSystemLog->LogType,Logfile))return SOAP_FAULT;

    LogfileRsp->String                    = Logfile->LogFile.fiName;

	tds__GetSystemLogResponse->SystemLog  =LogfileRsp;
    return SOAP_OK;   
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetSystemSupportInformation(struct soap* hSoap, struct _tds__GetSystemSupportInformation *tds__GetSystemSupportInformation, struct _tds__GetSystemSupportInformationResponse *tds__GetSystemSupportInformationResponse)
{
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    
    NEW(SupInfo,SUPORTINFO);//这里定义结构和Log相同
    NEW(SupInfoRsp,struct tt__SupportInformation);
    NEW(Data      ,struct tt__AttachmentData); 
    SupInfoRsp->Binary=Data;
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,SysGetSuportInfo);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->SysGetSuportInfo(SupInfo))return SOAP_FAULT;

    SupInfoRsp->String                    = SupInfo->LogFile.fiName;
	SupInfoRsp->Binary->xmime__contentType= SupInfo->LogFile.Data;

	tds__GetSystemSupportInformationResponse->SupportInformation =SupInfoRsp;
    return SOAP_OK;    
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDeviceInformation(struct soap* hSoap, struct _tds__GetDeviceInformation *tds__GetDeviceInformation, struct _tds__GetDeviceInformationResponse *tds__GetDeviceInformationResponse)
{
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    
    NEW(DevInfo,DEVICEINFO);

    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,SysGetDeviceInfo);
 //   printf("========================================GetDeviceInformation start==================================\n");
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->SysGetDeviceInfo(DevInfo))return SOAP_FAULT;

	tds__GetDeviceInformationResponse->FirmwareVersion= DevInfo->DevFirmwareVersion;//结构定义相同  
	//  printf("========================================%s==================================\n",DevInfo->DevFirmwareVersion); 
	tds__GetDeviceInformationResponse->HardwareId     = DevInfo->DevHardwareId;
//	 printf("========================================%s==================================\n",DevInfo->DevHardwareId); 
	tds__GetDeviceInformationResponse->Manufacturer   = DevInfo->DevManufacturer;
	//printf("========================================%s==================================\n",DevInfo->DevManufacturer); 
    tds__GetDeviceInformationResponse->Model          = DevInfo->DevModel;
   // printf("========================================%s==================================\n",DevInfo->DevModel); 
    tds__GetDeviceInformationResponse->SerialNumber   = DevInfo->DevSerialNumber;
   // printf("========================================%s==================================\n",DevInfo->DevSerialNumber); 
	//  printf("========================================GetDeviceInformation end==================================\n");
    return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetSystemFactoryDefault(struct soap* hSoap, struct _tds__SetSystemFactoryDefault *tds__SetSystemFactoryDefault, struct _tds__SetSystemFactoryDefaultResponse *tds__SetSystemFactoryDefaultResponse)
{
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;

    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,SysSetFactoryDefault);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->SysSetFactoryDefault(tds__SetSystemFactoryDefault->FactoryDefault))return SOAP_FAULT;

    return SOAP_OK;
}

//时钟
SOAP_FMAC5 int SOAP_FMAC6 __tds__SetSystemDateAndTime(struct soap* hSoap, struct _tds__SetSystemDateAndTime *tds__SetSystemDateAndTime, struct _tds__SetSystemDateAndTimeResponse *tds__SetSystemDateAndTimeResponse)
{
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
	NEW(dt ,    DATETIME);	
	NEWMIII(hSoap->fault ,struct SOAP_ENV__Fault,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code,struct SOAP_ENV__Code ,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode,struct SOAP_ENV__Code,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode,struct SOAP_ENV__Code ,1);
		NEWMIII(hSoap->fault->SOAP_ENV__Reason,struct SOAP_ENV__Reason,1);
	if(NULL != tds__SetSystemDateAndTime){
		dt->SetDateTimeType  =tds__SetSystemDateAndTime->DateTimeType;
//		printf("-----------------------------------DT%d\n",tds__SetSystemDateAndTime->DateTimeType);
		dt->IsDaylightSavings=tds__SetSystemDateAndTime->DaylightSavings;
		if(NULL != tds__SetSystemDateAndTime->TimeZone){
			STRNCPY(dt->TimeZone ,tds__SetSystemDateAndTime->TimeZone->TZ,OVFCHARLENTH);
		}
		if(NULL !=tds__SetSystemDateAndTime->UTCDateTime)
		{
			if(NULL != tds__SetSystemDateAndTime->UTCDateTime->Date){
				dt->UTCDateTime.Year  =tds__SetSystemDateAndTime->UTCDateTime->Date->Year;
				dt->UTCDateTime.Month =tds__SetSystemDateAndTime->UTCDateTime->Date->Month;
				dt->UTCDateTime.Date  =tds__SetSystemDateAndTime->UTCDateTime->Date->Day;
			}	
			if (NULL != tds__SetSystemDateAndTime->UTCDateTime->Time)
			{
				dt->UTCDateTime.Hour  =tds__SetSystemDateAndTime->UTCDateTime->Time->Hour;
				dt->UTCDateTime.Minute=tds__SetSystemDateAndTime->UTCDateTime->Time->Minute;
				dt->UTCDateTime.Second=tds__SetSystemDateAndTime->UTCDateTime->Time->Second;
			}
		}
		
	}
    
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,SysSetDateTime);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->SysSetDateTime(dt)){
		if (dt->TimeZone !=NULL)
		{
			hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode->SOAP_ENV__Value ="ter:InvalidTimeZone" ;
			hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Value ="ter:InvalidArgVal";
 			hSoap->fault->SOAP_ENV__Reason->SOAP_ENV__Text="the matching rule specified is not supported";
		}
		 return SOAP_FAULT;
	}
    if(2==Onvif->CallBackOvf->CallBackDevManage->SysSetDateTime(dt)){
		if (&dt->UTCDateTime !=NULL)
		{
			hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode->SOAP_ENV__Value ="ter:InvalidDateTime";
			hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Value="ter:InvalidArgVal";
			hSoap->fault->SOAP_ENV__Reason->SOAP_ENV__Text="An invalid date or time was specified.";
		}
		
		return SOAP_FAULT;
	}
    return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetSystemDateAndTime(struct soap* hSoap, struct _tds__GetSystemDateAndTime *tds__GetSystemDateAndTime, struct _tds__GetSystemDateAndTimeResponse *tds__GetSystemDateAndTimeResponse)
{
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
	NEW(TimeZone ,    struct tt__TimeZone);	
	NEW(UTCDateTime,  struct tt__DateTime);	
    NEW(UTCTime,	  struct tt__Time);	
	NEW(UTCDate,      struct tt__Date);
	NEW(LocDateTime,  struct tt__DateTime);	
    NEW(LocTime,	  struct tt__Time);	
	NEW(LocDate,      struct tt__Date);
    NEW(dtRsp,struct tt__SystemDateTime );
    NEW(dt ,    DATETIME);
   
	UTCDateTime->Date = UTCDate;
	UTCDateTime->Time = UTCTime;
	LocDateTime->Date = LocDate;
	LocDateTime->Time = LocTime;
	
 
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,SysGetDateTime);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->SysGetDateTime(dt))return SOAP_FAULT;
    dtRsp->LocalDateTime = LocDateTime;
	dtRsp->UTCDateTime   = UTCDateTime;
	dtRsp->TimeZone      = TimeZone;
	dtRsp->DateTimeType = dt->SetDateTimeType;
	dtRsp->DaylightSavings = dt->IsDaylightSavings;
	dtRsp->TimeZone->TZ    = dt->TimeZone;
	dtRsp->LocalDateTime->Date->Year  = dt->LocalTime.Year;
	dtRsp->LocalDateTime->Date->Month = dt->LocalTime.Month;
	dtRsp->LocalDateTime->Date->Day   = dt->LocalTime.Date;
	dtRsp->LocalDateTime->Time->Hour  = dt->LocalTime.Hour;
	dtRsp->LocalDateTime->Time->Minute= dt->LocalTime.Minute;
	dtRsp->LocalDateTime->Time->Second= dt->LocalTime.Second;
	dtRsp->UTCDateTime->Date->Year  = dt->UTCDateTime.Year;
	dtRsp->UTCDateTime->Date->Month = dt->UTCDateTime.Month;
	dtRsp->UTCDateTime->Date->Day   = dt->UTCDateTime.Date;
	dtRsp->UTCDateTime->Time->Hour  = dt->UTCDateTime.Hour;
	dtRsp->UTCDateTime->Time->Minute= dt->UTCDateTime.Minute;
	dtRsp->UTCDateTime->Time->Second= dt->UTCDateTime.Second;  

    tds__GetSystemDateAndTimeResponse->SystemDateAndTime=dtRsp;
    return SOAP_OK;
}

//升级
SOAP_FMAC5 int SOAP_FMAC6 __tds__StartFirmwareUpgrade(struct soap* hSoap, struct _tds__StartFirmwareUpgrade *tds__StartFirmwareUpgrade, struct _tds__StartFirmwareUpgradeResponse *tds__StartFirmwareUpgradeResponse)
{
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    
    NEW(Up,UPGRADE);

    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,SysStartFirewareUpGrade);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->SysStartFirewareUpGrade(Up))return SOAP_FAULT;

	tds__StartFirmwareUpgradeResponse->UploadUri    = Up->UploadUri;
	tds__StartFirmwareUpgradeResponse->UploadDelay  = Up->UploadDelay;
	tds__StartFirmwareUpgradeResponse->ExpectedDownTime= Up->ExpectedDownTime;
   
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__UpgradeSystemFirmware(struct soap* hSoap, struct _tds__UpgradeSystemFirmware *tds__UpgradeSystemFirmware, struct _tds__UpgradeSystemFirmwareResponse *tds__UpgradeSystemFirmwareResponse)
{
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    
    NEW(Up,ATTACHMENTDATA);
    NEW(Data,struct tt__AttachmentData);
    Up->Data =Data->xmime__contentType;
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,SysUpGradeFireware);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->SysUpGradeFireware(Up))return SOAP_FAULT; 
	return SOAP_OK;
}

//备份
SOAP_FMAC5 int SOAP_FMAC6 __tds__StartSystemRestore(struct soap* hSoap, struct _tds__StartSystemRestore *tds__StartSystemRestore, struct _tds__StartSystemRestoreResponse *tds__StartSystemRestoreResponse)
{
	printf("[__tds__StartSystemRestore]..................................................................\n");
	ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;

	NEW(Rep,RESTORESYSTEM);

	CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,SysStartSystemRestore);
	if(FALSE==Onvif->CallBackOvf->CallBackDevManage->SysStartSystemRestore(Rep))return SOAP_FAULT;

	tds__StartSystemRestoreResponse->UploadUri    = Rep->UploadUri;
	tds__StartSystemRestoreResponse->ExpectedDownTime= Rep->ExpectedDownTime;
       
    	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__RestoreSystem(struct soap* hSoap, struct _tds__RestoreSystem *tds__RestoreSystem, struct _tds__RestoreSystemResponse *tds__RestoreSystemResponse)
{
	printf("[__tds__RestoreSystem]..................................................................\n");
	ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
	INT     i;
	NEW(Restore,ATTACHMENTDATA);
	CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,SysRestoreSystem);
	for(i=0;i<tds__RestoreSystem->__sizeBackupFiles;i++){
	    STRNCPY(Restore->fiName,tds__RestoreSystem->BackupFiles[i].Name,OVFCHARLENTH);
		Restore->Data   = tds__RestoreSystem->BackupFiles[i].Data->xmime__contentType;
	   if(FALSE==Onvif->CallBackOvf->CallBackDevManage->SysRestoreSystem(Restore))return SOAP_FAULT;
	} 
	return SOAP_OK;
}



