#include<stdio.h>
#include<stdlib.h>
#include "stdsoap2.h"
#include "soapH.h"
#include "soapStub.h"
#include "OVF_Export.h"
#include "OVF_Core.h"
#include "OVF_Imaging.h"


SOAP_FMAC5 int SOAP_FMAC6 __timg__GetServiceCapabilities(struct soap* hSoap, struct _timg__GetServiceCapabilities *timg__GetServiceCapabilities, struct _timg__GetServiceCapabilitiesResponse *timg__GetServiceCapabilitiesResponse)
{//参数没有明确定义，暂时不支持
    return SOAP_OK;
}
	
SOAP_FMAC5 int SOAP_FMAC6 __timg__GetOptions(struct soap* hSoap, struct _timg__GetOptions *timg__GetOptions, struct _timg__GetOptionsResponse *timg__GetOptionsResponse)
{
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    NEW(ImgOption,OPTIONSIMAGINGS);
    NEW(Resp,struct tt__ImagingOptions20);	

    CHECK_CALLBACKFUC(Onvif->CallBackOvf, CallBackImaging, ImgGetOptions);
    if(FALSE==Onvif->CallBackOvf->CallBackImaging->ImgGetOptions(timg__GetOptions->VideoSourceToken, ImgOption))
	{
		//printf("[__timg__GetOptions0]................................soap_fault\n");
		//memcpy(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode->SOAP_ENV__Value, "ter:NoSource", sizeof("ter:NoSource"));
		//memcpy(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Value, "ter:InvalidArgVa", sizeof("ter:InvalidArgVa"));
		//memcpy(hSoap->fault->SOAP_ENV__Reason->SOAP_ENV__Text, "The requested VideoSource does not exist.", sizeof("The requested VideoSource does not exist."));
		//printf("hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode->SOAP_ENV__Value = %s\n", hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode->SOAP_ENV__Value);
		//printf("hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Value = %s\n", hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Value);
		//printf("hSoap->fault->SOAP_ENV__Reason->SOAP_ENV__Text = %s\n", hSoap->fault->SOAP_ENV__Reason->SOAP_ENV__Text);
		//printf("[__timg__GetOptions]................................soap_fault\n");
		return SOAP_FAULT;
	}
	
    Resp->Brightness               = (struct tt__FloatRange *)&ImgOption->ImgBrightnessRange; 
	Resp->ColorSaturation          = (struct tt__FloatRange *)&ImgOption->ImgColorSaturationRange;
	Resp->Contrast                 = (struct tt__FloatRange *)&ImgOption->ImgContrastRange;
	Resp->Sharpness                = (struct tt__FloatRange *)&ImgOption->ImgSharpness;
	Resp->__sizeIrCutFilterModes   =  ImgOption->IrCutModeSize;
	Resp->IrCutFilterModes         =  ImgOption->IrCutFilterModes;
	
    timg__GetOptionsResponse->ImagingOptions=Resp;
    
 	//printf("[__timg__GetOptions] Brightness=%f====ColorSaturation=%f===========Contrast=%f=========Sharpness=%f==========\n",Resp->Brightness->Max, Resp->ColorSaturation->Max, Resp->Contrast->Max, Resp->Sharpness->Max);
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __timg__GetImagingSettings(struct soap* hSoap, struct _timg__GetImagingSettings *timg__GetImagingSettings, struct _timg__GetImagingSettingsResponse *timg__GetImagingSettingsResponse)
{
   	ONVIF  *Onvif = (ONVIF*)hSoap->hdOnvif;
    NEW(ImgSetting,OPTIONSIMAGINGS);
    NEW(Resp,struct tt__ImagingSettings20);	

    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackImaging,ImgGetSetting);
    if(FALSE==Onvif->CallBackOvf->CallBackImaging->ImgGetSetting(timg__GetImagingSettings->VideoSourceToken, ImgSetting))
	{
		//printf("[__timg__GetImagingSettings0]................................soap_fault\n");
		//memcpy(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode->SOAP_ENV__Value, "ter:NoSource", sizeof("ter:NoSource"));
		//memcpy(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Value, "ter:InvalidArgVa", sizeof("ter:InvalidArgVa"));
		//memcpy(hSoap->fault->SOAP_ENV__Reason->SOAP_ENV__Text, "The requested VideoSource does not exist.", sizeof("The requested VideoSource does not exist."));
		//printf("hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode->SOAP_ENV__Value = %s\n", hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode->SOAP_ENV__Value);
		//printf("hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Value = %s\n", hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Value);
		//printf("hSoap->fault->SOAP_ENV__Reason->SOAP_ENV__Text = %s\n", hSoap->fault->SOAP_ENV__Reason->SOAP_ENV__Text);
		//printf("[__timg__GetImagingSettings]................................soap_fault\n");
		return SOAP_FAULT;
	}
 
	Resp->Brightness               = &ImgSetting->ImgBrightnessRange.Max;
	Resp->ColorSaturation          = &ImgSetting->ImgColorSaturationRange.Max;
	Resp->Contrast                 = &ImgSetting->ImgContrastRange.Max;
	Resp->Sharpness                = &ImgSetting->ImgSharpness.Max;
	
	Resp->IrCutFilter              = &ImgSetting->IrCutFilterModes[0];
	
    timg__GetImagingSettingsResponse->ImagingSettings=Resp;	
    printf("[__timg__GetImagingSettings] ImgBrightnessRange=%f========ImgColorSaturationRange=%f===ImgContrastRange=%f==ImgSharpness=%f====\n", ImgSetting->ImgBrightnessRange.Max, ImgSetting->ImgColorSaturationRange.Max, ImgSetting->ImgContrastRange.Max, ImgSetting->ImgSharpness.Max);
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __timg__SetImagingSettings(struct soap* hSoap, struct _timg__SetImagingSettings *timg__SetImagingSettings, struct _timg__SetImagingSettingsResponse *timg__SetImagingSettingsResponse)
{
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
	NEW(ImgSetting,OPTIONSIMAGINGS);
	
	ImgSetting->ImgBrightnessRange.Max     = (*(timg__SetImagingSettings->ImagingSettings->Brightness));
	ImgSetting->ImgColorSaturationRange.Max= (*(timg__SetImagingSettings->ImagingSettings->ColorSaturation));
	ImgSetting->ImgContrastRange.Max       = (*(timg__SetImagingSettings->ImagingSettings->Contrast));
	ImgSetting->ImgSharpness.Max           = (*(timg__SetImagingSettings->ImagingSettings->Sharpness));

	printf("[__timg__SetImagingSettings2] Brightness=%f====ColorSaturation=%f==Contrast=%f===Sharpness=%f\n",ImgSetting->ImgBrightnessRange.Max, ImgSetting->ImgColorSaturationRange.Max, ImgSetting->ImgContrastRange.Max, ImgSetting->ImgSharpness.Max);

	CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackImaging,ImgSetSetting);
	if(FALSE==Onvif->CallBackOvf->CallBackImaging->ImgSetSetting(timg__SetImagingSettings->VideoSourceToken, ImgSetting, timg__SetImagingSettings->ForcePersistence_x0020)) 
	{
		//printf("[__timg__SetImagingSettings0]................................soap_fault\n");
		//memcpy(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode->SOAP_ENV__Value, "ter:NoSource", sizeof("ter:NoSource"));
		//memcpy(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Value, "ter:InvalidArgVa", sizeof("ter:InvalidArgVa"));
		//memcpy(hSoap->fault->SOAP_ENV__Reason->SOAP_ENV__Text, "The requested VideoSource does not exist.", sizeof("The requested VideoSource does not exist."));
		//printf("hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode->SOAP_ENV__Value = %s\n", hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode->SOAP_ENV__Value);
		//printf("hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Value = %s\n", hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Value);
		//printf("hSoap->fault->SOAP_ENV__Reason->SOAP_ENV__Text = %s\n", hSoap->fault->SOAP_ENV__Reason->SOAP_ENV__Text);
		//printf("[__timg__SetImagingSettings]................................soap_fault\n");
		return SOAP_FAULT;
	}

	CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackImaging,SetIcut);
	Onvif->CallBackOvf->CallBackImaging->SetIcut(*(timg__SetImagingSettings->ImagingSettings->IrCutFilter)); 

	return SOAP_OK;
}


// 以下函数保留
SOAP_FMAC5 int SOAP_FMAC6 __timg__Move(struct soap* hSoap, struct _timg__Move *timg__Move, struct _timg__MoveResponse *timg__MoveResponse)
{return SOAP_OK;}

SOAP_FMAC5 int SOAP_FMAC6 __timg__Stop(struct soap* hSoap, struct _timg__Stop *timg__Stop, struct _timg__StopResponse *timg__StopResponse)
{return SOAP_OK;}

SOAP_FMAC5 int SOAP_FMAC6 __timg__GetStatus(struct soap* hSoap, struct _timg__GetStatus *timg__GetStatus, struct _timg__GetStatusResponse *timg__GetStatusResponse)
{return SOAP_OK;}

SOAP_FMAC5 int SOAP_FMAC6 __timg__GetMoveOptions(struct soap* hSoap, struct _timg__GetMoveOptions *timg__GetMoveOptions, struct _timg__GetMoveOptionsResponse *timg__GetMoveOptionsResponse)
{return SOAP_OK;}

