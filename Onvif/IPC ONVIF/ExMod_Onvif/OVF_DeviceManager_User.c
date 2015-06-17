#include "stdsoap2.h"
#include "soapH.h"
#include "soapStub.h"
#include "OVF_Export.h"
#include "OVF_Core.h"
#include "OVF_Discovery.h"
//////////////////////////////用户管理/////////////////////////////////////////////////////
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetRemoteUser(struct soap* hSoap, struct _tds__GetRemoteUser *tds__GetRemoteUser, struct _tds__GetRemoteUserResponse *tds__GetRemoteUserResponse)
{
  	NEW(lpRtUser,struct tt__RemoteUser);
    NEW(RtUser  ,REMOTEUSER);
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,GetRemoteUser);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->GetRemoteUser( RtUser))return SOAP_FAULT;
    
	lpRtUser->Username = RtUser->UserName;
	lpRtUser->Password = RtUser->UserPwd;
	lpRtUser->UseDerivedPassword = RtUser->UserUseDerivedPwd;
//	tds__GetRemoteUserResponse->RemoteUser =lpRtUser; 
    return SOAP_OK;
 }
SOAP_FMAC5 int SOAP_FMAC6 __tds__SetRemoteUser(struct soap* hSoap, struct _tds__SetRemoteUser *tds__SetRemoteUser, struct _tds__SetRemoteUserResponse *tds__SetRemoteUserResponse)
{
  	NEW(lpRtUser,struct tt__RemoteUser);
    NEW(RtUser  ,REMOTEUSER);
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
	
	STRNCPY(RtUser->UserName,lpRtUser->Username,OVFCHARLENTH);
	STRNCPY(RtUser->UserPwd ,lpRtUser->Password,OVFCHARLENTH);
	RtUser->UserUseDerivedPwd=lpRtUser->UseDerivedPassword;
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,SetRemoteUser);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->SetRemoteUser( RtUser))return SOAP_FAULT;
    	
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetUsers(struct soap* hSoap, struct _tds__GetUsers *tds__GetUsers, struct _tds__GetUsersResponse *tds__GetUsersResponse)
{
	struct tt__User         *lpUser[OVFMAXCHANNEL];
    NEW(User,USERS);
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
	INT     i;

    NEWM(lpUser     ,struct tt__User,OVFMAXCHANNEL);

    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,GetUsers);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->GetUsers( User))return SOAP_FAULT;
    for(i=0;i<User->UserSize&&i<OVFMAXCHANNEL;i++){
		lpUser[i]->Username=User->Users[i].UserName;
		lpUser[i]->Password=User->Users[i].UserPwd;
		lpUser[i]->UserLevel=User->Users[i].UserLevel;
    }
    
    return SOAP_OK;
 }

SOAP_FMAC5 int SOAP_FMAC6 __tds__CreateUsers(struct soap* hSoap, struct _tds__CreateUsers *tds__CreateUsers, struct _tds__CreateUsersResponse *tds__CreateUsersResponse)
{
	struct tt__User         *lpUser[OVFMAXCHANNEL];
    NEW(User,USERS);
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
	INT     i;

    NEWM(lpUser     ,struct tt__User,OVFMAXCHANNEL);
  
    for(i=0;i<tds__CreateUsers->__sizeUser&&i<OVFMAXCHANNEL;i++){
		STRNCPY(User->Users[i].UserName,tds__CreateUsers->User[i].Username,OVFCHARLENTH);
		STRNCPY(User->Users[i].UserPwd ,tds__CreateUsers->User[i].Password,OVFCHARLENTH);
		User->Users[i].UserLevel       =tds__CreateUsers->User[i].UserLevel;
		User->UserSize				   =tds__CreateUsers->__sizeUser;
    }
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,AddUsers);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->AddUsers( User))return SOAP_FAULT;

    
	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __tds__DeleteUsers(struct soap* hSoap, struct _tds__DeleteUsers *tds__DeleteUsers, struct _tds__DeleteUsersResponse *tds__DeleteUsersResponse)
{

    NEW(User,USERS);
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
	INT     i;
    
    for(i=0;i<tds__DeleteUsers->__sizeUsername &&i<OVFMAXCHANNEL;i++){
		STRNCPY(User->Users[i].UserName,tds__DeleteUsers->Username[i],OVFCHARLENTH);;

    }
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,DelUsers);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->DelUsers( User))return SOAP_FAULT;
   
    return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __tds__SetUser(struct soap* hSoap, struct _tds__SetUser *tds__SetUser, struct _tds__SetUserResponse *tds__SetUserResponse)
{
    NEW(User,USERS);
    ONVIF  *Onvif      = (ONVIF*)hSoap->hdOnvif;
	INT     i;
	NEWMIII(hSoap->fault ,struct SOAP_ENV__Fault,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code,struct SOAP_ENV__Code ,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode,struct SOAP_ENV__Code,1);
	NEWMIII(hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode,struct SOAP_ENV__Code ,1);
		NEWMIII(hSoap->fault->SOAP_ENV__Reason,struct SOAP_ENV__Reason,1);
    if(NULL != tds__SetUser && NULL != tds__SetUser->User){
		for(i=0;i<tds__SetUser->__sizeUser&&i<OVFMAXCHANNEL;i++){
			STRNCPY(User->Users[i].UserName,tds__SetUser->User[i].Username,OVFCHARLENTH);;
			STRNCPY(User->Users[i].UserPwd ,tds__SetUser->User[i].Password,OVFCHARLENTH);;
			User->Users[i].UserLevel       =tds__SetUser->User[i].UserLevel;
		}
	}
    
    CHECK_CALLBACKFUC(Onvif->CallBackOvf,CallBackDevManage,SetUsers);
    if(FALSE==Onvif->CallBackOvf->CallBackDevManage->SetUsers( User)){

		hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode->SOAP_ENV__Value ="ter:UsernameMissing" ;
		hSoap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Value ="ter:InvalidArgVal";
 		hSoap->fault->SOAP_ENV__Reason->SOAP_ENV__Text="The username Missing.";

		return SOAP_FAULT;
	}
   
    return SOAP_OK;
 }

