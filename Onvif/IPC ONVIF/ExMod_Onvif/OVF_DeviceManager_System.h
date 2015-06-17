//OVF_DeviceManager_System.h
/*################################################################################
#Project Description:
#      OVIF Э��SDK
#
# The File Description:
#      OVIF Э�� �豸����.ϵͳ����
# Note:
#      1.
#
#
# Authors:
#       Fifo2005@gmail.com                                       2011.12.30 First
#       
#Copyright:
#       Copyright(c) 2008~2001x 
#  	    Fifo2005@gmail.com All rights reserved.
###############################################################################*/
#ifndef OVF_DEVICEMAGER_SYSTEM_H
#define OVF_DEVICEMAGER_SYSTEM_H

typedef enum 
{LOGTYPEOVF_SYSTEM      = 0,                               //ϵͳ
 LOGTYPEOVF_ACCESS      = 1,                               //���ʼ�¼
 }LOGTYPE;                                              //LOG
typedef enum 
{FACTORY_DEFAULT_HARD= 0,                               //Ӳ��
 FACTORY_DEFAULT_SOFT= 1,                               //���
}ENU_FACTORYDEFFAULT;                                   //�ָ�Ĭ������
typedef enum
{SETDTTYPE_MANUAL    = 0,                               //�ֹ�
 SETDTTYPE_NTP       = 1                                //NTP
}ENU_SETDTTYPE;                                         //ʱ����������

typedef struct tagATTACHMENTDATA
{
	CHAR             fiName[OVFCHARLENTH];
	CHAR            *Data;	                              //xmime contentType �������(ע��:��������Ҫ�����߾�̬����)
}ATTACHMENTDATA,*LPATTACHMENTDATA;

typedef struct tagBACKUPFILES
{
    INT              nFiles;
    ATTACHMENTDATA   BackupFile[5];
}BACKUPFILES,*LPBACKUPFILES;
typedef struct tagSYSTEMLOGS
{ 
    ATTACHMENTDATA   LogFile;
}SYSTEMLOGS,*LPSYSTEMLOGS,
 SUPORTINFO,*LPSUPORTINFO;

typedef struct tagDEVICEINFO
{
	CHAR              DevManufacturer[OVFCHARLENTH];       //������Ϣ
	CHAR              DevModel[OVFCHARLENTH];	           //�ͺ�
    CHAR              DevFirmwareVersion[OVFCHARLENTH];    //Firmware�汾
	CHAR              DevSerialNumber[OVFCHARLENTH];	   //ϵ�к�
	CHAR              DevHardwareId[OVFCHARLENTH];	       //�豸ID��
}DEVICEINFO,*LPDEVICEINFO;
typedef struct tagDATETIMES
{
    INT               Year;
    INT               Month;
    INT               Date;
    INT               Hour;
    INT               Minute;
    INT               Second;
}DATETIMES;
typedef struct tagDATATIME
{
	ENU_SETDTTYPE     SetDateTimeType;
	BOOL              IsDaylightSavings;
	CHAR              TimeZone[OVFCHARLENTH];
	DATETIMES         UTCDateTime;                           //���ʱ�׼ʱ��
	//����ȡ
    DATETIMES         LocalTime;                   
}DATETIME,*LPDATETIME;
typedef struct tagUPGRADE
{
	CHAR              UploadUri[OVFCHARLENTH];
	CHAR              UploadDelay[OVFCHARLENTH];             //��ʱ
	CHAR              ExpectedDownTime[OVFCHARLENTH];        //�쳣�ж�ʱ��
}UPGRADE,*LPUPGRADE;
typedef struct tagRESTORESYSTEM
{
	CHAR              UploadUri[OVFCHARLENTH];	
	CHAR              ExpectedDownTime[OVFCHARLENTH];
}RESTORESYSTEM,*LPRESTORESYSTEM;
#endif//OVF_DEVICEMAGER_SYSTEM_H
//


