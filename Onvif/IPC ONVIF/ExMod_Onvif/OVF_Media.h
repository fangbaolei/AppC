//OVF_Media.h
/*################################################################################
#Project Description:
#      OVIF Э��SDK
#
# The File Description:
#      OVIF SDK PTZ����
# Note:
#      1.OVIF �����Stream �������ƻ���ʽ��ɾ��������
#      2.Stream ����¿ɹ�Imaging /ptz �Ⱦ��(���ƻ�)��ʵ����PTZ�Ĳ�����͸��Stream����ɡ�
#      3.OVIF ������Timeout ����CHAR*���͵ģ�û����ȷ�������ʽ�淶
#      
#
# Authors:
#       Fifo2005@gmail.com                                       2011.12.30 First
#       
#Copyright:
#       Copyright(c) 2008~2001x 
#  	    Fifo2005@gmail.com All rights reserved.
###############################################################################*/
#ifndef OVF_MEDIA_H
#define OVF_MEDIA_H
typedef enum                                            //OVIFЭ������֧�ֵ���Ƶ����
{ 
    AUDIOENC_G711        = 0,
    AUDIOENC_G726        = 1,
    AUDIOENC_AAC         = 2
}ENU_AUDIOENCTYPE;
typedef enum                                            //OVIFЭ������֧�ֵ���Ƶ����
{
    VIDEOENC_JPEG        = 0, 
    VIDEOENC_MPEG4       = 1,
    VIDEOENC_H264        = 2,
 }ENU_VIDEOENCTYPE;

typedef enum 
{
    MP4PROFILE_SP        = 0,
    MP4PROFILE_ASP       = 1
}ENU_MP4PROFILE;

typedef enum 
{
    H264PROFILE_BASELINE = 0,
    H264PROFILE_MAIN     = 1,
    H264PROFILE_EXTENDED = 2,
    H264PROFILE_HIGH     = 3,
}ENU_H264PROFILE;

typedef struct tagAUDIOSOURCE                            //��Ƶ����Դ,����ڵ�
{
	CHAR            AudioToken[OVFCHARLENTH];            //����
    INT             Channels;	                         //������
}AUDIONODE,*LPAUDIONODE;                          
typedef struct tagAUDIOSOURCES                           //��Ƶ����Դ��
{
    INT             AudioNodeSize;
    AUDIONODE       AudioNodes[16];                      //��ඨ��16����������ͨ��
}AUDIONODES,*LPAUDIONODES;   
typedef struct tagAUDIOCONFIG
{
	CHAR           ConfigName[OVFCHARLENTH];
	INT            ConfigUseCount;	
	CHAR           ConfigToken[OVFCHARLENTH];	
	CHAR           AudioNodeToken[OVFCHARLENTH];
	BOOL           ForcePersistence;                     //����Ĭ��
    //�������
    CHAR           AudioOutputSendPrimacy[OVFCHARLENTH]; //���ģʽ:ȫ���빤ģʽ����ΪURL (OVIF �ĵ���������������ʽ��������ĵ��޷���)
    INT            AudioOutputLevel;                     //�������
}AUDIOCONFIG,*LPAUDIOCONFIG;
typedef struct tagAUDIOCONFIGS
{
    INT               ConfigSize;
    AUDIOCONFIG       Configs[16];
}AUDIOCONFIGS,*LPAUDIOCONFIGS;
typedef struct tagAUDIOSOURCECONFIGOPTIONS
{
	INT              AudioNodeTokensAvailableSize;	
	CHAR             AudioNodeTokensAvailable[16][OVFCHARLENTH];	
    //�������
    INT              OutputSendPrimacyOptionsSize;	
	CHAR             OutputSendPrimacyOptions[16][OVFCHARLENTH];
	INTRANGE         OutputLevelRange;	
 }AUDIOCONFIGOPTIONS,*LPAUDIOCONFIGOPTIONS;
typedef struct tagMULTICASTCONFIG
{
	IPV4ADDRESS           Address;
	INT                   Port;
	INT                   TTL;	
	BOOL                  AutoStart;	                  //�����Զ�
}MUTICASTCONFIG;
typedef struct tagAUDIOCODINGCONFIG
{
	CHAR                  ConfigName[OVFCHARLENTH];
	INT                   ConfigUseCount;
	CHAR                  Configtoken[OVFCHARLENTH];	
    //���¶�����Ա����
	ENU_AUDIOENCTYPE      AudioEncType;	
	INT                   AudioEncBitrate;	
	INT                   AudioEncSampleRate;	
	MUTICASTCONFIG        Multicast;	
	CHAR                  RTSPSessionTimeout[OVFCHARLENTH];	
    //���¶����������
    BOOL                  ForcePersistence;
}AUDIOCODINGCONFIG,*LPAUDIOCODINGCONFIG;
typedef struct tagAUDIOCODINGCONFIGS
{
    INT                   ConfigSize;
    AUDIOCODINGCONFIG     ConfigEncs[16];
}AUDIOCODINGCONFIGS,*LPAUDIOCODINGCONFIGS;
typedef struct tagAUDIOENCCONFIGOPTION
{
	ENU_AUDIOENCTYPE       EncType;	
	INTLIST                EncBitrateList;
	INTLIST                EncSampleRateList;	
}AUDIOENCCONFIGOPTION,*LPAUDIOENCCONFIGOPTION;
typedef struct tagAUDIOENCCONFIGOPTIONS
{
    INT                    AudioEncConfigOptionSize;
    AUDIOENCCONFIGOPTION   AudioEncConfigOption[OVFMAXCHANNEL];
}AUDIOENCCONFIGOPTIONS,*LPAUDIOENCCONFIGOPTIONS;
typedef struct tagAUDIODECOPTON
{
	INTLIST                DecOptionBitrate;	
	INTLIST                DecOptonSampleRateRange;	
}AUDIODECOPTION;
typedef struct tagAUDIODECCONFIGOPTION
{
    AUDIODECOPTION         AACDecOptions;	
	AUDIODECOPTION         G711DecOptions;	
	AUDIODECOPTION         G726DecOptions;	   
}AUDIODECCONFIGOPTION,*LPAUDIODECCONFIGOPTON;
typedef struct tagAUDIODECCONFIGOPTIONS
{
    INT                     AudioDecConfigOptionSize;
    AUDIODECCONFIGOPTION    AudioDecConfigOptions[OVFMAXCHANNEL];
}AUDIODECCONFIGOPTIONS,*LPAUDIODECCONFIGOPTIONS;
//��Ƶ�ṹ
typedef struct tagRESOLUTION
{
	INT                      Width;	
	INT                      Height;
}RESOLUTION;
typedef struct tagVIDEOSOURCE
{
	CHAR                     VideoToken[OVFCHARLENTH];	
	FLOAT                    VideoSourceFramerate;	
	RESOLUTION               VideoSourceResolution;	
	/////ԭONVIF������ͼ�񼰴�������������IMGING�������ж��弰API���˴�ʡ��	
}VIDEOESOURCE,*LPVIDEOSOURCE;
typedef struct tagVIDEOSOURCES
{
    INT                      VideoSourceSize;
    VIDEOESOURCE             VideoSources[OVFMAXCHANNEL];
}VIDEOSOURCES,*LPVIDEOSOURCES;
typedef struct tagVIDEOSOURCECONFIG
{
	CHAR                     ConfigName[OVFCHARLENTH];	
	INT                      ConfigUseCount;	
	CHAR                     ConfigToken[OVFCHARLENTH];	
	CHAR                     SourceToken[OVFCHARLENTH];	
    INTRECT                  SourceBounds;	
	//������ʱʹ��
	INT                      ForcePersistence;
}VIDEOSOURCECONFIG,*LPVIDEOSOURCECONFIG;
typedef struct tagVIDEOSOURCECONFIGS
{
    INT                      ConfigSize;
    VIDEOSOURCECONFIG        VideoSourceConfigs[OVFCHARLENTH];
}VIDEOSOURCECONFIGS,*LPVIDEOSOURCECONFIGS;
typedef struct tagVIDEOSOURCECONFIGOPTIONS
{
	INTRECTRANGE             BoundsRange;	
	INT                      VideoSourceTokenSize;	
	CHAR                     VideoSourceTokens[OVFMAXCHANNEL][OVFCHARLENTH];	
}VIDEOSOURCECONFIGOPTIONS,*LPVIDEOSOURCECONFIGOPTIONS;


typedef struct tagVIDEORATECONTROL
{
	INT                      FrameRateLimit;	
	INT                      EncodingInterval;	
	INT                      BitrateLimit;	
}VIDEORATECONTROL;

typedef struct tagMP4CONFIG
{
	INT                      GovLength;	
	ENU_MP4PROFILE           Mpeg4Profile;	
}MP4CONFIG;

typedef struct tagAVSCONFIG
{
	INT                      GovLength;	
	ENU_H264PROFILE          H264Profile;	
}AVSCONFIG;
typedef struct tagVIDEOENCCONFIG
{
	CHAR                     ConfigName[OVFCHARLENTH];
	INT                      ConfigUseCount;	
	CHAR                     ConfigToken[OVFCHARLENTH];
	ENU_VIDEOENCTYPE         EncType;	
	RESOLUTION               EncResolution;
	FLOAT                    EncQuality;	
	VIDEORATECONTROL         RateControl;	
	MP4CONFIG                ConfigMPEG4;	
	AVSCONFIG                ConfigH264;	
	MUTICASTCONFIG           Multicast;	
	CHAR                     RtspSessionTimeout[OVFCHARLENTH];
	//������
	BOOL                     ForcePersistence;
}VIDEOENCCONFIG,*LPVIDEOENCCONFIG;
typedef struct tagVIDEOENCCONFIGS            //��Ƶ.����.����
{
    INT                      VideoEncConfigSize;
    VIDEOENCCONFIG           VideoEncConfigs[OVFCHARLENTH];
}VIDEOENCCONFIGS,*LPVIDEOENCCONFIGS;  
typedef struct tagJPEGOPTIONS
{
	INT                      ResolutionsAvailableSize;
	RESOLUTION               ResolutionsAvailable[OVFMAXCHANNEL];
	INTRANGE                 FrameRateRange;	
	INTRANGE                 EncodingIntervalRange;
}JPEGOPTIONS;
typedef struct tagMP4OPTIONS
{
	INT                      ResolutionsAvailableSize;	
	RESOLUTION               ResolutionsAvailables[OVFMAXCHANNEL];
	INTRANGE                 GovLengthRange;
	INTRANGE                 FrameRateRange;
	INTRANGE                 EncodingIntervalRange;
	INT                      Mpeg4ProfilesSupportedSize;
	ENU_MP4PROFILE           Mpeg4ProfilesSupported[OVFMAXCHANNEL];	
}MP4OPTIONS;
typedef struct tagAVSOPTIONS
{
	INT                      ResolutionsAvailableSize;	
	RESOLUTION               ResolutionsAvailables[OVFMAXCHANNEL];
	INTRANGE                 GovLengthRange;
	INTRANGE                 FrameRateRange;
	INTRANGE                 EncodingIntervalRange;
	INT                      AVSProfilesSupportedSize;
	ENU_H264PROFILE          AVSProfilesSupporteds[OVFMAXCHANNEL];
}AVSOPTIONS;
typedef struct tagVIDEOENCCONFIGOPTIONS
{
	INTRANGE                 EncQualityRange;
	JPEGOPTIONS              EncJpegOptions;
	MP4OPTIONS               EncMP4Options;	
	AVSOPTIONS               EncAVSOptions;
}VIDEOENCCONFIGOPTONS,*LPVIDEOENCCONFIGOPTIONS;
typedef struct tagMEDIAURL
{
	CHAR                     MediaUri[OVFCHARLENTH];	
	BOOL                     InvalidAfterConnect;	
	BOOL                     InvalidAfterReboot;	
	CHAR                     Timeout[OVFCHARLENTH];	
}MEDIAURL,*LPMEDIAURL;
//PROFILE ���
typedef struct tagMEDIAPROFILE
{
	CHAR                      Name[OVFCHARLENTH];	
	CHAR                      token[OVFCHARLENTH]; 
	BOOL                      fixed; 
    //����ΪΪ����ģ������ṹ��OVIF����ϸ��������ṹ��
    //�����ṹ�Ѷ������API�����������������������
    CHAR                      VideoSourceConfigToken[OVFCHARLENTH];
    CHAR                      VideoEncodeConfigToken[OVFCHARLENTH];
    CHAR                      AudioSourceConfigToken[OVFCHARLENTH];
    CHAR                      AudioEncodeConfigToken[OVFCHARLENTH];
    CHAR                      PtzConfigToken[OVFCHARLENTH];
   
}MEDIAPROFILE,*LPMEDIAPROFILE;
typedef struct tagMEDIAPROFILES
{
    INT                       ProfileSize;
    MEDIAPROFILE              ProFiles[OVFMAXCHANNEL];
}MEDIAPROFILES,*LPMEDIAPROFILES;
typedef struct tagMEDIAPROFILECAP
{
    INT                       MaxProfiles;
    BOOL                      RTPMulticast;	            //RTP�ಥ:FALSE
	BOOL                      RTP_USCORETCP;	        //RTP TCP����:TRUE
	BOOL                      RTP_USCORERTSP_USCORETCP;	//֧��RTP/RTSP/TCP:TRUE
	BOOL                      NonAggregateControl;	    //������ָ��������:TRUE
}MEDIAPROFILECAP,*LPMEDIAPROFILECAP;
//�ص��ӿ�
typedef struct  tagCALLBACKMEDIA
{   //ý��.profile
    BOOL  (*GetProfileCap)                 (LPMEDIAPROFILECAP lpMediaProfileCap);
	BOOL  (*GetProfiles)                   (LPMEDIAPROFILES lpMediaProfiles);
    BOOL  (*GetProfile)                    (CHAR *MediaProfileToken,LPMEDIAPROFILE lpMediaProfile);  
	BOOL  (*CreateProfile)                 (LPMEDIAPROFILE   MediaProfile);
	BOOL  (*DelProfile)                    (LPMEDIAPROFILE   MediaProfile);
    //ý��.��Ƶ.����.�豸
    BOOL  (*GetAudioSources)               (LPAUDIONODES   lpAudioSources);
    BOOL  (*GetAudioSourceConfigs)         (LPAUDIOCONFIGS lpAudioSourceConfigs);
    BOOL  (*GetAudioSourceConfigOptions)   (CHAR *ConfigAudioSourceToken,CHAR *MediaProfileToken,LPAUDIOCONFIGOPTIONS lpAudioSourceConfigOptions);
    BOOL  (*GetAudioSourceConfig)          (CHAR *ConfigAudioSourceToken,LPAUDIOCONFIG lpAudioSourceConfig);
    BOOL  (*SetAudioSourceConfig)          (CHAR *ConfigAudioSourceToken,LPAUDIOCONFIG   AudioSourceConfig);
    //ý��.��Ƶ.���.�豸
    BOOL  (*GetAudioOutputs)               (LPAUDIONODES   lpAudioOutput);
    BOOL  (*GetAudioOutputConfigs)         (LPAUDIOCONFIGS lpAudioOutputs);
    BOOL  (*GetAudioOutputConfigOptions)   (CHAR *ConfigAudioOutputToken,CHAR *MediaProfileToken,LPAUDIOCONFIGOPTIONS lpAudioSourceConfigOptions);
    BOOL  (*GetAudioOutputConfig)          (CHAR *ConfigAudioOutputToken,LPAUDIOCONFIG lpAudioOutputConfig);
    BOOL  (*SetAudioOutputConfig)          (CHAR *ConfigAudioOutputToken,LPAUDIOCONFIG   AudioOutputConfig);  
    //ý��.��Ƶ.����.����
    BOOL  (*GetAudioEncConfigs)            (LPAUDIOCODINGCONFIGS lpAudioCodingConfigs);
    BOOL  (*GetAudioEncConfigOptions)      (CHAR *ConfigAudioEncToken,CHAR *MediaProfileToken,LPAUDIOENCCONFIGOPTIONS lpAudioEncConfigOptons);
    BOOL  (*GetAudioEncConfig)             (CHAR *ConfigAudioEncToken,LPAUDIOCODINGCONFIG lpAudioCodingConfig);
    BOOL  (*SetAudioEncConfig)             (CHAR *ConfigAudioEncToken,LPAUDIOCODINGCONFIG   AudioCodingConfig);
    //ý��.��Ƶ.���.����
    BOOL  (*GetAudioDecConfigs)            (LPAUDIOCODINGCONFIGS lpAudioCodingConfigs);
    BOOL  (*GetAudioDecConfigsOptions)     (CHAR *ConfigAudioDecToken,CHAR *MediaProfileToken,LPAUDIODECCONFIGOPTON lpAudioDecConfigOption);
    BOOL  (*GetAudioDecConfig)             (CHAR *ConfigAudioDecToken,LPAUDIOCODINGCONFIG lpAudioCodingConfig);
    BOOL  (*SetAudioDecConfig)             (CHAR *ConfigAudioDecToken,LPAUDIOCODINGCONFIG   AudioCodingConfig);
    //ý��.��Ƶ.����.�豸
    BOOL  (*GetVideoSources)               (LPVIDEOSOURCES  lpVideoSources);
    BOOL  (*GetVideoSourceConfigs)         (LPVIDEOSOURCECONFIGS lpVideoSourcesConfigs);
    BOOL  (*GetVideoSourceConfigOptions)   (CHAR *ConfigVideoSourceToken,CHAR *MediaProfileToken,LPVIDEOSOURCECONFIGOPTIONS lpVideoSourceConfigOptions);
    BOOL  (*GetVideoSourceConfig)          (CHAR *ConfigVideoSourceToken,LPVIDEOSOURCECONFIG lpVideoSourceConfig);
    BOOL  (*SetVideoSourceConfig)          (CHAR *ConfigVideoSourceToken,LPVIDEOSOURCECONFIG   VideoSOurceConfig);
    //ý��.��Ƶ.����.����
    BOOL  (*GetVideoEncConfigs)            (LPVIDEOENCCONFIGS lpVideoEncConfigs);
    BOOL  (*GetVideoEncConfigOptions)      (CHAR *ConfigVideoEncToken,CHAR *MediaProfileToken,LPVIDEOENCCONFIGOPTIONS lpVideoEncConfigOptions);
    BOOL  (*GetVideoEncConfig)             (CHAR *ConfigVideoEncToken,LPVIDEOENCCONFIG lpVideoEncConfig);
    BOOL  (*SetVideoEncConfig)             (CHAR *ConfigVideoEncToken,LPVIDEOENCCONFIG   VideoEncConfig);
    //ý��.������̨
    BOOL  (*TachPtz)                       (CHAR *MediaProfileToken,CHAR *PtzConfigToken);
    BOOL  (*UnTachPtz)                     (CHAR *MediaProfileToken);
    //ý��.��
    BOOL  (*GetStreamURL)                  (CHAR *MediaProfileToken,LPMEDIAURL lpMediaURL);
    BOOL  (*GetSnapshotURL)                (CHAR *MediaProfileToken,LPMEDIAURL lpMediaURL);
    BOOL  (*MulticastStreamingStart)       (CHAR *MediaProfileToken);
    BOOL  (*MulticastStreamingStop)        (CHAR *MediaProfileToken);
    BOOL  (*SetSynchronizationPoint)       (CHAR *MediaProfileToken);      
    //ý��.��Ƶ�����������Ƶ��������������� (����)
    //ý��.��Ƶ�����ӿ�                       (����)
    //ý��.��Ƶ����ƵԪ���ݽӿ�               (����)
}CALLBACKMEDIA,*LPCALLBACKMEDIA;
#endif//OVF_MEDIA_H

