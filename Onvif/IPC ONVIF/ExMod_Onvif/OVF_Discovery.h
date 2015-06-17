//OVF_Disconvery.h
/*################################################################################
#Project Description:
#      OVIF Э��SDK
#
# The File Description:
#      OVIF Э�� �豸����
# Note:
#      1.OVIF �豸���̶ֹ�ʹ���鲥��ַ239.255.255.250:3702 ���տͻ��˵��豸������Ϣ
#        ���ظ�����
#
#
# Authors:
#       Fifo2005@gmail.com                                       2011.12.30 First
#       
#Copyright:
#       Copyright(c) 2008~2001x 
#  	    Fifo2005@gmail.com All rights reserved.
###############################################################################*/

#ifndef OVF_DISCOVERY_H
#define OVF_DISCOVERY_H

#include "OVF_Global.h"
//////////DISCONVERY
typedef struct tagOVFDISCONVERYINFO
{
	CHAR    DevGuid       [OVFCHARLENTH];    //�豸��ȫ��ΨһID:464A4854-4656-5242-4530-313035394100
	CHAR    DevName       [OVFCHARLENTH];    //�豸����:IPCAM_DEV
	CHAR    DevRootUrl    [OVFCHARLENTH];    //�豸���ʸ�·��:http://192.168.1.1/device OR http://name.3322.com/device
	CHAR    DevLocation   [OVFCHARLENTH];    //�豸��װλ��:SHENGZHEN/FUTIAN/TIANAN(�����������)
    CHAR    DevType       [OVFCHARLENTH];    //WS�����豸����:IPCAM=IPCAMWSDEVICETYPE
    CHAR    DevTypeII     [OVFCHARLENTH];    //���Ҷ�����豸����:IPCAM_NO20111212
}OVFDISCONVERYINFO,*LPOVFDISCONVERYINFO;

//�ص��ӿ�
typedef struct  tagCALLBACKOVFDISCOVERY
{   //��ȡ�豸������ز���
	BOOL  (*GetDiscoveryInfo)                (LPOVFDISCONVERYINFO lpDiscoveryInfo);
}CALLBACKOVFDISCOVERY,*LPCALLBACKOVFDISCOVERY;

#endif//OVF_DISCOVERY_H


