//OVF_DeviceManager_OvfInfo.h
/*################################################################################
#Project Description:
#      OVIF Э��SDK
#
# The File Description:
#      OVIF Э�� �豸����.OVIF������������
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
#ifndef OVF_DEVICEMANAGER_OVFINFO_H
#define OVF_DEVICEMANAGER_OVFINFO_H
typedef struct tagDEVMSVCAP_NET
{
	BOOL SupIPFilter ;	                      //IP����:FALSE?TRUE
	BOOL SupZeroConfiguration ;	              //����������:FALSE?TRUE
	BOOL SupIPVersion6 ;	                  //IPV6:FALSE
	BOOL SupDynDNS ;	                      //��̬����:TRUE
	BOOL SupDot11Configuration ;	          //802.11X����:FALSE
	BOOL SupHostnameFromDHCP ;	              //DHCP��ȡ������:FALSE
	BOOL SupNTP ;	                          //NTP:TRUE
}DEVMSVCAP_NET;
typedef struct tagDEVMSVCAP_SECURT
{
	BOOL SupTLS1_x002e0 ;	                  //֧��SSL���ܣ���ͬ:FALSE
	BOOL SupTLS1_x002e1 ;	 
	BOOL SupTLS1_x002e2 ;	 
	BOOL SupOnboardKeyGeneration ;	          //:FALSE 
	BOOL SupAccessPolicyConfig ;	          //���ʹ���:TRUE?FALSE
	BOOL SupDot1X ;	                          //802.11x���ܹ���:FALSE
	BOOL SupRemoteUserHandling ;	          //Զ�̵�¼�ʻ�����:TRUE?FALSE
	BOOL SupX_x002e509Token ;	              //509����:FALSE
	BOOL SupSAMLToken ;	                      //SAML����:FALSE
	BOOL SupKerberosToken ;	                  //Kerberos����:FALSE
	BOOL SupUsernameToken ;	                  //�ʻ�����:FALSE?TRUE
	BOOL SupHttpDigest ;	                  //http����ǩ��:FALSE?TRUE
	BOOL SupRELToken ;	                      //rel����:FALSE?TRUE
}DEVMSVCAP_SECURT;
typedef struct tagDEVMSVCAP_SYS
{
	BOOL SupDiscoveryResolve ;	              //���ֲ���,��ͬ:TRUE 
	BOOL SupDiscoveryBye ;	              
	BOOL SupRemoteDiscovery ;	 
	BOOL SupSystemBackup ;	                  //ϵͳ����:TRUE?FALSE
	BOOL SupSystemLogging ;	                  //log :TRUE?FALSE
	BOOL SupFirmwareUpgrade ;	              //ϵͳ����:TRUE?FALSE
	BOOL SupHttpFirmwareUpgrade ;	          //http��������:TRUE?FALSE
	BOOL SupHttpSystemBackup ;	              //httpϵͳ����:TRUE?FALSE
	BOOL SupHttpSystemLogging ;	              //http log����:TRUE?FALSE
	BOOL SupHttpSupportInformation ;	      //http ϵͳ��Ϣ�鿴:TRUE?FALSE
	
}DEVMSVCAP_SYS;
typedef struct tagDEVMSVCAP_ANALYTICS
{
	CHAR SupXAddr[OVFCHARLENTH];	          //��Ƶ��������·��:NULL
	BOOL SupRuleSupport;	                  //֧����Ƶ��������:FALSE
	BOOL SupAnalyticsModuleSupport;	          //��Ƶ����ģ��֧��:FALSE
}DEVMSVCAP_ANALYTICS;
typedef struct tagDEVMSCAP_IO
{
	INT  InputConnectors;	                  //�������
	INT  RelayOutputs;	                      //�����������
}DEVMSCAP_IO;
typedef struct tagDEVMSCAP_EVENT
{
	CHAR   SupXAddr[OVFCHARLENTH];	          //�¼�����URL:NULL
	BOOL   SupWSSubscriptionPolicySupport;    //WS����֮�¼�����֧��:FALSE
	BOOL   SupWSPullPointSupport;    	      //WS����֮�¼�����֧��:FALSE
	BOOL   SupWSPausableSubscriptionManagerInterfaceSupport;	//WS�����Ķ��������ӿ�֧��:FALSE

}DEVMSCAP_EVENT;
typedef struct tagDEVMSCAP_IMAG
{
	CHAR   SupXAddr[OVFCHARLENTH];              //ͼ������URL
}DEVMSCAP_IMAG;
typedef struct tagDEVMSCAP_LIVESTREAM
{
	BOOL SupRTPMulticast;	                    //RTP�ಥ:TRUE
	BOOL SupRTP_USCORETCP;	                    //RTP��TCP����:TRUE
	BOOL SupRTP_USCORERTSP_USCORETCP;	        //RTSP��TCP����:TRUE    
}DEVMSCAP_LIVESTREAM;
typedef struct tagDEVMSCAP_MEDIA
{
	CHAR  SupXAddr[OVFCHARLENTH];       
	DEVMSCAP_LIVESTREAM Streaming;	           //ý����Ϣ

}DEVMSCAP_MEDIA;
typedef struct tagDEVMSCAP_PTZ
{
	CHAR  SupXAddr[OVFCHARLENTH];              //����·��  	     

}DEVMSCAP_PTZ;
typedef struct tagDEVMSCAP_DEV
{
	CHAR                XAddr[OVFCHARLENTH];   //����URL
	DEVMSVCAP_NET       Network;	           //�豸����
	DEVMSVCAP_SYS       System;	               //ϵͳ����
	DEVMSCAP_IO         IO;	                   //IO
	DEVMSVCAP_SECURT    Security;	           //��ȫ

}DEVMSCAP_DEV;
typedef struct tagDEVMSVCAP
{
    DEVMSCAP_DEV         CapDevice;            //�豸����
    DEVMSVCAP_ANALYTICS  CapAnalytics;         //����
    DEVMSCAP_EVENT       CapEvent;             //�¼�
    DEVMSCAP_IMAG        CapImag;              //ͼ��
    DEVMSCAP_MEDIA       CapMedia;             //ý��
    DEVMSCAP_PTZ         CapPTZ;               //ptz�ƿ�
}DEVMSVCAP,*LPDEVSVCAP;
/////////��������//////////////
typedef enum  {
 LOG_SYSTEM = 0, 
 LOG_ACCESS = 1
}ENU_TYPELOG;

typedef struct tagSYSTEMURLLOG
{
	ENU_TYPELOG LogType;	                   //Log����
	CHAR        LogUri[OVFCHARLENTH];	       //Log��ȡURL
	INT         Reserve1;	                   //����
	CHAR **     Reserve2;                      //����
	CHAR       *Reserve3;	                   //����
}SYSTEMURLLOG;
typedef struct tagSYSTEMURL
{
    INT           urlSystemLogSize;
	SYSTEMURLLOG  urlSystemLog[2];	
	CHAR          urlSupportInfo [OVFCHARLENTH];//ϵͳ֧�֣����Ҽ���֧��
	CHAR          urlSystemBackup[OVFCHARLENTH];//ϵͳ����

}SYSTEMURL,*LPSYSTEMURL;
//////////////////////////////////


#endif//OVF_DEVICEMANAGER_ONVFINFO_H

