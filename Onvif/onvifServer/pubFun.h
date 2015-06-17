/*
 * pubFun.h
 *
 *  Created on: Apr 15, 2014
 *      Author: root
 */

#ifndef PUBFUN_H_
#define PUBFUN_H_

//#include <stdio.h>
#include "pubDef.h"

#ifdef _DEBUG_
#define TRACE(fmt, ...) \
	    fprintf(stdout, "[file \"%s\": line %d]: "fmt, __FILE__, __LINE__, ## __VA_ARGS__)
#else
#define TRACE(fmt, ...) do {} while (0)
#endif

int g_GetMAC(char *pMAC, const UINT uMACLen);			//get MAC address
int g_GetIP(char *pIP,const UINT uIPLen);					//get IP address
int g_SetIP(const char *pIP);								//set IP address
int g_GetGateway(char *pGateway,const UINT uGatewayLen);		//get gateway
int g_SetGateway(const char *pGateway);							//set gateway


int g_GetMediaURI(char *pURI, const UINT uURILen);			//get URI
#endif /* PUBFUN_H_ */
