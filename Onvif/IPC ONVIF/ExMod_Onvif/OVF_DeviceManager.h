//OVF_DeviceManager.h
/*################################################################################
#Project Description:
#      OVIF Э��SDK
#
# The File Description:
#      OVIF Э�� �豸����
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
#ifndef OVF_DEVICEMANAGER_H
#define OVF_DEVICEMANAGER_H
//OVF������Ϣ
#include "OVF_DeviceManager_OvfInfo.h"
//��������
#include "OVF_DeviceManager_NetWork.h"
//�ʻ�����
#include "OVF_DeviceManager_User.h"
//IO����
#include "OVF_DeviceManager_Io.h"
//ϵͳ���ü���ز���
#include "OVF_DeviceManager_System.h"
//ϵͳ��ȫ��֤�����
#include "OVF_DeviceManager_Security.h"
typedef struct tagCALLBACKDEVMS
{
//OVF������Ի�ȡ
  BOOL  (*GetImg)                (char*     addr); 
	BOOL  (*GetDevServerCap)                (LPDEVSVCAP     lpDevSvCap);    //��ȡ�豸��֧�ֵ�OVF���Է���
	BOOL  (*GetSystemUrl)                   (LPSYSTEMURL    lpSystemUrl);   //��ȡϵͳһЩ���ӵ�URL
	
	BOOL  (*GetDPAddress)                   (LPNETHOST      lpNetHost);     //�豸���ִ��������
    BOOL  (*SetDPAddress)                   (LPNETHOST        NetHost);
//����.����
    BOOL  (*GetNetInterface)                (LPNETINTERFACES lpNetInterfaces);
    BOOL  (*SetNetInterface)                (CHAR* InterfaceToken, LPNETINTERFACE NetInterface);
    BOOL  (*GetNetConfigExt)                (LPNETEXTCONFIG lpNetExtConfig);
    BOOL  (*SetNetConfigExt)                (LPNETEXTCONFIG   NetExtConfig,ENU_NETCFG_CMD SetCmd);
//����.Э��
    BOOL  (*GetNetProtocols)                (LPNETPROTOCALS lpNetProtocals);
    BOOL  (*SetNetProtocols)                (LPNETPROTOCALS   NetProtocals);
//����.������
    BOOL  (*GetNetZeroConfig)               (LPNETZEROCONFIG lpNetZeroConfig);
    BOOL  (*SetNetZeroConfig)               (LPNETZEROCONFIG   NetZeroConfig);
//����.IP����
    BOOL  (*GetNetIPAddressFilter)          (LPIPADDRFILTER  lpNetAddrFilter);
    BOOL  (*SetNetIPAddressFilter)          (LPIPADDRFILTER    NetAddrFilter);
    BOOL  (*AddNetIPAddressFilter)          (LPIPADDRFILTER    NetAddrFilter);
    BOOL  (*RemNetIPAddressFilter)          (LPIPADDRFILTER    NetAddrFilter);
//����.WIFI��չ����
    BOOL  (*WifiGetDot11Cap)                (LPDOT11CAP       lpNetDot11Cap);
    BOOL  (*WifiGetDot11Status)             (CHAR *InterfaceToken,LPNETDOT11STATUS lpNetDot11Status);
    BOOL  (*WifiScanHotPoint)               (CHAR *InterfaceToken,LPDOT11HOTPOINTS lpNetDot11HotPoints);
//IO.���
    BOOL  (*GetRelayOutputs)                (LPIORELAYOUTPUTS   lpIoRelayOutPuts );
    BOOL  (*SetRelayOutput )                (CHAR *IoToken,LPIORELAYOUTSET   IoRelayOutSet);
    BOOL  (*SetRelayActive)                 (CHAR *IoToken,ENU_IORELAYLOGIC  IoRelayLogic);
//�û�.Զ���û�
    BOOL  (*GetRemoteUser)                  (LPREMOTEUSER lpRemoteUser);
    BOOL  (*SetRemoteUser)                  (LPREMOTEUSER   RemoteUser);
//�û�.ϵͳ�û�
    BOOL  (*GetUsers)                       (LPUSERS  lpUsers );
    BOOL  (*SetUsers)                       (LPUSERS    Users );
    BOOL  (*AddUsers)                       (LPUSERS    Users );
    BOOL  (*DelUsers)                       (LPUSERS    Users );
//ϵͳ.ά��
    BOOL  (*SysReboot)                      ();
    BOOL  (*SysGetLog)                      (LOGTYPE LogType,LPSYSTEMLOGS lpSystemLog);
    BOOL  (*SysBackup)                      (LPBACKUPFILES lpBackupFiles);
    BOOL  (*SysGetSuportInfo)               (LPSUPORTINFO  lpSuportInfo);
    BOOL  (*SysGetDeviceInfo)               (LPDEVICEINFO  lpDeviceInfo);
    BOOL  (*SysSetFactoryDefault)           (ENU_FACTORYDEFFAULT FactoryDefaultType);
    BOOL  (*SysGetDateTime)                 (LPDATETIME lpGetDatetime);
    BOOL  (*SysSetDateTime)                 (LPDATETIME   SetDatetime);
    BOOL  (*SysStartFirewareUpGrade)        (LPUPGRADE    lpFirewareUpdate);
    BOOL  (*SysUpGradeFireware)             (LPATTACHMENTDATA  DataFireware);
    BOOL  (*SysStartSystemRestore)          (LPRESTORESYSTEM  lpRestoreSystem);
    BOOL  (*SysRestoreSystem)               (LPATTACHMENTDATA  DataRestore);
    
//��ȫ.SSL (����)
//��ȫ.֤��(����)
//��ȫ.11x (����)
}CALLBACKDEVMS,*LPCALLBACKDEVMS;


#endif//OVF_DEVICEMANAGER_H

