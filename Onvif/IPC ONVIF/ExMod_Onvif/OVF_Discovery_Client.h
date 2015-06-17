#ifndef OVF_DISCOVERY_CLIENT_H
#define OVF_DISCOVERY_CLIENT_H

#ifndef HONVIFCLN
#define HONVIFCLN     void *
#endif//HONVIFCLN

#include "OVF_Global.h"

//��ʼ��/ж��
HONVIFCLN        ONVIF_ClnInit                   (ULONG ulIP,USHORT usPort);
BOOL             ONVIF_ClnDeinit                 (HONVIFCLN hOnvifCln);


//�豸����
BOOL             ONVIF_ClnSendHello              (HONVIFCLN hOnvifCln,CHAR * EndPoint,CHAR * ServAddr,CHAR* DeviceType);
BOOL             ONVIF_ClnSendBye                (HONVIFCLN hOnvifCln,CHAR * endpoint,CHAR * ServAddr,CHAR *DeviceType);

#endif //OVF_DISCOVERY_CLIENT_H


