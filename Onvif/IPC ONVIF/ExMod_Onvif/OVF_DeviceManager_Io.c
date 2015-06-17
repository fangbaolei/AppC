#include<stdio.h>
#include "stdsoap2.h"
#include "soapH.h"
#include "soapStub.h"
#include "OVF_Export.h"
#include "OVF_Core.h"
#include "OVF_Discovery.h"
////////////////////////////¶Ë¿ÚÁª¶¯////////////////////////////////////
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetRelayOutputs(struct soap* hSoap, struct _tds__GetRelayOutputs *tds__GetRelayOutputs, struct _tds__GetRelayOutputsResponse *tds__GetRelayOutputsResponse)
{
    NEW(Io,IORELAYOUTPUTS);
	NEWMII(lpRelOutput,struct tt__RelayOutput,OVFMAXCHANNEL);
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
	INT     i;

	
	for(i=0;i<OVFMAXCHANNEL;i++)
		NEWMIII(lpRelOutput[i].Properties,struct tt__RelayOutputSettings,1);

    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,GetRelayOutputs);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->GetRelayOutputs( Io))return SOAP_FAULT;
    
	for(i=0;i<Io->IoRelayOutSize&&i<OVFMAXCHANNEL;i++){
		lpRelOutput[i].token							=Io->IoRelayOutputs[i].IoRelayouttoken;
		lpRelOutput[i].Properties->DelayTime			=Io->IoRelayOutputs[i].IoRelayoutputSet.IoDelayTime;
		lpRelOutput[i].Properties->IdleState			=Io->IoRelayOutputs[i].IoRelayoutputSet.IoIdleState;
		lpRelOutput[i].Properties->Mode					=Io->IoRelayOutputs[i].IoRelayoutputSet.IoRelayMode;
	}
	tds__GetRelayOutputsResponse->__sizeRelayOutputs	= Io->IoRelayOutSize;
	tds__GetRelayOutputsResponse->RelayOutputs			= lpRelOutput;
  printf("===============================================__tds__GetRelayOutputs=================================\n");
    return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetRelayOutputSettings(struct soap* hSoap, struct _tds__SetRelayOutputSettings *tds__SetRelayOutputSettings, struct _tds__SetRelayOutputSettingsResponse *tds__SetRelayOutputSettingsResponse)
{
    NEW(IoSet,IORELAYOUTPUTSET);
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
	if (tds__SetRelayOutputSettings->Properties != NULL ){
		IoSet->IoIdleState = tds__SetRelayOutputSettings->Properties->IdleState;
		IoSet->IoRelayMode = tds__SetRelayOutputSettings->Properties->Mode; 	
		STRNCPY(IoSet->IoDelayTime,tds__SetRelayOutputSettings->Properties->DelayTime,OVFCHARLENTH); 
	}  	

    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,SetRelayOutput);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->SetRelayOutput(tds__SetRelayOutputSettings->RelayOutputToken,IoSet))return SOAP_FAULT;
    printf("===============================================__tds__SetRelayOutputSettings=================================\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetRelayOutputState(struct soap* hSoap, struct _tds__SetRelayOutputState *tds__SetRelayOutputState, struct _tds__SetRelayOutputStateResponse *tds__SetRelayOutputStateResponse)
{
 
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;


    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,SetRelayActive);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->SetRelayActive(tds__SetRelayOutputState->RelayOutputToken,tds__SetRelayOutputState->LogicalState))return SOAP_FAULT;
    printf("===============================================__tds__SetRelayOutputState=================================\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SendAuxiliaryCommand(struct soap* hSoap, struct _tds__SendAuxiliaryCommand *tds__SendAuxiliaryCommand, struct _tds__SendAuxiliaryCommandResponse *tds__SendAuxiliaryCommandResponse)
{
	printf("===============================================__tds__SendAuxiliaryCommand=================================\n");
	return SOAP_OK;
}

