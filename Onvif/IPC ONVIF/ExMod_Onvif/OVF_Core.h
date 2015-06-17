//OVF_Core.h

#ifndef OVF_CORE_H
#define OVF_CORE_H
#include "pthread.h"
typedef struct tagONVIF
{
	struct soap  *soapUDP;
	struct soap  *soapTCP;
	VOID         *hOnvifCln;
	pthread_t     threadUDP;
	pthread_t     threadTCP;
	BOOL          IsKeepAliveUDP;
	BOOL          IsKeepAliveTCP;
	USHORT        PortTcpServer;
    CHAR          MessageID [OVFCHARLENTH];
    CHAR          EndpointReference[OVFCHARLENTH];
    CHAR          Namespace [1024];
    CHAR          xAddr     [256 ];
    UINT          Ver;
    UINT          SubVer;
	UINT          LocalIpaddr;//×Ö½ÚË³Ðò
    CALLBACKOVF  *CallBackOvf;
}ONVIF,*LPONVIF;

typedef struct MyIIONVIFK
{
	 struct soap *soap_info;
	 int client;
}MyOnvifInfo;
typedef struct tagONVIFCLN
{
	struct soap  *soapUDP;
	struct soap  *soapTCP;
	pthread_t     threadUDP;
	BOOL          IsKeepAliveUDP;
    CHAR          MessageID [OVFCHARLENTH];
    CHAR          EndpointReference[OVFCHARLENTH];
    CHAR          Namespace [1024];
    CHAR          xAddr     [256 ];
    UINT          Ver;
    UINT          SubVer;
	UINT          LocalIpaddr;//×Ö½ÚË³Ðò
	BOOL          IsCopyByServer;
	VOID*         OnvifServer;
	
}ONVIFCLIENT,*PONVIFCLIENT;
#define STRNCPY(Des,Source,size)\
    if(Source){\
        strncpy(Des,Source,size);\
    }\
	else{;}


#define MEMCPY(Des,Source,size)\
    if(Source && Des) \
        memcpy(Des,Source,size)

#define GETPOINTVAL(Des,Source)\
    if(Des&&Source)\
        Des =*Source
        
#define CHECK_CALLBACKFUC(OvfCallBack,SvType,FuncName)\
    if(NULL!=OvfCallBack){\
        if(NULL!=OvfCallBack->SvType){\
            if(NULL!=OvfCallBack->SvType->FuncName)\
				{}\
            else\
                return SOAP_FAULT;\
        }else   return SOAP_FAULT;\
    }else       return SOAP_FAULT;

#define NEW(Name,Type)\
   Type *Name =   (Type *)soap_malloc(hSoap,sizeof(Type))

#define NEWCLN(Name,Soap,Type)\
	Type *Name = (Type *)soap_malloc(Soap,sizeof(Type))


#define NEWCLNII(Name,Soap,Type)\
	 Name = (Type *)soap_malloc(Soap,sizeof(Type))

#define NEWCLNIII(Name,Soap,Type,size)\
    Type *Name =   (Type *)soap_malloc(Soap,sizeof(Type)*size)

#define NEWM(Name,Type,size)\
    {\
        int i ;\
        for(i=0;i<size;i++)\
            Name[i]=(Type *)soap_malloc(hSoap,sizeof(Type));\
    }

#define NEWMII(Name,Type,size)\
    Type *Name =   (Type *)soap_malloc(hSoap,sizeof(Type)*size)

#define NEWMIII(Name,Type,size)\
		 Name =   (Type *)soap_malloc(hSoap,sizeof(Type)*size);


  

#endif//OVF_CORE_H

