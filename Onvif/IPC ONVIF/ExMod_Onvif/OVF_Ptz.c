#include "stdsoap2.h"
#include "soapH.h"
#include "soapStub.h"
#include "OVF_Export.h"
#include "OVF_Core.h"
#include "OVF_Ptz.h"
SOAP_FMAC5 int SOAP_FMAC6 __tptz__GetServiceCapabilities(struct soap* hSoap, struct _tptz__GetServiceCapabilities *tptz__GetServiceCapabilities, struct _tptz__GetServiceCapabilitiesResponse *tptz__GetServiceCapabilitiesResponse)
{//无明确定义
return SOAP_OK;}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__GetConfigurations(struct soap* hSoap, struct _tptz__GetConfigurations *tptz__GetConfigurations, struct _tptz__GetConfigurationsResponse *tptz__GetConfigurationsResponse)
{
   // struct tt__PTZConfiguration *Resp[OVFMAXCHANNEL];
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    NEW(ptz,PTZCONFIGS);
    INT     i;
    NEWMII(Resp,struct tt__PTZConfiguration,OVFMAXCHANNEL);
	for (i=0;i<OVFMAXCHANNEL;i++){
		NEWMIII(Resp[i].DefaultPTZSpeed,struct tt__PTZSpeed,1);
		NEWMIII(Resp[i].DefaultPTZSpeed->PanTilt,struct tt__Vector2D,1);
		NEWMIII(Resp[i].DefaultPTZSpeed->Zoom,struct tt__Vector1D,1);
		NEWMIII(Resp[i].PanTiltLimits,struct tt__PanTiltLimits,1);
		NEWMIII(Resp[i].PanTiltLimits->Range,struct tt__Space2DDescription,1);
		NEWMIII(Resp[i].ZoomLimits,struct tt__ZoomLimits,1);
		NEWMIII(Resp[i].ZoomLimits->Range,struct tt__Space1DDescription,1);
	}
    
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackPtz,PtzGetConfigs);
    if(FALSE==Onvif->CallBackOvf->CallBackPtz->PtzGetConfigs(ptz))return SOAP_FAULT;   
    for(i=0;i<OVFMAXCHANNEL&&i<ptz->PtzCfgSize;i++){
	Resp[i].Name      = ptz->PtzCfgs[i].PtzCfgName;
	Resp[i].UseCount  = ptz->PtzCfgs[i].PtzCfgUseCount;
	Resp[i].token     = ptz->PtzCfgs[i].PtzCfgToken;
	Resp[i].NodeToken = ptz->PtzCfgs[i].PtzCfgNodeToken;
	Resp[i].DefaultAbsolutePantTiltPositionSpace		= ptz->PtzCfgs[i].DefAbsPantTiltPosSpace;
	Resp[i].DefaultAbsoluteZoomPositionSpace			= ptz->PtzCfgs[i].DefAbsZoomPosSpace;
	Resp[i].DefaultRelativePanTiltTranslationSpace		= ptz->PtzCfgs[i].DefRelativePanTiltTranslationSpace;
	Resp[i].DefaultRelativeZoomTranslationSpace			= ptz->PtzCfgs[i].DefRelativeZoomTranslationSpace;
	Resp[i].DefaultContinuousPanTiltVelocitySpace		= ptz->PtzCfgs[i].DefContinuousPanTiltVelocitySpace;
	Resp[i].DefaultContinuousZoomVelocitySpace			= ptz->PtzCfgs[i].DefContinuousZoomVelocitySpace;
	Resp[i].DefaultPTZSpeed->PanTilt->space				= ptz->PtzCfgs[i].DefPTZSpeed.PanTilt.space;
	Resp[i].DefaultPTZSpeed->PanTilt->x					= ptz->PtzCfgs[i].DefPTZSpeed.PanTilt.x;
	Resp[i].DefaultPTZSpeed->PanTilt->y					= ptz->PtzCfgs[i].DefPTZSpeed.PanTilt.y;
	Resp[i].DefaultPTZSpeed->Zoom->space				= ptz->PtzCfgs[i].DefPTZSpeed.Zoom.space;
	Resp[i].DefaultPTZSpeed->Zoom->x					= ptz->PtzCfgs[i].DefPTZSpeed.Zoom.x;
	Resp[i].DefaultPTZTimeout							= ptz->PtzCfgs[i].DefPTZTimeout;
	Resp[i].PanTiltLimits->Range->URI					= ptz->PtzCfgs[i].LimitsPanTilt.Space2dDespURL;
	Resp[i].PanTiltLimits->Range->XRange				= (struct tt__FloatRange*)&ptz->PtzCfgs[i].LimitsPanTilt.Space2dXRange;
	Resp[i].PanTiltLimits->Range->YRange				= (struct tt__FloatRange*)&ptz->PtzCfgs[i].LimitsPanTilt.Space2dYRange;
	Resp[i].ZoomLimits->Range->URI						= ptz->PtzCfgs[i].LimitsZoom.Space1dURI;
	Resp[i].ZoomLimits->Range->XRange					= (struct tt__FloatRange*)&ptz->PtzCfgs[i].LimitsZoom.Space1XRange;

    }
    tptz__GetConfigurationsResponse->__sizePTZConfiguration=ptz->PtzCfgSize;
    tptz__GetConfigurationsResponse->PTZConfiguration      =Resp;
    return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __tptz__GetConfigurationOptions(struct soap* hSoap, struct _tptz__GetConfigurationOptions *tptz__GetConfigurationOptions, struct _tptz__GetConfigurationOptionsResponse *tptz__GetConfigurationOptionsResponse)
{
   ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
 
   INT    time        =0;  
   NEWMII(StrTimeOut,CHAR,10);
   NEWMII(StrTimeOutMax,CHAR,25);
   NEWMII(StrTimeOutMin,CHAR,25);
   NEW(ConfigOps,PTZCONFIGOPTIONS);
   NEW(Resp,struct tt__PTZConfigurationOptions);
   NEWMIII(Resp->Spaces,struct tt__PTZSpaces,1);
   NEWMIII(Resp->Spaces->AbsolutePanTiltPositionSpace,struct tt__Space2DDescription,1);
   NEWMIII(Resp->Spaces->AbsoluteZoomPositionSpace,struct tt__Space1DDescription,1);
   NEWMIII(Resp->Spaces->PanTiltSpeedSpace,struct tt__Space1DDescription,1);
   NEWMIII(Resp->Spaces->ZoomSpeedSpace,struct tt__Space1DDescription,1);
   NEWMIII(Resp->Spaces->RelativePanTiltTranslationSpace,struct tt__Space2DDescription,1);
   NEWMIII(Resp->Spaces->RelativeZoomTranslationSpace,struct tt__Space1DDescription,1);
   NEWMIII(Resp->PTZTimeout,struct tt__DurationRange,1);
   NEWMIII(Resp->Spaces->ContinuousPanTiltVelocitySpace,struct tt__Space2DDescription,1);
   NEWMIII(Resp->Spaces->ContinuousZoomVelocitySpace,struct tt__Space1DDescription,1);

   CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackPtz,PtzGetConfigOptions);
   if(FALSE==Onvif->CallBackOvf->CallBackPtz->PtzGetConfigOptions(ConfigOps))return SOAP_FAULT;   
   Resp->Spaces->__sizeAbsolutePanTiltPositionSpace				=ConfigOps->Spaces.SizeAbsolutePanTiltPositionSpace;
   Resp->Spaces->AbsolutePanTiltPositionSpace->URI				=ConfigOps->Spaces.AbsolutePanTiltPositionSpace->Space2dDespURL;
   Resp->Spaces->AbsolutePanTiltPositionSpace->XRange           =(struct tt__FloatRange*)&ConfigOps->Spaces.AbsolutePanTiltPositionSpace->Space2dXRange;
   Resp->Spaces->AbsolutePanTiltPositionSpace->YRange           =(struct tt__FloatRange*)&ConfigOps->Spaces.AbsolutePanTiltPositionSpace->Space2dYRange;

   Resp->Spaces->__sizeAbsoluteZoomPositionSpace				=ConfigOps->Spaces.SizeAbsoluteZoomPositionSpace;
   Resp->Spaces->AbsoluteZoomPositionSpace->URI					=ConfigOps->Spaces.AbsoluteZoomPositionSpace->Space1dURI;
   Resp->Spaces->AbsoluteZoomPositionSpace->XRange			    =(struct tt__FloatRange*)&ConfigOps->Spaces.AbsoluteZoomPositionSpace->Space1XRange;

   Resp->Spaces->__sizePanTiltSpeedSpace						=ConfigOps->Spaces.SizePanTiltSpeedSpace;
   Resp->Spaces->PanTiltSpeedSpace->URI							=ConfigOps->Spaces.PanTiltSpeedSpace->Space1dURI;
   Resp->Spaces->PanTiltSpeedSpace->XRange					    =(struct tt__FloatRange*)&ConfigOps->Spaces.PanTiltSpeedSpace->Space1XRange;

   Resp->Spaces->__sizeZoomSpeedSpace							=ConfigOps->Spaces.SizeZoomSpeedSpace;
   Resp->Spaces->ZoomSpeedSpace->URI							=ConfigOps->Spaces.ZoomSpeedSpace->Space1dURI;
   Resp->Spaces->ZoomSpeedSpace->XRange					        =(struct tt__FloatRange*)&ConfigOps->Spaces.ZoomSpeedSpace->Space1XRange;

   Resp->Spaces->__sizeRelativePanTiltTranslationSpace			=ConfigOps->Spaces.SizeRelativePanTiltTranslationSpace;
   Resp->Spaces->RelativePanTiltTranslationSpace->URI			=ConfigOps->Spaces.RelativePanTiltTranslationSpace->Space2dDespURL;
   Resp->Spaces->RelativePanTiltTranslationSpace->XRange		=(struct tt__FloatRange*)&ConfigOps->Spaces.RelativePanTiltTranslationSpace->Space2dXRange;
   Resp->Spaces->RelativePanTiltTranslationSpace->YRange		=(struct tt__FloatRange*)&ConfigOps->Spaces.RelativePanTiltTranslationSpace->Space2dYRange;

   Resp->Spaces->__sizeRelativeZoomTranslationSpace				=ConfigOps->Spaces.SizeRelativeZoomTranslationSpace;
   Resp->Spaces->RelativeZoomTranslationSpace->URI				=ConfigOps->Spaces.RelativeZoomTranslationSpace->Space1dURI;
   Resp->Spaces->RelativeZoomTranslationSpace->XRange			=(struct tt__FloatRange*)&ConfigOps->Spaces.RelativeZoomTranslationSpace->Space1XRange;

   Resp->Spaces->__sizeContinuousPanTiltVelocitySpace			=ConfigOps->Spaces.SizeContinuousPanTiltVelocitySpace;
   Resp->Spaces->ContinuousPanTiltVelocitySpace->URI			=ConfigOps->Spaces.ContinuousPanTiltVelocitySpace->Space2dDespURL;
   Resp->Spaces->ContinuousPanTiltVelocitySpace->XRange         =(struct tt__FloatRange*)&ConfigOps->Spaces.ContinuousPanTiltVelocitySpace->Space2dXRange;
   Resp->Spaces->ContinuousPanTiltVelocitySpace->YRange         =(struct tt__FloatRange*)&ConfigOps->Spaces.ContinuousPanTiltVelocitySpace->Space2dYRange;

   Resp->Spaces->__sizeContinuousZoomVelocitySpace              =ConfigOps->Spaces.SizeContinuousZoomVelocitySpace;
   Resp->Spaces->ContinuousZoomVelocitySpace->URI				=ConfigOps->Spaces.ContinuousZoomVelocitySpace->Space1dURI;
   Resp->Spaces->ContinuousZoomVelocitySpace->XRange			=(struct tt__FloatRange*)&ConfigOps->Spaces.ContinuousZoomVelocitySpace->Space1XRange;

	time =(INT)ConfigOps->PTZTimeout.Max/60;
	sprintf(StrTimeOut,"%d",time);
	sprintf(StrTimeOutMax,"PT%sM",StrTimeOut);
	Resp->PTZTimeout->Max =StrTimeOutMax;
	time =(INT)ConfigOps->PTZTimeout.Min;
	sprintf(StrTimeOut,"%d",time);
	sprintf(StrTimeOutMin,"PT%sS",StrTimeOut);
	Resp->PTZTimeout->Min=StrTimeOutMin;
   tptz__GetConfigurationOptionsResponse->PTZConfigurationOptions      =Resp;


    return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __tptz__GetConfiguration(struct soap* hSoap, struct _tptz__GetConfiguration *tptz__GetConfiguration, struct _tptz__GetConfigurationResponse *tptz__GetConfigurationResponse)
{
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    NEW(ptz ,PTZCONFIG);
    NEW(Resp,struct tt__PTZConfiguration);
	NEWMIII(Resp->DefaultPTZSpeed,struct tt__PTZSpeed,1);
	NEWMIII(Resp->DefaultPTZSpeed->PanTilt,struct tt__Vector2D,1);
	NEWMIII(Resp->DefaultPTZSpeed->Zoom,struct tt__Vector1D,1);
	NEWMIII(Resp->PanTiltLimits,struct tt__PanTiltLimits,1);
	NEWMIII(Resp->PanTiltLimits->Range,struct tt__Space2DDescription,1);
	NEWMIII(Resp->ZoomLimits,struct tt__ZoomLimits,1);
	NEWMIII(Resp->ZoomLimits->Range,struct tt__Space1DDescription,1);
	
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackPtz,PtzGetConfig);
    if(FALSE==Onvif->CallBackOvf->CallBackPtz->PtzGetConfig(tptz__GetConfiguration->PTZConfigurationToken, ptz))return SOAP_FAULT;   
	Resp->Name      = ptz->PtzCfgName;
	Resp->UseCount  = ptz->PtzCfgUseCount;
	Resp->token     = ptz->PtzCfgToken;
	Resp->NodeToken = ptz->PtzCfgNodeToken;
	Resp->DefaultAbsolutePantTiltPositionSpace = ptz->DefAbsPantTiltPosSpace;
	Resp->DefaultAbsoluteZoomPositionSpace     = ptz->DefAbsZoomPosSpace;
	Resp->DefaultRelativePanTiltTranslationSpace = ptz->DefRelativePanTiltTranslationSpace;
	Resp->DefaultRelativeZoomTranslationSpace    = ptz->DefRelativeZoomTranslationSpace;
	Resp->DefaultContinuousPanTiltVelocitySpace  = ptz->DefContinuousPanTiltVelocitySpace;
	Resp->DefaultContinuousZoomVelocitySpace     = ptz->DefContinuousZoomVelocitySpace;
	Resp->DefaultPTZSpeed->PanTilt->space        = ptz->DefPTZSpeed.PanTilt.space;
	Resp->DefaultPTZSpeed->PanTilt->x			 = ptz->DefPTZSpeed.PanTilt.x;
	Resp->DefaultPTZSpeed->PanTilt->y			 = ptz->DefPTZSpeed.PanTilt.y;
	Resp->DefaultPTZSpeed->Zoom->space			 = ptz->DefPTZSpeed.Zoom.space;
	Resp->DefaultPTZSpeed->Zoom->x				 = ptz->DefPTZSpeed.Zoom.x;
	Resp->DefaultPTZTimeout						 = ptz->DefPTZTimeout;
	Resp->PanTiltLimits->Range->URI				 = ptz->LimitsPanTilt.Space2dDespURL;
	Resp->PanTiltLimits->Range->XRange           = (struct tt__FloatRange*)&ptz->LimitsPanTilt.Space2dXRange;
	Resp->PanTiltLimits->Range->YRange			 = (struct tt__FloatRange*)&ptz->LimitsPanTilt.Space2dYRange;
	Resp->ZoomLimits->Range->URI				 = ptz->LimitsZoom.Space1dURI;
	Resp->ZoomLimits->Range->XRange				 = (struct tt__FloatRange*)&ptz->LimitsZoom.Space1XRange;

    tptz__GetConfigurationResponse->PTZConfiguration     =Resp;
    
    return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __tptz__SetConfiguration(struct soap* hSoap, struct _tptz__SetConfiguration *tptz__SetConfiguration, struct _tptz__SetConfigurationResponse *tptz__SetConfigurationResponse)
{
	struct tt__PTZConfiguration *Req; 
	
    
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    NEW (Config,PTZCONFIG);
	NEWMIII(hSoap->fault ,struct SOAP_ENV__Fault,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code,struct SOAP_ENV__Code ,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode,struct SOAP_ENV__Code,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode,struct SOAP_ENV__Code ,1);
		NEWMIII(hSoap->fault->SOAP_ENV__Reason,struct SOAP_ENV__Reason,1);
	if(NULL != tptz__SetConfiguration)
	{
		Req	=tptz__SetConfiguration->PTZConfiguration;
		if(NULL != Req){
			STRNCPY(Config->PtzCfgName ,Req->Name,OVFCHARLENTH);
			Config->PtzCfgUseCount=Req->UseCount;
			STRNCPY(Config->DefPTZTimeout,Req->DefaultPTZTimeout,OVFCHARLENTH);
			STRNCPY(Config->PtzCfgToken,Req->token,OVFCHARLENTH);
		}
	}	
	
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackPtz,PtzSetConfig);
    if(FALSE==Onvif->CallBackOvf->CallBackPtz->PtzSetConfig(Req->token, Config)){
		hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode->SOAP_ENV__Value ="ter:NoConfig" ;
		hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Value ="ter:InvalidArgVal";
 		hSoap->fault->SOAP_ENV__Reason->SOAP_ENV__Text="The configuration does not exist. ";
		return SOAP_FAULT;
	}  
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__GetNodes(struct soap* hSoap, struct _tptz__GetNodes *tptz__GetNodes, struct _tptz__GetNodesResponse *tptz__GetNodesResponse)
{
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    NEW(node,PTZNODES);
    INT     i;
    NEWMII(Resp,struct tt__PTZNode,OVFMAXCHANNEL);
	for (i=0;i<OVFMAXCHANNEL;i++){
		NEWMIII(Resp[i].SupportedPTZSpaces,struct tt__PTZSpaces,1);
		NEWMIII(Resp[i].SupportedPTZSpaces->AbsolutePanTiltPositionSpace,struct tt__Space2DDescription ,1);
		NEWMIII(Resp[i].SupportedPTZSpaces->AbsoluteZoomPositionSpace,struct tt__Space1DDescription,1);
		NEWMIII(Resp[i].SupportedPTZSpaces->PanTiltSpeedSpace,struct tt__Space1DDescription ,1);
		NEWMIII(Resp[i].SupportedPTZSpaces->ZoomSpeedSpace,struct tt__Space1DDescription ,1);
		NEWMIII(Resp[i].SupportedPTZSpaces->RelativePanTiltTranslationSpace,struct tt__Space2DDescription,1);
		NEWMIII(Resp[i].SupportedPTZSpaces->RelativeZoomTranslationSpace,struct tt__Space1DDescription,1);
		NEWMIII(Resp[i].SupportedPTZSpaces->ContinuousPanTiltVelocitySpace,struct tt__Space2DDescription,1);
		NEWMIII(Resp[i].SupportedPTZSpaces->ContinuousZoomVelocitySpace,struct tt__Space1DDescription,1);
	}

    
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackPtz,PtzGetNodes);
    if(FALSE==Onvif->CallBackOvf->CallBackPtz->PtzGetNodes(node))return SOAP_FAULT;   
    for(i=0;i<OVFMAXCHANNEL&&i<node->NodeSize;i++){
		Resp[i].token                      = node->Nodes[i].Nodetoken;
		Resp[i].Name                       = node->Nodes[i].NodeName;
		Resp[i].MaximumNumberOfPresets     = 255;//node->Nodes[i].MaxPresets;
		Resp[i].HomeSupported              = node->Nodes[i].HomeSupported;
 		Resp[i].__sizeAuxiliaryCommands    = node->Nodes[i].AuxCommandsSize;
		Resp[i].AuxiliaryCommands          = (CHAR**)node->Nodes[i].AuxCommands;   

		Resp[i].SupportedPTZSpaces->__sizeAbsolutePanTiltPositionSpace= node->Nodes[i].NodePTZSpaces.SizeAbsolutePanTiltPositionSpace;
		Resp[i].SupportedPTZSpaces->AbsolutePanTiltPositionSpace->URI = node->Nodes[i].NodePTZSpaces.AbsolutePanTiltPositionSpace->Space2dDespURL;
		Resp[i].SupportedPTZSpaces->AbsolutePanTiltPositionSpace->XRange	=(struct tt__FloatRange*)&node->Nodes[i].NodePTZSpaces.AbsolutePanTiltPositionSpace->Space2dXRange;
		Resp[i].SupportedPTZSpaces->AbsolutePanTiltPositionSpace->YRange	=(struct tt__FloatRange*)&node->Nodes[i].NodePTZSpaces.AbsolutePanTiltPositionSpace->Space2dYRange;

		Resp[i].SupportedPTZSpaces->__sizeAbsoluteZoomPositionSpace			= node->Nodes[i].NodePTZSpaces.SizeAbsoluteZoomPositionSpace;
		Resp[i].SupportedPTZSpaces->AbsoluteZoomPositionSpace->URI			= node->Nodes[i].NodePTZSpaces.AbsoluteZoomPositionSpace->Space1dURI;
		Resp[i].SupportedPTZSpaces->AbsoluteZoomPositionSpace->XRange		= (struct tt__FloatRange*)&node->Nodes[i].NodePTZSpaces.AbsoluteZoomPositionSpace->Space1XRange;


		Resp[i].SupportedPTZSpaces->__sizePanTiltSpeedSpace= node->Nodes[i].NodePTZSpaces.SizePanTiltSpeedSpace;
		Resp[i].SupportedPTZSpaces->PanTiltSpeedSpace->URI = node->Nodes[i].NodePTZSpaces.PanTiltSpeedSpace->Space1dURI;
		Resp[i].SupportedPTZSpaces->PanTiltSpeedSpace->XRange = (struct tt__FloatRange*)&node->Nodes[i].NodePTZSpaces.PanTiltSpeedSpace->Space1XRange;

		Resp[i].SupportedPTZSpaces->__sizeZoomSpeedSpace   = node->Nodes[i].NodePTZSpaces.SizeZoomSpeedSpace;
		Resp[i].SupportedPTZSpaces->ZoomSpeedSpace->URI    = node->Nodes[i].NodePTZSpaces.ZoomSpeedSpace->Space1dURI;	
		Resp[i].SupportedPTZSpaces->ZoomSpeedSpace->XRange = (struct tt__FloatRange*)&node->Nodes[i].NodePTZSpaces.ZoomSpeedSpace->Space1XRange;


		Resp[i].SupportedPTZSpaces->__sizeRelativePanTiltTranslationSpace	  = node->Nodes[i].NodePTZSpaces.SizeRelativePanTiltTranslationSpace;
		Resp[i].SupportedPTZSpaces->RelativePanTiltTranslationSpace->URI	  = node->Nodes[i].NodePTZSpaces.RelativePanTiltTranslationSpace->Space2dDespURL;
		Resp[i].SupportedPTZSpaces->RelativePanTiltTranslationSpace->XRange = (struct tt__FloatRange*)&node->Nodes[i].NodePTZSpaces.RelativePanTiltTranslationSpace->Space2dXRange;
		Resp[i].SupportedPTZSpaces->RelativePanTiltTranslationSpace->YRange = (struct tt__FloatRange*)&node->Nodes[i].NodePTZSpaces.RelativePanTiltTranslationSpace->Space2dYRange;
		
		Resp[i].SupportedPTZSpaces->__sizeRelativeZoomTranslationSpace      = node->Nodes[i].NodePTZSpaces.SizeRelativeZoomTranslationSpace;
		Resp[i].SupportedPTZSpaces->RelativeZoomTranslationSpace->URI       = node->Nodes[i].NodePTZSpaces.RelativeZoomTranslationSpace->Space1dURI;
		Resp[i].SupportedPTZSpaces->RelativeZoomTranslationSpace->XRange	  = (struct tt__FloatRange*)&node->Nodes[i].NodePTZSpaces.RelativeZoomTranslationSpace->Space1XRange;

		Resp[i].SupportedPTZSpaces->__sizeContinuousPanTiltVelocitySpace    = node->Nodes[i].NodePTZSpaces.SizeContinuousPanTiltVelocitySpace;
		Resp[i].SupportedPTZSpaces->ContinuousPanTiltVelocitySpace->URI     = node->Nodes[i].NodePTZSpaces.ContinuousPanTiltVelocitySpace->Space2dDespURL;
		Resp[i].SupportedPTZSpaces->ContinuousPanTiltVelocitySpace->XRange  = (struct tt__FloatRange*)&node->Nodes[i].NodePTZSpaces.ContinuousPanTiltVelocitySpace->Space2dXRange;
		Resp[i].SupportedPTZSpaces->ContinuousPanTiltVelocitySpace->YRange  = (struct tt__FloatRange*)&node->Nodes[i].NodePTZSpaces.ContinuousPanTiltVelocitySpace->Space2dYRange;
		
		Resp[i].SupportedPTZSpaces->__sizeContinuousZoomVelocitySpace		  = node->Nodes[i].NodePTZSpaces.SizeContinuousZoomVelocitySpace;
		Resp[i].SupportedPTZSpaces->ContinuousZoomVelocitySpace->URI		  = node->Nodes[i].NodePTZSpaces.ContinuousZoomVelocitySpace->Space1dURI;
		Resp[i].SupportedPTZSpaces->ContinuousZoomVelocitySpace->XRange	  = (struct tt__FloatRange*)&node->Nodes[i].NodePTZSpaces.ContinuousZoomVelocitySpace->Space1XRange;

    }
    tptz__GetNodesResponse->__sizePTZNode =node->NodeSize;
    tptz__GetNodesResponse->PTZNode       =Resp;
    return SOAP_OK;

}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__GetNode(struct soap* hSoap, struct _tptz__GetNode *tptz__GetNode, struct _tptz__GetNodeResponse *tptz__GetNodeResponse)
{
	
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;

    NEW(node,PTZNODE);
    NEW(Resp,struct tt__PTZNode);
	NEWMIII(Resp->SupportedPTZSpaces,struct tt__PTZSpaces,1);
	NEWMIII(Resp->SupportedPTZSpaces->AbsolutePanTiltPositionSpace,struct tt__Space2DDescription,1);
	NEWMIII(Resp->SupportedPTZSpaces->AbsoluteZoomPositionSpace,struct tt__Space1DDescription,1);
	NEWMIII(Resp->SupportedPTZSpaces->PanTiltSpeedSpace,struct tt__Space1DDescription,1);
	NEWMIII(Resp->SupportedPTZSpaces->ZoomSpeedSpace,struct tt__Space1DDescription,1);
	NEWMIII(Resp->SupportedPTZSpaces->RelativePanTiltTranslationSpace,struct tt__Space2DDescription,1);
	NEWMIII(Resp->SupportedPTZSpaces->RelativeZoomTranslationSpace,struct tt__Space1DDescription,1);
	NEWMIII(Resp->SupportedPTZSpaces->ContinuousPanTiltVelocitySpace,struct tt__Space2DDescription,1);
	NEWMIII(Resp->SupportedPTZSpaces->ContinuousZoomVelocitySpace,struct tt__Space1DDescription,1);

	NEWMIII(hSoap->fault ,struct SOAP_ENV__Fault,1);
		NEWMIII(hSoap->fault->SOAP_ENV__Code,struct SOAP_ENV__Code ,1);
		NEWMIII(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode,struct SOAP_ENV__Code,1);
		NEWMIII(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode,struct SOAP_ENV__Code ,1);
		NEWMIII(hSoap->fault->SOAP_ENV__Reason,struct SOAP_ENV__Reason,1);
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackPtz,PtzGetNode);
    if(FALSE==Onvif->CallBackOvf->CallBackPtz->PtzGetNode(tptz__GetNode->NodeToken, node))
	{
		hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode->SOAP_ENV__Value ="ter:NoEntity" ;
 		hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Value ="ter:InvalidArgVal";
 		hSoap->fault->SOAP_ENV__Reason->SOAP_ENV__Text="No such PTZNode on the device .";
		return SOAP_FAULT; 
	}

	Resp->token                      = node->Nodetoken;
	Resp->Name                       = node->NodeName;
	Resp->MaximumNumberOfPresets     = node->MaxPresets;
	Resp->HomeSupported              = node->HomeSupported;
 	Resp->__sizeAuxiliaryCommands    = node->AuxCommandsSize;
	Resp->AuxiliaryCommands          = (CHAR**)node->AuxCommands;   
	Resp->SupportedPTZSpaces->__sizeAbsolutePanTiltPositionSpace   = node->NodePTZSpaces.SizeAbsolutePanTiltPositionSpace;
	Resp->SupportedPTZSpaces->AbsolutePanTiltPositionSpace->URI    = node->NodePTZSpaces.AbsolutePanTiltPositionSpace->Space2dDespURL;
	Resp->SupportedPTZSpaces->AbsolutePanTiltPositionSpace->XRange =(struct tt__FloatRange*)&node->NodePTZSpaces.AbsolutePanTiltPositionSpace->Space2dXRange;
	Resp->SupportedPTZSpaces->AbsolutePanTiltPositionSpace->YRange =(struct tt__FloatRange*)&node->NodePTZSpaces.AbsolutePanTiltPositionSpace->Space2dYRange;

	Resp->SupportedPTZSpaces->__sizeAbsoluteZoomPositionSpace      = node->NodePTZSpaces.SizeAbsoluteZoomPositionSpace;
	Resp->SupportedPTZSpaces->AbsoluteZoomPositionSpace->URI	   = node->NodePTZSpaces.AbsoluteZoomPositionSpace->Space1dURI;
	Resp->SupportedPTZSpaces->AbsoluteZoomPositionSpace->XRange	   = (struct tt__FloatRange*)&node->NodePTZSpaces.AbsoluteZoomPositionSpace->Space1XRange;

	Resp->SupportedPTZSpaces->__sizePanTiltSpeedSpace= node->NodePTZSpaces.SizePanTiltSpeedSpace;
	Resp->SupportedPTZSpaces->PanTiltSpeedSpace->URI = node->NodePTZSpaces.PanTiltSpeedSpace->Space1dURI;
	Resp->SupportedPTZSpaces->PanTiltSpeedSpace->XRange = (struct tt__FloatRange*)&node->NodePTZSpaces.PanTiltSpeedSpace->Space1XRange;

	Resp->SupportedPTZSpaces->__sizeZoomSpeedSpace   = node->NodePTZSpaces.SizeZoomSpeedSpace;
	Resp->SupportedPTZSpaces->ZoomSpeedSpace->URI     = node->NodePTZSpaces.ZoomSpeedSpace->Space1dURI;
	Resp->SupportedPTZSpaces->ZoomSpeedSpace->XRange = (struct tt__FloatRange*)&node->NodePTZSpaces.ZoomSpeedSpace->Space1XRange;

	Resp->SupportedPTZSpaces->__sizeRelativePanTiltTranslationSpace	  = node->NodePTZSpaces.SizeRelativePanTiltTranslationSpace;
	Resp->SupportedPTZSpaces->RelativePanTiltTranslationSpace->URI	  = node->NodePTZSpaces.RelativePanTiltTranslationSpace->Space2dDespURL;
	Resp->SupportedPTZSpaces->RelativePanTiltTranslationSpace->XRange = (struct tt__FloatRange*)&node->NodePTZSpaces.RelativePanTiltTranslationSpace->Space2dXRange;
	Resp->SupportedPTZSpaces->RelativePanTiltTranslationSpace->YRange = (struct tt__FloatRange*)&node->NodePTZSpaces.RelativePanTiltTranslationSpace->Space2dYRange;

	Resp->SupportedPTZSpaces->__sizeRelativeZoomTranslationSpace      = node->NodePTZSpaces.SizeRelativeZoomTranslationSpace;
	Resp->SupportedPTZSpaces->RelativeZoomTranslationSpace->URI       = node->NodePTZSpaces.RelativeZoomTranslationSpace->Space1dURI;
	Resp->SupportedPTZSpaces->RelativeZoomTranslationSpace->XRange	  = (struct tt__FloatRange*)&node->NodePTZSpaces.RelativeZoomTranslationSpace->Space1XRange;

	Resp->SupportedPTZSpaces->__sizeContinuousPanTiltVelocitySpace    = node->NodePTZSpaces.SizeContinuousPanTiltVelocitySpace;
	Resp->SupportedPTZSpaces->ContinuousPanTiltVelocitySpace->URI     = node->NodePTZSpaces.ContinuousPanTiltVelocitySpace->Space2dDespURL;
	Resp->SupportedPTZSpaces->ContinuousPanTiltVelocitySpace->XRange  = (struct tt__FloatRange*)&node->NodePTZSpaces.ContinuousPanTiltVelocitySpace->Space2dXRange;
	Resp->SupportedPTZSpaces->ContinuousPanTiltVelocitySpace->YRange  = (struct tt__FloatRange*)&node->NodePTZSpaces.ContinuousPanTiltVelocitySpace->Space2dYRange;

	Resp->SupportedPTZSpaces->__sizeContinuousZoomVelocitySpace		  = node->NodePTZSpaces.SizeContinuousZoomVelocitySpace;
	Resp->SupportedPTZSpaces->ContinuousZoomVelocitySpace->URI		  = node->NodePTZSpaces.ContinuousZoomVelocitySpace->Space1dURI;
	Resp->SupportedPTZSpaces->ContinuousZoomVelocitySpace->XRange	  = (struct tt__FloatRange*)&node->NodePTZSpaces.ContinuousZoomVelocitySpace->Space1XRange;


    tptz__GetNodeResponse->PTZNode      =Resp;    
	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __tptz__GetPresets(struct soap* hSoap, struct _tptz__GetPresets *tptz__GetPresets, struct _tptz__GetPresetsResponse *tptz__GetPresetsResponse)
{
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    NEW(Prest,PTZPRESETS);
    INT     i;
    NEWMII(Resp,struct tt__PTZPreset,128);
    
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackPtz,PtzGetPresets);
    if(FALSE==Onvif->CallBackOvf->CallBackPtz->PtzGetPresets(tptz__GetPresets->ProfileToken,Prest))return SOAP_FAULT;   
    for(i=0;i<128&&i<Prest->PresetSize;i++){
	Resp[i].token                      = Prest->Presets[i].PresetToken;
	Resp[i].Name                       = Prest->Presets[i].PresetName;
    }
    tptz__GetPresetsResponse->__sizePreset =Prest->PresetSize;
    tptz__GetPresetsResponse->Preset       =Resp;
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__SetPreset(struct soap* hSoap, struct _tptz__SetPreset *tptz__SetPreset, struct _tptz__SetPresetResponse *tptz__SetPresetResponse)
{
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;

    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackPtz,PtzSetPreset);
    if(FALSE==Onvif->CallBackOvf->CallBackPtz->PtzSetPreset(
        tptz__SetPreset->ProfileToken,tptz__SetPreset->PresetToken,tptz__SetPreset->PresetName))return SOAP_FAULT;   
	
   
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__RemovePreset(struct soap* hSoap, struct _tptz__RemovePreset *tptz__RemovePreset, struct _tptz__RemovePresetResponse *tptz__RemovePresetResponse)
{
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
  
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackPtz,PtzRemPreset);
    if(FALSE==Onvif->CallBackOvf->CallBackPtz->PtzRemPreset(
        tptz__RemovePreset->ProfileToken,tptz__RemovePreset->PresetToken))return SOAP_FAULT;   
	    
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__GotoPreset(struct soap* hSoap, struct _tptz__GotoPreset *tptz__GotoPreset, struct _tptz__GotoPresetResponse *tptz__GotoPresetResponse)
{
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;

    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackPtz,PtzGotoPreset);
    if(FALSE==Onvif->CallBackOvf->CallBackPtz->PtzGotoPreset(
        tptz__GotoPreset->ProfileToken,tptz__GotoPreset->PresetToken,NULL))return SOAP_FAULT;   
	    
	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __tptz__GotoHomePosition(struct soap* hSoap, struct _tptz__GotoHomePosition *tptz__GotoHomePosition, struct _tptz__GotoHomePositionResponse *tptz__GotoHomePositionResponse)
{
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;

    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackPtz,PtzGotoHomePosition);
    if(FALSE==Onvif->CallBackOvf->CallBackPtz->PtzGotoHomePosition(
        tptz__GotoHomePosition->ProfileToken,NULL))return SOAP_FAULT;   

    return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__SetHomePosition(struct soap* hSoap, struct _tptz__SetHomePosition *tptz__SetHomePosition, struct _tptz__SetHomePositionResponse *tptz__SetHomePositionResponse)
{
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackPtz,PtzSetHomePosition);
    if(FALSE==Onvif->CallBackOvf->CallBackPtz->PtzSetHomePosition(
        tptz__SetHomePosition->ProfileToken)){

		return SOAP_FAULT;   }

    return SOAP_OK;
 }
SOAP_FMAC5 int SOAP_FMAC6 __tptz__GetStatus(struct soap* hSoap, struct _tptz__GetStatus *tptz__GetStatus, struct _tptz__GetStatusResponse *tptz__GetStatusResponse)
{
	ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
	NEW(Status,PTZSTATUS);
	NEW(Resp,struct tt__PTZStatus);
	NEWMIII(Resp->MoveStatus,struct tt__PTZMoveStatus,1);
	NEWMIII(Resp->Position,struct tt__PTZVector,1);
	NEWMIII(Resp->Position->PanTilt,struct tt__Vector2D,1);
	NEWMIII(Resp->Position->Zoom,struct tt__Vector1D,1);

    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackPtz,PtzGetStatus);
    if(FALSE==Onvif->CallBackOvf->CallBackPtz->PtzGetStatus(
        tptz__GetStatus->ProfileToken,Status))return SOAP_FAULT;  
	Resp->MoveStatus->PanTilt		= &Status->PanTilt;
	Resp->MoveStatus->Zoom			= &Status->Zoom;
	Resp->Position->PanTilt->space	= Status->Position.PanTilt.space;
	Resp->Position->PanTilt->x		= Status->Position.PanTilt.x;
	Resp->Position->PanTilt->y		= Status->Position.PanTilt.y;
	Resp->Position->Zoom->space     = Status->Position.Zoom.space;
	Resp->Position->Zoom->x			= Status->Position.Zoom.x;
	tptz__GetStatusResponse->PTZStatus =Resp;

	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__ContinuousMove(struct soap* hSoap, struct _tptz__ContinuousMove *tptz__ContinuousMove, struct _tptz__ContinuousMoveResponse *tptz__ContinuousMoveResponse)
{return SOAP_OK;}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__RelativeMove(struct soap* hSoap, struct _tptz__RelativeMove *tptz__RelativeMove, struct _tptz__RelativeMoveResponse *tptz__RelativeMoveResponse)
{
	ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
	NEW(MovRel,PTZVECTOR);
	NEW(Speed,PTZSPEED);
	if (NULL != tptz__RelativeMove)
	{
		if(NULL != tptz__RelativeMove->Translation){
			if (NULL != tptz__RelativeMove->Translation->PanTilt){
				STRNCPY(MovRel->PanTilt.space , tptz__RelativeMove->Translation->PanTilt->space,OVFBCHARLENTH);
				MovRel->PanTilt.x     = tptz__RelativeMove->Translation->PanTilt->x;
				MovRel->PanTilt.y     = tptz__RelativeMove->Translation->PanTilt->y;
			}
			if(NULL != tptz__RelativeMove->Translation->Zoom){
				STRNCPY(MovRel->Zoom.space    , tptz__RelativeMove->Translation->Zoom->space,OVFBCHARLENTH);
				MovRel->Zoom.x		  = tptz__RelativeMove->Translation->Zoom->x;
			}
		}
		if(NULL != tptz__RelativeMove->Speed){
			if (NULL != tptz__RelativeMove->Speed->PanTilt){
				STRNCPY(Speed->PanTilt.space , tptz__RelativeMove->Speed->PanTilt->space,OVFBCHARLENTH);
				Speed->PanTilt.x     = tptz__RelativeMove->Speed->PanTilt->x;
				Speed->PanTilt.y     = tptz__RelativeMove->Speed->PanTilt->y;
			}
			if(NULL != tptz__RelativeMove->Speed->Zoom){
				STRNCPY(Speed->Zoom.space    , tptz__RelativeMove->Speed->Zoom->space,OVFBCHARLENTH);
				Speed->Zoom.x		 = tptz__RelativeMove->Speed->Zoom->x;
			}
		}
	}
	CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackPtz,PtzMovRelative);
    if(FALSE==Onvif->CallBackOvf->CallBackPtz->PtzMovRelative(
        tptz__RelativeMove->ProfileToken,MovRel,Speed))return SOAP_FAULT;  

	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__AbsoluteMove(struct soap* hSoap, struct _tptz__AbsoluteMove *tptz__AbsoluteMove, struct _tptz__AbsoluteMoveResponse *tptz__AbsoluteMoveResponse)
{
	ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
	NEW(MovRel,PTZVECTOR);
	NEW(Speed,PTZSPEED);
	NEWMIII(hSoap->fault ,struct SOAP_ENV__Fault,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code,struct SOAP_ENV__Code ,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode,struct SOAP_ENV__Code,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode,struct SOAP_ENV__Code ,1);
		NEWMIII(hSoap->fault->SOAP_ENV__Reason,struct SOAP_ENV__Reason,1);
		if (NULL != tptz__AbsoluteMove)
		{
			if(NULL != tptz__AbsoluteMove->Position){
				if (NULL != tptz__AbsoluteMove->Position->PanTilt){
					STRNCPY(MovRel->PanTilt.space , tptz__AbsoluteMove->Position->PanTilt->space,OVFBCHARLENTH);
					MovRel->PanTilt.x     = tptz__AbsoluteMove->Position->PanTilt->x;
					MovRel->PanTilt.y     = tptz__AbsoluteMove->Position->PanTilt->y;
				}
				if(NULL != tptz__AbsoluteMove->Position->Zoom){
					STRNCPY(MovRel->Zoom.space    , tptz__AbsoluteMove->Position->Zoom->space,OVFBCHARLENTH);
					MovRel->Zoom.x		  = tptz__AbsoluteMove->Position->Zoom->x;
				}
			}
			if(NULL != tptz__AbsoluteMove->Speed){
				if (NULL != tptz__AbsoluteMove->Speed->PanTilt){
					STRNCPY(Speed->PanTilt.space , tptz__AbsoluteMove->Speed->PanTilt->space,OVFBCHARLENTH);
					Speed->PanTilt.x     = tptz__AbsoluteMove->Speed->PanTilt->x;
					Speed->PanTilt.y     = tptz__AbsoluteMove->Speed->PanTilt->y;
				}
				if(NULL != tptz__AbsoluteMove->Speed->Zoom){
					STRNCPY(Speed->Zoom.space    , tptz__AbsoluteMove->Speed->Zoom->space,OVFBCHARLENTH);
					Speed->Zoom.x		 = tptz__AbsoluteMove->Speed->Zoom->x;
				}
			}
		}
	CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackPtz,PtzMovAbsolute); 
	if(FALSE==Onvif->CallBackOvf->CallBackPtz->PtzMovAbsolute(
        tptz__AbsoluteMove->ProfileToken,MovRel,Speed)){

		hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode->SOAP_ENV__Value ="ter:InvalidPosition" ;
		hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Value ="ter:InvalidArgVal";
 		hSoap->fault->SOAP_ENV__Reason->SOAP_ENV__Text="The requested translation is out of bounds.";

		return SOAP_FAULT;
	} 
	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __tptz__SendAuxiliaryCommand(struct soap* hSoap, struct _tptz__SendAuxiliaryCommand *tptz__SendAuxiliaryCommand, struct _tptz__SendAuxiliaryCommandResponse *tptz__SendAuxiliaryCommandResponse)
{
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;

    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackPtz,PtzSendAuxComd);
    if(FALSE==Onvif->CallBackOvf->CallBackPtz->PtzSendAuxComd(
        tptz__SendAuxiliaryCommand->ProfileToken,tptz__SendAuxiliaryCommand->AuxiliaryData))return SOAP_FAULT;   
    
    return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __tptz__Stop(struct soap* hSoap, struct _tptz__Stop *tptz__Stop, struct _tptz__StopResponse *tptz__StopResponse)
{
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;

    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackPtz,PtzStop);
    if(FALSE==Onvif->CallBackOvf->CallBackPtz->PtzStop(
        tptz__Stop->ProfileToken,*tptz__Stop->PanTilt,*tptz__Stop->Zoom))return SOAP_FAULT;   
     
    return SOAP_OK;
}

