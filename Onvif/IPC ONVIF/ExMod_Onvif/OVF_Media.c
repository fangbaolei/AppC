#include "stdsoap2.h"
#include "soapH.h"
#include "soapStub.h"
#include "OVF_Export.h"
#include "OVF_Core.h"
#include "OVF_Media.h"
#include "OVF_Ptz.h"
//Stream Profile
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetServiceCapabilities(struct soap* hSoap, struct _trt__GetServiceCapabilities *trt__GetServiceCapabilities, struct _trt__GetServiceCapabilitiesResponse *trt__GetServiceCapabilitiesResponse)
{
    NEW(Resp,struct trt__Capabilities );
 	NEW(ProfileCap,struct trt__ProfileCapabilities); 
	NEW(StreamCap ,struct trt__StreamingCapabilities);	 
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    NEW(Cap,MEDIAPROFILECAP);

    Resp->ProfileCapabilities = ProfileCap;
	Resp->StreamingCapabilities= StreamCap;
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,GetProfileCap);
    if(FALSE==Onvif->CallBackOvf->CallBackMedia->GetProfileCap(Cap))return SOAP_FAULT;   
	Resp->ProfileCapabilities->MaximumNumberOfProfiles = &Cap->MaxProfiles;
	Resp->StreamingCapabilities->RTPMulticast          = &Cap->RTPMulticast;
	Resp->StreamingCapabilities->RTP_USCORETCP         = &Cap->RTP_USCORETCP;
	Resp->StreamingCapabilities->RTP_USCORERTSP_USCORETCP= &Cap->RTP_USCORERTSP_USCORETCP;
	Resp->StreamingCapabilities->NonAggregateControl   = &Cap->NonAggregateControl;
    return SOAP_OK;
 }
SOAP_FMAC5 int SOAP_FMAC6 __trt__CreateProfile(struct soap* hSoap, struct _trt__CreateProfile *trt__CreateProfile, struct _trt__CreateProfileResponse *trt__CreateProfileResponse)
{ //不用支持
	NEWMIII(trt__CreateProfileResponse->Profile , struct tt__Profile,1);
	if(NULL != trt__CreateProfile){
		trt__CreateProfileResponse->Profile->Name = trt__CreateProfile->Name;
		trt__CreateProfileResponse->Profile->token = trt__CreateProfile->Name;
	}

    return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __trt__DeleteProfile(struct soap* hSoap, struct _trt__DeleteProfile *trt__DeleteProfile, struct _trt__DeleteProfileResponse *trt__DeleteProfileResponse)
{   //不用支持
    return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetProfiles(struct soap* hSoap, struct _trt__GetProfiles *trt__GetProfiles, struct _trt__GetProfilesResponse *trt__GetProfilesResponse)
{
	printf("[__trt__GetProfiles].........................................................................................\n");
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    NEW(Profiles,MEDIAPROFILES);
	NEW(VideoConfigs,VIDEOSOURCECONFIGS);
	NEW(AudioConfigs,AUDIOCONFIGS);
	NEW(VideoEnConfigs,VIDEOENCCONFIGS);
	NEW(AudioEnConfigs,AUDIOCODINGCONFIGS);
	NEW(ptz,PTZCONFIGS);
    INT     i;
    NEWMII(Resp,struct tt__Profile,OVFMAXCHANNEL);
	for(i=0;i<OVFMAXCHANNEL;i++){
		NEWMIII(Resp[i].VideoSourceConfiguration,struct tt__VideoSourceConfiguration,1);
		NEWMIII(Resp[i].VideoSourceConfiguration->Bounds,struct tt__IntRectangle,1);
		NEWMIII(Resp[i].AudioSourceConfiguration,struct tt__AudioSourceConfiguration,1);
		
		NEWMIII(Resp[i].VideoEncoderConfiguration,struct tt__VideoEncoderConfiguration,1);
		NEWMIII(Resp[i].VideoEncoderConfiguration->Resolution,struct tt__VideoResolution,1);
		NEWMIII(Resp[i].VideoEncoderConfiguration->Multicast,struct tt__MulticastConfiguration,1);
		NEWMIII(Resp[i].VideoEncoderConfiguration->Multicast->Address,struct tt__IPAddress,1);
		NEWMIII(Resp[i].VideoEncoderConfiguration->RateControl,struct tt__VideoRateControl,1);
		NEWMIII(Resp[i].VideoEncoderConfiguration->H264,struct tt__H264Configuration,1);

		NEWMIII(Resp[i].AudioEncoderConfiguration,struct tt__AudioEncoderConfiguration,1);
		NEWMIII(Resp[i].AudioEncoderConfiguration->Multicast,struct tt__MulticastConfiguration,1);
		NEWMIII(Resp[i].AudioEncoderConfiguration->Multicast->Address,struct tt__IPAddress,1);
		
		NEWMIII(Resp[i].PTZConfiguration,struct tt__PTZConfiguration,1);
		NEWMIII(Resp[i].PTZConfiguration->DefaultPTZSpeed,struct tt__PTZSpeed,1);
		NEWMIII(Resp[i].PTZConfiguration->DefaultPTZSpeed->PanTilt,struct tt__Vector2D,1);
		NEWMIII(Resp[i].PTZConfiguration->DefaultPTZSpeed->Zoom,struct tt__Vector1D,1);

		NEWMIII(Resp[i].PTZConfiguration->PanTiltLimits,struct tt__PanTiltLimits,1);
		NEWMIII(Resp[i].PTZConfiguration->PanTiltLimits->Range ,struct tt__Space2DDescription,1);
		NEWMIII(Resp[i].PTZConfiguration->ZoomLimits,struct tt__ZoomLimits,1);
		NEWMIII(Resp[i].PTZConfiguration->ZoomLimits->Range,struct tt__Space1DDescription,1);
	
	}

    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,GetVideoSourceConfigs);
	 if (FALSE==Onvif->CallBackOvf->CallBackMedia->GetVideoSourceConfigs(VideoConfigs))return SOAP_FAULT;

	 CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,GetVideoEncConfigs);
	 if (FALSE==Onvif->CallBackOvf->CallBackMedia->GetVideoEncConfigs(VideoEnConfigs))return SOAP_FAULT;

	 CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,GetAudioSourceConfigs);
	 if (FALSE==Onvif->CallBackOvf->CallBackMedia->GetAudioSourceConfigs(AudioConfigs))return SOAP_FAULT;
	 
	 CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,GetAudioEncConfigs);
	 if (FALSE==Onvif->CallBackOvf->CallBackMedia->GetAudioEncConfigs(AudioEnConfigs))return SOAP_FAULT;
	 
	 CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackPtz,PtzGetConfigs);
    if(FALSE==Onvif->CallBackOvf->CallBackPtz->PtzGetConfigs(ptz))return SOAP_FAULT;    

	CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,GetProfiles);
     if(FALSE==Onvif->CallBackOvf->CallBackMedia->GetProfiles(Profiles))return SOAP_FAULT; 

	  for(i=0;i<OVFMAXCHANNEL&&i<Profiles->ProfileSize;i++){
	  static int j=0;
	//  printf("=====================================%d=================\n",j);
	  j++;
		Resp[i].Name        = Profiles->ProFiles[i].Name;
		Resp[i].token       = Profiles->ProFiles[i].token;
		Resp[i].fixed       =&Profiles->ProFiles[i].fixed;

  	Resp[i].VideoSourceConfiguration->token	         = VideoConfigs->VideoSourceConfigs[0].ConfigToken;	
		Resp[i].VideoSourceConfiguration->Name		     = VideoConfigs->VideoSourceConfigs[0].ConfigName;
		Resp[i].VideoSourceConfiguration->UseCount	     = VideoConfigs->VideoSourceConfigs[0].ConfigUseCount;
		Resp[i].VideoSourceConfiguration->SourceToken    = VideoConfigs->VideoSourceConfigs[0].SourceToken;
		Resp[i].VideoSourceConfiguration->Bounds->height = VideoConfigs->VideoSourceConfigs[0].SourceBounds.height;
		Resp[i].VideoSourceConfiguration->Bounds->width  = VideoConfigs->VideoSourceConfigs[0].SourceBounds.width;
		Resp[i].VideoSourceConfiguration->Bounds->x      = VideoConfigs->VideoSourceConfigs[0].SourceBounds.x;
		Resp[i].VideoSourceConfiguration->Bounds->y      = VideoConfigs->VideoSourceConfigs[0].SourceBounds.y;
	
		Resp[i].AudioSourceConfiguration->token		     = AudioConfigs->Configs[0].ConfigToken;	
		Resp[i].AudioSourceConfiguration->Name		     = AudioConfigs->Configs[0].ConfigName;
		Resp[i].AudioSourceConfiguration->UseCount		 = AudioConfigs->Configs[0].ConfigUseCount;
		Resp[i].AudioSourceConfiguration->SourceToken    = AudioConfigs->Configs[0].AudioNodeToken;
	
		Resp[i].VideoEncoderConfiguration->token	     = VideoEnConfigs->VideoEncConfigs[i].ConfigToken;
		Resp[i].VideoEncoderConfiguration->Name			 = VideoEnConfigs->VideoEncConfigs[i].ConfigName;
		Resp[i].VideoEncoderConfiguration->UseCount      = VideoEnConfigs->VideoEncConfigs[i].ConfigUseCount;
		Resp[i].VideoEncoderConfiguration->Encoding      = VideoEnConfigs->VideoEncConfigs[i].EncType;
		Resp[i].VideoEncoderConfiguration->Quality       = VideoEnConfigs->VideoEncConfigs[i].EncQuality;
		Resp[i].VideoEncoderConfiguration->RateControl->BitrateLimit		= VideoEnConfigs->VideoEncConfigs[i].RateControl.BitrateLimit;
		Resp[i].VideoEncoderConfiguration->RateControl->EncodingInterval	= VideoEnConfigs->VideoEncConfigs[i].RateControl.EncodingInterval;
		Resp[i].VideoEncoderConfiguration->RateControl->FrameRateLimit		= VideoEnConfigs->VideoEncConfigs[i].RateControl.FrameRateLimit;
		Resp[i].VideoEncoderConfiguration->SessionTimeout					= VideoEnConfigs->VideoEncConfigs[i].RtspSessionTimeout;
		Resp[i].VideoEncoderConfiguration->Resolution->Height				= VideoEnConfigs->VideoEncConfigs[i].EncResolution.Height;
		Resp[i].VideoEncoderConfiguration->Resolution->Width				= VideoEnConfigs->VideoEncConfigs[i].EncResolution.Width;
		Resp[i].VideoEncoderConfiguration->H264->GovLength					= VideoEnConfigs->VideoEncConfigs[i].ConfigH264.GovLength;
		Resp[i].VideoEncoderConfiguration->H264->H264Profile				= VideoEnConfigs->VideoEncConfigs[i].ConfigH264.H264Profile;


		Resp[i].VideoEncoderConfiguration->Multicast->AutoStart				= VideoEnConfigs->VideoEncConfigs[i].Multicast.AutoStart;
		Resp[i].VideoEncoderConfiguration->Multicast->TTL					= VideoEnConfigs->VideoEncConfigs[i].Multicast.TTL;
		Resp[i].VideoEncoderConfiguration->Multicast->Address->Type			= 0;

		Resp[i].AudioEncoderConfiguration->token	     = AudioEnConfigs->ConfigEncs[0].Configtoken;
		Resp[i].AudioEncoderConfiguration->UseCount      = AudioEnConfigs->ConfigEncs[0].ConfigUseCount;
		Resp[i].AudioEncoderConfiguration->Name          = AudioEnConfigs->ConfigEncs[0].ConfigName;
		Resp[i].AudioEncoderConfiguration->SessionTimeout= AudioEnConfigs->ConfigEncs[0].RTSPSessionTimeout;
		Resp[i].AudioEncoderConfiguration->Multicast->AutoStart		    =AudioEnConfigs->ConfigEncs[0].Multicast.AutoStart;
		Resp[i].AudioEncoderConfiguration->Multicast->TTL				=AudioEnConfigs->ConfigEncs[0].Multicast.TTL;
		Resp[i].AudioEncoderConfiguration->Multicast->Address->Type     =0;

		Resp[i].PTZConfiguration         ->token	     = ptz->PtzCfgs[0].PtzCfgToken;
		Resp[i].PTZConfiguration         ->Name          = ptz->PtzCfgs[0].PtzCfgName;
		Resp[i].PTZConfiguration         ->NodeToken     = ptz->PtzCfgs[0].PtzCfgNodeToken;
		Resp[i].PTZConfiguration		 ->UseCount      = ptz->PtzCfgs[0].PtzCfgUseCount;
		Resp[i].PTZConfiguration->DefaultPTZTimeout		 = ptz->PtzCfgs[0].DefPTZTimeout;
		Resp[i].PTZConfiguration->DefaultAbsolutePantTiltPositionSpace  =ptz->PtzCfgs[0].DefAbsPantTiltPosSpace;
		Resp[i].PTZConfiguration->DefaultAbsoluteZoomPositionSpace      =ptz->PtzCfgs[0].DefAbsZoomPosSpace;
		Resp[i].PTZConfiguration->DefaultRelativePanTiltTranslationSpace=ptz->PtzCfgs[0].DefRelativePanTiltTranslationSpace;
		Resp[i].PTZConfiguration->DefaultRelativeZoomTranslationSpace   =ptz->PtzCfgs[0].DefRelativeZoomTranslationSpace;
		Resp[i].PTZConfiguration->DefaultContinuousPanTiltVelocitySpace =ptz->PtzCfgs[0].DefContinuousPanTiltVelocitySpace;
		Resp[i].PTZConfiguration->DefaultContinuousZoomVelocitySpace	=ptz->PtzCfgs[0].DefContinuousZoomVelocitySpace;

		Resp[i].PTZConfiguration->DefaultPTZSpeed->PanTilt->space       =ptz->PtzCfgs[0].DefPTZSpeed.PanTilt.space;
		Resp[i].PTZConfiguration->DefaultPTZSpeed->PanTilt->x			=ptz->PtzCfgs[0].DefPTZSpeed.PanTilt.x;
		Resp[i].PTZConfiguration->DefaultPTZSpeed->PanTilt->y			=ptz->PtzCfgs[0].DefPTZSpeed.PanTilt.y;
		Resp[i].PTZConfiguration->DefaultPTZSpeed->Zoom->space			=ptz->PtzCfgs[0].DefPTZSpeed.Zoom.space;
		Resp[i].PTZConfiguration->DefaultPTZSpeed->Zoom->x				=ptz->PtzCfgs[0].DefPTZSpeed.Zoom.x;

		Resp[i].PTZConfiguration->PanTiltLimits->Range->URI				=ptz->PtzCfgs[0].LimitsPanTilt.Space2dDespURL;
		Resp[i].PTZConfiguration->PanTiltLimits->Range->XRange			=(struct tt__FloatRange *)&ptz->PtzCfgs[0].LimitsPanTilt.Space2dXRange;
		Resp[i].PTZConfiguration->PanTiltLimits->Range->YRange			=(struct tt__FloatRange *)&ptz->PtzCfgs[0].LimitsPanTilt.Space2dYRange;
		
		Resp[i].PTZConfiguration->ZoomLimits->Range->URI				=ptz->PtzCfgs[0].LimitsZoom.Space1dURI;
		Resp[i].PTZConfiguration->ZoomLimits->Range->XRange				=(struct tt__FloatRange *)&ptz->PtzCfgs[0].LimitsZoom.Space1XRange;
	}
	trt__GetProfilesResponse->__sizeProfiles=Profiles->ProfileSize;
	trt__GetProfilesResponse->Profiles      =Resp;
//	printf("******************************************************GetProfiles end**************************************\n");
    return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetProfile(struct soap* hSoap, struct _trt__GetProfile *trt__GetProfile, struct _trt__GetProfileResponse *trt__GetProfileResponse)
{
	ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
	NEW(Profile,MEDIAPROFILE);
	NEW(VideoConfig,VIDEOSOURCECONFIG);
	NEW(AudioConfig,AUDIOCONFIG);
	NEW(VideoEnConfig,VIDEOENCCONFIG);
	NEW(AudioEnConfig,AUDIOCODINGCONFIG);
	NEW(ptz,PTZCONFIG);
	NEW(Resp,struct tt__Profile);
		NEWMIII(Resp->VideoSourceConfiguration,struct tt__VideoSourceConfiguration,1);
		NEWMIII(Resp->VideoSourceConfiguration->Bounds,struct tt__IntRectangle,1);
		NEWMIII(Resp->AudioSourceConfiguration,struct tt__AudioSourceConfiguration,1);
		NEWMIII(Resp->VideoEncoderConfiguration,struct tt__VideoEncoderConfiguration,1);
		NEWMIII(Resp->VideoEncoderConfiguration->Resolution,struct tt__VideoResolution,1);
		NEWMIII(Resp->VideoEncoderConfiguration->Multicast,struct tt__MulticastConfiguration,1);
		NEWMIII(Resp->VideoEncoderConfiguration->Multicast->Address,struct tt__IPAddress,1);
		NEWMIII(Resp->VideoEncoderConfiguration->RateControl,struct tt__VideoRateControl,1);
		NEWMIII(Resp->VideoEncoderConfiguration->H264,struct tt__H264Configuration,1);
		
		NEWMIII(Resp->AudioEncoderConfiguration,struct tt__AudioEncoderConfiguration,1);
		NEWMIII(Resp->AudioEncoderConfiguration->Multicast,struct tt__MulticastConfiguration,1);
		NEWMIII(Resp->AudioEncoderConfiguration->Multicast->Address,struct tt__IPAddress,1);
	
		NEWMIII(Resp->PTZConfiguration,struct tt__PTZConfiguration,1);
		NEWMIII(Resp->PTZConfiguration->DefaultPTZSpeed,struct tt__PTZSpeed,1);
		NEWMIII(Resp->PTZConfiguration->DefaultPTZSpeed->PanTilt,struct tt__Vector2D,1);
		NEWMIII(Resp->PTZConfiguration->DefaultPTZSpeed->Zoom ,struct tt__Vector1D,1);

     CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,GetProfile);
    if(FALSE==Onvif->CallBackOvf->CallBackMedia->GetProfile(trt__GetProfile->ProfileToken, Profile))return SOAP_FAULT;   

	CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,GetVideoSourceConfig);
	if (FALSE==Onvif->CallBackOvf->CallBackMedia->GetVideoSourceConfig(Profile->VideoSourceConfigToken,VideoConfig))return SOAP_FAULT;
	
	CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,GetVideoEncConfig);
	if (FALSE==Onvif->CallBackOvf->CallBackMedia->GetVideoEncConfig(Profile->VideoEncodeConfigToken,VideoEnConfig))return SOAP_FAULT;

	CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,GetAudioSourceConfig);
	if (FALSE==Onvif->CallBackOvf->CallBackMedia->GetAudioSourceConfig(Profile->AudioSourceConfigToken,AudioConfig))return SOAP_FAULT;
	
	CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,GetAudioEncConfig);
	if (FALSE==Onvif->CallBackOvf->CallBackMedia->GetAudioEncConfig(Profile->AudioEncodeConfigToken,AudioEnConfig))return SOAP_FAULT;

	CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackPtz,PtzGetConfig);
    if(FALSE==Onvif->CallBackOvf->CallBackPtz->PtzGetConfig(Profile->PtzConfigToken, ptz))return SOAP_FAULT;  

		Resp->Name        = Profile->Name;
		Resp->token       = Profile->token;
		Resp->fixed       =&Profile->fixed;

  	Resp->VideoSourceConfiguration ->token		 = VideoConfig->ConfigToken;	
		Resp->VideoSourceConfiguration->Name		     = VideoConfig->ConfigName;
		Resp->VideoSourceConfiguration->UseCount	     = VideoConfig->ConfigUseCount;
		Resp->VideoSourceConfiguration->SourceToken    = VideoConfig->SourceToken;
		Resp->VideoSourceConfiguration->Bounds->height = VideoConfig->SourceBounds.height;
		Resp->VideoSourceConfiguration->Bounds->width  = VideoConfig->SourceBounds.width;
		Resp->VideoSourceConfiguration->Bounds->x      = VideoConfig->SourceBounds.x;
		Resp->VideoSourceConfiguration->Bounds->y      = VideoConfig->SourceBounds.y;

		Resp->VideoEncoderConfiguration->token	     = VideoEnConfig->ConfigToken;
		Resp->VideoEncoderConfiguration->Name			 = VideoEnConfig->ConfigName;
		Resp->VideoEncoderConfiguration->UseCount      = VideoEnConfig->ConfigUseCount;
		Resp->VideoEncoderConfiguration->Encoding      = VideoEnConfig->EncType;
		Resp->VideoEncoderConfiguration->Quality       = VideoEnConfig->EncQuality;
		Resp->VideoEncoderConfiguration->RateControl->BitrateLimit		= VideoEnConfig->RateControl.BitrateLimit;
		Resp->VideoEncoderConfiguration->RateControl->EncodingInterval	= VideoEnConfig->RateControl.EncodingInterval;
		Resp->VideoEncoderConfiguration->RateControl->FrameRateLimit	= VideoEnConfig->RateControl.FrameRateLimit;
		Resp->VideoEncoderConfiguration->SessionTimeout					= VideoEnConfig->RtspSessionTimeout;
		Resp->VideoEncoderConfiguration->Resolution->Height				= VideoEnConfig->EncResolution.Height;
		Resp->VideoEncoderConfiguration->Resolution->Width				= VideoEnConfig->EncResolution.Width;
		Resp->VideoEncoderConfiguration->H264->GovLength				= VideoEnConfig->ConfigH264.GovLength;
		Resp->VideoEncoderConfiguration->H264->H264Profile				= VideoEnConfig->ConfigH264.H264Profile;
		Resp->VideoEncoderConfiguration->Multicast->AutoStart			= VideoEnConfig->Multicast.AutoStart;
		Resp->VideoEncoderConfiguration->Multicast->TTL					= VideoEnConfig->Multicast.TTL;
		Resp->VideoEncoderConfiguration->Multicast->Address->Type			= 0;

		
		Resp->AudioSourceConfiguration->token		     = AudioConfig->ConfigToken;	
		Resp->AudioSourceConfiguration->Name		     = AudioConfig->ConfigName;
		Resp->AudioSourceConfiguration->UseCount		 = AudioConfig->ConfigUseCount;
		Resp->AudioSourceConfiguration->SourceToken      = AudioConfig->AudioNodeToken;

		Resp->AudioEncoderConfiguration->token	     = AudioEnConfig->Configtoken;
		Resp->AudioEncoderConfiguration->UseCount      = AudioEnConfig->ConfigUseCount;
		Resp->AudioEncoderConfiguration->Name          = AudioEnConfig->ConfigName;
		Resp->AudioEncoderConfiguration->SessionTimeout= AudioEnConfig->RTSPSessionTimeout;
		Resp->AudioEncoderConfiguration->Multicast->AutoStart		    =AudioEnConfig->Multicast.AutoStart;
		Resp->AudioEncoderConfiguration->Multicast->TTL				=AudioEnConfig->Multicast.TTL;
		Resp->AudioEncoderConfiguration->Multicast->Address->Type     =0;

		Resp->PTZConfiguration         ->token	       = ptz->PtzCfgToken;
		Resp->PTZConfiguration         ->Name          = ptz->PtzCfgName;
		Resp->PTZConfiguration         ->NodeToken     = ptz->PtzCfgNodeToken;
		Resp->PTZConfiguration->DefaultAbsolutePantTiltPositionSpace  =ptz->DefAbsPantTiltPosSpace;
		Resp->PTZConfiguration->DefaultRelativePanTiltTranslationSpace=ptz->DefRelativePanTiltTranslationSpace;
		Resp->PTZConfiguration->DefaultRelativeZoomTranslationSpace   =ptz->DefRelativeZoomTranslationSpace;
		Resp->PTZConfiguration->DefaultPTZSpeed->PanTilt->space       =ptz->DefPTZSpeed.PanTilt.space;
		Resp->PTZConfiguration->DefaultPTZSpeed->PanTilt->x			  =ptz->DefPTZSpeed.PanTilt.x;
		Resp->PTZConfiguration->DefaultPTZSpeed->PanTilt->y		      =ptz->DefPTZSpeed.PanTilt.y;
		Resp->PTZConfiguration->DefaultPTZSpeed->Zoom->space		  =ptz->DefPTZSpeed.Zoom.space;
		Resp->PTZConfiguration->DefaultPTZSpeed->Zoom->x			  =ptz->DefPTZSpeed.Zoom.x;

	trt__GetProfileResponse->Profile      =Resp;
    return SOAP_OK;
}


///////////////////////////////////////////////////////////
//音频.输入
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioSources(struct soap* hSoap, struct _trt__GetAudioSources *trt__GetAudioSources, struct _trt__GetAudioSourcesResponse *trt__GetAudioSourcesResponse)
{
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    NEW(Nodes,AUDIONODES);
    INT     i;
    NEWMII(Resp,struct tt__AudioSource,OVFMAXCHANNEL);
    
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,GetAudioSources);
    if(FALSE==Onvif->CallBackOvf->CallBackMedia->GetAudioSources(Nodes))return SOAP_FAULT;   
    for(i=0;i<OVFMAXCHANNEL&&i<Nodes->AudioNodeSize;i++){
	Resp[i].token                     = Nodes->AudioNodes[i].AudioToken;
	Resp[i].Channels                  = Nodes->AudioNodes[i].Channels;
    }
    trt__GetAudioSourcesResponse->__sizeAudioSources =Nodes->AudioNodeSize;
    trt__GetAudioSourcesResponse->AudioSources       =Resp;
	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioSourceConfigurations(struct soap* hSoap, struct _trt__GetAudioSourceConfigurations *trt__GetAudioSourceConfigurations, struct _trt__GetAudioSourceConfigurationsResponse *trt__GetAudioSourceConfigurationsResponse)
{
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    NEW(Nodes,AUDIOCONFIGS);
    INT     i;
    NEWMII(Resp,struct tt__AudioSourceConfiguration,OVFMAXCHANNEL);

    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,GetAudioSourceConfigs);
    if(FALSE==Onvif->CallBackOvf->CallBackMedia->GetAudioSourceConfigs(Nodes))return SOAP_FAULT;   
    for(i=0;i<OVFMAXCHANNEL&&i<Nodes->ConfigSize;i++){
	Resp[i].token                = Nodes->Configs[i].ConfigToken;
	Resp[i].Name                 = Nodes->Configs[i].ConfigName;
	Resp[i].UseCount			= Nodes->Configs[i].ConfigUseCount;
	Resp[i].SourceToken		= Nodes->Configs[i].AudioNodeToken;
   }
   

	trt__GetAudioSourceConfigurationsResponse->__sizeConfigurations =Nodes->ConfigSize;
	trt__GetAudioSourceConfigurationsResponse->Configurations     = Resp;

	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioSourceConfigurationOptions(struct soap* hSoap, struct _trt__GetAudioSourceConfigurationOptions *trt__GetAudioSourceConfigurationOptions, struct _trt__GetAudioSourceConfigurationOptionsResponse *trt__GetAudioSourceConfigurationOptionsResponse)
{
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    NEW(Configs,AUDIOCONFIGOPTIONS);
    NEW(Resp   ,struct tt__AudioSourceConfigurationOptions);
	NEWMIII(Resp->InputTokensAvailable ,CHAR ,1);
	NEWMIII(*Resp->InputTokensAvailable,CHAR *,64);
	NEWMIII(hSoap->fault ,struct SOAP_ENV__Fault,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code,struct SOAP_ENV__Code ,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode,struct SOAP_ENV__Code,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode,struct SOAP_ENV__Code ,1);
		NEWMIII(hSoap->fault->SOAP_ENV__Reason,struct SOAP_ENV__Reason,1);
	CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,GetAudioSourceConfigOptions);
	if(FALSE==Onvif->CallBackOvf->CallBackMedia->GetAudioSourceConfigOptions(
		trt__GetAudioSourceConfigurationOptions->ConfigurationToken,
		trt__GetAudioSourceConfigurationOptions->ProfileToken,Configs)){

		hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode->SOAP_ENV__Value ="ter:NoConfig" ;
		hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Value ="ter:InvalidArgVal";
 		hSoap->fault->SOAP_ENV__Reason->SOAP_ENV__Text="The configuration does not exist. ";

		return SOAP_FAULT;  }
	
	Resp->__sizeInputTokensAvailable					=        Configs->AudioNodeTokensAvailableSize;
	*Resp->InputTokensAvailable							=        Configs->AudioNodeTokensAvailable[0];	
	trt__GetAudioSourceConfigurationOptionsResponse->Options      =Resp;

	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioSourceConfiguration(struct soap* hSoap, struct _trt__GetAudioSourceConfiguration *trt__GetAudioSourceConfiguration, struct _trt__GetAudioSourceConfigurationResponse *trt__GetAudioSourceConfigurationResponse)
{
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    NEW(Configs,AUDIOCONFIG);
    NEW(Resp   ,struct tt__AudioSourceConfiguration);
	NEWMIII(hSoap->fault ,struct SOAP_ENV__Fault,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code,struct SOAP_ENV__Code ,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode,struct SOAP_ENV__Code,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode,struct SOAP_ENV__Code ,1);
		NEWMIII(hSoap->fault->SOAP_ENV__Reason,struct SOAP_ENV__Reason,1);
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,GetAudioSourceConfig);
    if(FALSE==Onvif->CallBackOvf->CallBackMedia->GetAudioSourceConfig(trt__GetAudioSourceConfiguration->ConfigurationToken,Configs)){

		hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode->SOAP_ENV__Value ="ter:NoVideoSource" ;
		hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Value ="ter:InvalidArgVal";
 		hSoap->fault->SOAP_ENV__Reason->SOAP_ENV__Text="The requested AudioSource does not exist.";

		return SOAP_FAULT;   }

	Resp->token                = Configs->ConfigToken;
	Resp->Name                 = Configs->ConfigName;
	Resp->UseCount             = Configs->ConfigUseCount;
	Resp->SourceToken          = Configs->AudioNodeToken;
 

    trt__GetAudioSourceConfigurationResponse->Configuration      =(struct tt__AudioSourceConfiguration *)Resp;
	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __trt__SetAudioSourceConfiguration(struct soap* hSoap, struct _trt__SetAudioSourceConfiguration *trt__SetAudioSourceConfiguration, struct _trt__SetAudioSourceConfigurationResponse *trt__SetAudioSourceConfigurationResponse)
{
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
	struct tt__AudioSourceConfiguration *Resp;
    NEW(Configs,AUDIOCONFIG);
	NEWMIII(hSoap->fault ,struct SOAP_ENV__Fault,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code,struct SOAP_ENV__Code ,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode,struct SOAP_ENV__Code,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode,struct SOAP_ENV__Code ,1);
		NEWMIII(hSoap->fault->SOAP_ENV__Reason,struct SOAP_ENV__Reason,1);
	if (NULL !=trt__SetAudioSourceConfiguration){
		Resp = trt__SetAudioSourceConfiguration->Configuration;
		if (NULL != Resp){
			STRNCPY(Configs->ConfigToken    ,  Resp->token ,OVFCHARLENTH) ;
			STRNCPY(Configs->ConfigName 	,  Resp->Name  ,OVFCHARLENTH) ;
			Configs->ConfigUseCount =  Resp->UseCount  ;
			STRNCPY(Configs->AudioNodeToken ,  Resp->SourceToken,OVFCHARLENTH) ;
			Configs->ForcePersistence= trt__SetAudioSourceConfiguration->ForcePersistence;
		}
	}  
    
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,SetAudioSourceConfig);
    if(FALSE==Onvif->CallBackOvf->CallBackMedia->SetAudioSourceConfig(Resp->SourceToken,Configs)){

		hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode->SOAP_ENV__Value ="ter: ConfigModify" ;
		hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Value ="ter:InvalidArgVal";
		hSoap->fault->SOAP_ENV__Reason->SOAP_ENV__Text="The configuration parameters are not possible to set.";		
		
		return SOAP_FAULT;  } //协议似乎定义有误，请求端无没带Token


	return SOAP_OK;
}
//音频.输出
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioOutputs(struct soap* hSoap, struct _trt__GetAudioOutputs *trt__GetAudioOutputs, struct _trt__GetAudioOutputsResponse *trt__GetAudioOutputsResponse)
{
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    NEW(Nodes,AUDIONODES);
    INT     i;
    NEWMII(Resp,struct tt__AudioOutput,OVFMAXCHANNEL);
    
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,GetAudioOutputs);
    if(FALSE==Onvif->CallBackOvf->CallBackMedia->GetAudioOutputs(Nodes))return SOAP_FAULT;   
    for(i=0;i<OVFMAXCHANNEL<Nodes->AudioNodeSize;i++){
	Resp[i].token                     = Nodes->AudioNodes[i].AudioToken;
    }
    trt__GetAudioOutputsResponse->__sizeAudioOutputs =Nodes->AudioNodeSize;
    trt__GetAudioOutputsResponse->AudioOutputs       =Resp;
	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioOutputConfigurations(struct soap* hSoap, struct _trt__GetAudioOutputConfigurations *trt__GetAudioOutputConfigurations, struct _trt__GetAudioOutputConfigurationsResponse *trt__GetAudioOutputConfigurationsResponse)
{
    struct tt__AudioOutputConfiguration *Resp[OVFMAXCHANNEL];
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    NEW(Nodes,AUDIOCONFIGS);
    INT     i;
    NEWM(Resp,struct tt__AudioOutputConfiguration,OVFMAXCHANNEL);
    
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,GetAudioOutputConfigs);
    if(FALSE==Onvif->CallBackOvf->CallBackMedia->GetAudioOutputConfigs(Nodes))return SOAP_FAULT;   
    for(i=0;i<OVFMAXCHANNEL&&i<Nodes->ConfigSize;i++){
	Resp[i]->token                = Nodes->Configs[i].ConfigToken;
	Resp[i]->Name                 = Nodes->Configs[i].ConfigName;
	Resp[i]->UseCount             = Nodes->Configs[i].ConfigUseCount;
	Resp[i]->OutputToken          = Nodes->Configs[i].AudioNodeToken;
 	Resp[i]->SendPrimacy          = Nodes->Configs[i].AudioOutputSendPrimacy;
	Resp[i]->OutputLevel          = Nodes->Configs[i].AudioOutputLevel;   
    }
    trt__GetAudioOutputConfigurationsResponse->__sizeConfigurations =Nodes->ConfigSize;
    trt__GetAudioOutputConfigurationsResponse->Configurations       =(struct tt__AudioOutputConfiguration *)Resp;
	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioOutputConfigurationOptions(struct soap* hSoap, struct _trt__GetAudioOutputConfigurationOptions *trt__GetAudioOutputConfigurationOptions, struct _trt__GetAudioOutputConfigurationOptionsResponse *trt__GetAudioOutputConfigurationOptionsResponse)
{
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    NEW(Configs,AUDIOCONFIGOPTIONS);
    NEW(Resp   ,struct tt__AudioOutputConfigurationOptions);
    
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,GetAudioOutputConfigOptions);
    if(FALSE==Onvif->CallBackOvf->CallBackMedia->GetAudioOutputConfigOptions(
		trt__GetAudioOutputConfigurationOptions->ConfigurationToken,
        trt__GetAudioOutputConfigurationOptions->ProfileToken,Configs))return SOAP_FAULT;   

	Resp->__sizeOutputTokensAvailable                =        Configs->AudioNodeTokensAvailableSize;
	Resp->OutputTokensAvailable                      =(CHAR**)Configs->AudioNodeTokensAvailable;
    Resp->OutputLevelRange                           =(struct tt__IntRange *)&Configs->OutputLevelRange;
	Resp->__sizeSendPrimacyOptions                   =        Configs->OutputSendPrimacyOptionsSize;
	Resp->SendPrimacyOptions                         =(CHAR**)Configs->OutputSendPrimacyOptions;;

    trt__GetAudioOutputConfigurationOptionsResponse->Options      =(struct tt__AudioOutputConfigurationOptions *)Resp;
	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioOutputConfiguration(struct soap* hSoap, struct _trt__GetAudioOutputConfiguration *trt__GetAudioOutputConfiguration, struct _trt__GetAudioOutputConfigurationResponse *trt__GetAudioOutputConfigurationResponse)
{
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    NEW(Configs,AUDIOCONFIG);
    NEW(Resp   ,struct tt__AudioOutputConfiguration);
    
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,GetAudioSourceConfig);
    if(FALSE==Onvif->CallBackOvf->CallBackMedia->GetAudioSourceConfig(trt__GetAudioOutputConfiguration->ConfigurationToken,Configs))return SOAP_FAULT;   

	Resp->token                = Configs->ConfigToken;
	Resp->Name                 = Configs->ConfigName;
	Resp->UseCount             = Configs->ConfigUseCount;
 	Resp->OutputToken          = Configs->AudioNodeToken;
 	Resp->SendPrimacy          = Configs->AudioOutputSendPrimacy;
	Resp->OutputLevel          = Configs->AudioOutputLevel;  

    trt__GetAudioOutputConfigurationResponse->Configuration      =(struct tt__AudioOutputConfiguration *)Resp;
	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __trt__SetAudioOutputConfiguration(struct soap* hSoap, struct _trt__SetAudioOutputConfiguration *trt__SetAudioOutputConfiguration, struct _trt__SetAudioOutputConfigurationResponse *trt__SetAudioOutputConfigurationResponse)
{
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    NEW(Configs,AUDIOCONFIG);
    struct tt__AudioOutputConfiguration *Resp = trt__SetAudioOutputConfiguration->Configuration;
	NEWMIII(hSoap->fault ,struct SOAP_ENV__Fault,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code,struct SOAP_ENV__Code ,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode,struct SOAP_ENV__Code,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode,struct SOAP_ENV__Code ,1);
		NEWMIII(hSoap->fault->SOAP_ENV__Reason,struct SOAP_ENV__Reason,1);
    STRNCPY(Configs->ConfigToken    ,  Resp->token ,OVFCHARLENTH) ;
    STRNCPY(Configs->ConfigName 	,  Resp->Name  ,OVFCHARLENTH) ;
	STRNCPY(Configs->AudioNodeToken ,  Resp->OutputToken,OVFCHARLENTH) ;
 	STRNCPY(Configs->AudioOutputSendPrimacy,Resp->SendPrimacy,OVFCHARLENTH);;
	Configs->AudioOutputLevel=  Resp->OutputLevel   ;      
    Configs->ConfigUseCount  =  Resp->UseCount  ;
    Configs->ForcePersistence= trt__SetAudioOutputConfiguration->ForcePersistence;
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,SetAudioOutputConfig);
    if(FALSE==Onvif->CallBackOvf->CallBackMedia->SetAudioOutputConfig(Resp->token,Configs)){

		hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode->SOAP_ENV__Value ="ter:NoConfig" ;
		hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Value ="ter:InvalidArgVal";
 		hSoap->fault->SOAP_ENV__Reason->SOAP_ENV__Text="The configuration does not exist. ";

		return SOAP_FAULT;  } //协议似乎定义有误，请求端无没带Token

	return SOAP_OK;
}
//音频.编码
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioEncoderConfigurations(struct soap* hSoap, struct _trt__GetAudioEncoderConfigurations *trt__GetAudioEncoderConfigurations, struct _trt__GetAudioEncoderConfigurationsResponse *trt__GetAudioEncoderConfigurationsResponse)
{
		
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    INT     i;
    NEW (Configs,AUDIOCODINGCONFIGS);
	NEWMII(Resps,struct tt__AudioEncoderConfiguration,OVFMAXCHANNEL) ; 
	for (i=0;i<OVFMAXCHANNEL;i++)
	{
		NEWMIII(Resps[i].Multicast,struct tt__MulticastConfiguration,1);
		NEWMIII(Resps[i].Multicast->Address,struct tt__IPAddress,1);
// 		NEWMIII(Resps[i].Multicast->Address->IPv4Address,CHAR*,1);
// 		NEWMIII(*Resps[i].Multicast->Address->IPv4Address,CHAR,OVFCHARLENTH);
	}

    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,GetAudioEncConfigs);
    if(FALSE==Onvif->CallBackOvf->CallBackMedia->GetAudioEncConfigs(Configs))return SOAP_FAULT;       
    for(i =0 ;i<OVFMAXCHANNEL&&i<Configs->ConfigSize;i++){
		Resps[i].Name             = Configs->ConfigEncs[i].ConfigName;
		Resps[i].token            = Configs->ConfigEncs[i].Configtoken;
		Resps[i].UseCount         = Configs->ConfigEncs[i].ConfigUseCount;
		Resps[i].Encoding         = Configs->ConfigEncs[i].AudioEncType;
		Resps[i].SampleRate       = Configs->ConfigEncs[i].AudioEncSampleRate;
		Resps[i].Bitrate          = Configs->ConfigEncs[i].AudioEncBitrate;
		Resps[i].SessionTimeout   = Configs->ConfigEncs[i].RTSPSessionTimeout;
		Resps[i].Multicast->AutoStart                 = Configs->ConfigEncs[i].Multicast.AutoStart;
		Resps[i].Multicast->Port                      = Configs->ConfigEncs[i].Multicast.Port;
		Resps[i].Multicast->TTL                       = Configs->ConfigEncs[i].Multicast.TTL;
//         Resps[i].Multicast->Address->Type             = IPTYPE_V4;
// 		*Resps[i].Multicast->Address->IPv4Address      =Configs->ConfigEncs[i].Multicast.Address.ipv4Address;
   
    }
    trt__GetAudioEncoderConfigurationsResponse->__sizeConfigurations = Configs->ConfigSize;
    trt__GetAudioEncoderConfigurationsResponse->Configurations       = Resps;
    return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioEncoderConfigurationOptions(struct soap* hSoap, struct _trt__GetAudioEncoderConfigurationOptions *trt__GetAudioEncoderConfigurationOptions, struct _trt__GetAudioEncoderConfigurationOptionsResponse *trt__GetAudioEncoderConfigurationOptionsResponse)
{
     ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
     INT     i;
    NEW(Options,AUDIOENCCONFIGOPTIONS);
    NEW(OptionsRsp,struct tt__AudioEncoderConfigurationOptions);
    NEWMII(Resps   ,struct tt__AudioEncoderConfigurationOption,OVFMAXCHANNEL);
	for (i=0;i<OVFMAXCHANNEL;i++){
		NEWMIII(Resps[i].BitrateList,struct tt__IntList,1);
		NEWMIII(Resps[i].SampleRateList,struct tt__IntList,1);
	}
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,GetAudioEncConfigOptions);
    if(FALSE==Onvif->CallBackOvf->CallBackMedia->GetAudioEncConfigOptions(
		 trt__GetAudioEncoderConfigurationOptions->ConfigurationToken,
        trt__GetAudioEncoderConfigurationOptions->ProfileToken,Options))return SOAP_FAULT;   
    for(i=0;i<OVFMAXCHANNEL&&i<Options->AudioEncConfigOptionSize;i++){
		Resps[i].Encoding       =                       Options->AudioEncConfigOption[i].EncType;
		Resps[i].BitrateList->__sizeItems = Options->AudioEncConfigOption[i].EncBitrateList.ItemsSize;
		Resps[i].BitrateList->Items       = Options->AudioEncConfigOption[i].EncBitrateList.Items;
		Resps[i].SampleRateList->__sizeItems = Options->AudioEncConfigOption[i].EncSampleRateList.ItemsSize;
		Resps[i].SampleRateList->Items       = Options->AudioEncConfigOption[i].EncSampleRateList.Items;

	//  Resps[i].BitrateList    = (struct tt__IntList*)&Options->AudioEncConfigOption[i].EncBitrateList; //结构相同，直接转定义
	//  Resps[i].SampleRateList = (struct tt__IntList*)&Options->AudioEncConfigOption[i].EncSampleRateList;
	 }
     trt__GetAudioEncoderConfigurationOptionsResponse->Options=OptionsRsp;
	 trt__GetAudioEncoderConfigurationOptionsResponse->Options->__sizeOptions= Options->AudioEncConfigOptionSize;
     trt__GetAudioEncoderConfigurationOptionsResponse->Options->Options      = Resps;

	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioEncoderConfiguration(struct soap* hSoap, struct _trt__GetAudioEncoderConfiguration *trt__GetAudioEncoderConfiguration, struct _trt__GetAudioEncoderConfigurationResponse *trt__GetAudioEncoderConfigurationResponse)
{
     struct tt__AudioEncoderConfiguration *Resps[1];
           struct tt__MulticastConfiguration *Multicast[1];
                  struct tt__IPAddress *Address[1];
    
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    INT     i;
    NEW (Configs,AUDIOCODINGCONFIGS);
    NEWM(Resps    , struct tt__AudioEncoderConfiguration,1);
    NEWM(Multicast, struct tt__MulticastConfiguration,1);
    NEWM(Address  , struct tt__IPAddress,1);
    for(i=0;i<1;i++){
       Resps[i]->Multicast=Multicast[i];
       Resps[i]->Multicast->Address=Address[i];
    }
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,GetAudioEncConfig);
    if(FALSE==Onvif->CallBackOvf->CallBackMedia->GetAudioEncConfig(trt__GetAudioEncoderConfiguration->ConfigurationToken, Configs->ConfigEncs))return SOAP_FAULT;       
    for(i =0 ;i<1 ;i++){
		Resps[i]->Name             = Configs->ConfigEncs[i].ConfigName;
		Resps[i]->token            = Configs->ConfigEncs[i].Configtoken;
		Resps[i]->UseCount         = Configs->ConfigEncs[i].ConfigUseCount;
		Resps[i]->Encoding         = Configs->ConfigEncs[i].AudioEncType;
		Resps[i]->SampleRate       = Configs->ConfigEncs[i].AudioEncSampleRate;
		Resps[i]->Bitrate          = Configs->ConfigEncs[i].AudioEncBitrate;
		Resps[i]->SessionTimeout   = Configs->ConfigEncs[i].RTSPSessionTimeout;
		Resps[i]->Multicast->AutoStart                 = Configs->ConfigEncs[i].Multicast.AutoStart;
		Resps[i]->Multicast->Port                      = Configs->ConfigEncs[i].Multicast.Port;
		Resps[i]->Multicast->TTL                       = Configs->ConfigEncs[i].Multicast.TTL;
        Resps[i]->Multicast->Address->Type             = IPTYPE_V4;
	//	Resps[i]->Multicast->Address->IPv4Address      =(CHAR**) &Configs->ConfigEncs[i].Multicast.Address.ipv4Address;
   
    }

    trt__GetAudioEncoderConfigurationResponse->Configuration       =(struct tt__AudioEncoderConfiguration *)Resps[0];
    return SOAP_OK;   
}
SOAP_FMAC5 int SOAP_FMAC6 __trt__SetAudioEncoderConfiguration(struct soap* hSoap, struct _trt__SetAudioEncoderConfiguration *trt__SetAudioEncoderConfiguration, struct _trt__SetAudioEncoderConfigurationResponse *trt__SetAudioEncoderConfigurationResponse)
{
     struct tt__AudioEncoderConfiguration *Req ;

    
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    NEW (Config,AUDIOCODINGCONFIG);
	NEWMIII(hSoap->fault ,struct SOAP_ENV__Fault,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code,struct SOAP_ENV__Code ,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode,struct SOAP_ENV__Code,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode,struct SOAP_ENV__Code ,1);
		NEWMIII(hSoap->fault->SOAP_ENV__Reason,struct SOAP_ENV__Reason,1);
	if(NULL != trt__SetAudioEncoderConfiguration )
	{
		Req = trt__SetAudioEncoderConfiguration->Configuration;
		if(NULL != Req){
			STRNCPY(Config->ConfigName ,Req->Name,OVFCHARLENTH) ;
			STRNCPY(Config->Configtoken,Req->token,OVFCHARLENTH) ;
			Config->ConfigUseCount =Req->UseCount ;
			Config->AudioEncType=Req->Encoding ;
			Config->AudioEncSampleRate=Req->SampleRate  ;
			Config->AudioEncBitrate =Req->Bitrate ;
			STRNCPY(Config->RTSPSessionTimeout ,Req->SessionTimeout,OVFCHARLENTH) ;
			if(NULL != Req->Multicast){
				Config->Multicast.AutoStart=Req->Multicast->AutoStart ;
				Config->Multicast.Port=Req->Multicast->Port ;
				Config->Multicast.TTL =Req->Multicast->TTL  ;
				if(NULL != Req->Multicast->Address->IPv4Address)
					STRNCPY(Config->Multicast.Address.ipv4Address,*Req->Multicast->Address->IPv4Address,OVFCHARLENTH) ;
			}	
		}
			Config->ForcePersistence  = trt__SetAudioEncoderConfiguration->ForcePersistence;
	}

    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,SetAudioEncConfig);
    if(FALSE==Onvif->CallBackOvf->CallBackMedia->SetAudioEncConfig(Req->token, Config))return SOAP_FAULT;       
	if(2==Onvif->CallBackOvf->CallBackMedia->SetAudioEncConfig(Req->token, Config)){

		hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode->SOAP_ENV__Value ="ter:ConfigModify" ;
		hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Value ="ter:InvalidArgVal";
 		hSoap->fault->SOAP_ENV__Reason->SOAP_ENV__Text="The configuration parameters are not possible to set. ";

		return SOAP_FAULT;  
	}
    return SOAP_OK;
}
//音频.解码
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioDecoderConfigurations(struct soap* hSoap, struct _trt__GetAudioDecoderConfigurations *trt__GetAudioDecoderConfigurations, struct _trt__GetAudioDecoderConfigurationsResponse *trt__GetAudioDecoderConfigurationsResponse)
{
   struct tt__AudioDecoderConfiguration *Resps[OVFMAXCHANNEL];

    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    INT     i;
    NEW (Configs,AUDIOCODINGCONFIGS);
    NEWM(Resps    , struct tt__AudioDecoderConfiguration,OVFMAXCHANNEL);

    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,GetAudioDecConfigs);
    if(FALSE==Onvif->CallBackOvf->CallBackMedia->GetAudioDecConfigs(Configs))return SOAP_FAULT;       
    for(i =0 ;i<OVFMAXCHANNEL&&i<Configs->ConfigSize;i++){
		Resps[i]->Name             = Configs->ConfigEncs[i].ConfigName;
		Resps[i]->token            = Configs->ConfigEncs[i].Configtoken;
		Resps[i]->UseCount         = Configs->ConfigEncs[i].ConfigUseCount;  
    }
    trt__GetAudioDecoderConfigurationsResponse->__sizeConfigurations = Configs->ConfigSize;
    trt__GetAudioDecoderConfigurationsResponse->Configurations       =(struct tt__AudioDecoderConfiguration *)Resps;
    return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioDecoderConfigurationOptions(struct soap* hSoap, struct _trt__GetAudioDecoderConfigurationOptions *trt__GetAudioDecoderConfigurationOptions, struct _trt__GetAudioDecoderConfigurationOptionsResponse *trt__GetAudioDecoderConfigurationOptionsResponse)
{
    NEW(Resps,struct tt__AudioDecoderConfigurationOptions);
           	NEW(AACDecOptions,struct tt__AACDecOptions );
	        NEW(G711DecOptions,struct tt__G711DecOptions);
	        NEW(G726DecOptions,struct tt__G726DecOptions);
	NEW(Options,AUDIODECCONFIGOPTION);

    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    Resps->AACDecOptions = AACDecOptions;
	Resps->G711DecOptions= G711DecOptions;
	Resps->G726DecOptions= G726DecOptions;
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,GetAudioDecConfigsOptions);
    if(FALSE==Onvif->CallBackOvf->CallBackMedia->GetAudioDecConfigsOptions(
		trt__GetAudioDecoderConfigurationOptions->ConfigurationToken,
        trt__GetAudioDecoderConfigurationOptions->ProfileToken,Options))return SOAP_FAULT;   

		 Resps->AACDecOptions->Bitrate          = (struct tt__IntList*)&Options->AACDecOptions.DecOptionBitrate; //结构相同，直接转定义
		 Resps->AACDecOptions->SampleRateRange  = (struct tt__IntList*)&Options->AACDecOptions.DecOptonSampleRateRange;
		 Resps->G711DecOptions->Bitrate         = (struct tt__IntList*)&Options->G711DecOptions.DecOptionBitrate; //结构相同，直接转定义
		 Resps->G711DecOptions->SampleRateRange = (struct tt__IntList*)&Options->G711DecOptions.DecOptonSampleRateRange;
		 Resps->G726DecOptions->Bitrate         = (struct tt__IntList*)&Options->G726DecOptions.DecOptionBitrate; //结构相同，直接转定义
		 Resps->G726DecOptions->SampleRateRange = (struct tt__IntList*)&Options->G726DecOptions.DecOptonSampleRateRange;

     trt__GetAudioDecoderConfigurationOptionsResponse->Options      = (struct tt__AudioDecoderConfigurationOptions*)Resps;
           
    return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioDecoderConfiguration(struct soap* hSoap, struct _trt__GetAudioDecoderConfiguration *trt__GetAudioDecoderConfiguration, struct _trt__GetAudioDecoderConfigurationResponse *trt__GetAudioDecoderConfigurationResponse)
{
   struct tt__AudioDecoderConfiguration *Resps[1];
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    INT     i;
    NEW (Configs,AUDIOCODINGCONFIGS);
    NEWM(Resps    , struct tt__AudioDecoderConfiguration,1);

    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,GetAudioDecConfig);
    if(FALSE==Onvif->CallBackOvf->CallBackMedia->GetAudioDecConfig(trt__GetAudioDecoderConfiguration->ConfigurationToken,&Configs->ConfigEncs[0]))return SOAP_FAULT;       
    for(i =0 ;i<1;i++){
		Resps[i]->Name             = Configs->ConfigEncs[i].ConfigName;
		Resps[i]->token            = Configs->ConfigEncs[i].Configtoken;
		Resps[i]->UseCount         = Configs->ConfigEncs[i].ConfigUseCount;  
    }

    trt__GetAudioDecoderConfigurationResponse->Configuration       =(struct tt__AudioDecoderConfiguration *)Resps;
    return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __trt__SetAudioDecoderConfiguration(struct soap* hSoap, struct _trt__SetAudioDecoderConfiguration *trt__SetAudioDecoderConfiguration, struct _trt__SetAudioDecoderConfigurationResponse *trt__SetAudioDecoderConfigurationResponse)
{
     struct tt__AudioDecoderConfiguration *Req =trt__SetAudioDecoderConfiguration->Configuration;

    
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    NEW (Config,AUDIOCODINGCONFIG);

	STRNCPY(Config->ConfigName ,Req->Name,OVFCHARLENTH) ;
	STRNCPY(Config->Configtoken,Req->token,OVFCHARLENTH) ;
	Config->ConfigUseCount =Req->UseCount ;

	Config->ForcePersistence  = trt__SetAudioDecoderConfiguration->ForcePersistence;

    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,SetAudioDecConfig);
    if(FALSE==Onvif->CallBackOvf->CallBackMedia->SetAudioDecConfig(Req->token, Config))return SOAP_FAULT;       

    return SOAP_OK;
}
//以下为其他暂不支持的音频相关接口
//音频.输入
SOAP_FMAC5 int SOAP_FMAC6 __trt__AddAudioSourceConfiguration(struct soap* hSoap, struct _trt__AddAudioSourceConfiguration *trt__AddAudioSourceConfiguration, struct _trt__AddAudioSourceConfigurationResponse *trt__AddAudioSourceConfigurationResponse)
{return SOAP_OK;}
SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveAudioSourceConfiguration(struct soap* hSoap, struct _trt__RemoveAudioSourceConfiguration *trt__RemoveAudioSourceConfiguration, struct _trt__RemoveAudioSourceConfigurationResponse *trt__RemoveAudioSourceConfigurationResponse)
{return SOAP_OK;}

//音频.输出
SOAP_FMAC5 int SOAP_FMAC6 __trt__AddAudioOutputConfiguration(struct soap* hSoap, struct _trt__AddAudioOutputConfiguration *trt__AddAudioOutputConfiguration, struct _trt__AddAudioOutputConfigurationResponse *trt__AddAudioOutputConfigurationResponse)
{return SOAP_OK;}
SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveAudioOutputConfiguration(struct soap* hSoap, struct _trt__RemoveAudioOutputConfiguration *trt__RemoveAudioOutputConfiguration, struct _trt__RemoveAudioOutputConfigurationResponse *trt__RemoveAudioOutputConfigurationResponse)
{return SOAP_OK;}


//音频.编码
SOAP_FMAC5 int SOAP_FMAC6 __trt__AddAudioEncoderConfiguration(struct soap* hSoap, struct _trt__AddAudioEncoderConfiguration *trt__AddAudioEncoderConfiguration, struct _trt__AddAudioEncoderConfigurationResponse *trt__AddAudioEncoderConfigurationResponse)
{return SOAP_OK;}
SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveAudioEncoderConfiguration(struct soap* hSoap, struct _trt__RemoveAudioEncoderConfiguration *trt__RemoveAudioEncoderConfiguration, struct _trt__RemoveAudioEncoderConfigurationResponse *trt__RemoveAudioEncoderConfigurationResponse)
{return SOAP_OK;}


//音频.解码

SOAP_FMAC5 int SOAP_FMAC6 __trt__AddAudioDecoderConfiguration(struct soap* hSoap, struct _trt__AddAudioDecoderConfiguration *trt__AddAudioDecoderConfiguration, struct _trt__AddAudioDecoderConfigurationResponse *trt__AddAudioDecoderConfigurationResponse)
{return SOAP_OK;}
SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveAudioDecoderConfiguration(struct soap* hSoap, struct _trt__RemoveAudioDecoderConfiguration *trt__RemoveAudioDecoderConfiguration, struct _trt__RemoveAudioDecoderConfigurationResponse *trt__RemoveAudioDecoderConfigurationResponse)
{return SOAP_OK;}


//音频.兼容(暂不支持)
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleAudioEncoderConfigurations(struct soap* hSoap, struct _trt__GetCompatibleAudioEncoderConfigurations *trt__GetCompatibleAudioEncoderConfigurations, struct _trt__GetCompatibleAudioEncoderConfigurationsResponse *trt__GetCompatibleAudioEncoderConfigurationsResponse)
{
	ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    INT     i;
    NEW (Configs,AUDIOCODINGCONFIGS);
	NEWMII(Resps,struct tt__AudioEncoderConfiguration,OVFMAXCHANNEL) ; 
	for (i=0;i<OVFMAXCHANNEL;i++)
	{
		NEWMIII(Resps[i].Multicast,struct tt__MulticastConfiguration,1);
		NEWMIII(Resps[i].Multicast->Address,struct tt__IPAddress,1);
// 		NEWMIII(Resps[i].Multicast->Address->IPv4Address,CHAR*,1);
// 		NEWMIII(*Resps[i].Multicast->Address->IPv4Address,CHAR,OVFCHARLENTH);
	}
	
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,GetAudioEncConfigs);
    if(FALSE==Onvif->CallBackOvf->CallBackMedia->GetAudioEncConfigs(Configs))return SOAP_FAULT;       
    for(i =0 ;i<OVFMAXCHANNEL&&i<Configs->ConfigSize;i++){
		Resps[i].Name             = Configs->ConfigEncs[i].ConfigName;
		Resps[i].token            = Configs->ConfigEncs[i].Configtoken;
		Resps[i].UseCount         = Configs->ConfigEncs[i].ConfigUseCount;
		Resps[i].Encoding         = Configs->ConfigEncs[i].AudioEncType;
		Resps[i].SampleRate       = Configs->ConfigEncs[i].AudioEncSampleRate;
		Resps[i].Bitrate          = Configs->ConfigEncs[i].AudioEncBitrate;
		Resps[i].SessionTimeout   = Configs->ConfigEncs[i].RTSPSessionTimeout;
		Resps[i].Multicast->AutoStart                 = Configs->ConfigEncs[i].Multicast.AutoStart;
		Resps[i].Multicast->Port                      = Configs->ConfigEncs[i].Multicast.Port;
		Resps[i].Multicast->TTL                       = Configs->ConfigEncs[i].Multicast.TTL;
        Resps[i].Multicast->Address->Type             = IPTYPE_V4;
//		*Resps[i].Multicast->Address->IPv4Address      =Configs->ConfigEncs[i].Multicast.Address.ipv4Address;
		
    }
    trt__GetCompatibleAudioEncoderConfigurationsResponse->__sizeConfigurations = Configs->ConfigSize;
    trt__GetCompatibleAudioEncoderConfigurationsResponse->Configurations       = Resps;

	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleAudioSourceConfigurations(struct soap* hSoap, struct _trt__GetCompatibleAudioSourceConfigurations *trt__GetCompatibleAudioSourceConfigurations, struct _trt__GetCompatibleAudioSourceConfigurationsResponse *trt__GetCompatibleAudioSourceConfigurationsResponse)
{
	ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    NEW(Nodes,AUDIOCONFIGS);
    INT     i;
    NEWMII(Resp,struct tt__AudioSourceConfiguration,OVFMAXCHANNEL);
	
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,GetAudioSourceConfigs);
    if(FALSE==Onvif->CallBackOvf->CallBackMedia->GetAudioSourceConfigs(Nodes))return SOAP_FAULT;   
    for(i=0;i<OVFMAXCHANNEL&&i<Nodes->ConfigSize;i++){
		Resp[i].token                = Nodes->Configs[i].ConfigToken;
		Resp[i].Name                 = Nodes->Configs[i].ConfigName;
		Resp[i].UseCount			= Nodes->Configs[i].ConfigUseCount;
		Resp[i].SourceToken		   = Nodes->Configs[i].AudioNodeToken;
	}
	
	
	trt__GetCompatibleAudioSourceConfigurationsResponse->__sizeConfigurations =Nodes->ConfigSize;
	trt__GetCompatibleAudioSourceConfigurationsResponse->Configurations    = Resp;
	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleAudioOutputConfigurations(struct soap* hSoap, struct _trt__GetCompatibleAudioOutputConfigurations *trt__GetCompatibleAudioOutputConfigurations, struct _trt__GetCompatibleAudioOutputConfigurationsResponse *trt__GetCompatibleAudioOutputConfigurationsResponse)
{return SOAP_OK;}
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleAudioDecoderConfigurations(struct soap* hSoap, struct _trt__GetCompatibleAudioDecoderConfigurations *trt__GetCompatibleAudioDecoderConfigurations, struct _trt__GetCompatibleAudioDecoderConfigurationsResponse *trt__GetCompatibleAudioDecoderConfigurationsResponse)
{return SOAP_OK;}
////////////////////////////////////////////////////////////
//视频.输入
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoSources(struct soap* hSoap, struct _trt__GetVideoSources *trt__GetVideoSources, struct _trt__GetVideoSourcesResponse *trt__GetVideoSourcesResponse)
{
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    NEW(Nodes,VIDEOSOURCES);
    INT     i;
    NEWMII(Resp,struct tt__VideoSource,OVFMAXCHANNEL);
    
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,GetVideoSources);
    if(FALSE==Onvif->CallBackOvf->CallBackMedia->GetVideoSources(Nodes))return SOAP_FAULT;   
    for(i=0;i<OVFMAXCHANNEL && i<Nodes->VideoSourceSize;i++){
	Resp[i].token                    = Nodes->VideoSources[i].VideoToken;
	Resp[i].Framerate                = Nodes->VideoSources[i].VideoSourceFramerate;
	Resp[i].Resolution               =(struct tt__VideoResolution*) &Nodes->VideoSources[i].VideoSourceResolution;//结构相同
    }
    trt__GetVideoSourcesResponse->__sizeVideoSources =Nodes->VideoSourceSize;
    trt__GetVideoSourcesResponse->VideoSources       =Resp;
	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoSourceConfigurations(struct soap* hSoap, struct _trt__GetVideoSourceConfigurations *trt__GetVideoSourceConfigurations, struct _trt__GetVideoSourceConfigurationsResponse *trt__GetVideoSourceConfigurationsResponse)
{
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    NEW(Nodes,VIDEOSOURCECONFIGS);
    INT     i;
    NEWMII(Resp,struct tt__VideoSourceConfiguration,OVFMAXCHANNEL);
	
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,GetVideoSourceConfigs);
    if(FALSE==Onvif->CallBackOvf->CallBackMedia->GetVideoSourceConfigs(Nodes))return SOAP_FAULT;   
    for(i=0;i<OVFMAXCHANNEL&&i<Nodes->ConfigSize;i++){
		Resp[i].Name              = Nodes->VideoSourceConfigs[i].ConfigName;
		Resp[i].token             = Nodes->VideoSourceConfigs[i].ConfigToken;
		Resp[i].SourceToken       = Nodes->VideoSourceConfigs[i].SourceToken;
		Resp[i].UseCount          = Nodes->VideoSourceConfigs[i].ConfigUseCount;
		Resp[i].Bounds            =(struct tt__IntRectangle*) &Nodes->VideoSourceConfigs[i].SourceBounds;//结构相同

    }
    trt__GetVideoSourceConfigurationsResponse->__sizeConfigurations =Nodes->ConfigSize;
    trt__GetVideoSourceConfigurationsResponse->Configurations       =Resp;
	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoSourceConfigurationOptions(struct soap* hSoap, struct _trt__GetVideoSourceConfigurationOptions *trt__GetVideoSourceConfigurationOptions, struct _trt__GetVideoSourceConfigurationOptionsResponse *trt__GetVideoSourceConfigurationOptionsResponse)
{
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
	INT len= 0;
    NEW(Configs,VIDEOSOURCECONFIGOPTIONS);
    NEW(Resp   ,struct tt__VideoSourceConfigurationOptions);
	NEWMIII(Resp->BoundsRange,struct tt__IntRectangleRange,1);
	NEWMIII(Resp->BoundsRange->HeightRange,struct tt__IntRange,1);
	NEWMIII(Resp->BoundsRange->WidthRange,struct tt__IntRange,1);
	NEWMIII(Resp->BoundsRange->XRange,struct tt__IntRange,1);
	NEWMIII(Resp->BoundsRange->YRange,struct tt__IntRange,1);
	NEWMIII(Resp->VideoSourceTokensAvailable,CHAR,1);
	NEWMIII(*Resp->VideoSourceTokensAvailable,CHAR *,OVFCHARLENTH);
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,GetVideoSourceConfigOptions);
    if(FALSE==Onvif->CallBackOvf->CallBackMedia->GetVideoSourceConfigOptions(
		trt__GetVideoSourceConfigurationOptions->ConfigurationToken,
        trt__GetVideoSourceConfigurationOptions->ProfileToken,Configs))return SOAP_FAULT;   

	Resp->__sizeVideoSourceTokensAvailable                =Configs->VideoSourceTokenSize;
	*Resp->VideoSourceTokensAvailable                     =Configs->VideoSourceTokens[0];
	len =sizeof(Configs->VideoSourceTokens[0]);
	Resp->BoundsRange->HeightRange                        =(struct tt__IntRange*)&Configs->BoundsRange.HeightRange;       //结构相同
	Resp->BoundsRange->WidthRange						  =(struct tt__IntRange*)&Configs->BoundsRange.WidthRange;
	Resp->BoundsRange->XRange							  =(struct tt__IntRange*)&Configs->BoundsRange.XRange;
	Resp->BoundsRange->YRange							  =(struct tt__IntRange*)&Configs->BoundsRange.YRange;

    trt__GetVideoSourceConfigurationOptionsResponse->Options      =Resp;
	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoSourceConfiguration(struct soap* hSoap, struct _trt__GetVideoSourceConfiguration *trt__GetVideoSourceConfiguration, struct _trt__GetVideoSourceConfigurationResponse *trt__GetVideoSourceConfigurationResponse)
{
	ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
	NEW(Resp,struct tt__VideoSourceConfiguration);
	NEW(Config,VIDEOSOURCECONFIG);
    if(FALSE==Onvif->CallBackOvf->CallBackMedia->GetVideoSourceConfig(trt__GetVideoSourceConfiguration->ConfigurationToken,Config))return SOAP_FAULT;
	Resp->Bounds		=(struct tt__IntRectangle *)&Config->SourceBounds;
	Resp->Name			=Config->ConfigName;
	Resp->token			=Config->ConfigToken;
	Resp->SourceToken	=Config->SourceToken;
	Resp->UseCount		=Config->ConfigUseCount;
	
    trt__GetVideoSourceConfigurationResponse->Configuration       =Resp;

	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __trt__SetVideoSourceConfiguration(struct soap* hSoap, struct _trt__SetVideoSourceConfiguration *trt__SetVideoSourceConfiguration, struct _trt__SetVideoSourceConfigurationResponse *trt__SetVideoSourceConfigurationResponse)
{
     struct tt__VideoSourceConfiguration *Req; 

    
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    NEW (Config,VIDEOSOURCECONFIG);
	NEWMIII(hSoap->fault ,struct SOAP_ENV__Fault,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code,struct SOAP_ENV__Code ,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode,struct SOAP_ENV__Code,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode,struct SOAP_ENV__Code ,1);
		NEWMIII(hSoap->fault->SOAP_ENV__Reason,struct SOAP_ENV__Reason,1);
	if(NULL != trt__SetVideoSourceConfiguration)
	{
		Req	=trt__SetVideoSourceConfiguration->Configuration;
		if(NULL != Req){
			STRNCPY(Config->ConfigName ,Req->Name,OVFCHARLENTH) ;
			STRNCPY(Config->ConfigToken,Req->token,OVFCHARLENTH) ;
			Config->ConfigUseCount =Req->UseCount ;
			Config->SourceBounds.height   = Req->Bounds->height;
			Config->SourceBounds.width	  = Req->Bounds->width;
			Config->SourceBounds.x        = Req->Bounds->x;
			Config->SourceBounds.y        = Req->Bounds->y;
		}
			
		Config->ForcePersistence  = trt__SetVideoSourceConfiguration->ForcePersistence;
	}
	

    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,SetVideoSourceConfig);
    if(FALSE==Onvif->CallBackOvf->CallBackMedia->SetVideoSourceConfig(Req->token, Config))return SOAP_FAULT;       
    if(2==Onvif->CallBackOvf->CallBackMedia->SetVideoSourceConfig(Req->token, Config)){

		hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode->SOAP_ENV__Value ="ter:ConfigModify" ;
		hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Value ="ter:InvalidArgVal";
 		hSoap->fault->SOAP_ENV__Reason->SOAP_ENV__Text="The configuration parameters are not possible to set. ";

		return SOAP_FAULT;    
	}
    return SOAP_OK;
}

//视频.编码
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoEncoderConfigurations(struct soap* hSoap, struct _trt__GetVideoEncoderConfigurations *trt__GetVideoEncoderConfigurations, struct _trt__GetVideoEncoderConfigurationsResponse *trt__GetVideoEncoderConfigurationsResponse)
{
	printf("[__trt__GetVideoEncoderConfigurations]........................................................................................\n");
	ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
	NEW(Configs,VIDEOENCCONFIGS);
	
	INT     i;   
	NEWMII(Resps,struct tt__VideoEncoderConfiguration,OVFMAXCHANNEL) ; 
    for(i=0;i<OVFMAXCHANNEL;i++){
         NEWMIII(Resps[i].Multicast,struct tt__MulticastConfiguration,1);
         NEWMIII(Resps[i].Multicast->Address,struct tt__IPAddress,1);
		 NEWMIII(Resps[i].H264,struct tt__H264Configuration,1);
//		 NEWMIII(Resps[i].MPEG4,struct tt__Mpeg4Configuration,1);
		 NEWMIII(Resps[i].Resolution,struct tt__VideoResolution,1);
		 NEWMIII(Resps[i].RateControl,struct tt__VideoRateControl,1);
    }
 
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,GetVideoEncConfigs);
    if(FALSE==Onvif->CallBackOvf->CallBackMedia->GetVideoEncConfigs(Configs))return SOAP_FAULT;   
    for(i=0;i<OVFMAXCHANNEL&&i<Configs->VideoEncConfigSize;i++){
		Resps[i].Name             = Configs->VideoEncConfigs[i].ConfigName;
		Resps[i].token            = Configs->VideoEncConfigs[i].ConfigToken;
		Resps[i].UseCount         = Configs->VideoEncConfigs[i].ConfigUseCount;
		Resps[i].Encoding         = Configs->VideoEncConfigs[i].EncType;
        
		Resps[i].Resolution       = (struct tt__VideoResolution *)&Configs->VideoEncConfigs[i].EncResolution;
		Resps[i].Quality          = Configs->VideoEncConfigs[i].EncQuality;
		Resps[i].RateControl      = (struct tt__VideoRateControl*)&Configs->VideoEncConfigs[i].RateControl;
	//	Resps[i].MPEG4            = (struct tt__Mpeg4Configuration*)&Configs->VideoEncConfigs[i].ConfigMPEG4;
		Resps[i].H264             = (struct tt__H264Configuration *)&Configs->VideoEncConfigs[i].ConfigH264; 


		Resps[i].SessionTimeout   = Configs->VideoEncConfigs[i].RtspSessionTimeout;
		Resps[i].Multicast->AutoStart                 = Configs->VideoEncConfigs[i].Multicast.AutoStart;
		Resps[i].Multicast->Port                      = Configs->VideoEncConfigs[i].Multicast.Port;
		Resps[i].Multicast->TTL                       = Configs->VideoEncConfigs[i].Multicast.TTL;
        Resps[i].Multicast->Address->Type             = IPTYPE_V4;
 }

     trt__GetVideoEncoderConfigurationsResponse->__sizeConfigurations =Configs->VideoEncConfigSize;
     trt__GetVideoEncoderConfigurationsResponse->Configurations        =Resps;
	 
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoEncoderConfiguration(struct soap* hSoap, struct _trt__GetVideoEncoderConfiguration *trt__GetVideoEncoderConfiguration, struct _trt__GetVideoEncoderConfigurationResponse *trt__GetVideoEncoderConfigurationResponse)
{
	printf("[__trt__GetVideoEncoderConfiguration]................................................................\n");
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    NEW(Configs,VIDEOENCCONFIGS);

    INT     i;   
    NEWMII(Resps,struct tt__VideoEncoderConfiguration,1) ; 
	for (i=0;i<1;i++)
	{
		NEWMIII(Resps[i].Multicast,struct tt__MulticastConfiguration,1);
			NEWMIII(Resps[i].Multicast->Address,struct tt__IPAddress,1);
// 			NEWMIII(Resps[i].Multicast->Address->IPv4Address,char*,1);
// 			NEWMIII(*Resps[i].Multicast->Address->IPv4Address,char,OVFCHARLENTH);
	}
    
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,GetVideoEncConfig);
    if(FALSE==Onvif->CallBackOvf->CallBackMedia->GetVideoEncConfig(
		trt__GetVideoEncoderConfiguration->ConfigurationToken,
		Configs->VideoEncConfigs))return SOAP_FAULT;   
    for(i=0;i<1;i++){
		Resps[i].Name             = Configs->VideoEncConfigs[i].ConfigName;
		Resps[i].token            = Configs->VideoEncConfigs[i].ConfigToken;
		Resps[i].UseCount         = Configs->VideoEncConfigs[i].ConfigUseCount;
		Resps[i].Encoding         = Configs->VideoEncConfigs[i].EncType;
        
		Resps[i].Resolution       = (struct tt__VideoResolution *)&Configs->VideoEncConfigs[i].EncResolution;
		Resps[i].Quality          = Configs->VideoEncConfigs[i].EncQuality;
		Resps[i].RateControl      = (struct tt__VideoRateControl*)&Configs->VideoEncConfigs[i].RateControl;
//		Resps[i].MPEG4            = (struct tt__Mpeg4Configuration*)&Configs->VideoEncConfigs[i].ConfigMPEG4;
		Resps[i].H264             = (struct tt__H264Configuration *)&Configs->VideoEncConfigs[i].ConfigH264; 
        
		Resps[i].SessionTimeout   = Configs->VideoEncConfigs[i].RtspSessionTimeout;
		Resps[i].Multicast->AutoStart                 = Configs->VideoEncConfigs[i].Multicast.AutoStart;
		Resps[i].Multicast->Port                      = Configs->VideoEncConfigs[i].Multicast.Port;
		Resps[i].Multicast->TTL                       = Configs->VideoEncConfigs[i].Multicast.TTL;
        Resps[i].Multicast->Address->Type             = IPTYPE_V4;
 }
    trt__GetVideoEncoderConfigurationResponse->Configuration       =Resps;

	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__SetVideoEncoderConfiguration(struct soap* hSoap, struct _trt__SetVideoEncoderConfiguration *trt__SetVideoEncoderConfiguration, struct _trt__SetVideoEncoderConfigurationResponse *trt__SetVideoEncoderConfigurationResponse)
{
	printf("[__trt__SetVideoEncoderConfiguration].....................................................................................\n");
    struct tt__VideoEncoderConfiguration *Req ;

    
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    NEW (Config,VIDEOENCCONFIG);
	NEWMIII(hSoap->fault ,struct SOAP_ENV__Fault,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code,struct SOAP_ENV__Code ,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode,struct SOAP_ENV__Code,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode,struct SOAP_ENV__Code ,1);
		NEWMIII(hSoap->fault->SOAP_ENV__Reason,struct SOAP_ENV__Reason,1);
	if(NULL != trt__SetVideoEncoderConfiguration){
		Req = trt__SetVideoEncoderConfiguration->Configuration;
		if(NULL != Req){
			STRNCPY(Config->ConfigName ,Req->Name,OVFCHARLENTH) ;
			STRNCPY(Config->ConfigToken,Req->token,OVFCHARLENTH) ;
			Config->ConfigUseCount =Req->UseCount ;
			Config->EncType=Req->Encoding ;
			Config->EncQuality =Req->Quality ;
			MEMCPY(&Config->EncResolution,(RESOLUTION*)Req->Resolution ,sizeof(RESOLUTION)) ;
			MEMCPY(&Config->RateControl ,Req->RateControl ,sizeof(VIDEORATECONTROL));
			MEMCPY(&Config->ConfigMPEG4 ,Req->MPEG4 ,sizeof(MP4CONFIG)) ;
			MEMCPY(&Config->ConfigH264  ,Req->H264  ,sizeof(AVSCONFIG)) ;
			if(NULL != Req->Multicast ){
				Config->Multicast.AutoStart=Req->Multicast->AutoStart ;
				Config->Multicast.Port=Req->Multicast->Port ;
				Config->Multicast.TTL =Req->Multicast->TTL  ;
				STRNCPY(Config->RtspSessionTimeout ,Req->SessionTimeout,OVFCHARLENTH) ;
			}	
// 			if(Req->Multicast &&Req->Multicast->Address)
// 			STRNCPY(Config->Multicast.Address.ipv4Address,Req->Multicast->Address->IPv4Address,OVFCHARLENTH) ;
		}
	
		Config->ForcePersistence  = trt__SetVideoEncoderConfiguration->ForcePersistence;
	}
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,SetVideoEncConfig);
    if(FALSE==Onvif->CallBackOvf->CallBackMedia->SetVideoEncConfig(Req->token, Config))return SOAP_FAULT;  
	if (2==Onvif->CallBackOvf->CallBackMedia->SetVideoEncConfig(Req->token, Config))
	{
		hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode->SOAP_ENV__Value ="ter: ConfigModify" ;
		hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Value ="ter:InvalidArgVal";
 		hSoap->fault->SOAP_ENV__Reason->SOAP_ENV__Text="The configuration parameters are not possible to set.";
		return SOAP_FAULT;
	}
    
    return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoEncoderConfigurationOptions(struct soap* hSoap, struct _trt__GetVideoEncoderConfigurationOptions *trt__GetVideoEncoderConfigurationOptions, struct _trt__GetVideoEncoderConfigurationOptionsResponse *trt__GetVideoEncoderConfigurationOptionsResponse)
{
	printf("[__trt__GetVideoEncoderConfigurationOptions].......................................................................\n");
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;

    NEW(Options,VIDEOENCCONFIGOPTONS);
    NEW(Resps     ,struct tt__VideoEncoderConfigurationOptions);
	NEWMIII(Resps->QualityRange,struct tt__IntRange,1);
	NEWMIII(Resps->JPEG,struct tt__JpegOptions,1);
	NEWMIII(Resps->JPEG->FrameRateRange,struct tt__IntRange,1);
	NEWMIII(Resps->JPEG->EncodingIntervalRange,struct tt__IntRange,1);
	NEWMIII(Resps->JPEG->ResolutionsAvailable,struct tt__VideoResolution,1);

// 	NEWMIII(Resps->MPEG4,struct tt__Mpeg4Options,1);
// 	NEWMIII(Resps->MPEG4->EncodingIntervalRange,struct tt__IntRange,1);
// 	NEWMIII(Resps->MPEG4->FrameRateRange,struct tt__IntRange,1);
// 	NEWMIII(Resps->MPEG4->GovLengthRange,struct tt__IntRange,1);
// 	NEWMIII(Resps->MPEG4->ResolutionsAvailable,struct tt__VideoResolution,1);
	NEWMIII(Resps->H264,struct tt__H264Options,1);
	NEWMIII(Resps->H264->EncodingIntervalRange,struct tt__IntRange,1);
	NEWMIII(Resps->H264->FrameRateRange,struct tt__IntRange,1);
	NEWMIII(Resps->H264->GovLengthRange,struct tt__IntRange,1);
	NEWMIII(Resps->H264->ResolutionsAvailable,struct tt__VideoResolution,1);

    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,GetVideoEncConfigOptions);
    if(FALSE==Onvif->CallBackOvf->CallBackMedia->GetVideoEncConfigOptions(
		trt__GetVideoEncoderConfigurationOptions->ConfigurationToken,
        trt__GetVideoEncoderConfigurationOptions->ProfileToken,Options))return SOAP_FAULT;  
	
   Resps->QualityRange					        = (struct tt__IntRange *)&Options->EncQualityRange;

 //Resps->JPEG							    	= (struct tt__JpegOptions*)&Options->EncJpegOptions; //以下三个结构对称
   Resps->JPEG->__sizeResolutionsAvailable		= Options->EncJpegOptions.ResolutionsAvailableSize;
   Resps->JPEG->ResolutionsAvailable	        = Options->EncJpegOptions.ResolutionsAvailable;
   Resps->JPEG->EncodingIntervalRange       	= (struct tt__IntRange*)&Options->EncJpegOptions.EncodingIntervalRange;
   Resps->JPEG->FrameRateRange		        	= (struct tt__IntRange*)&Options->EncJpegOptions.FrameRateRange;

// Resps->MPEG4							    	= (struct tt__Mpeg4Options*)&Options->EncMP4Options;
//    Resps->MPEG4->__sizeResolutionsAvailable     = Options->EncMP4Options.ResolutionsAvailableSize;
//    Resps->MPEG4->__sizeMpeg4ProfilesSupported   = Options->EncMP4Options.Mpeg4ProfilesSupportedSize;
//    Resps->MPEG4->Mpeg4ProfilesSupported			= Options->EncMP4Options.Mpeg4ProfilesSupported;
//    Resps->MPEG4->EncodingIntervalRange          = (struct tt__IntRange*)&Options->EncMP4Options.EncodingIntervalRange;
//    Resps->MPEG4->FrameRateRange                 = (struct tt__IntRange*)&Options->EncMP4Options.FrameRateRange;
//    Resps->MPEG4->GovLengthRange                 = (struct tt__IntRange*)&Options->EncMP4Options.GovLengthRange;
//    Resps->MPEG4->ResolutionsAvailable           = Options->EncMP4Options.ResolutionsAvailables;

// Resps->H264						     	    = (struct tt__H264Options*)&Options->EncAVSOptions;
   Resps->H264->__sizeH264ProfilesSupported     = Options->EncAVSOptions.AVSProfilesSupportedSize;
   Resps->H264->__sizeResolutionsAvailable      = Options->EncAVSOptions.ResolutionsAvailableSize;
   Resps->H264->H264ProfilesSupported			= Options->EncAVSOptions.AVSProfilesSupporteds;
   Resps->H264->ResolutionsAvailable            = Options->EncAVSOptions.ResolutionsAvailables;
   Resps->H264->EncodingIntervalRange           = (struct tt__IntRange*)&Options->EncAVSOptions.EncodingIntervalRange;
   Resps->H264->FrameRateRange                  = (struct tt__IntRange*)&Options->EncAVSOptions.FrameRateRange;
   Resps->H264->GovLengthRange                  = (struct tt__IntRange*)&Options->EncAVSOptions.GovLengthRange;
	
     trt__GetVideoEncoderConfigurationOptionsResponse->Options=Resps;
    return SOAP_OK;
}
//以下为不支持的视频接口
//视频.输入
SOAP_FMAC5 int SOAP_FMAC6 __trt__AddVideoSourceConfiguration(struct soap* hSoap, struct _trt__AddVideoSourceConfiguration *trt__AddVideoSourceConfiguration, struct _trt__AddVideoSourceConfigurationResponse *trt__AddVideoSourceConfigurationResponse)
{	

	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __trt__AddVideoEncoderConfiguration(struct soap* hSoap, struct _trt__AddVideoEncoderConfiguration *trt__AddVideoEncoderConfiguration, struct _trt__AddVideoEncoderConfigurationResponse *trt__AddVideoEncoderConfigurationResponse)
{return SOAP_OK;}
SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveVideoEncoderConfiguration(struct soap* hSoap, struct _trt__RemoveVideoEncoderConfiguration *trt__RemoveVideoEncoderConfiguration, struct _trt__RemoveVideoEncoderConfigurationResponse *trt__RemoveVideoEncoderConfigurationResponse)
{return SOAP_OK;}
SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveVideoSourceConfiguration(struct soap* hSoap, struct _trt__RemoveVideoSourceConfiguration *trt__RemoveVideoSourceConfiguration, struct _trt__RemoveVideoSourceConfigurationResponse *trt__RemoveVideoSourceConfigurationResponse)
{return SOAP_OK;}
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleVideoEncoderConfigurations(struct soap* hSoap, struct _trt__GetCompatibleVideoEncoderConfigurations *trt__GetCompatibleVideoEncoderConfigurations, struct _trt__GetCompatibleVideoEncoderConfigurationsResponse *trt__GetCompatibleVideoEncoderConfigurationsResponse)
{
	printf("[__trt__GetCompatibleVideoEncoderConfigurations].......................................................................................\n");
	   ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
	   NEW(Configs,VIDEOENCCONFIGS);
	   
	   INT     i;   
	   NEWMII(Resps,struct tt__VideoEncoderConfiguration,OVFMAXCHANNEL) ; 
	   for(i=0;i<OVFMAXCHANNEL;i++){
		   NEWMIII(Resps[i].Multicast,struct tt__MulticastConfiguration,1);
		   NEWMIII(Resps[i].Multicast->Address,struct tt__IPAddress,1);
		   NEWMIII(Resps[i].H264,struct tt__H264Configuration,1);
		   NEWMIII(Resps[i].MPEG4,struct tt__Mpeg4Configuration,1);
		   NEWMIII(Resps[i].Resolution,struct tt__VideoResolution,1);
		   NEWMIII(Resps[i].RateControl,struct tt__VideoRateControl,1);
	   }
	   
	   CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,GetVideoEncConfigs);
	   if(FALSE==Onvif->CallBackOvf->CallBackMedia->GetVideoEncConfigs(Configs))return SOAP_FAULT;   
	   for(i=0;i<OVFMAXCHANNEL&&i<Configs->VideoEncConfigSize;i++){
		   Resps[i].Name             = Configs->VideoEncConfigs[i].ConfigName;
		   Resps[i].token            = Configs->VideoEncConfigs[i].ConfigToken;
		   Resps[i].UseCount         = Configs->VideoEncConfigs[i].ConfigUseCount;
		   Resps[i].Encoding         = Configs->VideoEncConfigs[i].EncType;
		   
		   Resps[i].Resolution       = (struct tt__VideoResolution *)&Configs->VideoEncConfigs[i].EncResolution;
		   Resps[i].Quality          = Configs->VideoEncConfigs[i].EncQuality;
		   Resps[i].RateControl      = (struct tt__VideoRateControl*)&Configs->VideoEncConfigs[i].RateControl;
		   Resps[i].MPEG4            = (struct tt__Mpeg4Configuration*)&Configs->VideoEncConfigs[i].ConfigMPEG4;
		   Resps[i].H264             = (struct tt__H264Configuration *)&Configs->VideoEncConfigs[i].ConfigH264; 
		   
		   Resps[i].SessionTimeout   = Configs->VideoEncConfigs[i].RtspSessionTimeout;
		   Resps[i].Multicast->AutoStart                 = Configs->VideoEncConfigs[i].Multicast.AutoStart;
		   Resps[i].Multicast->Port                      = Configs->VideoEncConfigs[i].Multicast.Port;
		   Resps[i].Multicast->TTL                       = Configs->VideoEncConfigs[i].Multicast.TTL;
		   Resps[i].Multicast->Address->Type             = IPTYPE_V4;
	   }
	   
	   trt__GetCompatibleVideoEncoderConfigurationsResponse->__sizeConfigurations =Configs->VideoEncConfigSize;
	   trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations      =Resps;
	return SOAP_OK;}
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleVideoSourceConfigurations(struct soap* hSoap, struct _trt__GetCompatibleVideoSourceConfigurations *trt__GetCompatibleVideoSourceConfigurations, struct _trt__GetCompatibleVideoSourceConfigurationsResponse *trt__GetCompatibleVideoSourceConfigurationsResponse)
{
	ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    NEW(Nodes,VIDEOSOURCECONFIGS);
    INT     i;
    NEWMII(Resp,struct tt__VideoSourceConfiguration,OVFMAXCHANNEL);
	
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,GetVideoSourceConfigs);
    if(FALSE==Onvif->CallBackOvf->CallBackMedia->GetVideoSourceConfigs(Nodes))return SOAP_FAULT;   
    for(i=0;i<OVFMAXCHANNEL&&i<Nodes->ConfigSize;i++){
		Resp[i].Name              = Nodes->VideoSourceConfigs[i].ConfigName;
		Resp[i].token             = Nodes->VideoSourceConfigs[i].ConfigToken;
		Resp[i].SourceToken       = Nodes->VideoSourceConfigs[i].SourceToken;
		Resp[i].UseCount          = Nodes->VideoSourceConfigs[i].ConfigUseCount;
		Resp[i].Bounds            =(struct tt__IntRectangle*) &Nodes->VideoSourceConfigs[i].SourceBounds;//结构相同
		
    }
    trt__GetCompatibleVideoSourceConfigurationsResponse->__sizeConfigurations =Nodes->ConfigSize;
    trt__GetCompatibleVideoSourceConfigurationsResponse->Configurations       =Resp;
	return SOAP_OK;
}
//
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetGuaranteedNumberOfVideoEncoderInstances(struct soap* hSoap, struct _trt__GetGuaranteedNumberOfVideoEncoderInstances *trt__GetGuaranteedNumberOfVideoEncoderInstances, struct _trt__GetGuaranteedNumberOfVideoEncoderInstancesResponse *trt__GetGuaranteedNumberOfVideoEncoderInstancesResponse)
{return SOAP_OK;}

////////////////////////////云台.TACH///////////
SOAP_FMAC5 int SOAP_FMAC6 __trt__AddPTZConfiguration(struct soap* hSoap, struct _trt__AddPTZConfiguration *trt__AddPTZConfiguration, struct _trt__AddPTZConfigurationResponse *trt__AddPTZConfigurationResponse)
{
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;

    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,TachPtz);
    if(FALSE==Onvif->CallBackOvf->CallBackMedia->TachPtz(
        trt__AddPTZConfiguration->ProfileToken,
        trt__AddPTZConfiguration->ConfigurationToken))return SOAP_FAULT; 
	
    return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __trt__RemovePTZConfiguration(struct soap* hSoap, struct _trt__RemovePTZConfiguration *trt__RemovePTZConfiguration, struct _trt__RemovePTZConfigurationResponse *trt__RemovePTZConfigurationResponse)
{
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;

    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,UnTachPtz);
    if(FALSE==Onvif->CallBackOvf->CallBackMedia->UnTachPtz(
        trt__RemovePTZConfiguration->ProfileToken))return SOAP_FAULT;  
    return SOAP_OK;    
 
}

/////////////////////////视频分析////////////////////////////////(暂不支持)
SOAP_FMAC5 int SOAP_FMAC6 __trt__AddVideoAnalyticsConfiguration(struct soap* hSoap, struct _trt__AddVideoAnalyticsConfiguration *trt__AddVideoAnalyticsConfiguration, struct _trt__AddVideoAnalyticsConfigurationResponse *trt__AddVideoAnalyticsConfigurationResponse)
{return SOAP_OK;}

SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveVideoAnalyticsConfiguration(struct soap* hSoap, struct _trt__RemoveVideoAnalyticsConfiguration *trt__RemoveVideoAnalyticsConfiguration, struct _trt__RemoveVideoAnalyticsConfigurationResponse *trt__RemoveVideoAnalyticsConfigurationResponse)
{return SOAP_OK;}
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoAnalyticsConfigurations(struct soap* hSoap, struct _trt__GetVideoAnalyticsConfigurations *trt__GetVideoAnalyticsConfigurations, struct _trt__GetVideoAnalyticsConfigurationsResponse *trt__GetVideoAnalyticsConfigurationsResponse)
{return SOAP_OK;}
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoAnalyticsConfiguration(struct soap* hSoap, struct _trt__GetVideoAnalyticsConfiguration *trt__GetVideoAnalyticsConfiguration, struct _trt__GetVideoAnalyticsConfigurationResponse *trt__GetVideoAnalyticsConfigurationResponse)
{return SOAP_OK;}
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleVideoAnalyticsConfigurations(struct soap* hSoap, struct _trt__GetCompatibleVideoAnalyticsConfigurations *trt__GetCompatibleVideoAnalyticsConfigurations, struct _trt__GetCompatibleVideoAnalyticsConfigurationsResponse *trt__GetCompatibleVideoAnalyticsConfigurationsResponse)
{return SOAP_OK;}
SOAP_FMAC5 int SOAP_FMAC6 __trt__SetVideoAnalyticsConfiguration(struct soap* hSoap, struct _trt__SetVideoAnalyticsConfiguration *trt__SetVideoAnalyticsConfiguration, struct _trt__SetVideoAnalyticsConfigurationResponse *trt__SetVideoAnalyticsConfigurationResponse)
{return SOAP_OK;}

///////////////////////Metadata数据/////////////////////////////(暂不支持)
SOAP_FMAC5 int SOAP_FMAC6 __trt__AddMetadataConfiguration(struct soap* hSoap, struct _trt__AddMetadataConfiguration *trt__AddMetadataConfiguration, struct _trt__AddMetadataConfigurationResponse *trt__AddMetadataConfigurationResponse)
{return SOAP_OK;}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetMetadataConfigurations(struct soap* hSoap, struct _trt__GetMetadataConfigurations *trt__GetMetadataConfigurations, struct _trt__GetMetadataConfigurationsResponse *trt__GetMetadataConfigurationsResponse)
{return SOAP_OK;}
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetMetadataConfiguration(struct soap* hSoap, struct _trt__GetMetadataConfiguration *trt__GetMetadataConfiguration, struct _trt__GetMetadataConfigurationResponse *trt__GetMetadataConfigurationResponse)
{return SOAP_OK;}
SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveMetadataConfiguration(struct soap* hSoap, struct _trt__RemoveMetadataConfiguration *trt__RemoveMetadataConfiguration, struct _trt__RemoveMetadataConfigurationResponse *trt__RemoveMetadataConfigurationResponse)
{return SOAP_OK;}
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleMetadataConfigurations(struct soap* hSoap, struct _trt__GetCompatibleMetadataConfigurations *trt__GetCompatibleMetadataConfigurations, struct _trt__GetCompatibleMetadataConfigurationsResponse *trt__GetCompatibleMetadataConfigurationsResponse)
{return SOAP_OK;}
SOAP_FMAC5 int SOAP_FMAC6 __trt__SetMetadataConfiguration(struct soap* hSoap, struct _trt__SetMetadataConfiguration *trt__SetMetadataConfiguration, struct _trt__SetMetadataConfigurationResponse *trt__SetMetadataConfigurationResponse)
{return SOAP_OK;}
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetMetadataConfigurationOptions(struct soap* hSoap, struct _trt__GetMetadataConfigurationOptions *trt__GetMetadataConfigurationOptions, struct _trt__GetMetadataConfigurationOptionsResponse *trt__GetMetadataConfigurationOptionsResponse)
{return SOAP_OK;}
//////////////////////////////Stream Profile///////////////////////////////////


///////////////////////媒体///////////////////////////////////////////////////
//媒体.流
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetStreamUri(struct soap* hSoap, struct _trt__GetStreamUri *trt__GetStreamUri, struct _trt__GetStreamUriResponse *trt__GetStreamUriResponse)
{
//	 printf("******************************************************GetStreamUri start**************************************\n");
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;

    NEW(Url,MEDIAURL);
    NEW(Resps ,struct tt__MediaUri);
	NEWMIII(hSoap->fault ,struct SOAP_ENV__Fault,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code,struct SOAP_ENV__Code ,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode,struct SOAP_ENV__Code,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode,struct SOAP_ENV__Code ,1);
		NEWMIII(hSoap->fault->SOAP_ENV__Reason,struct SOAP_ENV__Reason,1);
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,GetStreamURL);
    if(FALSE==Onvif->CallBackOvf->CallBackMedia->GetStreamURL(
        trt__GetStreamUri->ProfileToken,Url))
   {

		hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode->SOAP_ENV__Value ="ter:NoProfile" ;
		hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Value ="ter:InvalidArgVal";
 		hSoap->fault->SOAP_ENV__Reason->SOAP_ENV__Text="The requested ProfileToken does not exist.";

		return SOAP_FAULT;  
	}
	
  Resps->InvalidAfterConnect = Url->InvalidAfterConnect;
	Resps->InvalidAfterReboot  = Url->InvalidAfterReboot;
	Resps->Timeout             = Url->Timeout;
	Resps->Uri                 = Url->MediaUri;

     trt__GetStreamUriResponse->MediaUri =Resps;        
    //  printf("******************************************************GetStreamUri end**************************************\n");
    return SOAP_OK;
 }
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetSnapshotUri(struct soap* hSoap, struct _trt__GetSnapshotUri *trt__GetSnapshotUri, struct _trt__GetSnapshotUriResponse *trt__GetSnapshotUriResponse)
{
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;

    NEW(Url,MEDIAURL);
    NEW(Resps ,struct tt__MediaUri);

    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,GetSnapshotURL);
    if(FALSE==Onvif->CallBackOvf->CallBackMedia->GetSnapshotURL(
        trt__GetSnapshotUri->ProfileToken,Url))return SOAP_FAULT;  
	
    Resps->InvalidAfterConnect = Url->InvalidAfterConnect;
	Resps->InvalidAfterReboot  = Url->InvalidAfterReboot;
	Resps->Timeout             = Url->Timeout;
	Resps->Uri                 = Url->MediaUri;

    trt__GetSnapshotUriResponse->MediaUri =Resps; 
	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __trt__StartMulticastStreaming(struct soap* hSoap, struct _trt__StartMulticastStreaming *trt__StartMulticastStreaming, struct _trt__StartMulticastStreamingResponse *trt__StartMulticastStreamingResponse)
{
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
	NEWMIII(hSoap->fault ,struct SOAP_ENV__Fault,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code,struct SOAP_ENV__Code ,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode,struct SOAP_ENV__Code,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode,struct SOAP_ENV__Code ,1);
		NEWMIII(hSoap->fault->SOAP_ENV__Reason,struct SOAP_ENV__Reason,1);
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,MulticastStreamingStart);
    if(FALSE==Onvif->CallBackOvf->CallBackMedia->MulticastStreamingStart(
        trt__StartMulticastStreaming->ProfileToken)){

		hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode->SOAP_ENV__Value ="ter:NoProfile" ;
		hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Value ="ter:InvalidArgVal";
 		hSoap->fault->SOAP_ENV__Reason->SOAP_ENV__Text="The requested profile token does not exist";

		return SOAP_FAULT;}  
    return SOAP_OK;   
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__StopMulticastStreaming(struct soap* hSoap, struct _trt__StopMulticastStreaming *trt__StopMulticastStreaming, struct _trt__StopMulticastStreamingResponse *trt__StopMulticastStreamingResponse)
{
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;

    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,MulticastStreamingStop);
    if(FALSE==Onvif->CallBackOvf->CallBackMedia->MulticastStreamingStop(
        trt__StopMulticastStreaming->ProfileToken))return SOAP_FAULT;  
    return SOAP_OK;   
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__SetSynchronizationPoint(struct soap* hSoap, struct _trt__SetSynchronizationPoint *trt__SetSynchronizationPoint, struct _trt__SetSynchronizationPointResponse *trt__SetSynchronizationPointResponse)
{
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;

    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackMedia,SetSynchronizationPoint);
    if(FALSE==Onvif->CallBackOvf->CallBackMedia->SetSynchronizationPoint(
        trt__SetSynchronizationPoint->ProfileToken))return SOAP_FAULT;  
    return SOAP_OK;   
}


