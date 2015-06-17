//OVF_Export.h
/*################################################################################
#Project Description:
#      OVIF Э��SDK
#
# The File Description:
#      OVIF SDK �����ļ�
# Note:
#      1.��̷����赼�뱾�ļ����ɡ�
#      2.OVF_Init/DeInit ����������ж��OVIF����ģ��,OVIF����ģ���ڽ�����ռ��һ��
#        TCP�˿ں�һ��UDP�˿�,UDP�˿�������ģ�OVIF���豸���ֲ���ʹ�ù̶����鲥ͨ��
#        �μ�OVF_Discovery���ֶ��壬�ö˿��Ƕ�ռ��ʽ��
#      3.��̷����ص������ṹ�ͺͺ�������ע�뺯������ע�뺯���ṹ������豸��ģ��
#        ��֧�֣���ע���Ӧ�������߶�Ӧ������֧�֡�
#        
#      4.��������:
         4.1 �����Ͳ���ʹ����������������
         4.2 ����lpxxxǰ׺��Ϊ�����������֮���������.
#      5.�������εĽṹָ������ر�����������OVIFģ���ڲ������ص��ڲ�ֻ��ʹ�ü��ɡ�
#      6.OVF ��׼�����и��ж�����IO������������Device�ڵ�IO�����Imaging�ں�Media��
#        ��ز����ظ�����API�ӿ�ȥ����
       7.OVF ������IVT(ipcam)�����豸Э����ʱδ����֧���¼���������NVR(DVR)���豸��̬
       ������Ҳ���������Э�顣
       8.����Ϊ�����Ĳ�����������ʹ�ã�����ɲ���֧��
#
# Authors:
#       Fifo2005@gmail.com                                       2011.12.30 First
#       
#Copyright:
#       Copyright(c) 2008~2001x 
#  	    Fifo2005@gmail.com All rights reserved.
###############################################################################*/
#ifndef OVF_EXPORT_H
#define OVF_EXPORT_H

#include "OVF_Global.h"

//////�豸���ֽӿ�
#include "OVF_Discovery.h"
//////�豸����ӿ�
#include "OVF_DeviceManager.h"
//////ý����ƽӿ�
#include "OVF_Media.h"
//////����ͷ���ƽӿ�
#include "OVF_Imaging.h"
//////��̨���ƽӿ�
#include "OVF_Ptz.h"
//////�¼�����ӿ�
//////IO  ���ƽӿ�
//////�洢���ƽӿ�
//////��Ƶ�����ӿ�
#include <time.h>
///////

//////ONVIF ģ��ӿ�
typedef struct tagCALLBACKOVF
{
	CALLBACKOVFDISCOVERY      *CallBackDiscovery;                                   //�豸������ػص����:OVF_Discovery.h
	CALLBACKDEVMS             *CallBackDevManage;                                   //�豸����ص����    :OVF_DevManager.h
	CALLBACKIMAGING           *CallBackImaging;                                     //����ͷ,CCD/CMOS etc.:OVF_Imaging.h
	CALLBACKMEDIA             *CallBackMedia;                                       //ý�崦��            :OVF_Media.h
	CALLBACKPTZ               *CallBackPtz;                                         //Ptz�ӿ�             :OVF_Ptz.h
}CALLBACKOVF,*LPCALLBACKOVF;
//ģ�����
HDOVF   OVF_Init            (UINT usIP,USHORT usPort,USHORT TimeOut,CALLBACKOVF*lpCallBack ); //TCP�ķ������˿�,TimeOut��λΪ��,usPortΪ0ʱ��������������ʹ��IsONVIF(),��StartONVIFִ��һ��ONVIF����
VOID    OVF_DeInit          (HDOVF  hOVF);                                          //ж��OVF����ģ��
//���Խӿ�
BOOL    OVF_EnableDiscovery (HDOVF  hOVF ,BOOL IsEnable);                           //�رջ���豸��Ѱ����
//һ���Է���ӿ�
BOOL    OVF_IsONVIF         (HDOVF  hOVF ,CHAR*Buff,USHORT BufLenth);               //
BOOL    OVF_StartONVIF      (HDOVF  hOVF ,CHAR*Buff,USHORT BufLenth,INT nSocket,SOCKETIN *SocketIn);
//�����������ܺ���
VOID    OVF_Sleep           (UINT   Seconds);
VOID    OVF_MSleep          (UINT   Milliseconds);
BOOL    OVF_CreateUUIDS     (CHAR  *sUUID);                                         //����һ��ȫ���־��
#endif//OVF_EXPORT_H

