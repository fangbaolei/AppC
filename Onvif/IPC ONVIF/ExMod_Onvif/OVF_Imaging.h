//OVF_Imaging.h
/*################################################################################
#Project Description:
#      OVIF Э��SDK
#
# The File Description:
#      OVIF SDK ����ͷ����
# Note:
#      1.OVIF ���������ͷ�����ų�����ͷ(������)��̬�����⣬����������ͷ�۽��ƶ�������
#
#
# Authors:
#       Fifo2005@gmail.com                                       2011.12.30 First
#       
#Copyright:
#       Copyright(c) 2008~2001x 
#  	    Fifo2005@gmail.com All rights reserved.
###############################################################################*/
#ifndef OVF_IMAGING_H
#define OVF_IMAGING_H





typedef enum 
{ST_FOCUSMOV_IDLE           = 0, 
 ST_FOCUSMOV_MOVING         = 1,
 ST_FOCUSMOV_UNKNOWN        = 2
}ENU_FOCUSMOVSTATUS;                                   //�۽��ƶ�״̬          


typedef enum 
{MODE_AUTOFOCUS_AUTO        = 0,
 MODE_AUTOFOCUS_MANUAL      = 1
 }ENU_AUTOFOCUSMODE;                                   //�Խ�ģʽ

typedef enum  
{MODE_WIDEDYNAMIC_OFF       = 0,
 MODE_WIDEDYNAMIC_ON        = 1
}ENU_WIDEDYNAMICMODE;                                  //��̬ģʽ



typedef enum 
{MODE_BACKLIGTHCOMP_OFF     = 0,
 MODE_BACKLIGTHCOMP_ON      = 1
 }ENU_BACKLIGHTCOMPMODE;                               //���ⲹ��


typedef enum 
{MODE_EXPOSUREPRIT_LOWNOISE = 0,                       //������
 MODE_EXPOSUREPRIT_FPS      = 1                        //�̶�֡��
 }ENU_EXPOSUREPRITMODE;                                //�ع����ȷ�ʽ

typedef enum 
{MODE_EXPOSURE_AUTO         = 0,
 MODE_EXPOSURE_MANUAL       = 1
}ENU_EXPOSUREMODE;                                     //�ع�ģʽ

typedef enum 
{ WHITEBALANCE_MODE_AUTO    = 0,
  WHITEBALANCE_MODE_MANUAL  = 1
}ENU_WHITEBALANCEMODE;                                 //��ƽ��ģʽ

typedef enum 
{IRCUT_MODE_ON              = 0,
 IRCUT_MODE_OFF             = 1,
 IRCUT_MODE_AUTO            = 2,
}ENU_IRCUTMODE;                                        //IR CUT ģʽ




typedef struct tagOPTIONSEXPOSURE
{
	INT                      ExpoModeSize;	    
	ENU_EXPOSUREMODE         ExpoModes[5];	           //�ع�ģʽ
	INT                      ExpoPriSize;	
	ENU_EXPOSUREPRITMODE     ExpoPris[5];              //�ع�����ģʽ
    FLOATRANGE               ExpoMinTime;	           //�ع�ʱ��
	FLOATRANGE               ExpoMaxTime;	
	FLOATRANGE               ExpoMinGain;	           //����
	FLOATRANGE               ExpoMaxGain;	
	FLOATRANGE               ExpoMinIris;	           //��Ȧ
	FLOATRANGE               ExpoMaxIris;	
	FLOATRANGE               ExpoTime;	 
	FLOATRANGE               ExpoGain;	
	FLOATRANGE               ExpoIris;	
}OPTIONSEXPOSURE;
typedef struct tagOPTIONSFOCUS                          //�۽�����
{
    INT                      FocusModeSize;	
	ENU_AUTOFOCUSMODE        FocusModes[5];	            //�۽�ģʽ
	FLOATRANGE               FocusDefaultSpeed;
	FLOATRANGE               FocusNearLimit;	
	FLOATRANGE               FocusFarLimit;	
}OPTIONSFOCUS;
typedef struct tagOPTIONSWIDEDYNAMIC
{
	INT                      wdModeSize;
	ENU_WIDEDYNAMICMODE      wdModes[5];
	FLOATRANGE               wdLevel;	
}OPTIONSWIDEDYNAMIC;
typedef struct tagOPTIONSWHITEBALANCE
{
	INT                      wbModeSize;	
	ENU_WHITEBALANCEMODE     wbModes[5];	
	FLOATRANGE               wbYrGain;	                  //��������
	FLOATRANGE               wbYbGain;	                  //ɫ������
}OPTIONSWHITEBALANCE;
typedef struct tagOPTIONSIMAGINGS
{
    //���¶���Ϊ��Χģʽ�������û��ȡ�����豸���ʱʹ�õ�λ��
    FLOATRANGE               ImgBrightnessRange;          //����
    FLOATRANGE               ImgColorSaturationRange;     //ɫ��
    FLOATRANGE               ImgContrastRange;            //�Աȶ�
	FLOATRANGE               ImgSharpness;	              //���

	INT                      IrCutModeSize;
	ENU_IRCUTMODE            IrCutFilterModes[5];          //���úͶ�ȡʱʹ�����λ��
    //����CCD/CMOS/��ͷ������û��ʹ�ã��˴����屣��   
    INT                      BacklightCompSize;
    ENU_BACKLIGHTCOMPMODE    BacklightCompMode[5];
    FLOATRANGE               BacklightCompRange;           //���ⲹ��
    OPTIONSEXPOSURE          OptionsExposure;              //����
	OPTIONSFOCUS             OptionsFocus;	               //�۽�
	OPTIONSWIDEDYNAMIC       OptionsWideDynamic;	       //��̬
	OPTIONSWHITEBALANCE      OptionsWhiteBalance;	       //��ƽ��
}OPTIONSIMAGINGS,*LPOPTIONSIMAGINGS;

typedef struct tagOPTIONSFOCUSMOV
{
    FLOATRANGE               AbsolutePosition;	
	FLOATRANGE               AbsoluteSpeed;	

	FLOATRANGE               RelativeDistance;	
	FLOATRANGE               RelativeSpeed;	

	FLOATRANGE               ContinuousSpeed;

}OPTIONSFOCUSMOV,*LPOPTIONSFOCUSMOV;
typedef struct tagFOCUSMOVSTATUS
{
	FLOAT                    FocusPosition;
	ENU_FOCUSMOVSTATUS       FocusMoveStatus;
	CHAR                     FocusError;	
}FOCUSMOVSTATUS,*LPFOCUSMOVSTATUS;
//�ص��ӿ�
typedef struct  tagCALLBACKIMAGING
{   //ͼ��.ͼ�����ʺʹ���������
	void (*SetIcut)                     (int mode);
	BOOL  (*ImgGetOptions)             (CHAR *VideoSourceToken,LPOPTIONSIMAGINGS lpOptionsImagings);
    BOOL  (*ImgGetSetting)             (CHAR *VideoSourceToken,LPOPTIONSIMAGINGS lpImgSetting);                        //ʹ����������ṹ��mix �ֶ�
    BOOL  (*ImgSetSetting)             (CHAR *VideoSourceToken,LPOPTIONSIMAGINGS   ImgSetting,BOOL isFoce2Persistence);//ʹ����������ṹ��mix �ֶ�
    //ͼ��.��ͷ�۽�(IPCAM�����Դ���ͷ���ƣ����¶��屣��)
    BOOL  (*MovFocusGetOptions)        (CHAR *VideoSourceToken,LPOPTIONSFOCUSMOV lpFocusMovOptions);                   //ʹ����������ṹ��mix �ֶ�
    BOOL  (*MovFocusMove)              (CHAR *VideoSourceToken,LPOPTIONSFOCUSMOV   FocusMovOptions);                   //ʹ����������ṹ��mix �ֶ�
    BOOL  (*MovFocusStop)              (CHAR *VideoSourceToken);
    BOOL  (*MovFocusGetStatus)         (CHAR *VideoSourceToken, LPFOCUSMOVSTATUS lpFocusMovStatus);
    
}CALLBACKIMAGING,*LPCALLBACKIMAGING;
#endif//OVF_IMAGING_H

