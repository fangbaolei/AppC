#ifndef __UPNP_H__
#define __UPNP_H
#ifdef __cplusplus
extern "C" {
#endif

int RoutePortMapping(char *RouteAddr, uint16_t PortSetArr[3], char UPnPEnFlg);


#endif
