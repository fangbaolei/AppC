//OVF_PTZ.h
/*################################################################################
#Project Description:
#      OVIF Э��SDK
#
# The File Description:
#      OVIF SDK PTZ����
# Note:
#      1.OVIF �����PTZ����ʵ���ǹ���һ�����ľ���ϵġ�
#      2.OVIF �����PTZ�ƶ���ʽ���ǰ����귽ʽ�ƶ������Ƚ���֣���������һ�鸨��
#        ����ӿ�(AuxComd)���������ʹ�øýӿ�����ģ���ƶ�,���ַ�ʽ�ܷ���ݣ���д��
#        ���ĵ�ʱ��û�������ɲ��ԡ�
#      3.����OVF ������ƶ���ʽ�����ã�����ⲿ�ֽ���������֧��(ע�⺯����ע)
#      4.OVIF �����PTZ������485Ӳ�������������
#      5.OVIF �����PTZ��������̨��ַ���������
#
# Authors:
#       Fifo2005@gmail.com                                       2011.12.30 First
#       
#Copyright:
#       Copyright(c) 2008~2001x 
#  	    Fifo2005@gmail.com All rights reserved.
###############################################################################*/
#ifndef OVF_PTZ_H
#define OVF_PTZ_H

typedef enum 
{
 PTZMOV_IDLE     = 0, 
 PTZMOV_MOVING   = 1,
 PTZMOV_UNKNOWN  = 2
}ENU_PTZMOVSTATUS;                //PTZ�ƶ�״̬  
typedef struct tagSPACE2DDESP
{
	CHAR         Space2dDespURL[OVFBCHARLENTH];
	FLOATRANGE   Space2dXRange;
	FLOATRANGE   Space2dYRange;
}SPACE2DDESP;                     //SPACE 2D ����
typedef struct tagSPACE1DDESP
{
	CHAR         Space1dURI[OVFBCHARLENTH];	
	FLOATRANGE   Space1XRange;	
}SPACE1DDESP;                     //SPACE 1D ����
typedef struct tagVECTOR2D
{
	FLOAT         x;	
	FLOAT         y;	
	CHAR          space[OVFBCHARLENTH];
}VECTOR2D;                        //vector 2d ����

typedef struct tagVECTOR1D
{
	FLOAT         x;	
	CHAR          space[OVFBCHARLENTH];
}VECTOR1D;                        //vector 1d ����
typedef struct tagPTZSpeed
{
	VECTOR2D      PanTilt;
    VECTOR1D      Zoom;	
}PTZSPEED ,*LPPTZSPEED,
 PTZVECTOR,*LPPTZVECTOR;
typedef struct tagPTZCONFIG
{
	CHAR          PtzCfgName[OVFCHARLENTH];
	INT           PtzCfgUseCount;	
	CHAR          PtzCfgToken[OVFCHARLENTH];
	CHAR          PtzCfgNodeToken[OVFCHARLENTH];
    //���¶��屣��
	CHAR          DefAbsPantTiltPosSpace[OVFBCHARLENTH];
	CHAR          DefAbsZoomPosSpace[OVFBCHARLENTH];
	CHAR          DefRelativePanTiltTranslationSpace[OVFBCHARLENTH];
	CHAR          DefRelativeZoomTranslationSpace[OVFBCHARLENTH];	
	CHAR          DefContinuousPanTiltVelocitySpace[OVFBCHARLENTH];	
	CHAR          DefContinuousZoomVelocitySpace[OVFBCHARLENTH];	
	PTZSPEED      DefPTZSpeed;	
	CHAR          DefPTZTimeout[OVFCHARLENTH];
	SPACE2DDESP   LimitsPanTilt;	
	SPACE1DDESP   LimitsZoom;	
}PTZCONFIG,*LPPTZCONFIG;
typedef struct tagPTZCONFIGS
{
    INT           PtzCfgSize;
    PTZCONFIG     PtzCfgs[OVFMAXCHANNEL];
}PTZCONFIGS,*LPPTZCONFIGS;
typedef struct tagPTZSPACES
{
	INT           SizeAbsolutePanTiltPositionSpace;	
	SPACE2DDESP   AbsolutePanTiltPositionSpace[5];	
	INT           SizeAbsoluteZoomPositionSpace;	
	SPACE1DDESP   AbsoluteZoomPositionSpace[5];	
	INT           SizeRelativePanTiltTranslationSpace;	
	SPACE2DDESP   RelativePanTiltTranslationSpace[5];	
	INT           SizeRelativeZoomTranslationSpace;	
	SPACE1DDESP   RelativeZoomTranslationSpace[5];	
	INT           SizeContinuousPanTiltVelocitySpace;
	SPACE2DDESP   ContinuousPanTiltVelocitySpace[5];
	INT           SizeContinuousZoomVelocitySpace;
	SPACE1DDESP   ContinuousZoomVelocitySpace[5];
	INT           SizePanTiltSpeedSpace;
	SPACE1DDESP   PanTiltSpeedSpace[5];
	INT           SizeZoomSpeedSpace;
	SPACE1DDESP   ZoomSpeedSpace[5];	
}PTZSPACES;                           //PTZ ����ռ�
typedef struct tagPTZCONFIGOPTIONS
{
	PTZSPACES     Spaces;	
	FLOATRANGE    PTZTimeout;
}PTZCONFIGOPTIONS,*LPPTZCONFIGOPTIONS;    //PTZ �������Ա�
typedef struct tagPTZNODE
{
	CHAR         Nodetoken[OVFCHARLENTH];	
	CHAR         NodeName[OVFCHARLENTH];	
	INT          MaxPresets;	
	BOOL         HomeSupported;	
	INT          AuxCommandsSize;	
	CHAR         AuxCommands[OVFCHARLENTH][OVFCHARLENTH];
    //(���±���)
    PTZSPACES    NodePTZSpaces;	                         
}PTZNODE,*LPPTZNODE;                      //PTZ �豸�ڵ�
typedef struct tagPTZNODES
{
    INT          NodeSize;
    PTZNODE      Nodes[OVFMAXCHANNEL];
}PTZNODES,*LPPTZNODES;                    //PTZ �豸�ڵ���
typedef struct tagPTZPRESET
{
	CHAR        PresetName[OVFCHARLENTH];
    CHAR        PresetToken[OVFCHARLENTH];
    //���¶��屣��
	PTZVECTOR   PresetPTZPosition;	
}PTZPRESET,*LPPTZPRESET;                 //PTZ Ԥ��λ
typedef struct tagPTZPRESETS
{
    INT         PresetSize;
    PTZPRESET   Presets[128];
}PTZPRESETS,*LPPTZPRESETS;                //PTZ Ԥ��λ��
typedef struct tagPTZSTATUS
{
	PTZVECTOR        Position;
    ENU_PTZMOVSTATUS PanTilt;
    ENU_PTZMOVSTATUS Zoom;
	CHAR             Error[OVFCHARLENTH];
	INT              UtcTime;
}PTZSTATUS,*LPPTZSTATUS;
//////////////////////////////PTZ�ӿ�//////////////////////////////////////////////////
typedef struct  tagCALLBACKPTZ
{
  //PTZ.����
    BOOL    (*PtzGetConfigs)              (LPPTZCONFIGS lpPtzConfigs);
    BOOL    (*PtzGetConfig )              (CHAR * PtzConfigToken,LPPTZCONFIG  lpPtzConfig);  
    BOOL    (*PtzSetConfig )              (CHAR * PtzConfigToken,LPPTZCONFIG    PtzConfig); //(����) 
    BOOL    (*PtzGetConfigOptions)        (LPPTZCONFIGOPTIONS lpPtzConfigOptions);          //(����)     
  //PTZ.�豸�ڵ�
    BOOL    (*PtzGetNodes)                (LPPTZNODES lpPtzNodes);
    BOOL    (*PtzGetNode )                (CHAR * PtzPtzNodeToken,LPPTZNODE PtzNode);
  //PTZ.Ԥ��λ
    BOOL    (*PtzGetPresets)              (CHAR * MediaProfileToken,LPPTZPRESETS lpPtzPresets);
    BOOL    (*PtzSetPreset )              (CHAR * MediaProfileToken,CHAR *PresetToken,CHAR *PresetName);
    BOOL    (*PtzRemPreset )              (CHAR * MediaProfileToken,CHAR *PresetToken);
    BOOL    (*PtzGotoPreset)              (CHAR * MediaProfileToken,CHAR *PresetToken,LPPTZSPEED   PtzSpeed);//SpeedΪOVIF ����ʵ������������(��ͬ)
    BOOL    (*PtzSetHomePosition)         (CHAR * MediaProfileToken);
    BOOL    (*PtzGotoHomePosition)        (CHAR * MediaProfileToken,LPPTZSPEED  PtzSpeed);
  //PTZ.�ƶ� (������غ�������)
    BOOL    (*PtzMovAbsolute)             (CHAR * MediaProfileToken,LPPTZVECTOR lpTranslation,LPPTZSPEED  PtzSpeed);
    BOOL    (*PtzMovRelative)             (CHAR * MediaProfileToken,LPPTZVECTOR lpPosition   ,LPPTZSPEED  PtzSpeed);
    BOOL    (*PtzMovContinuous)           (CHAR * MediaProfileToken,LPPTZSPEED  Velocity,CHAR * PtzTimeOut);
  //PTZ.��������
    BOOL    (*PtzSendAuxComd)             (CHAR * MediaProfileToken,CHAR * Command);
  //PTZ.ֹͣ
    BOOL    (*PtzStop)                    (CHAR * MediaProfileToken,BOOL IsStopPanTilt,BOOL IsStopRoom);
  //PTZ.״̬ (������غ�������)
    BOOL    (*PtzGetStatus)               (CHAR * MediaProfileToken,LPPTZSTATUS lpPtzStatus);
}CALLBACKPTZ,*LPCALLBACKPTZ;
#endif//OVF_PTZ_H

