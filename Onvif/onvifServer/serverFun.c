/*
 * serverFun.c
 *
 *  Created on: Apr 14, 2014
 *      Author: root
 */

#include "soapH.h"
#include "pubFun.h"

static char g_cHostName[LEN_HOSTNAME] = {"hostname_48"};		//save hostname

static struct tt__Profile g_ProfileList[SIZE_PROFILE];					//save 10 Profile
static UINT g_uProfileCount = 0;									//ProfileListCount


int g_CopyProfile(struct soap* soap,struct tt__Profile *pProfile_Dst, const struct tt__Profile *pProfile_Src)
{
	//copy two profile
	int nReturn = RET_FAILED;
	if( pProfile_Dst == NULL || pProfile_Src == NULL)
	{
		return nReturn;
	}
	if( pProfile_Src->fixed != NULL)
	{
		pProfile_Dst->fixed = (enum xsd__boolean*)soap_malloc(soap,sizeof(enum xsd__boolean));
		*(pProfile_Dst->fixed) = *(pProfile_Src->fixed);
	}
	if( pProfile_Src->Name != NULL)
	{
		pProfile_Dst->Name = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
		strcpy(pProfile_Dst->Name, pProfile_Src->Name);
	}
	if( pProfile_Src->token != NULL)
	{
		pProfile_Dst->token = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
		strcpy(pProfile_Dst->token, pProfile_Src->token);
	}
	if( pProfile_Src->AudioEncoderConfiguration != NULL)
	{
		pProfile_Dst->AudioEncoderConfiguration = (struct tt__AudioEncoderConfiguration*)soap_malloc(soap,sizeof( struct tt__AudioEncoderConfiguration));
		pProfile_Dst->AudioEncoderConfiguration->Bitrate = pProfile_Src->AudioEncoderConfiguration->Bitrate;
		if (pProfile_Src->AudioEncoderConfiguration->Name != NULL)
		{
			pProfile_Dst->AudioEncoderConfiguration->Name = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
			strcpy(pProfile_Dst->AudioEncoderConfiguration->Name,pProfile_Src->AudioEncoderConfiguration->Name);
		}
		pProfile_Dst->AudioEncoderConfiguration->Encoding = pProfile_Src->AudioEncoderConfiguration->Encoding;
		if( pProfile_Src->AudioEncoderConfiguration->Multicast != NULL)
		{
			pProfile_Dst->AudioEncoderConfiguration->Multicast = (struct tt__MulticastConfiguration*)soap_malloc(soap,sizeof(struct tt__MulticastConfiguration));
			pProfile_Dst->AudioEncoderConfiguration->Multicast->TTL = pProfile_Src->AudioEncoderConfiguration->Multicast->TTL;
			if( pProfile_Src->AudioEncoderConfiguration->Multicast->Address != NULL)
			{
				pProfile_Dst->AudioEncoderConfiguration->Multicast->Address == (struct tt__IPAddress*)soap_malloc(soap,sizeof(struct tt__IPAddress));
				pProfile_Dst->AudioEncoderConfiguration->Multicast->Address->Type = pProfile_Src->AudioEncoderConfiguration->Multicast->Address->Type;

		////////////////////////////////////////////////////////////////////////////////////////////
				if(pProfile_Src->AudioEncoderConfiguration->Multicast->Address->IPv4Address != NULL)
				{
					pProfile_Dst->AudioEncoderConfiguration->Multicast->Address->IPv4Address = NULL;
//							trt__GetProfilesResponse->Profiles[i].AudioEncoderConfiguration->Multicast->Address->IPv4Address = (char**)soap_malloc(soap,sizeof(char*));
				}


				if( pProfile_Src->AudioEncoderConfiguration->Multicast->Address->IPv6Address != NULL)
				{
					pProfile_Dst->AudioEncoderConfiguration->Multicast->Address->IPv6Address = NULL;
//							trt__GetProfilesResponse->Profiles[i].AudioEncoderConfiguration->Multicast->Address->IPv6Address = (char**)soap_malloc(soap,sizeof(char*));
				}
		//////////////////////////////////////////////////////////////////////////////////////////////
			}
			pProfile_Dst->AudioEncoderConfiguration->Multicast->AutoStart = pProfile_Src->AudioEncoderConfiguration->Multicast->AutoStart;
			pProfile_Dst->AudioEncoderConfiguration->Multicast->Port = pProfile_Src->AudioEncoderConfiguration->Multicast->Port;
			pProfile_Dst->AudioEncoderConfiguration->Multicast->__size = pProfile_Src->AudioEncoderConfiguration->Multicast->__size;
			pProfile_Dst->AudioEncoderConfiguration->Multicast->__anyAttribute = NULL;
			pProfile_Dst->AudioEncoderConfiguration->Multicast->__any = NULL;
		}
		pProfile_Dst->AudioEncoderConfiguration->SampleRate = pProfile_Src->AudioEncoderConfiguration->SampleRate;
		pProfile_Dst->AudioEncoderConfiguration->SessionTimeout = pProfile_Src->AudioEncoderConfiguration->SessionTimeout;
		pProfile_Dst->AudioEncoderConfiguration->UseCount = pProfile_Src->AudioEncoderConfiguration->UseCount;
		if( pProfile_Src->AudioEncoderConfiguration->token != NULL)
		{
			pProfile_Dst->AudioEncoderConfiguration->token = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
			strcpy(pProfile_Dst->AudioEncoderConfiguration->token, pProfile_Src->AudioEncoderConfiguration->token);
		}
		pProfile_Dst->AudioEncoderConfiguration->__any = NULL;
		pProfile_Dst->AudioEncoderConfiguration->__anyAttribute = NULL;
		pProfile_Dst->AudioEncoderConfiguration->__size = pProfile_Src->AudioEncoderConfiguration->__size;
	}
	if( pProfile_Src->AudioSourceConfiguration != NULL)
	{
		pProfile_Dst->AudioSourceConfiguration = (struct tt__AudioSourceConfiguration*)soap_malloc(soap,sizeof(struct tt__AudioSourceConfiguration));
		if(  pProfile_Src->AudioSourceConfiguration->Name != NULL)
		{
			pProfile_Dst->AudioSourceConfiguration->Name = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
			strcpy(pProfile_Dst->AudioSourceConfiguration->Name, pProfile_Src->AudioSourceConfiguration->Name);
			if( pProfile_Src->AudioSourceConfiguration->SourceToken != NULL)
			{
				pProfile_Dst->AudioSourceConfiguration->SourceToken = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
				strcpy( pProfile_Dst->AudioSourceConfiguration->SourceToken, pProfile_Src->AudioSourceConfiguration->SourceToken);
			}
			pProfile_Dst->AudioSourceConfiguration->UseCount = pProfile_Src->AudioSourceConfiguration->UseCount;
			pProfile_Dst->AudioSourceConfiguration->__any = NULL;
			pProfile_Dst->AudioSourceConfiguration->__anyAttribute = NULL;
			pProfile_Dst->AudioSourceConfiguration->__size = pProfile_Src->AudioSourceConfiguration->__size;
			if( pProfile_Src->AudioSourceConfiguration->token != NULL)
			{
				pProfile_Dst->AudioSourceConfiguration->token = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
				strcpy( pProfile_Dst->AudioSourceConfiguration->token,pProfile_Src->AudioSourceConfiguration->token);
			}
		}
	}
	if( pProfile_Src->VideoSourceConfiguration != NULL)
	{
		pProfile_Dst->VideoSourceConfiguration = (struct tt__VideoSourceConfiguration*)soap_malloc(soap,sizeof(struct tt__VideoSourceConfiguration));
		if( pProfile_Src->VideoSourceConfiguration->SourceToken != NULL)
		{
			pProfile_Dst->VideoSourceConfiguration->SourceToken = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
			strcpy(pProfile_Dst->VideoSourceConfiguration->SourceToken, pProfile_Src->VideoSourceConfiguration->SourceToken);
		}
		if( pProfile_Src->VideoSourceConfiguration->Name != NULL)
		{
			pProfile_Dst->VideoSourceConfiguration->Name = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
			strcpy( pProfile_Dst->VideoSourceConfiguration->Name,pProfile_Src->VideoSourceConfiguration->Name);
		}
		if( pProfile_Src->VideoSourceConfiguration->token != NULL)
		{
			pProfile_Dst->VideoSourceConfiguration->token = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
			strcpy(pProfile_Dst->VideoSourceConfiguration->token,pProfile_Src->VideoSourceConfiguration->token);
		}
		pProfile_Dst->VideoSourceConfiguration->UseCount = pProfile_Src->VideoSourceConfiguration->UseCount;
		if( pProfile_Src->VideoSourceConfiguration->Bounds != NULL)
		{
			pProfile_Dst->VideoSourceConfiguration->Bounds = (struct tt__IntRectangle*)soap_malloc(soap,sizeof(struct tt__IntRectangle));
			pProfile_Dst->VideoSourceConfiguration->Bounds->height = pProfile_Src->VideoSourceConfiguration->Bounds->height;
			pProfile_Dst->VideoSourceConfiguration->Bounds->width = pProfile_Src->VideoSourceConfiguration->Bounds->width;
			pProfile_Dst->VideoSourceConfiguration->Bounds->x = pProfile_Src->VideoSourceConfiguration->Bounds->x;
			pProfile_Dst->VideoSourceConfiguration->Bounds->y = pProfile_Src->VideoSourceConfiguration->Bounds->y;
		}
		pProfile_Dst->VideoSourceConfiguration->__size = pProfile_Src->VideoSourceConfiguration->__size;
		pProfile_Dst->VideoSourceConfiguration->__any = NULL;
		if( pProfile_Src->VideoSourceConfiguration->Extension != NULL)
		{
			pProfile_Dst->VideoSourceConfiguration->Extension = (struct tt__VideoSourceConfigurationExtension*)soap_malloc(soap,sizeof(struct tt__VideoSourceConfigurationExtension));
			if( pProfile_Src->VideoSourceConfiguration->Extension->Rotate != NULL)
			{
				pProfile_Dst->VideoSourceConfiguration->Extension->Rotate = (struct tt__Rotate*)soap_malloc(soap,sizeof(struct tt__Rotate));
				pProfile_Dst->VideoSourceConfiguration->Extension->Rotate->Mode = pProfile_Src->VideoSourceConfiguration->Extension->Rotate->Mode;
				if( pProfile_Src->VideoSourceConfiguration->Extension->Rotate->Extension != NULL)
				{
					pProfile_Dst->VideoSourceConfiguration->Extension->Rotate->Extension = (struct tt__RotateExtension*)soap_malloc(soap,sizeof(struct  tt__RotateExtension));
					pProfile_Dst->VideoSourceConfiguration->Extension->Rotate->Extension->__size = 0;
					pProfile_Dst->VideoSourceConfiguration->Extension->Rotate->Extension->__any = NULL;
				}
				if(pProfile_Src->VideoSourceConfiguration->Extension->Rotate->Degree != NULL)
				{
					pProfile_Dst->VideoSourceConfiguration->Extension->Rotate->Degree = (int*)soap_malloc(soap,sizeof(int));
					*(pProfile_Dst->VideoSourceConfiguration->Extension->Rotate->Degree) = *(pProfile_Src->VideoSourceConfiguration->Extension->Rotate->Degree);
				}
				pProfile_Dst->VideoSourceConfiguration->Extension->Rotate->__anyAttribute = NULL;
			}
			if(pProfile_Src->VideoSourceConfiguration->Extension->Extension != NULL)
			{
				pProfile_Dst->VideoSourceConfiguration->Extension->Extension = (struct tt__VideoSourceConfigurationExtension2*)soap_malloc(soap,sizeof(struct tt__VideoSourceConfigurationExtension2));
				pProfile_Dst->VideoSourceConfiguration->Extension->Extension->__any = NULL;
				pProfile_Dst->VideoSourceConfiguration->Extension->Extension->__size = pProfile_Src->VideoSourceConfiguration->Extension->Extension->__size;
			}
		}
		pProfile_Dst->VideoSourceConfiguration->__anyAttribute = NULL;
	}
	if( pProfile_Src->VideoEncoderConfiguration != NULL)
	{
		pProfile_Dst->VideoEncoderConfiguration = (struct tt__VideoEncoderConfiguration*)soap_malloc(soap,sizeof(struct tt__VideoEncoderConfiguration));
		if( pProfile_Src->VideoEncoderConfiguration->token != NULL)
		{
			pProfile_Dst->VideoEncoderConfiguration->token = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
			strcpy(pProfile_Dst->VideoEncoderConfiguration->token, pProfile_Src->VideoEncoderConfiguration->token);
		}
		if( pProfile_Src->VideoEncoderConfiguration->Name != NULL)
		{
			pProfile_Dst->VideoEncoderConfiguration->Name = (char*)soap_malloc(soap,sizeof(char*) * SMALL_INFO_LENGTH);
			strcpy(pProfile_Dst->VideoEncoderConfiguration->Name, pProfile_Src->VideoEncoderConfiguration->Name);
		}
		pProfile_Dst->VideoEncoderConfiguration->Encoding = pProfile_Src->VideoEncoderConfiguration->Encoding;
		if( pProfile_Src->VideoEncoderConfiguration->H264 != NULL)
		{
			pProfile_Dst->VideoEncoderConfiguration->H264 = (struct tt__H264Configuration*)soap_malloc(soap, sizeof(struct tt__H264Configuration));
			pProfile_Dst->VideoEncoderConfiguration->H264->GovLength = pProfile_Src->VideoEncoderConfiguration->H264->GovLength;
			pProfile_Dst->VideoEncoderConfiguration->H264->H264Profile = pProfile_Src->VideoEncoderConfiguration->H264->H264Profile;
		}
		if( pProfile_Src->VideoEncoderConfiguration->MPEG4 != NULL)
		{
			pProfile_Dst->VideoEncoderConfiguration->MPEG4 = (struct tt__Mpeg4Configuration*)soap_malloc(soap,sizeof(struct tt__Mpeg4Configuration));
			pProfile_Dst->VideoEncoderConfiguration->MPEG4->GovLength = pProfile_Src->VideoEncoderConfiguration->MPEG4->GovLength;
			pProfile_Dst->VideoEncoderConfiguration->MPEG4->Mpeg4Profile = pProfile_Src->VideoEncoderConfiguration->MPEG4->Mpeg4Profile;
		}
		if( pProfile_Src->VideoEncoderConfiguration->Multicast != NULL)
		{
			pProfile_Dst->VideoEncoderConfiguration->Multicast = (struct tt__MulticastConfiguration*)soap_malloc(soap,sizeof(struct tt__MulticastConfiguration));
			if(pProfile_Src->VideoEncoderConfiguration->Multicast->Address != NULL)
			{
				pProfile_Dst->VideoEncoderConfiguration->Multicast->Address = (struct tt__IPAddress*)soap_malloc(soap,sizeof(struct tt__IPAddress));
				pProfile_Dst->VideoEncoderConfiguration->Multicast->Address->Type = pProfile_Src->VideoEncoderConfiguration->Multicast->Address->Type;
				pProfile_Dst->VideoEncoderConfiguration->Multicast->Address->IPv4Address = NULL;
				pProfile_Dst->VideoEncoderConfiguration->Multicast->Address->IPv6Address = NULL;
			}
			pProfile_Dst->VideoEncoderConfiguration->Multicast->AutoStart = pProfile_Src->VideoEncoderConfiguration->Multicast->AutoStart;
			pProfile_Dst->VideoEncoderConfiguration->Multicast->Port = pProfile_Src->VideoEncoderConfiguration->Multicast->Port;
			pProfile_Dst->VideoEncoderConfiguration->Multicast->TTL = pProfile_Src->VideoEncoderConfiguration->Multicast->TTL;
			pProfile_Dst->VideoEncoderConfiguration->Multicast->__any = NULL;
			pProfile_Dst->VideoEncoderConfiguration->Multicast->__anyAttribute = NULL;
			pProfile_Dst->VideoEncoderConfiguration->Multicast->__size = pProfile_Src->VideoEncoderConfiguration->Multicast->__size;
		}
		pProfile_Dst->VideoEncoderConfiguration->Quality = pProfile_Src->VideoEncoderConfiguration->Quality;
		if( pProfile_Src->VideoEncoderConfiguration->RateControl != NULL)
		{
			pProfile_Dst->VideoEncoderConfiguration->RateControl = (struct tt__VideoRateControl*)soap_malloc(soap,sizeof(struct tt__VideoRateControl));
			pProfile_Dst->VideoEncoderConfiguration->RateControl->BitrateLimit = pProfile_Src->VideoEncoderConfiguration->RateControl->BitrateLimit;
			pProfile_Dst->VideoEncoderConfiguration->RateControl->EncodingInterval = pProfile_Src->VideoEncoderConfiguration->RateControl->BitrateLimit;
			pProfile_Dst->VideoEncoderConfiguration->RateControl->FrameRateLimit = pProfile_Src->VideoEncoderConfiguration->RateControl->BitrateLimit;
		}
		if( pProfile_Src->VideoEncoderConfiguration->Resolution != NULL)
		{
			pProfile_Dst->VideoEncoderConfiguration->Resolution = (struct tt__VideoResolution*)soap_malloc(soap,sizeof(struct tt__VideoResolution));
			pProfile_Dst->VideoEncoderConfiguration->Resolution->Height = pProfile_Src->VideoEncoderConfiguration->Resolution->Height;
			pProfile_Dst->VideoEncoderConfiguration->Resolution->Width = pProfile_Src->VideoEncoderConfiguration->Resolution->Width;
		}
		pProfile_Dst->VideoEncoderConfiguration->SessionTimeout = pProfile_Src->VideoEncoderConfiguration->SessionTimeout;
		pProfile_Dst->VideoEncoderConfiguration->UseCount = pProfile_Src->VideoEncoderConfiguration->UseCount;
		pProfile_Dst->VideoEncoderConfiguration->__any = NULL;
		pProfile_Dst->VideoEncoderConfiguration->__anyAttribute = NULL;
		pProfile_Dst->VideoEncoderConfiguration->__size = pProfile_Src->VideoEncoderConfiguration->__size;
	}
	if( pProfile_Src->VideoAnalyticsConfiguration != NULL)
	{
		pProfile_Dst->VideoAnalyticsConfiguration = (struct tt__VideoAnalyticsConfiguration*)soap_malloc(soap,sizeof(struct tt__VideoAnalyticsConfiguration));
		if( pProfile_Src->VideoAnalyticsConfiguration->token != NULL)
		{
			pProfile_Dst->VideoAnalyticsConfiguration->token = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
			strcpy(pProfile_Dst->VideoAnalyticsConfiguration->token,pProfile_Src->VideoAnalyticsConfiguration->token );
		}
		if( pProfile_Src->VideoAnalyticsConfiguration->Name != NULL)
		{
			pProfile_Dst->VideoAnalyticsConfiguration->Name = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
			strcpy(pProfile_Dst->VideoAnalyticsConfiguration->Name,pProfile_Src->VideoAnalyticsConfiguration->Name);
		}
		if( pProfile_Src->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration != NULL)
		{
			pProfile_Dst->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration = (struct tt__AnalyticsEngineConfiguration*)soap_malloc(soap,sizeof(struct tt__AnalyticsEngineConfiguration));
			int nSizeAnalyticsModule = pProfile_Src->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->__sizeAnalyticsModule;
			pProfile_Dst->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->__sizeAnalyticsModule = nSizeAnalyticsModule;
			pProfile_Dst->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->AnalyticsModule = (struct tt__Config*)soap_malloc(soap,sizeof(struct tt__Config) * nSizeAnalyticsModule);
			int i = 0;
			for( i = 0; i < nSizeAnalyticsModule; i++)
			{
				if( pProfile_Src->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Name != NULL)
				{
					pProfile_Dst->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Name = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
					strcpy(pProfile_Dst->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Name, pProfile_Src->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Name);
				}
				if(pProfile_Src->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Type != NULL)
				{
					pProfile_Dst->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Type = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
					strcpy(pProfile_Dst->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Type,pProfile_Src->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Type);
				}
				if( pProfile_Src->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters != NULL)
				{
					pProfile_Dst->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters = (struct tt__ItemList*)soap_malloc(soap, sizeof( struct tt__ItemList));
					pProfile_Dst->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->__anyAttribute = NULL;

					int nSizeElementItem = pProfile_Src->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->__sizeElementItem;
					pProfile_Dst->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->__sizeElementItem = nSizeElementItem;
					if( pProfile_Src->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->ElementItem != NULL)
					{
						pProfile_Dst->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->ElementItem = (struct _tt__ItemList_ElementItem*)soap_malloc(soap, sizeof(struct _tt__ItemList_ElementItem) * nSizeElementItem);
						int j = 0;
						for(j = 0; j < nSizeElementItem; j++)
						{
							if( pProfile_Src->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->ElementItem[j].Name != NULL)
							{
								pProfile_Dst->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->ElementItem[j].Name =
										(char*)soap_malloc(soap, sizeof(char) * SMALL_INFO_LENGTH);
								strcpy(pProfile_Dst->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->ElementItem[j].Name,
										pProfile_Src->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->ElementItem[j].Name);
							}
							if( pProfile_Src->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->ElementItem[j].__any != NULL)
							{
								pProfile_Dst->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->ElementItem[j].__any =
										(char*)soap_malloc(soap, sizeof(char) * SMALL_INFO_LENGTH);
								strcpy( pProfile_Dst->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->ElementItem[j].__any,
										pProfile_Src->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->ElementItem[j].__any);
							}
						}
					}
					int nSizeSimpleItem = pProfile_Src->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->__sizeSimpleItem;
					pProfile_Dst->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->__sizeSimpleItem = nSizeSimpleItem;
					if( pProfile_Src->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->SimpleItem != NULL)
					{
						pProfile_Dst->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->SimpleItem =
								(struct _tt__ItemList_SimpleItem*)soap_malloc(soap,sizeof(struct _tt__ItemList_SimpleItem) * nSizeSimpleItem);
						int j = 0;
						for( j = 0; j <nSizeSimpleItem; j++)
						{
							if( pProfile_Src->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->SimpleItem[j].Name != NULL)
							{
								pProfile_Dst->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->SimpleItem[j].Name =
										(char*)soap_malloc(soap, sizeof(char) * SMALL_INFO_LENGTH);
								strcpy( pProfile_Dst->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->SimpleItem[j].Name,
										pProfile_Src->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->SimpleItem[j].Name);
							}
							if( pProfile_Src->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->SimpleItem[j].Value != NULL)
							{
								pProfile_Dst->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->SimpleItem[j].Value =
										(char*)soap_malloc(soap, sizeof(char) * SMALL_INFO_LENGTH);
								strcpy( pProfile_Dst->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->SimpleItem[j].Value,
										pProfile_Src->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->SimpleItem[j].Value);
							}
						}
					}
					pProfile_Dst->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->Extension = NULL;

				}
			}
			pProfile_Dst->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->Extension = (struct tt__AnalyticsEngineConfigurationExtension*)soap_malloc(soap,sizeof(struct tt__AnalyticsEngineConfigurationExtension));;
			pProfile_Dst->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->Extension->__size = pProfile_Src->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->Extension->__size;
			pProfile_Dst->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->Extension->__any = NULL;
			pProfile_Dst->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->__anyAttribute = NULL;

		}
		if( pProfile_Src->VideoAnalyticsConfiguration->RuleEngineConfiguration != NULL)
		{
			pProfile_Dst->VideoAnalyticsConfiguration->RuleEngineConfiguration = (struct tt__RuleEngineConfiguration*)soap_malloc(soap,sizeof(struct tt__RuleEngineConfiguration));
			int nSizeRule = pProfile_Src->VideoAnalyticsConfiguration->RuleEngineConfiguration->__sizeRule;
			pProfile_Dst->VideoAnalyticsConfiguration->RuleEngineConfiguration->__sizeRule = nSizeRule;
			pProfile_Dst->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule = (struct tt__Config*)soap_malloc(soap,sizeof(struct tt__Config) * nSizeRule);
			int i = 0;
			for( i = 0; i < nSizeRule; i++)
			{
				if( pProfile_Src->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Name != NULL)
				{
					pProfile_Dst->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Name = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
					strcpy(pProfile_Dst->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Name,pProfile_Src->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Name);
				}
				if( pProfile_Src->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Parameters != NULL)
				{
					pProfile_Dst->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Parameters = (struct tt__ItemList*)soap_malloc(soap,sizeof(struct tt__ItemList));
					if( pProfile_Src->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Parameters->__anyAttribute != NULL)
					{
						pProfile_Dst->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Parameters->__anyAttribute = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
						strcpy(pProfile_Dst->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Parameters->__anyAttribute,pProfile_Src->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Parameters->__anyAttribute);
					}
					int nSizeElementItem = pProfile_Src->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Parameters->__sizeElementItem;
					pProfile_Dst->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Parameters->__sizeElementItem = nSizeElementItem;
					if( pProfile_Src->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Parameters->ElementItem != NULL)
					{
						pProfile_Dst->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Parameters->ElementItem = (struct _tt__ItemList_ElementItem*)soap_malloc(soap,sizeof(struct _tt__ItemList_ElementItem) * nSizeElementItem);
						int j = 0;
						for( j = 0; j <  nSizeElementItem; j++)
						{
							if( pProfile_Src->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Parameters->ElementItem[j].Name != NULL)
							{
								pProfile_Dst->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Parameters->ElementItem[j].Name = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
								strcpy(pProfile_Dst->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Parameters->ElementItem[j].Name,pProfile_Src->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Parameters->ElementItem[j].Name);
							}
							if( pProfile_Src->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Parameters->ElementItem[j].__any != NULL)
							{
								pProfile_Dst->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Parameters->ElementItem[j].__any = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
								strcpy(pProfile_Dst->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Parameters->ElementItem[j].__any, pProfile_Src->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Parameters->ElementItem[j].__any);
							}
						}
					}
					int nSizeSimpleItem = pProfile_Src->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Parameters->__sizeSimpleItem;
					pProfile_Dst->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Parameters->__sizeSimpleItem = nSizeSimpleItem;
					if( pProfile_Src->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Parameters->SimpleItem != NULL)
					{
						pProfile_Dst->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Parameters->SimpleItem = (struct _tt__ItemList_SimpleItem*)soap_malloc(soap,sizeof(struct _tt__ItemList_SimpleItem) * nSizeSimpleItem);
						int j = 0;
						for( j = 0; j < nSizeSimpleItem; i++)
						{
							if(pProfile_Src->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Parameters->SimpleItem[j].Name != NULL)
							{
								pProfile_Dst->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Parameters->SimpleItem[j].Name = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
								strcpy(pProfile_Dst->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Parameters->SimpleItem[j].Name,pProfile_Src->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Parameters->SimpleItem[j].Name);
							}
							if( pProfile_Src->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Parameters->SimpleItem[j].Value != NULL)
							{
								pProfile_Dst->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Parameters->SimpleItem[j].Value = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
								strcpy(pProfile_Dst->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Parameters->SimpleItem[j].Value,pProfile_Src->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Parameters->SimpleItem[j].Value);
							}
						}
					}
					if( pProfile_Src->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Parameters->Extension != NULL)
					{
						pProfile_Dst->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Parameters->Extension = (struct tt__ItemListExtension*)soap_malloc(soap,sizeof(struct tt__ItemListExtension));
						pProfile_Dst->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Parameters->Extension->__any = NULL;
						pProfile_Dst->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Parameters->Extension->__size = pProfile_Src->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Parameters->Extension->__size;
					}
				}
				if(pProfile_Src->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Type != NULL)
				{
					pProfile_Dst->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Type = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
					strcpy(pProfile_Dst->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Type,pProfile_Src->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule[i].Type);
				}
			}
			pProfile_Dst->VideoAnalyticsConfiguration->RuleEngineConfiguration->Extension = NULL;
			pProfile_Dst->VideoAnalyticsConfiguration->RuleEngineConfiguration->__anyAttribute = NULL;
		}
		pProfile_Dst->VideoAnalyticsConfiguration->UseCount = pProfile_Src->VideoAnalyticsConfiguration->UseCount;
		pProfile_Dst->VideoAnalyticsConfiguration->__any = NULL;
		pProfile_Dst->VideoAnalyticsConfiguration->__anyAttribute = NULL;
		pProfile_Dst->VideoAnalyticsConfiguration->__size = pProfile_Src->VideoAnalyticsConfiguration->__size;
	}
	if( pProfile_Src->Extension != NULL)
	{
		pProfile_Dst->Extension = (struct tt__ProfileExtension*)soap_malloc(soap,sizeof(struct tt__ProfileExtension));
		if( pProfile_Src->Extension->AudioDecoderConfiguration != NULL)
		{
			pProfile_Dst->Extension->AudioDecoderConfiguration = (struct tt__AudioDecoderConfiguration*)soap_malloc(soap,sizeof(struct tt__AudioDecoderConfiguration));
			if( pProfile_Src->Extension->AudioDecoderConfiguration->Name != NULL)
			{
				pProfile_Dst->Extension->AudioDecoderConfiguration->Name = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
				strcpy(pProfile_Dst->Extension->AudioDecoderConfiguration->Name,pProfile_Src->Extension->AudioDecoderConfiguration->Name);
			}
			if( pProfile_Src->Extension->AudioDecoderConfiguration->token != NULL)
			{
				pProfile_Dst->Extension->AudioDecoderConfiguration->token = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
				strcpy(pProfile_Dst->Extension->AudioDecoderConfiguration->token,pProfile_Src->Extension->AudioDecoderConfiguration->token);
			}
			pProfile_Dst->Extension->AudioDecoderConfiguration->UseCount = pProfile_Src->Extension->AudioDecoderConfiguration->UseCount;
			pProfile_Dst->Extension->AudioDecoderConfiguration->__any = NULL;
			pProfile_Dst->Extension->AudioDecoderConfiguration->__anyAttribute = NULL;
			pProfile_Dst->Extension->AudioDecoderConfiguration->__size = 0;

		}
		if( pProfile_Src->Extension->AudioOutputConfiguration != NULL)
		{
			pProfile_Dst->Extension->AudioOutputConfiguration = (struct tt__AudioOutputConfiguration*)soap_malloc(soap,sizeof( struct tt__AudioOutputConfiguration));
			if( pProfile_Src->Extension->AudioOutputConfiguration->Name != NULL)
			{
				pProfile_Dst->Extension->AudioOutputConfiguration->Name = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
				strcpy(pProfile_Dst->Extension->AudioOutputConfiguration->Name,pProfile_Src->Extension->AudioOutputConfiguration->Name);
			}
			if( pProfile_Dst->Extension->AudioOutputConfiguration->token != NULL)
			{
				pProfile_Dst->Extension->AudioOutputConfiguration->token = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
				strcpy(pProfile_Dst->Extension->AudioOutputConfiguration->token, pProfile_Src->Extension->AudioOutputConfiguration->token);
			}
			pProfile_Dst->Extension->AudioOutputConfiguration->OutputLevel = pProfile_Src->Extension->AudioOutputConfiguration->OutputLevel;
			if( pProfile_Src->Extension->AudioOutputConfiguration->OutputToken != NULL)
			{
				pProfile_Dst->Extension->AudioOutputConfiguration->OutputToken = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
				strcpy(pProfile_Dst->Extension->AudioOutputConfiguration->OutputToken,pProfile_Src->Extension->AudioOutputConfiguration->OutputToken);
			}
			if( pProfile_Src->Extension->AudioOutputConfiguration->SendPrimacy != NULL)
			{
				pProfile_Dst->Extension->AudioOutputConfiguration->SendPrimacy = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
				strcpy(pProfile_Dst->Extension->AudioOutputConfiguration->SendPrimacy,pProfile_Src->Extension->AudioOutputConfiguration->SendPrimacy);
			}
			pProfile_Dst->Extension->AudioOutputConfiguration->UseCount = pProfile_Src->Extension->AudioOutputConfiguration->UseCount;
			pProfile_Dst->Extension->AudioOutputConfiguration->__any = NULL;
			pProfile_Dst->Extension->AudioOutputConfiguration->__anyAttribute = NULL;
			pProfile_Dst->Extension->AudioOutputConfiguration->__size = 0;
		}
		if( pProfile_Src->Extension->Extension != NULL)
		{
			pProfile_Dst->Extension->Extension = (struct tt__ProfileExtension2*)soap_malloc(soap,sizeof(struct tt__ProfileExtension2));
			pProfile_Dst->Extension->Extension->__any = NULL;
			pProfile_Dst->Extension->Extension->__size = 0;
		}
		pProfile_Dst->Extension->__any = NULL;
		pProfile_Dst->Extension->__anyAttribute = NULL;
		pProfile_Dst->Extension->__size = 0;
	}

	if( pProfile_Src->MetadataConfiguration != NULL)
	{
		pProfile_Dst->MetadataConfiguration = (struct tt__MetadataConfiguration*)soap_malloc(soap,sizeof(struct tt__MetadataConfiguration));
		if( pProfile_Src->MetadataConfiguration->token != NULL)
		{
			pProfile_Dst->MetadataConfiguration->token = (char*)soap_malloc(soap,sizeof(char) *  SMALL_INFO_LENGTH);
			strcpy(pProfile_Dst->MetadataConfiguration->token,pProfile_Src->MetadataConfiguration->token);
		}
		if( pProfile_Src->MetadataConfiguration->Name != NULL)
		{
			pProfile_Dst->MetadataConfiguration->Name = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
			strcpy(pProfile_Dst->MetadataConfiguration->Name,pProfile_Src->MetadataConfiguration->Name);
		}
		if( pProfile_Src->MetadataConfiguration->Analytics != NULL)
		{
			pProfile_Dst->MetadataConfiguration->Analytics = (enum xsd__boolean*)soap_malloc(soap,sizeof(enum xsd__boolean));
			*(pProfile_Dst->MetadataConfiguration->Analytics) = *(pProfile_Src->MetadataConfiguration->Analytics);
		}
		if( pProfile_Src->MetadataConfiguration->AnalyticsEngineConfiguration != NULL)
		{
			pProfile_Dst->MetadataConfiguration->AnalyticsEngineConfiguration = (struct tt__AnalyticsEngineConfiguration*)soap_malloc(soap,sizeof(struct tt__AnalyticsEngineConfiguration));
			int nSizeAnalyticsModule = pProfile_Src->MetadataConfiguration->AnalyticsEngineConfiguration->__sizeAnalyticsModule;
			pProfile_Dst->MetadataConfiguration->AnalyticsEngineConfiguration->__sizeAnalyticsModule = nSizeAnalyticsModule;

			if( pProfile_Src->MetadataConfiguration->AnalyticsEngineConfiguration->AnalyticsModule != NULL)
			{
				pProfile_Dst->MetadataConfiguration->AnalyticsEngineConfiguration->AnalyticsModule = (struct tt__Config*)soap_malloc(soap,sizeof(struct tt__Config) * nSizeAnalyticsModule);
				int i = 0;
				for( i = 0; i < nSizeAnalyticsModule; i++)
				{
					if (pProfile_Src->MetadataConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Name!= NULL)
					{
							pProfile_Dst->MetadataConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Name = (char*) soap_malloc(soap, sizeof(char) * SMALL_INFO_LENGTH);
							strcpy( pProfile_Dst->MetadataConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Name, pProfile_Src->MetadataConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Name);
					}
					if( pProfile_Src->MetadataConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters != NULL)
					{
						pProfile_Dst->MetadataConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters = (struct tt__ItemList*)soap_malloc(soap,sizeof(struct tt__ItemList));
						int nSizeElementItem = pProfile_Src->MetadataConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->__sizeElementItem;
						pProfile_Dst->MetadataConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->__sizeElementItem = nSizeElementItem;
						if( pProfile_Src->MetadataConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->ElementItem != NULL)
						{
							int j = 0;
							for( j = 0; j < nSizeElementItem; j++)
							{
								pProfile_Dst->MetadataConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->ElementItem = (struct _tt__ItemList_ElementItem*)soap_malloc(soap,sizeof(struct _tt__ItemList_ElementItem) * nSizeElementItem);
								pProfile_Dst->MetadataConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->ElementItem[j].Name = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
								strcpy(pProfile_Dst->MetadataConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->ElementItem[j].Name, pProfile_Src->MetadataConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->ElementItem[j].Name);
								pProfile_Dst->MetadataConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->ElementItem[j].__any = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
								strcpy( pProfile_Dst->MetadataConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->ElementItem[j].__any, pProfile_Src->MetadataConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->ElementItem[j].__any);
							}
						}
						int nSizeSimpleItem = pProfile_Src->MetadataConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->__sizeSimpleItem;
						pProfile_Dst->MetadataConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->__sizeSimpleItem = nSizeSimpleItem;
						if( pProfile_Src->MetadataConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->SimpleItem != NULL)
						{
							int j = 0;
							for( j = 0; j < nSizeSimpleItem; j++)
							{
								pProfile_Dst->MetadataConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->SimpleItem = (struct _tt__ItemList_SimpleItem*)soap_malloc(soap,sizeof(struct _tt__ItemList_SimpleItem) * nSizeSimpleItem);
								pProfile_Dst->MetadataConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->SimpleItem[i].Name = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
								strcpy(pProfile_Dst->MetadataConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->SimpleItem[j].Name, pProfile_Src->MetadataConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->SimpleItem[j].Name);
								pProfile_Dst->MetadataConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->SimpleItem[j].Value = (char*)soap_malloc(soap, sizeof(char) * SMALL_INFO_LENGTH);
								strcpy(pProfile_Dst->MetadataConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->SimpleItem[j].Value, pProfile_Src->MetadataConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->SimpleItem[j].Value);
							}
						}
						if( pProfile_Src->MetadataConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->Extension != NULL)
						{
							pProfile_Dst->MetadataConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->Extension = NULL;
						}
						pProfile_Dst->MetadataConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Parameters->__anyAttribute = NULL;
					}
					if( pProfile_Src->MetadataConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Type != NULL)
					{
						pProfile_Dst->MetadataConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Type = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
						strcpy(pProfile_Dst->MetadataConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Type, pProfile_Src->MetadataConfiguration->AnalyticsEngineConfiguration->AnalyticsModule[i].Type);
					}
				}
			}
			if( pProfile_Src->MetadataConfiguration->AnalyticsEngineConfiguration->Extension != NULL)
			{
				pProfile_Dst->MetadataConfiguration->AnalyticsEngineConfiguration->Extension = NULL;
			}
			if( pProfile_Src->MetadataConfiguration->AnalyticsEngineConfiguration->__anyAttribute != NULL)
			{
				pProfile_Dst->MetadataConfiguration->AnalyticsEngineConfiguration->__anyAttribute = NULL;
			}
		}
		if( pProfile_Src->MetadataConfiguration->Events != NULL)
		{
			pProfile_Dst->MetadataConfiguration->Events = (struct tt__EventSubscription*)soap_malloc(soap, sizeof(struct tt__EventSubscription));
			if( pProfile_Src->MetadataConfiguration->Events->Filter != NULL)
			{
				pProfile_Dst->MetadataConfiguration->Events->Filter = NULL;
				//...................
			}
			if( pProfile_Src->MetadataConfiguration->Events->SubscriptionPolicy != NULL)
			{
				pProfile_Dst->MetadataConfiguration->Events->SubscriptionPolicy = NULL;
				//..............
			}
			pProfile_Dst->MetadataConfiguration->Events->__any = NULL;
			pProfile_Dst->MetadataConfiguration->Events->__anyAttribute = NULL;
			pProfile_Dst->MetadataConfiguration->Events->__size = 0;
		}
		if( pProfile_Src->MetadataConfiguration->Extension != NULL)
		{
			pProfile_Dst->MetadataConfiguration->Extension = NULL;
			//......
		}
		if( pProfile_Src->MetadataConfiguration->Multicast != NULL)
		{
			pProfile_Dst->MetadataConfiguration->Multicast = (struct tt__MulticastConfiguration*)soap_malloc(soap,sizeof(struct tt__MulticastConfiguration));
			pProfile_Dst->MetadataConfiguration->Multicast->AutoStart = pProfile_Src->MetadataConfiguration->Multicast->AutoStart;
			if( pProfile_Src->MetadataConfiguration->Multicast->Address != NULL)
			{
				pProfile_Dst->MetadataConfiguration->Multicast->Address = (struct tt__IPAddress*)soap_malloc(soap, sizeof(struct tt__IPAddress));
				pProfile_Dst->MetadataConfiguration->Multicast->Address->Type = pProfile_Src->MetadataConfiguration->Multicast->Address->Type;
				pProfile_Dst->MetadataConfiguration->Multicast->Address->IPv4Address = NULL;
				pProfile_Dst->MetadataConfiguration->Multicast->Address->IPv6Address = NULL;
			}
			pProfile_Dst->MetadataConfiguration->Multicast->Port = pProfile_Src->MetadataConfiguration->Multicast->Port;
			pProfile_Dst->MetadataConfiguration->Multicast->TTL = pProfile_Src->MetadataConfiguration->Multicast->TTL;
			pProfile_Dst->MetadataConfiguration->Multicast->__any = NULL;
			pProfile_Dst->MetadataConfiguration->Multicast->__anyAttribute = NULL;
			pProfile_Dst->MetadataConfiguration->Multicast->__size = 0;
		}
		if( pProfile_Src->MetadataConfiguration->PTZStatus != NULL)
		{
			pProfile_Dst->MetadataConfiguration->PTZStatus = (struct tt__PTZFilter*)soap_malloc(soap, sizeof(struct tt__PTZFilter));
			pProfile_Dst->MetadataConfiguration->PTZStatus->__anyAttribute = NULL;
			pProfile_Dst->MetadataConfiguration->PTZStatus->Position = pProfile_Src->MetadataConfiguration->PTZStatus->Position;
			pProfile_Dst->MetadataConfiguration->PTZStatus->Status = pProfile_Src->MetadataConfiguration->PTZStatus->Status;
		}
		pProfile_Dst->MetadataConfiguration->SessionTimeout = pProfile_Src->MetadataConfiguration->SessionTimeout;
		pProfile_Dst->MetadataConfiguration->UseCount = pProfile_Src->MetadataConfiguration->UseCount;
		pProfile_Dst->MetadataConfiguration->__any = NULL;
		pProfile_Dst->MetadataConfiguration->__anyAttribute = NULL;
		pProfile_Dst->MetadataConfiguration->__size = 0;
	}
	if( pProfile_Src->PTZConfiguration != NULL)
	{
		pProfile_Dst->PTZConfiguration = (struct tt__PTZConfiguration*)soap_malloc(soap,sizeof(struct tt__PTZConfiguration));
		if( pProfile_Src->PTZConfiguration->token != NULL)
		{
			pProfile_Dst->PTZConfiguration->token = (char*)soap_malloc(soap, sizeof(char)* SMALL_INFO_LENGTH);
			strcpy(pProfile_Dst->PTZConfiguration->token,pProfile_Src->PTZConfiguration->token);
		}
		if( pProfile_Src->PTZConfiguration->Name != NULL)
		{
			pProfile_Dst->PTZConfiguration->Name = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
			strcpy(pProfile_Dst->PTZConfiguration->Name,pProfile_Src->PTZConfiguration->Name);
		}
		if( pProfile_Src->PTZConfiguration->DefaultAbsolutePantTiltPositionSpace != NULL)
		{
			pProfile_Dst->PTZConfiguration->DefaultAbsolutePantTiltPositionSpace = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
			strcpy( pProfile_Dst->PTZConfiguration->DefaultAbsolutePantTiltPositionSpace,pProfile_Src->PTZConfiguration->DefaultAbsolutePantTiltPositionSpace);
		}
		if( pProfile_Src->PTZConfiguration->DefaultAbsoluteZoomPositionSpace != NULL)
		{
			pProfile_Dst->PTZConfiguration->DefaultAbsoluteZoomPositionSpace = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
			strcpy( pProfile_Dst->PTZConfiguration->DefaultAbsoluteZoomPositionSpace,pProfile_Src->PTZConfiguration->DefaultAbsoluteZoomPositionSpace);
		}
		if( pProfile_Src->PTZConfiguration->DefaultContinuousPanTiltVelocitySpace != NULL)
		{
			pProfile_Dst->PTZConfiguration->DefaultContinuousPanTiltVelocitySpace = (char*)soap_malloc(soap, sizeof(char) * SMALL_INFO_LENGTH);
			strcpy( pProfile_Dst->PTZConfiguration->DefaultContinuousPanTiltVelocitySpace, pProfile_Src->PTZConfiguration->DefaultContinuousPanTiltVelocitySpace);
		}
		if( pProfile_Src->PTZConfiguration->DefaultContinuousZoomVelocitySpace != NULL)
		{
			pProfile_Dst->PTZConfiguration->DefaultContinuousZoomVelocitySpace = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
			strcpy(pProfile_Dst->PTZConfiguration->DefaultContinuousZoomVelocitySpace,pProfile_Src->PTZConfiguration->DefaultContinuousZoomVelocitySpace);
		}
		if( pProfile_Src->PTZConfiguration->DefaultPTZSpeed != NULL)
		{
			pProfile_Dst->PTZConfiguration->DefaultPTZSpeed = (struct tt__PTZSpeed*)soap_malloc(soap, sizeof( struct tt__PTZSpeed));
			if( pProfile_Src->PTZConfiguration->DefaultPTZSpeed->PanTilt != NULL)
			{
				pProfile_Dst->PTZConfiguration->DefaultPTZSpeed->PanTilt = (struct tt__Vector2D*)soap_malloc(soap, sizeof(struct tt__Vector2D));
				pProfile_Dst->PTZConfiguration->DefaultPTZSpeed->PanTilt->space = pProfile_Src->PTZConfiguration->DefaultPTZSpeed->PanTilt->space;
				pProfile_Dst->PTZConfiguration->DefaultPTZSpeed->PanTilt->x = pProfile_Src->PTZConfiguration->DefaultPTZSpeed->PanTilt->x;
				pProfile_Dst->PTZConfiguration->DefaultPTZSpeed->PanTilt->y = pProfile_Src->PTZConfiguration->DefaultPTZSpeed->PanTilt->y;
			}
			if( pProfile_Src->PTZConfiguration->DefaultPTZSpeed->Zoom != NULL)
			{
				pProfile_Dst->PTZConfiguration->DefaultPTZSpeed->Zoom = (struct tt__Vector1D*)soap_malloc(soap, sizeof(struct tt__Vector1D));
				pProfile_Dst->PTZConfiguration->DefaultPTZSpeed->Zoom->space = pProfile_Src->PTZConfiguration->DefaultPTZSpeed->Zoom->space;
				pProfile_Dst->PTZConfiguration->DefaultPTZSpeed->Zoom->x = pProfile_Src->PTZConfiguration->DefaultPTZSpeed->Zoom->x;
			}
		}
		if( pProfile_Src->PTZConfiguration->DefaultPTZTimeout != NULL)
		{
			pProfile_Dst->PTZConfiguration->DefaultPTZTimeout = (LONG64*)soap_malloc(soap, sizeof(LONG64));
			*(pProfile_Dst->PTZConfiguration->DefaultPTZTimeout) = *(pProfile_Src->PTZConfiguration->DefaultPTZTimeout);
		}
		if( pProfile_Src->PTZConfiguration->DefaultRelativePanTiltTranslationSpace != NULL)
		{
			pProfile_Dst->PTZConfiguration->DefaultRelativePanTiltTranslationSpace = (char*)soap_malloc(soap, sizeof(char) * SMALL_INFO_LENGTH);
			strcpy( pProfile_Dst->PTZConfiguration->DefaultRelativePanTiltTranslationSpace, pProfile_Src->PTZConfiguration->DefaultRelativePanTiltTranslationSpace);
		}
		if( pProfile_Src->PTZConfiguration->DefaultRelativeZoomTranslationSpace != NULL)
		{
			pProfile_Dst->PTZConfiguration->DefaultRelativeZoomTranslationSpace = (char*)soap_malloc(soap, sizeof(char) * SMALL_INFO_LENGTH);
			strcpy( pProfile_Dst->PTZConfiguration->DefaultRelativeZoomTranslationSpace, pProfile_Src->PTZConfiguration->DefaultRelativeZoomTranslationSpace);
		}
		pProfile_Dst->PTZConfiguration->Extension = NULL;
		if( pProfile_Src->PTZConfiguration->NodeToken != NULL)
		{
			pProfile_Dst->PTZConfiguration->NodeToken = (char*)soap_malloc(soap, sizeof(char) * SMALL_INFO_LENGTH);
			strcpy( pProfile_Dst->PTZConfiguration->NodeToken, pProfile_Src->PTZConfiguration->NodeToken);
		}
		if( pProfile_Src->PTZConfiguration->PanTiltLimits != NULL)
		{
			pProfile_Dst->PTZConfiguration->PanTiltLimits = (struct tt__PanTiltLimits*)soap_malloc(soap, sizeof(struct tt__PanTiltLimits));
			if( pProfile_Dst->PTZConfiguration->PanTiltLimits->Range != NULL)
			{
				pProfile_Dst->PTZConfiguration->PanTiltLimits->Range = (struct tt__Space2DDescription*)soap_malloc(soap, sizeof(struct tt__Space2DDescription));
				pProfile_Dst->PTZConfiguration->PanTiltLimits->Range->URI = (char*)soap_malloc(soap, sizeof(char) * SMALL_INFO_LENGTH);
				strcpy( pProfile_Dst->PTZConfiguration->PanTiltLimits->Range->URI, pProfile_Src->PTZConfiguration->PanTiltLimits->Range->URI);
				if( pProfile_Src->PTZConfiguration->PanTiltLimits->Range->XRange != NULL)
				{
					pProfile_Dst->PTZConfiguration->PanTiltLimits->Range->XRange = (struct tt__FloatRange*)soap_malloc(soap, sizeof(struct tt__FloatRange));
					pProfile_Dst->PTZConfiguration->PanTiltLimits->Range->XRange->Max = pProfile_Src->PTZConfiguration->PanTiltLimits->Range->XRange->Max;
					pProfile_Dst->PTZConfiguration->PanTiltLimits->Range->XRange->Min = pProfile_Src->PTZConfiguration->PanTiltLimits->Range->XRange->Min;
				}
				if( pProfile_Dst->PTZConfiguration->PanTiltLimits->Range->YRange != NULL)
				{
					pProfile_Dst->PTZConfiguration->PanTiltLimits->Range->YRange = (struct tt__FloatRange*)soap_malloc(soap, sizeof(struct tt__FloatRange));
					pProfile_Dst->PTZConfiguration->PanTiltLimits->Range->YRange->Max = pProfile_Src->PTZConfiguration->PanTiltLimits->Range->YRange->Max;
					pProfile_Dst->PTZConfiguration->PanTiltLimits->Range->YRange->Min = pProfile_Src->PTZConfiguration->PanTiltLimits->Range->YRange->Min;
				}
			}
		}
		pProfile_Dst->PTZConfiguration->UseCount = pProfile_Src->PTZConfiguration->UseCount;
		if( pProfile_Src->PTZConfiguration->ZoomLimits != NULL)
		{
			pProfile_Dst->PTZConfiguration->ZoomLimits = (struct tt__ZoomLimits*)soap_malloc(soap, sizeof( struct tt__ZoomLimits));
			if( pProfile_Src->PTZConfiguration->ZoomLimits->Range != NULL)
			{
				pProfile_Dst->PTZConfiguration->ZoomLimits->Range = (struct tt__Space1DDescription*)soap_malloc(soap, sizeof( struct tt__Space1DDescription));
				if( pProfile_Src->PTZConfiguration->ZoomLimits->Range->URI != NULL)
				{
					pProfile_Dst->PTZConfiguration->ZoomLimits->Range->URI = (char*)soap_malloc(soap, sizeof(char) * SMALL_INFO_LENGTH);
					strcpy( pProfile_Dst->PTZConfiguration->ZoomLimits->Range->URI, pProfile_Src->PTZConfiguration->ZoomLimits->Range->URI);
				}
				if( pProfile_Src->PTZConfiguration->ZoomLimits->Range->XRange != NULL)
				{
					pProfile_Dst->PTZConfiguration->ZoomLimits->Range->XRange = (struct tt__FloatRange*)soap_malloc(soap,sizeof( struct tt__FloatRange));
					pProfile_Dst->PTZConfiguration->ZoomLimits->Range->XRange->Max = pProfile_Src->PTZConfiguration->ZoomLimits->Range->XRange->Max;
					pProfile_Dst->PTZConfiguration->ZoomLimits->Range->XRange->Min = pProfile_Src->PTZConfiguration->ZoomLimits->Range->XRange->Min;
				}
			}
		}
		pProfile_Dst->PTZConfiguration->__anyAttribute = NULL;
	}
	if( pProfile_Src->__anyAttribute != NULL)
	{
		pProfile_Dst->__anyAttribute = NULL;
	}
	return nReturn;
}

SOAP_FMAC5 int SOAP_FMAC6 __wsdd__Hello(struct soap* soap, struct wsdd__HelloType *wsdd__Hello)
{
	TRACE("__wsdd_Hello start\n");
	TRACE("__wsdd_Hello end\n");
	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __wsdd__Bye(struct soap* soap, struct wsdd__ByeType *wsdd__Bye)
{
	TRACE("__wsdd__Bye start\n");
	TRACE("__wsdd_Bye end\n");
	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __wsdd__Probe(struct soap* soap, struct wsdd__ProbeType *wsdd__Probe)
{
	TRACE("__wsdd__Probe start\n");

	char macaddr[6] = {0};
	char _IPAddr[INFO_LENGTH] = {0};
	char _HwId[INFO_LENGTH] = {0};

	wsdd__ProbeMatchesType ProbeMatches;
	ProbeMatches.ProbeMatch = (struct wsdd__ProbeMatchType *)soap_malloc(soap, sizeof(struct wsdd__ProbeMatchType));
	ProbeMatches.ProbeMatch->XAddrs = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
	ProbeMatches.ProbeMatch->Types = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
	ProbeMatches.ProbeMatch->Scopes = (struct wsdd__ScopesType*)soap_malloc(soap,sizeof(struct wsdd__ScopesType));
	ProbeMatches.ProbeMatch->wsa__EndpointReference.ReferenceProperties = (struct wsa__ReferencePropertiesType*)soap_malloc(soap,sizeof(struct wsa__ReferencePropertiesType));
	ProbeMatches.ProbeMatch->wsa__EndpointReference.ReferenceParameters = (struct wsa__ReferenceParametersType*)soap_malloc(soap,sizeof(struct wsa__ReferenceParametersType));
	ProbeMatches.ProbeMatch->wsa__EndpointReference.ServiceName = (struct wsa__ServiceNameType*)soap_malloc(soap,sizeof(struct wsa__ServiceNameType));
	ProbeMatches.ProbeMatch->wsa__EndpointReference.PortType = (char **)soap_malloc(soap, sizeof(char *) * SMALL_INFO_LENGTH);
	ProbeMatches.ProbeMatch->wsa__EndpointReference.__any = (char **)soap_malloc(soap, sizeof(char*) * SMALL_INFO_LENGTH);
	ProbeMatches.ProbeMatch->wsa__EndpointReference.__anyAttribute = (char *)soap_malloc(soap, sizeof(char) * SMALL_INFO_LENGTH);
	ProbeMatches.ProbeMatch->wsa__EndpointReference.Address = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);

	macaddr[0]=0x01;macaddr[1]=0x01;macaddr[2]=0x01;macaddr[3]=0x01;macaddr[4]=0x01;macaddr[5]=0x01;
	sprintf(_HwId,"urn:uuid:2419d68a-2dd2-21b2-a205-%02X%02X%02X%02X%02X%02X",macaddr[0], macaddr[1], macaddr[2], macaddr[3], macaddr[4], macaddr[5]);

	sprintf(_IPAddr, "http://%03d.%03d.%1d.%02d:%d/onvif/device_service", IP_SERVER,PORT_SERVER);
	ProbeMatches.__sizeProbeMatch = 1;
	ProbeMatches.ProbeMatch->Scopes->__item =(char *)soap_malloc(soap, 1024);
	memset(ProbeMatches.ProbeMatch->Scopes->__item,0,sizeof(ProbeMatches.ProbeMatch->Scopes->__item));

	//Scopes MUST BE
	strcat(ProbeMatches.ProbeMatch->Scopes->__item, "onvif://www.onvif.org/type/NetworkVideoTransmitter");

	ProbeMatches.ProbeMatch->Scopes->MatchBy = NULL;
	strcpy(ProbeMatches.ProbeMatch->XAddrs, _IPAddr);
	strcpy(ProbeMatches.ProbeMatch->Types, wsdd__Probe->Types);
	TRACE("wsdd__Probe->Types=%s\n",wsdd__Probe->Types);
	ProbeMatches.ProbeMatch->MetadataVersion = 1;
	//ws-discovery规定 为可选项
	ProbeMatches.ProbeMatch->wsa__EndpointReference.ReferenceProperties->__size = 0;
	ProbeMatches.ProbeMatch->wsa__EndpointReference.ReferenceProperties->__any = NULL;
	ProbeMatches.ProbeMatch->wsa__EndpointReference.ReferenceParameters->__size = 0;
	ProbeMatches.ProbeMatch->wsa__EndpointReference.ReferenceParameters->__any = NULL;

	ProbeMatches.ProbeMatch->wsa__EndpointReference.PortType[0] = (char *)soap_malloc(soap, sizeof(char) * SMALL_INFO_LENGTH);
	//ws-discovery规定 为可选项
	strcpy(ProbeMatches.ProbeMatch->wsa__EndpointReference.PortType[0], "ttl");
	ProbeMatches.ProbeMatch->wsa__EndpointReference.ServiceName->__item = NULL;
	ProbeMatches.ProbeMatch->wsa__EndpointReference.ServiceName->PortName = NULL;
	ProbeMatches.ProbeMatch->wsa__EndpointReference.ServiceName->__anyAttribute = NULL;
	ProbeMatches.ProbeMatch->wsa__EndpointReference.__any[0] = (char *)soap_malloc(soap, sizeof(char) * SMALL_INFO_LENGTH);
	strcpy(ProbeMatches.ProbeMatch->wsa__EndpointReference.__any[0], "Any");
	strcpy(ProbeMatches.ProbeMatch->wsa__EndpointReference.__anyAttribute, "Attribute");
	ProbeMatches.ProbeMatch->wsa__EndpointReference.__size = 0;
	strcpy(ProbeMatches.ProbeMatch->wsa__EndpointReference.Address, _HwId);

	/*注释的部分为可选，注释掉onvif test也能发现ws-d*/
	soap->header->wsa__To = "http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous";
	soap->header->wsa__Action = "http://schemas.xmlsoap.org/ws/2005/04/discovery/ProbeMatches";
	soap->header->wsa__RelatesTo = (struct wsa__Relationship*)soap_malloc(soap, sizeof(struct wsa__Relationship));
	//it's here
	soap->header->wsa__RelatesTo->__item = soap->header->wsa__MessageID;
	soap->header->wsa__RelatesTo->RelationshipType = NULL;
	soap->header->wsa__RelatesTo->__anyAttribute = NULL;

	soap->header->wsa__MessageID =(char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
	strcpy(soap->header->wsa__MessageID,_HwId+4);

    /* send over current socket as HTTP OK response: */
	/*测试过，第二参数必须http，action随意*/
    soap_send___wsdd__ProbeMatches(soap, "http://", NULL, &ProbeMatches);
    TRACE("__wsdd__Probe end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __wsdd__ProbeMatches(struct soap* soap, struct wsdd__ProbeMatchesType *wsdd__ProbeMatches)
{
	TRACE("__wsdd__ProbeMatches start\n");
	TRACE("__wsdd__ProbeMatches end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __wsdd__Resolve(struct soap* soap, struct wsdd__ResolveType *wsdd__Resolve)
{
	TRACE("__wsdd__Resolve start\n");
	TRACE("__wsdd__Resolve end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __wsdd__ResolveMatches(struct soap* soap, struct wsdd__ResolveMatchesType *wsdd__ResolveMatches)
{
	TRACE("__wsdd__ResolveMatches start\n");
	TRACE("__wsdd__ResolveMatches end\n");
	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __ns1__GetSupportedActions(struct soap* soap, struct _ns1__GetSupportedActions *ns1__GetSupportedActions, struct _ns1__GetSupportedActionsResponse *ns1__GetSupportedActionsResponse)
{
	TRACE("__nsl__GetSupportedActions start\n");
	TRACE("__nsl__GetSupportedActions end\n");
	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __ns1__GetActions(struct soap* soap, struct _ns1__GetActions *ns1__GetActions, struct _ns1__GetActionsResponse *ns1__GetActionsResponse)
{
	TRACE("__nsl__GetActions start\n");
	TRACE("__nsl__GetActions end\n");
	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __ns1__CreateActions(struct soap* soap, struct _ns1__CreateActions *ns1__CreateActions, struct _ns1__CreateActionsResponse *ns1__CreateActionsResponse)
{
	TRACE("__nsl__CreateActions start\n");
	TRACE("__nsl__CreateActions end\n");
	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __ns1__DeleteActions(struct soap* soap, struct _ns1__DeleteActions *ns1__DeleteActions, struct _ns1__DeleteActionsResponse *ns1__DeleteActionsResponse)
{
	TRACE("__nsl__DeleteActions start\n");
	TRACE("__nsl__DeleteActions end\n");
	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __ns1__ModifyActions(struct soap* soap, struct _ns1__ModifyActions *ns1__ModifyActions, struct _ns1__ModifyActionsResponse *ns1__ModifyActionsResponse)
{
	TRACE("__nsl__ModifyActions start\n");
	TRACE("__nsl__ModifyActions end\n");
	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __ns1__GetServiceCapabilities(struct soap* soap, struct _ns1__GetServiceCapabilities *ns1__GetServiceCapabilities, struct _ns1__GetServiceCapabilitiesResponse *ns1__GetServiceCapabilitiesResponse)
{
	TRACE("__nsl__GetServiceCapabilities start\n");
	TRACE("__nsl__GetServiceCapabilities end\n");
	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __ns1__GetActionTriggers(struct soap* soap, struct _ns1__GetActionTriggers *ns1__GetActionTriggers, struct _ns1__GetActionTriggersResponse *ns1__GetActionTriggersResponse)
{
	TRACE("__nsl__GetActionTriggers start\n");
	TRACE("__nsl__GetActionTriggers end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns1__CreateActionTriggers(struct soap* soap, struct _ns1__CreateActionTriggers *ns1__CreateActionTriggers, struct _ns1__CreateActionTriggersResponse *ns1__CreateActionTriggersResponse)
{
	TRACE("__nsl__CreateActionTriggers start\n");
	TRACE("__nsl__CreateActionTriggers end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns1__DeleteActionTriggers(struct soap* soap, struct _ns1__DeleteActionTriggers *ns1__DeleteActionTriggers, struct _ns1__DeleteActionTriggersResponse *ns1__DeleteActionTriggersResponse)
{
	TRACE("__nsl__DeleteActionTriggers start\n");
	TRACE("__nsl__DeleteActionTriggers end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns1__ModifyActionTriggers(struct soap* soap, struct _ns1__ModifyActionTriggers *ns1__ModifyActionTriggers, struct _ns1__ModifyActionTriggersResponse *ns1__ModifyActionTriggersResponse)
{
	TRACE("__nsl__ModifyActionTriggers start\n");
	TRACE("__nsl__ModifyActionTriggers end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns10__Notify(struct soap* soap, struct _wsnt__Notify *wsnt__Notify)
{
	TRACE("__ns10__Notify start\n");
	TRACE("__ns10__Notify end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns11__GetMessages(struct soap* soap, struct _wsnt__GetMessages *wsnt__GetMessages, struct _wsnt__GetMessagesResponse *wsnt__GetMessagesResponse)
{
	TRACE("__nsll__GetMessages start\n");
	TRACE("__nsll__GetMessages end\n");
	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __ns11__DestroyPullPoint(struct soap* soap, struct _wsnt__DestroyPullPoint *wsnt__DestroyPullPoint, struct _wsnt__DestroyPullPointResponse *wsnt__DestroyPullPointResponse)
{
	TRACE("__nsll__DestroyPullPoint start\n");
	TRACE("__nsll__DestroyPullPoint end\n");
	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __ns11__Notify(struct soap* soap, struct _wsnt__Notify *wsnt__Notify)
{
	TRACE("__nsll__Notify start\n");
	TRACE("__nsll__Notify end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns12__CreatePullPoint(struct soap* soap, struct _wsnt__CreatePullPoint *wsnt__CreatePullPoint, struct _wsnt__CreatePullPointResponse *wsnt__CreatePullPointResponse)
{
	TRACE("__nsl2__CreatePullPoint start\n");
	TRACE("__nsl2__CreatePullPoint end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns13__Renew(struct soap* soap, struct _wsnt__Renew *wsnt__Renew, struct _wsnt__RenewResponse *wsnt__RenewResponse)
{
	TRACE("__nsl3__Renew start\n");
	TRACE("__nsl3__Renew end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns13__Unsubscribe(struct soap* soap, struct _wsnt__Unsubscribe *wsnt__Unsubscribe, struct _wsnt__UnsubscribeResponse *wsnt__UnsubscribeResponse)
{
	TRACE("__nsl3__Unsubscribe start\n");
	TRACE("__nsl3__Unsubscribe end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns13__PauseSubscription(struct soap* soap, struct _wsnt__PauseSubscription *wsnt__PauseSubscription, struct _wsnt__PauseSubscriptionResponse *wsnt__PauseSubscriptionResponse)
{
	TRACE("__nsl3__PauseSubscription start\n");
	TRACE("__nsl3__PauseSubscription end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns13__ResumeSubscription(struct soap* soap, struct _wsnt__ResumeSubscription *wsnt__ResumeSubscription, struct _wsnt__ResumeSubscriptionResponse *wsnt__ResumeSubscriptionResponse)
{
	TRACE("__nsl3__ResumeSubscription start\n");
	TRACE("__nsl3__ResumeSubscription end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns14__Hello(struct soap* soap, struct wsdd__HelloType tdn__Hello, struct wsdd__ResolveType *tdn__HelloResponse)
{
	TRACE("__nsl4__Hello start\n");
	TRACE("__nsl4__Hello end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns14__Bye(struct soap* soap, struct wsdd__ByeType tdn__Bye, struct wsdd__ResolveType *tdn__ByeResponse)
{
	TRACE("__nsl4__Bye start\n");
	TRACE("__nsl4__Bye end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns15__Probe(struct soap* soap, struct wsdd__ProbeType tdn__Probe, struct wsdd__ProbeMatchesType *tdn__ProbeResponse)
{
	TRACE("__nsl4__Probe start\n");
	TRACE("__nsl4__Probe end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns16__GetSupportedRules(struct soap* soap, struct _tan__GetSupportedRules *tan__GetSupportedRules, struct _tan__GetSupportedRulesResponse *tan__GetSupportedRulesResponse)
{
	TRACE("__nsl6__GetSupportedRules start\n");
	TRACE("__nsl6__GetSupportedRules end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns16__CreateRules(struct soap* soap, struct _tan__CreateRules *tan__CreateRules, struct _tan__CreateRulesResponse *tan__CreateRulesResponse)
{
	TRACE("__nsl6__CreateRules start\n");
	TRACE("__nsl6__CreateRules end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns16__DeleteRules(struct soap* soap, struct _tan__DeleteRules *tan__DeleteRules, struct _tan__DeleteRulesResponse *tan__DeleteRulesResponse)
{
	TRACE("__nsl6__DeleteRules start\n");
	TRACE("__nsl6__DeleteRules end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns16__GetRules(struct soap* soap, struct _tan__GetRules *tan__GetRules, struct _tan__GetRulesResponse *tan__GetRulesResponse)
{
	TRACE("__nsl6__GetRules start\n");
	TRACE("__nsl6__GetRules end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns16__ModifyRules(struct soap* soap, struct _tan__ModifyRules *tan__ModifyRules, struct _tan__ModifyRulesResponse *tan__ModifyRulesResponse)
{
	TRACE("__nsl6__ModifyRules start\n");
	TRACE("__nsl6__ModifyRules end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns17__GetServiceCapabilities(struct soap* soap, struct _tan__GetServiceCapabilities *tan__GetServiceCapabilities, struct _tan__GetServiceCapabilitiesResponse *tan__GetServiceCapabilitiesResponse)
{
	printf("__nsl7__GetServiceCapabilities\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns17__GetSupportedAnalyticsModules(struct soap* soap, struct _tan__GetSupportedAnalyticsModules *tan__GetSupportedAnalyticsModules, struct _tan__GetSupportedAnalyticsModulesResponse *tan__GetSupportedAnalyticsModulesResponse)
{
	printf("__nsl7__GetSupportedAnalyticsModules\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns17__CreateAnalyticsModules(struct soap* soap, struct _tan__CreateAnalyticsModules *tan__CreateAnalyticsModules, struct _tan__CreateAnalyticsModulesResponse *tan__CreateAnalyticsModulesResponse)
{
	printf("__nsl7__CreateAnalyticsModules\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns17__DeleteAnalyticsModules(struct soap* soap, struct _tan__DeleteAnalyticsModules *tan__DeleteAnalyticsModules, struct _tan__DeleteAnalyticsModulesResponse *tan__DeleteAnalyticsModulesResponse)
{
	printf("__nsl7__DeleteAnalyticsModules\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns17__GetAnalyticsModules(struct soap* soap, struct _tan__GetAnalyticsModules *tan__GetAnalyticsModules, struct _tan__GetAnalyticsModulesResponse *tan__GetAnalyticsModulesResponse)
{
	printf("__nsl7__GetAnalyticsModules\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns17__ModifyAnalyticsModules(struct soap* soap, struct _tan__ModifyAnalyticsModules *tan__ModifyAnalyticsModules, struct _tan__ModifyAnalyticsModulesResponse *tan__ModifyAnalyticsModulesResponse)
{
	printf("__nsl7__ModifyAnalyticsModules\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns18__GetServiceCapabilities(struct soap* soap, struct _ns4__GetServiceCapabilities *ns4__GetServiceCapabilities, struct _ns4__GetServiceCapabilitiesResponse *ns4__GetServiceCapabilitiesResponse)
{
	printf("__nsl8__GetServiceCapabilities\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns19__CreateRSAKeyPair(struct soap* soap, struct _ns4__CreateRSAKeyPair *ns4__CreateRSAKeyPair, struct _ns4__CreateRSAKeyPairResponse *ns4__CreateRSAKeyPairResponse)
{
	printf("__nsl9__CreateRSAKeyPair\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns19__GetKeyStatus(struct soap* soap, struct _ns4__GetKeyStatus *ns4__GetKeyStatus, struct _ns4__GetKeyStatusResponse *ns4__GetKeyStatusResponse)
{
	printf("__nsl9__GetKeyStatus\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns19__GetPrivateKeyStatus(struct soap* soap, struct _ns4__GetPrivateKeyStatus *ns4__GetPrivateKeyStatus, struct _ns4__GetPrivateKeyStatusResponse *ns4__GetPrivateKeyStatusResponse)
{
	printf("__nsl9__GetPrivateKeyStatus\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns19__GetAllKeys(struct soap* soap, struct _ns4__GetAllKeys *ns4__GetAllKeys, struct _ns4__GetAllKeysResponse *ns4__GetAllKeysResponse)
{
	printf("__nsl9__getAllKeys\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns19__DeleteKey(struct soap* soap, struct _ns4__DeleteKey *ns4__DeleteKey, struct _ns4__DeleteKeyResponse *ns4__DeleteKeyResponse)
{
	printf("__nsl9__DeleteKey\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns19__CreatePKCS10CSR(struct soap* soap, struct _ns4__CreatePKCS10CSR *ns4__CreatePKCS10CSR, struct _ns4__CreatePKCS10CSRResponse *ns4__CreatePKCS10CSRResponse)
{
	printf("__nsl9__CreatePKCS10CSR\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns19__CreateSelfSignedCertificate(struct soap* soap, struct _ns4__CreateSelfSignedCertificate *ns4__CreateSelfSignedCertificate, struct _ns4__CreateSelfSignedCertificateResponse *ns4__CreateSelfSignedCertificateResponse)
{
	printf("__nsl9__CreateSelfSignedCertificate\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns19__UploadCertificate(struct soap* soap, struct _ns4__UploadCertificate *ns4__UploadCertificate, struct _ns4__UploadCertificateResponse *ns4__UploadCertificateResponse)
{
	printf("__nsl9__UploadCertificate\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns19__GetCertificate(struct soap* soap, struct _ns4__GetCertificate *ns4__GetCertificate, struct _ns4__GetCertificateResponse *ns4__GetCertificateResponse)
{
	printf("__ns19__GetCertificate\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns19__GetAllCertificates(struct soap* soap, struct _ns4__GetAllCertificates *ns4__GetAllCertificates, struct _ns4__GetAllCertificatesResponse *ns4__GetAllCertificatesResponse)
{
	printf("__ns19__GetAllCertificates\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns19__DeleteCertificate(struct soap* soap, struct _ns4__DeleteCertificate *ns4__DeleteCertificate, struct _ns4__DeleteCertificateResponse *ns4__DeleteCertificateResponse)
{
	printf("__ns19__DeleteCertificate\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns19__CreateCertificationPath(struct soap* soap, struct _ns4__CreateCertificationPath *ns4__CreateCertificationPath, struct _ns4__CreateCertificationPathResponse *ns4__CreateCertificationPathResponse)
{
	printf("__ns19__CreateCertificationPath\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns19__GetCertificationPath(struct soap* soap, struct _ns4__GetCertificationPath *ns4__GetCertificationPath, struct _ns4__GetCertificationPathResponse *ns4__GetCertificationPathResponse)
{
	printf("__ns19__GetCertificationPath\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns19__GetAllCertificationPaths(struct soap* soap, struct _ns4__GetAllCertificationPaths *ns4__GetAllCertificationPaths, struct _ns4__GetAllCertificationPathsResponse *ns4__GetAllCertificationPathsResponse)
{
	printf("__ns19__GetAllCertificationPaths\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns19__DeleteCertificationPath(struct soap* soap, struct _ns4__DeleteCertificationPath *ns4__DeleteCertificationPath, struct _ns4__DeleteCertificationPathResponse *ns4__DeleteCertificationPathResponse)
{
	printf("__ns19__DeleteCertificationPath\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns2__GetServiceCapabilities(struct soap* soap, struct _ns2__GetServiceCapabilities *ns2__GetServiceCapabilities, struct _ns2__GetServiceCapabilitiesResponse *ns2__GetServiceCapabilitiesResponse)
{
	printf("__ns2__GetServiceCapabilities\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns2__GetAccessPointInfoList(struct soap* soap, struct _ns2__GetAccessPointInfoList *ns2__GetAccessPointInfoList, struct _ns2__GetAccessPointInfoListResponse *ns2__GetAccessPointInfoListResponse)
{
	printf("__ns2__GetAccessPointInfoList\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns2__GetAccessPointInfo(struct soap* soap, struct _ns2__GetAccessPointInfo *ns2__GetAccessPointInfo, struct _ns2__GetAccessPointInfoResponse *ns2__GetAccessPointInfoResponse)
{
	printf("__ns2__GetAccessPointInfo\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns2__GetAreaInfoList(struct soap* soap, struct _ns2__GetAreaInfoList *ns2__GetAreaInfoList, struct _ns2__GetAreaInfoListResponse *ns2__GetAreaInfoListResponse)
{
	printf("__ns2__GetAreaInfoList\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns2__GetAreaInfo(struct soap* soap, struct _ns2__GetAreaInfo *ns2__GetAreaInfo, struct _ns2__GetAreaInfoResponse *ns2__GetAreaInfoResponse)
{
	printf("__ns2__GetAreaInfo\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns2__GetAccessPointState(struct soap* soap, struct _ns2__GetAccessPointState *ns2__GetAccessPointState, struct _ns2__GetAccessPointStateResponse *ns2__GetAccessPointStateResponse)
{
	printf("__ns2__GetAccessPointState\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns2__EnableAccessPoint(struct soap* soap, struct _ns2__EnableAccessPoint *ns2__EnableAccessPoint, struct _ns2__EnableAccessPointResponse *ns2__EnableAccessPointResponse)
{
	printf("__ns2__EnableAccessPoint\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns2__DisableAccessPoint(struct soap* soap, struct _ns2__DisableAccessPoint *ns2__DisableAccessPoint, struct _ns2__DisableAccessPointResponse *ns2__DisableAccessPointResponse)
{
	printf("__ns2__DisableAccessPoint\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns2__ExternalAuthorization(struct soap* soap, struct _ns2__ExternalAuthorization *ns2__ExternalAuthorization, struct _ns2__ExternalAuthorizationResponse *ns2__ExternalAuthorizationResponse)
{
	printf("__ns2__ExternalAuthorization\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns20__AddServerCertificateAssignment(struct soap* soap, struct _ns4__AddServerCertificateAssignment *ns4__AddServerCertificateAssignment, struct _ns4__AddServerCertificateAssignmentResponse *ns4__AddServerCertificateAssignmentResponse)
{
	printf("__ns20__AddServerCertificateAssignment\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns20__RemoveServerCertificateAssignment(struct soap* soap, struct _ns4__RemoveServerCertificateAssignment *ns4__RemoveServerCertificateAssignment, struct _ns4__RemoveServerCertificateAssignmentResponse *ns4__RemoveServerCertificateAssignmentResponse)
{
	printf("__ns20__RemoveServerCertificateAssignment\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns20__ReplaceServerCertificateAssignment(struct soap* soap, struct _ns4__ReplaceServerCertificateAssignment *ns4__ReplaceServerCertificateAssignment, struct _ns4__ReplaceServerCertificateAssignmentResponse *ns4__ReplaceServerCertificateAssignmentResponse)
{
	printf("__ns20__ReplaceServerCertificateAssignment\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns20__GetAssignedServerCertificates(struct soap* soap, struct _ns4__GetAssignedServerCertificates *ns4__GetAssignedServerCertificates, struct _ns4__GetAssignedServerCertificatesResponse *ns4__GetAssignedServerCertificatesResponse)
{
	printf("__ns20__GetAssignedServerCertificates\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns5__GetServiceCapabilities(struct soap* soap, struct _ns5__GetServiceCapabilities *ns5__GetServiceCapabilities, struct _ns5__GetServiceCapabilitiesResponse *ns5__GetServiceCapabilitiesResponse)
{
	printf("__ns5__GetServiceCapabilities\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns5__GetDoorInfoList(struct soap* soap, struct _ns5__GetDoorInfoList *ns5__GetDoorInfoList, struct _ns5__GetDoorInfoListResponse *ns5__GetDoorInfoListResponse)
{
	printf("__ns5__GetDoorInfoList\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns5__GetDoorInfo(struct soap* soap, struct _ns5__GetDoorInfo *ns5__GetDoorInfo, struct _ns5__GetDoorInfoResponse *ns5__GetDoorInfoResponse)
{
	printf("__ns5__GetDoorInfo\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns5__GetDoorState(struct soap* soap, struct _ns5__GetDoorState *ns5__GetDoorState, struct _ns5__GetDoorStateResponse *ns5__GetDoorStateResponse)
{
	printf("__ns5__GetDoorState\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns5__AccessDoor(struct soap* soap, struct _ns5__AccessDoor *ns5__AccessDoor, struct _ns5__AccessDoorResponse *ns5__AccessDoorResponse)
{
	printf("__ns5__AccessDoor\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns5__LockDoor(struct soap* soap, struct _ns5__LockDoor *ns5__LockDoor, struct _ns5__LockDoorResponse *ns5__LockDoorResponse)
{
	printf("__ns5__LockDoor\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns5__UnlockDoor(struct soap* soap, struct _ns5__UnlockDoor *ns5__UnlockDoor, struct _ns5__UnlockDoorResponse *ns5__UnlockDoorResponse)
{
	TRACE("__ns5__UnlockDoor start\n");
	TRACE("__ns5__UnlockDoor end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns5__BlockDoor(struct soap* soap, struct _ns5__BlockDoor *ns5__BlockDoor, struct _ns5__BlockDoorResponse *ns5__BlockDoorResponse)
{
	TRACE("__ns5__BlockDoor\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns5__LockDownDoor(struct soap* soap, struct _ns5__LockDownDoor *ns5__LockDownDoor, struct _ns5__LockDownDoorResponse *ns5__LockDownDoorResponse)
{
	TRACE("__ns5__LockDownDoor\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns5__LockDownReleaseDoor(struct soap* soap, struct _ns5__LockDownReleaseDoor *ns5__LockDownReleaseDoor, struct _ns5__LockDownReleaseDoorResponse *ns5__LockDownReleaseDoorResponse)
{
	TRACE("__ns5__LockDownReleaseDoor\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns5__LockOpenDoor(struct soap* soap, struct _ns5__LockOpenDoor *ns5__LockOpenDoor, struct _ns5__LockOpenDoorResponse *ns5__LockOpenDoorResponse)
{
	TRACE("__ns5__LockOpenDoor\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns5__LockOpenReleaseDoor(struct soap* soap, struct _ns5__LockOpenReleaseDoor *ns5__LockOpenReleaseDoor, struct _ns5__LockOpenReleaseDoorResponse *ns5__LockOpenReleaseDoorResponse)
{
	TRACE("__ns5__LockOpenReleaseDoor\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns5__DoubleLockDoor(struct soap* soap, struct _ns5__DoubleLockDoor *ns5__DoubleLockDoor, struct _ns5__DoubleLockDoorResponse *ns5__DoubleLockDoorResponse)
{
	TRACE("__ns5__DoubleLockDoor\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns6__PullMessages(struct soap* soap, struct _tev__PullMessages *tev__PullMessages, struct _tev__PullMessagesResponse *tev__PullMessagesResponse)
{
	TRACE("__ns6__PullMessages\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns6__Seek(struct soap* soap, struct _tev__Seek *tev__Seek, struct _tev__SeekResponse *tev__SeekResponse)
{
	TRACE("__ns6__Seek\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns6__SetSynchronizationPoint(struct soap* soap, struct _tev__SetSynchronizationPoint *tev__SetSynchronizationPoint, struct _tev__SetSynchronizationPointResponse *tev__SetSynchronizationPointResponse)
{
	TRACE("__ns6__SetSynchronizationPoint\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns7__GetServiceCapabilities(struct soap* soap, struct _tev__GetServiceCapabilities *tev__GetServiceCapabilities, struct _tev__GetServiceCapabilitiesResponse *tev__GetServiceCapabilitiesResponse)
{
	TRACE("__ns7__GetServiceCapabilities\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns7__CreatePullPointSubscription(struct soap* soap, struct _tev__CreatePullPointSubscription *tev__CreatePullPointSubscription, struct _tev__CreatePullPointSubscriptionResponse *tev__CreatePullPointSubscriptionResponse)
{
	TRACE("__ns7__CreatePullPointSubscription\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns7__GetEventProperties(struct soap* soap, struct _tev__GetEventProperties *tev__GetEventProperties, struct _tev__GetEventPropertiesResponse *tev__GetEventPropertiesResponse)
{
	TRACE("__ns7__GetEventProperties\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns8__Renew(struct soap* soap, struct _wsnt__Renew *wsnt__Renew, struct _wsnt__RenewResponse *wsnt__RenewResponse)
{
	TRACE("__ns8__Renew\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns8__Unsubscribe(struct soap* soap, struct _wsnt__Unsubscribe *wsnt__Unsubscribe, struct _wsnt__UnsubscribeResponse *wsnt__UnsubscribeResponse)
{
	TRACE("__ns8__Unsubscribe\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns9__Subscribe(struct soap* soap, struct _wsnt__Subscribe *wsnt__Subscribe, struct _wsnt__SubscribeResponse *wsnt__SubscribeResponse)
{
	TRACE("__ns9__Subscribe\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __ns9__GetCurrentMessage(struct soap* soap, struct _wsnt__GetCurrentMessage *wsnt__GetCurrentMessage, struct _wsnt__GetCurrentMessageResponse *wsnt__GetCurrentMessageResponse)
{
	TRACE("__ns9__GetCurrentMessage\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tad__GetServiceCapabilities(struct soap* soap, struct _tad__GetServiceCapabilities *tad__GetServiceCapabilities, struct _tad__GetServiceCapabilitiesResponse *tad__GetServiceCapabilitiesResponse)
{
	TRACE("__tad__GetServiceCapabilities\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tad__DeleteAnalyticsEngineControl(struct soap* soap, struct _tad__DeleteAnalyticsEngineControl *tad__DeleteAnalyticsEngineControl, struct _tad__DeleteAnalyticsEngineControlResponse *tad__DeleteAnalyticsEngineControlResponse)
{
	TRACE("__tad__DeleteAnalyticsEngineControl\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tad__CreateAnalyticsEngineControl(struct soap* soap, struct _tad__CreateAnalyticsEngineControl *tad__CreateAnalyticsEngineControl, struct _tad__CreateAnalyticsEngineControlResponse *tad__CreateAnalyticsEngineControlResponse)
{
	TRACE("__tad__CreateAnalyticsEngineControl\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tad__SetAnalyticsEngineControl(struct soap* soap, struct _tad__SetAnalyticsEngineControl *tad__SetAnalyticsEngineControl, struct _tad__SetAnalyticsEngineControlResponse *tad__SetAnalyticsEngineControlResponse)
{
	TRACE("__tad__SetAnalyticsEngineControl\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tad__GetAnalyticsEngineControl(struct soap* soap, struct _tad__GetAnalyticsEngineControl *tad__GetAnalyticsEngineControl, struct _tad__GetAnalyticsEngineControlResponse *tad__GetAnalyticsEngineControlResponse)
{
	TRACE("__tad__GetAnalyticsEngineControl\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tad__GetAnalyticsEngineControls(struct soap* soap, struct _tad__GetAnalyticsEngineControls *tad__GetAnalyticsEngineControls, struct _tad__GetAnalyticsEngineControlsResponse *tad__GetAnalyticsEngineControlsResponse)
{
	TRACE("__tad__GetAnalyticsEngineControls\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tad__GetAnalyticsEngine(struct soap* soap, struct _tad__GetAnalyticsEngine *tad__GetAnalyticsEngine, struct _tad__GetAnalyticsEngineResponse *tad__GetAnalyticsEngineResponse)
{
	TRACE("__tad__GetAnalyticsEngine\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tad__GetAnalyticsEngines(struct soap* soap, struct _tad__GetAnalyticsEngines *tad__GetAnalyticsEngines, struct _tad__GetAnalyticsEnginesResponse *tad__GetAnalyticsEnginesResponse)
{
	TRACE("__tad__GetAnalyticsEngines\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tad__SetVideoAnalyticsConfiguration(struct soap* soap, struct _tad__SetVideoAnalyticsConfiguration *tad__SetVideoAnalyticsConfiguration, struct _tad__SetVideoAnalyticsConfigurationResponse *tad__SetVideoAnalyticsConfigurationResponse)
{
	TRACE("__tad__SetVideoAnalyticsConfiguration\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tad__SetAnalyticsEngineInput(struct soap* soap, struct _tad__SetAnalyticsEngineInput *tad__SetAnalyticsEngineInput, struct _tad__SetAnalyticsEngineInputResponse *tad__SetAnalyticsEngineInputResponse)
{
	TRACE("__tad__SetAnalyticsEngineInput\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tad__GetAnalyticsEngineInput(struct soap* soap, struct _tad__GetAnalyticsEngineInput *tad__GetAnalyticsEngineInput, struct _tad__GetAnalyticsEngineInputResponse *tad__GetAnalyticsEngineInputResponse)
{
	TRACE("__tad__GetAnalyticsEngineInput\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tad__GetAnalyticsEngineInputs(struct soap* soap, struct _tad__GetAnalyticsEngineInputs *tad__GetAnalyticsEngineInputs, struct _tad__GetAnalyticsEngineInputsResponse *tad__GetAnalyticsEngineInputsResponse)
{
	TRACE("__tad__GetAnalyticsEngineInputs\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tad__GetAnalyticsDeviceStreamUri(struct soap* soap, struct _tad__GetAnalyticsDeviceStreamUri *tad__GetAnalyticsDeviceStreamUri, struct _tad__GetAnalyticsDeviceStreamUriResponse *tad__GetAnalyticsDeviceStreamUriResponse)
{
	TRACE("__tad__GetAnalyticsDeviceStreamUri\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tad__GetVideoAnalyticsConfiguration(struct soap* soap, struct _tad__GetVideoAnalyticsConfiguration *tad__GetVideoAnalyticsConfiguration, struct _tad__GetVideoAnalyticsConfigurationResponse *tad__GetVideoAnalyticsConfigurationResponse)
{
	TRACE("__tad__GetVideoAnalyticsConfiguration\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tad__CreateAnalyticsEngineInputs(struct soap* soap, struct _tad__CreateAnalyticsEngineInputs *tad__CreateAnalyticsEngineInputs, struct _tad__CreateAnalyticsEngineInputsResponse *tad__CreateAnalyticsEngineInputsResponse)
{
	TRACE("__tad__CreateAnalyticsEngineInputs\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tad__DeleteAnalyticsEngineInputs(struct soap* soap, struct _tad__DeleteAnalyticsEngineInputs *tad__DeleteAnalyticsEngineInputs, struct _tad__DeleteAnalyticsEngineInputsResponse *tad__DeleteAnalyticsEngineInputsResponse)
{
	TRACE("__tad__DeleteAnalyticsEngineInputs\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tad__GetAnalyticsState(struct soap* soap, struct _tad__GetAnalyticsState *tad__GetAnalyticsState, struct _tad__GetAnalyticsStateResponse *tad__GetAnalyticsStateResponse)
{
	TRACE("__tad__GetAnalyticsState\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetServices(struct soap* soap, struct _tds__GetServices *tds__GetServices, struct _tds__GetServicesResponse *tds__GetServicesResponse)
{
	TRACE("__tds__GetServices start\n");
	char _IPAddr[INFO_LENGTH];
	sprintf(_IPAddr,"http://%s/onvif/services",IP_SERVER);
	tds__GetServicesResponse->__sizeService = 1;
	tds__GetServicesResponse->Service = (struct tds__Service*)soap_malloc(soap,sizeof(struct tds__Service));
	tds__GetServicesResponse->Service[0].XAddr = (char*)soap_malloc(soap,sizeof(char) * INFO_LENGTH);
	tds__GetServicesResponse->Service[0].Namespace = (char*)soap_malloc(soap,sizeof(char) * INFO_LENGTH);
	strcpy(tds__GetServicesResponse->Service[0].Namespace,"http://www.onvif.org/ver10/events/wsdl");
	strcpy(tds__GetServicesResponse->Service[0].XAddr,_IPAddr);
	tds__GetServicesResponse->Service[0].Capabilities = NULL;
	tds__GetServicesResponse->Service[0].Version = (struct tt__OnvifVersion*)soap_malloc(soap,sizeof(struct tt__OnvifVersion));
	tds__GetServicesResponse->Service[0].Version->Major = 0;
	tds__GetServicesResponse->Service[0].Version->Minor = 3;
	tds__GetServicesResponse->Service[0].__any = (char**)soap_malloc(soap,sizeof(char*));
	tds__GetServicesResponse->Service[0].__any[0] = (char*)soap_malloc(soap,sizeof(char) * INFO_LENGTH);
	strcpy(tds__GetServicesResponse->Service[0].__any[0],"why1");
	tds__GetServicesResponse->Service[0].__any[1] = (char*)soap_malloc(soap,sizeof(char) * INFO_LENGTH);
	strcpy(tds__GetServicesResponse->Service[0].__any[1],"why2");
	tds__GetServicesResponse->Service[0].__size = 0;
	tds__GetServicesResponse->Service[0].__anyAttribute = NULL;
	TRACE("__tds__GetServices end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetServiceCapabilities(struct soap* soap, struct _tds__GetServiceCapabilities *tds__GetServiceCapabilities, struct _tds__GetServiceCapabilitiesResponse *tds__GetServiceCapabilitiesResponse)
{
	TRACE("__tds__GetServiceCapabilities start\n");
	TRACE("__tds__GetServiceCapabilities end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDeviceInformation(struct soap* soap, struct _tds__GetDeviceInformation *tds__GetDeviceInformation, struct _tds__GetDeviceInformationResponse *tds__GetDeviceInformationResponse)
{
	TRACE("__tds__GetDeviceInformation start\n");
	if(tds__GetDeviceInformationResponse != NULL)
	{
		tds__GetDeviceInformationResponse->Manufacturer = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
		strcpy(tds__GetDeviceInformationResponse->Manufacturer, "Hero&amp;Speed Technology Co., Ltd.");
		tds__GetDeviceInformationResponse->FirmwareVersion = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
		strcpy(tds__GetDeviceInformationResponse->FirmwareVersion, "V0.2");
		tds__GetDeviceInformationResponse->HardwareId = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
		strcpy(tds__GetDeviceInformationResponse->HardwareId,"4.0");
		tds__GetDeviceInformationResponse->Model = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
		strcpy(tds__GetDeviceInformationResponse->Model,"HS3245");
		tds__GetDeviceInformationResponse->SerialNumber = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
		strcpy(tds__GetDeviceInformationResponse->SerialNumber,"CSAF4E56BK7BIQQIU5548");
	}
	else
	{
		TRACE("__tds__GetDeviceInformation, tds__GetDeviceInformationResponse = NULL\n");
	}
	TRACE("__tds__GetDeviceInformation end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetSystemDateAndTime(struct soap* soap, struct _tds__SetSystemDateAndTime *tds__SetSystemDateAndTime, struct _tds__SetSystemDateAndTimeResponse *tds__SetSystemDateAndTimeResponse)
{
	TRACE("__tds__SetSystemDateAndTime start\n");
	TRACE("__tds__SetSystemDateAndTime end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetSystemDateAndTime(struct soap* soap, struct _tds__GetSystemDateAndTime *tds__GetSystemDateAndTime, struct _tds__GetSystemDateAndTimeResponse *tds__GetSystemDateAndTimeResponse)
{
	TRACE("__tds__GetSystemDateAndTime start\n");
	TRACE("__tds__GetSystemDateAndTime end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetSystemFactoryDefault(struct soap* soap, struct _tds__SetSystemFactoryDefault *tds__SetSystemFactoryDefault, struct _tds__SetSystemFactoryDefaultResponse *tds__SetSystemFactoryDefaultResponse)
{
	TRACE("__tds__SetSystemFactoryDefault start\n");
	TRACE("__tds__SetSystemFactoryDefault end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__UpgradeSystemFirmware(struct soap* soap, struct _tds__UpgradeSystemFirmware *tds__UpgradeSystemFirmware, struct _tds__UpgradeSystemFirmwareResponse *tds__UpgradeSystemFirmwareResponse)
{
	TRACE("__tds__UpgradeSystemFirmware start\n");
	TRACE("__tds__UpgradeSystemFirmware end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SystemReboot(struct soap* soap, struct _tds__SystemReboot *tds__SystemReboot, struct _tds__SystemRebootResponse *tds__SystemRebootResponse)
{
	TRACE("__tds__SystemReboot start\n");
	TRACE("__tds__SystemReboot end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__RestoreSystem(struct soap* soap, struct _tds__RestoreSystem *tds__RestoreSystem, struct _tds__RestoreSystemResponse *tds__RestoreSystemResponse)
{
	TRACE("__tds__RestoreSystem start\n");
	TRACE("__tds__RestoreSystem end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetSystemBackup(struct soap* soap, struct _tds__GetSystemBackup *tds__GetSystemBackup, struct _tds__GetSystemBackupResponse *tds__GetSystemBackupResponse)
{
	TRACE("__tds__GetSystemBackup start\n");
	TRACE("__tds__GetSystemBackup end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetSystemLog(struct soap* soap, struct _tds__GetSystemLog *tds__GetSystemLog, struct _tds__GetSystemLogResponse *tds__GetSystemLogResponse)
{
	TRACE("__tds__GetSystemLog start\n");
	TRACE("__tds__GetSystemLog end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetSystemSupportInformation(struct soap* soap, struct _tds__GetSystemSupportInformation *tds__GetSystemSupportInformation, struct _tds__GetSystemSupportInformationResponse *tds__GetSystemSupportInformationResponse)
{
	TRACE("__tds__GetSystemSupportInformation start\n");
	TRACE("__tds__GetSystemSupportInformation end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetScopes(struct soap* soap, struct _tds__GetScopes *tds__GetScopes, struct _tds__GetScopesResponse *tds__GetScopesResponse)
{
	TRACE("__tds__GetScopes start\n");
	int nScopes = 7;
	if( tds__GetScopesResponse != NULL)
	{
		tds__GetScopesResponse->__sizeScopes = nScopes;
		tds__GetScopesResponse->Scopes = (struct tt__Scope*)soap_malloc(soap,sizeof(struct tt__Scope) * nScopes);

		tds__GetScopesResponse->Scopes[0].ScopeItem = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
		strcpy(tds__GetScopesResponse->Scopes[0].ScopeItem,"onvif://www.onvif.org/type/NetworkVideoTransmitter");
		tds__GetScopesResponse->Scopes[0].ScopeDef = tt__ScopeDefinition__Fixed;

		tds__GetScopesResponse->Scopes[1].ScopeItem = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
		strcpy(tds__GetScopesResponse->Scopes[1].ScopeItem,"onvif://www.onvif.org/type/video_encoder");
		tds__GetScopesResponse->Scopes[1].ScopeDef = tt__ScopeDefinition__Fixed;

		tds__GetScopesResponse->Scopes[2].ScopeItem = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
		strcpy(tds__GetScopesResponse->Scopes[2].ScopeItem,"onvif://www.onvif.org/type/audio_encoder");
		tds__GetScopesResponse->Scopes[2].ScopeDef = tt__ScopeDefinition__Fixed;

		tds__GetScopesResponse->Scopes[3].ScopeItem = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
		strcpy(tds__GetScopesResponse->Scopes[3].ScopeItem,"onvif://www.onvif.org/location/city/guangzhou");
		tds__GetScopesResponse->Scopes[3].ScopeDef = tt__ScopeDefinition__Configurable;


		tds__GetScopesResponse->Scopes[4].ScopeItem = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
		strcpy(tds__GetScopesResponse->Scopes[4].ScopeItem,"onvif://www.onvif.org/hardware/IP Camera");
		tds__GetScopesResponse->Scopes[4].ScopeDef = tt__ScopeDefinition__Fixed;

		tds__GetScopesResponse->Scopes[5].ScopeItem = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
		strcpy(tds__GetScopesResponse->Scopes[5].ScopeItem,"onvif://www.onvif.org/name/IP Camera");
		tds__GetScopesResponse->Scopes[5].ScopeDef = tt__ScopeDefinition__Configurable;

		tds__GetScopesResponse->Scopes[6].ScopeItem = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
		strcpy(tds__GetScopesResponse->Scopes[6].ScopeItem,"onvif://www.onvif.org/manufacturer/HeroSpeed");
		tds__GetScopesResponse->Scopes[6].ScopeDef = tt__ScopeDefinition__Fixed;

	}
	else
	{
		TRACE("__tds__GetScopes,tds__GetScopesResponse == NULL\n");
	}
	TRACE("__tds__GetScopes end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetScopes(struct soap* soap, struct _tds__SetScopes *tds__SetScopes, struct _tds__SetScopesResponse *tds__SetScopesResponse)
{
	TRACE("__tds__SetScopes start\n");
	TRACE("__tds__SetScopes end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__AddScopes(struct soap* soap, struct _tds__AddScopes *tds__AddScopes, struct _tds__AddScopesResponse *tds__AddScopesResponse)
{
	TRACE("__tds__AddScopes start\n");
	TRACE("__tds__AddScopes end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__RemoveScopes(struct soap* soap, struct _tds__RemoveScopes *tds__RemoveScopes, struct _tds__RemoveScopesResponse *tds__RemoveScopesResponse)
{
	TRACE("__tds__RemoveScopes start\n");
	TRACE("__tds__RemoveScopes end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDiscoveryMode(struct soap* soap, struct _tds__GetDiscoveryMode *tds__GetDiscoveryMode, struct _tds__GetDiscoveryModeResponse *tds__GetDiscoveryModeResponse)
{
	TRACE("__tds__GetDiscoveryMode start\n");
	TRACE("__tds__GetDiscoveryMode end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetDiscoveryMode(struct soap* soap, struct _tds__SetDiscoveryMode *tds__SetDiscoveryMode, struct _tds__SetDiscoveryModeResponse *tds__SetDiscoveryModeResponse)
{
	TRACE("__tds__SetDiscoveryMode start\n");
	TRACE("__tds__SetDiscoveryMode end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetRemoteDiscoveryMode(struct soap* soap, struct _tds__GetRemoteDiscoveryMode *tds__GetRemoteDiscoveryMode, struct _tds__GetRemoteDiscoveryModeResponse *tds__GetRemoteDiscoveryModeResponse)
{
	TRACE("__tds__GetRemoteDiscoveryMode start\n");
	TRACE("__tds__GetRemoteDiscoveryMode end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetRemoteDiscoveryMode(struct soap* soap, struct _tds__SetRemoteDiscoveryMode *tds__SetRemoteDiscoveryMode, struct _tds__SetRemoteDiscoveryModeResponse *tds__SetRemoteDiscoveryModeResponse)
{
	TRACE("__tds__SetRemoteDiscoveryMode start\n");
	TRACE("__tds__SetRemoteDiscoveryMode end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDPAddresses(struct soap* soap, struct _tds__GetDPAddresses *tds__GetDPAddresses, struct _tds__GetDPAddressesResponse *tds__GetDPAddressesResponse)
{
	TRACE("__tds__GetDPAddresses start\n");
	TRACE("__tds__GetDPAddresses end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetEndpointReference(struct soap* soap, struct _tds__GetEndpointReference *tds__GetEndpointReference, struct _tds__GetEndpointReferenceResponse *tds__GetEndpointReferenceResponse)
{
	TRACE("__tds__GetEndpointReference start\n");
	TRACE("__tds__GetEndpointReference end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetRemoteUser(struct soap* soap, struct _tds__GetRemoteUser *tds__GetRemoteUser, struct _tds__GetRemoteUserResponse *tds__GetRemoteUserResponse)
{
	TRACE("__tds__GetRemoteUser start\n");
	TRACE("__tds__GetRemoteUser end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetRemoteUser(struct soap* soap, struct _tds__SetRemoteUser *tds__SetRemoteUser, struct _tds__SetRemoteUserResponse *tds__SetRemoteUserResponse)
{
	TRACE("__tds__SetRemoteUser start\n");
	TRACE("__tds__SetRemoteUser end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetUsers(struct soap* soap, struct _tds__GetUsers *tds__GetUsers, struct _tds__GetUsersResponse *tds__GetUsersResponse)
{
	TRACE("__tds__GetUsers start\n");
	TRACE("__tds__GetUsers end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__CreateUsers(struct soap* soap, struct _tds__CreateUsers *tds__CreateUsers, struct _tds__CreateUsersResponse *tds__CreateUsersResponse)
{
	TRACE("__tds__CreateUsers start\n");
	TRACE("__tds__CreateUsers end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__DeleteUsers(struct soap* soap, struct _tds__DeleteUsers *tds__DeleteUsers, struct _tds__DeleteUsersResponse *tds__DeleteUsersResponse)
{
	TRACE("__tds__DeleteUsers start\n");
	TRACE("__tds__DeleteUsers end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetUser(struct soap* soap, struct _tds__SetUser *tds__SetUser, struct _tds__SetUserResponse *tds__SetUserResponse)
{
	TRACE("__tds__SetUser start\n");
	TRACE("__tds__SetUser end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetWsdlUrl(struct soap* soap, struct _tds__GetWsdlUrl *tds__GetWsdlUrl, struct _tds__GetWsdlUrlResponse *tds__GetWsdlUrlResponse)
{
	TRACE("__tds__GetWsdlUrl start\n");
	TRACE("__tds__GetWsdlUrl end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetCapabilities(struct soap* soap, struct _tds__GetCapabilities *tds__GetCapabilities, struct _tds__GetCapabilitiesResponse *tds__GetCapabilitiesResponse)
{
	TRACE("__tds__GetCapabilities start\n");
	if( tds__GetCapabilitiesResponse != NULL)
	{
		tds__GetCapabilitiesResponse->Capabilities = (struct tt__Capabilities*)soap_malloc(soap,sizeof(struct tt__Capabilities));

		tds__GetCapabilitiesResponse->Capabilities->Device = (struct tt__DeviceCapabilities*)soap_malloc(soap,sizeof(struct tt__DeviceCapabilities));
		tds__GetCapabilitiesResponse->Capabilities->Device->XAddr = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
		sprintf( tds__GetCapabilitiesResponse->Capabilities->Device->XAddr, "http://%s:%u/onvif/Device",IP_SERVER,PORT_SERVER);

		tds__GetCapabilitiesResponse->Capabilities->Device->Network = (struct tt__NetworkCapabilities*)soap_malloc(soap,sizeof(struct tt__NetworkCapabilities));
		tds__GetCapabilitiesResponse->Capabilities->Device->Network->IPFilter = (enum xsd__boolean*)soap_malloc(soap,sizeof(enum xsd__boolean));
		*(tds__GetCapabilitiesResponse->Capabilities->Device->Network->IPFilter) = xsd__boolean__false_;
		tds__GetCapabilitiesResponse->Capabilities->Device->Network->ZeroConfiguration = (enum xsd__boolean*)soap_malloc(soap,sizeof(enum xsd__boolean));
		*(tds__GetCapabilitiesResponse->Capabilities->Device->Network->ZeroConfiguration) = xsd__boolean__false_;
		tds__GetCapabilitiesResponse->Capabilities->Device->Network->IPVersion6 = (enum xsd__boolean*)soap_malloc(soap,sizeof(enum xsd__boolean));
		*(tds__GetCapabilitiesResponse->Capabilities->Device->Network->IPVersion6) = xsd__boolean__false_;
		tds__GetCapabilitiesResponse->Capabilities->Device->Network->DynDNS = (enum xsd__boolean*)soap_malloc(soap,sizeof(enum xsd__boolean));
		*(tds__GetCapabilitiesResponse->Capabilities->Device->Network->DynDNS) = xsd__boolean__true_;

		tds__GetCapabilitiesResponse->Capabilities->Device->System = (struct tt__SystemCapabilities*)soap_malloc(soap,sizeof(struct tt__SystemCapabilities));
		tds__GetCapabilitiesResponse->Capabilities->Device->System->DiscoveryResolve = xsd__boolean__true_;
		tds__GetCapabilitiesResponse->Capabilities->Device->System->DiscoveryBye = xsd__boolean__false_;
		tds__GetCapabilitiesResponse->Capabilities->Device->System->RemoteDiscovery = xsd__boolean__false_;
		tds__GetCapabilitiesResponse->Capabilities->Device->System->SystemBackup = xsd__boolean__true_;
		tds__GetCapabilitiesResponse->Capabilities->Device->System->SystemLogging = xsd__boolean__false_;
		tds__GetCapabilitiesResponse->Capabilities->Device->System->FirmwareUpgrade = xsd__boolean__true_;
		tds__GetCapabilitiesResponse->Capabilities->Device->System->SupportedVersions = (struct tt__OnvifVersion*)soap_malloc(soap,sizeof(struct tt__OnvifVersion));
		tds__GetCapabilitiesResponse->Capabilities->Device->System->SupportedVersions->Minor = 10;
		tds__GetCapabilitiesResponse->Capabilities->Device->System->SupportedVersions->Major = 2;

		tds__GetCapabilitiesResponse->Capabilities->Device->IO = (struct tt__IOCapabilities*)soap_malloc(soap,sizeof(struct tt__IOCapabilities));
		tds__GetCapabilitiesResponse->Capabilities->Device->IO->__anyAttribute = NULL;
//		tds__GetCapabilitiesResponse->Capabilities->Device->IO->Extension = NULL;
//		tds__GetCapabilitiesResponse->Capabilities->Device->IO->Extension->Auxiliary;
//		tds__GetCapabilitiesResponse->Capabilities->Device->IO->Extension->AuxiliaryCommands;
//		tds__GetCapabilitiesResponse->Capabilities->Device->IO->Extension->Extension;
//		tds__GetCapabilitiesResponse->Capabilities->Device->IO->Extension->__any;
//		tds__GetCapabilitiesResponse->Capabilities->Device->IO->Extension->__anyAttribute;
//		tds__GetCapabilitiesResponse->Capabilities->Device->IO->Extension->__size;
//		tds__GetCapabilitiesResponse->Capabilities->Device->IO->Extension->__sizeAuxiliaryCommands
		tds__GetCapabilitiesResponse->Capabilities->Device->IO->InputConnectors = NULL;
		tds__GetCapabilitiesResponse->Capabilities->Device->IO->RelayOutputs = NULL;

		tds__GetCapabilitiesResponse->Capabilities->Device->Security = (struct tt__SecurityCapabilities*)soap_malloc(soap,sizeof(struct tt__SecurityCapabilities));
		tds__GetCapabilitiesResponse->Capabilities->Device->Security->TLS1_x002e1 = xsd__boolean__false_;
		tds__GetCapabilitiesResponse->Capabilities->Device->Security->TLS1_x002e2 = xsd__boolean__false_;
		tds__GetCapabilitiesResponse->Capabilities->Device->Security->OnboardKeyGeneration = xsd__boolean__false_;
		tds__GetCapabilitiesResponse->Capabilities->Device->Security->AccessPolicyConfig = xsd__boolean__false_;
		tds__GetCapabilitiesResponse->Capabilities->Device->Security->X_x002e509Token = xsd__boolean__false_;
		tds__GetCapabilitiesResponse->Capabilities->Device->Security->SAMLToken = xsd__boolean__false_;
		tds__GetCapabilitiesResponse->Capabilities->Device->Security->KerberosToken = xsd__boolean__false_;
		tds__GetCapabilitiesResponse->Capabilities->Device->Security->RELToken = xsd__boolean__false_;

		tds__GetCapabilitiesResponse->Capabilities->Events = (struct tt__EventCapabilities*)soap_malloc(soap,sizeof(struct tt__EventCapabilities));
		tds__GetCapabilitiesResponse->Capabilities->Events->XAddr = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
		sprintf(tds__GetCapabilitiesResponse->Capabilities->Events->XAddr,"http://%s:%u/onvif/Events", IP_SERVER,PORT_SERVER);
		tds__GetCapabilitiesResponse->Capabilities->Events->WSPausableSubscriptionManagerInterfaceSupport = xsd__boolean__true_;
		tds__GetCapabilitiesResponse->Capabilities->Events->WSPullPointSupport = xsd__boolean__true_;
		tds__GetCapabilitiesResponse->Capabilities->Events->WSSubscriptionPolicySupport = xsd__boolean__true_;

		tds__GetCapabilitiesResponse->Capabilities->Imaging = (struct tt__ImagingCapabilities*)soap_malloc(soap,sizeof(struct tt__ImagingCapabilities));
		tds__GetCapabilitiesResponse->Capabilities->Imaging->XAddr = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
		sprintf(tds__GetCapabilitiesResponse->Capabilities->Imaging->XAddr,"http://%s:%u/onvif/Imaging",IP_SERVER,PORT_SERVER);

		tds__GetCapabilitiesResponse->Capabilities->Media = (struct tt__MediaCapabilities*)soap_malloc(soap,sizeof(struct tt__MediaCapabilities));
		tds__GetCapabilitiesResponse->Capabilities->Media->XAddr = (char*)soap_malloc(soap,sizeof(char) * SMALL_INFO_LENGTH);
		sprintf(tds__GetCapabilitiesResponse->Capabilities->Media->XAddr,"http://%s:%u/onvif/Media",IP_SERVER,PORT_SERVER);
		tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities = (struct tt__RealTimeStreamingCapabilities*)soap_malloc(soap,sizeof(struct tt__RealTimeStreamingCapabilities));
		tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities->RTPMulticast = (enum xsd__boolean*)soap_malloc(soap,sizeof(enum xsd__boolean));
		*(tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities->RTPMulticast) = xsd__boolean__false_;
		tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities->RTP_USCORERTSP_USCORETCP = (enum xsd__boolean*)soap_malloc(soap,sizeof(enum xsd__boolean));
		*(tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities->RTP_USCORERTSP_USCORETCP) = xsd__boolean__false_;
		tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities->RTP_USCORETCP = (enum xsd__boolean*)soap_malloc(soap,sizeof(enum xsd__boolean));
		*(tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities->RTP_USCORETCP) = xsd__boolean__false_;
	}
	TRACE("__tds__GetCapabilities end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetDPAddresses(struct soap* soap, struct _tds__SetDPAddresses *tds__SetDPAddresses, struct _tds__SetDPAddressesResponse *tds__SetDPAddressesResponse)
{
	TRACE("__tds__SetDPAddresses start\n");
	TRACE("__tds__SetDPAddresses end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetHostname(struct soap* soap, struct _tds__GetHostname *tds__GetHostname, struct _tds__GetHostnameResponse *tds__GetHostnameResponse)
{
	TRACE("__tds__GetHostname start\n");
	if (tds__GetHostnameResponse != NULL)
	{
		tds__GetHostnameResponse->HostnameInformation = (struct tt__HostnameInformation*) soap_malloc(soap,sizeof(struct tt__HostnameInformation));
		tds__GetHostnameResponse->HostnameInformation->Name = (char*) soap_malloc(soap, sizeof(char) * LEN_HOSTNAME);
		strcpy(tds__GetHostnameResponse->HostnameInformation->Name, g_cHostName);
		tds__GetHostnameResponse->HostnameInformation->Extension = NULL;
		tds__GetHostnameResponse->HostnameInformation->FromDHCP = xsd__boolean__false_;
		tds__GetHostnameResponse->HostnameInformation->__anyAttribute = NULL;
	}
	else
	{
		TRACE("__tds__GetHostname failed..tds__GetHostnameResponse == NULL\n");
	}
	TRACE("__tds__GetHostname end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetHostname(struct soap* soap, struct _tds__SetHostname *tds__SetHostname, struct _tds__SetHostnameResponse *tds__SetHostnameResponse)
{
	TRACE("__tds__SetHostname start\n");
	if (tds__SetHostname != NULL)
	{
		memset(g_cHostName,'\0', LEN_HOSTNAME);
		strncpy( g_cHostName,tds__SetHostname->Name,LEN_HOSTNAME);
		TRACE("__tds__SetHostname suc...\n");
	}
	else
	{
		TRACE("__tds__SetHostname == NULL\n");
	}
	TRACE("__tds__SetHostname end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetHostnameFromDHCP(struct soap* soap, struct _tds__SetHostnameFromDHCP *tds__SetHostnameFromDHCP, struct _tds__SetHostnameFromDHCPResponse *tds__SetHostnameFromDHCPResponse)
{
	TRACE("__tds__SetHostnameFromDHCP start\n");
	TRACE("__tds__SetHostnameFromDHCP end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDNS(struct soap* soap, struct _tds__GetDNS *tds__GetDNS, struct _tds__GetDNSResponse *tds__GetDNSResponse)
{
	TRACE("__tds__GetDNS start\n");
	if( tds__GetDNSResponse != NULL)
	{
//		tds__GetDNSResponse->DNSInformation = (struct tt__DNSInformation*)soap_malloc(soap,sizeof(struct tt__DNSInformation));
//		tds__GetDNSResponse->DNSInformation->DNSFromDHCP;

	}

	TRACE("__tds__GetDNS end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetDNS(struct soap* soap, struct _tds__SetDNS *tds__SetDNS, struct _tds__SetDNSResponse *tds__SetDNSResponse)
{
	TRACE("__tds__SetDNS start\n");
	TRACE("__tds__SetDNS end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetNTP(struct soap* soap, struct _tds__GetNTP *tds__GetNTP, struct _tds__GetNTPResponse *tds__GetNTPResponse)
{
	TRACE("__tds__GetNTP start\n");
	TRACE("__tds__GetNTP end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetNTP(struct soap* soap, struct _tds__SetNTP *tds__SetNTP, struct _tds__SetNTPResponse *tds__SetNTPResponse)
{
	TRACE("__tds__SetNTP start\n");
	TRACE("__tds__SetNTP end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDynamicDNS(struct soap* soap, struct _tds__GetDynamicDNS *tds__GetDynamicDNS, struct _tds__GetDynamicDNSResponse *tds__GetDynamicDNSResponse)
{
	TRACE("__tds__GetDynamicDNS start\n");
	TRACE("__tds__GetDynamicDNS end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetDynamicDNS(struct soap* soap, struct _tds__SetDynamicDNS *tds__SetDynamicDNS, struct _tds__SetDynamicDNSResponse *tds__SetDynamicDNSResponse)
{
	TRACE("__tds__SetDynamicDNS start\n");
	TRACE("__tds__SetDynamicDNS end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetNetworkInterfaces(struct soap* soap, struct _tds__GetNetworkInterfaces *tds__GetNetworkInterfaces, struct _tds__GetNetworkInterfacesResponse *tds__GetNetworkInterfacesResponse)
{
	TRACE("__tds__GetNetworkInterfaces start\n");
	TRACE("__tds__GetNetworkInterfaces end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetNetworkInterfaces(struct soap* soap, struct _tds__SetNetworkInterfaces *tds__SetNetworkInterfaces, struct _tds__SetNetworkInterfacesResponse *tds__SetNetworkInterfacesResponse)
{
	TRACE("__tds__SetNetworkInterfaces start\n");
	TRACE("__tds__SetNetworkInterfaces end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetNetworkProtocols(struct soap* soap, struct _tds__GetNetworkProtocols *tds__GetNetworkProtocols, struct _tds__GetNetworkProtocolsResponse *tds__GetNetworkProtocolsResponse)
{
	TRACE("__tds__GetNetworkProtocols start\n");
	TRACE("__tds__GetNetworkProtocols end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetNetworkProtocols(struct soap* soap, struct _tds__SetNetworkProtocols *tds__SetNetworkProtocols, struct _tds__SetNetworkProtocolsResponse *tds__SetNetworkProtocolsResponse)
{
	TRACE("__tds__SetNetworkProtocols start\n");
	TRACE("__tds__SetNetworkProtocols end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetNetworkDefaultGateway(struct soap* soap, struct _tds__GetNetworkDefaultGateway *tds__GetNetworkDefaultGateway, struct _tds__GetNetworkDefaultGatewayResponse *tds__GetNetworkDefaultGatewayResponse)
{
	TRACE("__tds__GetNetworkDefaultGateway start\n");
	if( tds__GetNetworkDefaultGatewayResponse != NULL)
	{
		char cGateway[LEN_IP] = {0};
		g_GetGateway(cGateway,LEN_IP);
		tds__GetNetworkDefaultGatewayResponse->NetworkGateway = (struct tt__NetworkGateway*)soap_malloc(soap,sizeof(struct tt__NetworkGateway));
		tds__GetNetworkDefaultGatewayResponse->NetworkGateway->__sizeIPv4Address = 1;
		tds__GetNetworkDefaultGatewayResponse->NetworkGateway->IPv4Address =(char**)soap_malloc(soap,sizeof(char*) * 1);
		tds__GetNetworkDefaultGatewayResponse->NetworkGateway->IPv4Address[0] = (char*)soap_malloc(soap,sizeof(char) * LEN_IP);
		strcpy(tds__GetNetworkDefaultGatewayResponse->NetworkGateway->IPv4Address[0], cGateway);
		tds__GetNetworkDefaultGatewayResponse->NetworkGateway->__sizeIPv6Address = 0;
		tds__GetNetworkDefaultGatewayResponse->NetworkGateway->IPv6Address = NULL;
	}
	else
	{
		TRACE("__tds__GetNetworkDefaultGateway,tds__GetNetworkDefaultGatewayResponse == NULL\n");
	}
	TRACE("__tds__GetNetworkDefaultGateway end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetNetworkDefaultGateway(struct soap* soap, struct _tds__SetNetworkDefaultGateway *tds__SetNetworkDefaultGateway, struct _tds__SetNetworkDefaultGatewayResponse *tds__SetNetworkDefaultGatewayResponse)
{
	TRACE("__tds__SetNetworkDefaultGateway start\n");
	if( tds__SetNetworkDefaultGateway != NULL)
	{
		//g_SetGateway();
	}
	else
	{
		TRACE("__tds__SetNetworkDefaultGateway,tds__SetNetworkDefaultGateway == NULL\n");
	}
	TRACE("__tds__SetNetworkDefaultGateway end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetZeroConfiguration(struct soap* soap, struct _tds__GetZeroConfiguration *tds__GetZeroConfiguration, struct _tds__GetZeroConfigurationResponse *tds__GetZeroConfigurationResponse)
{
	TRACE("__tds__GetZeroConfiguration start\n");
	TRACE("__tds__GetZeroConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetZeroConfiguration(struct soap* soap, struct _tds__SetZeroConfiguration *tds__SetZeroConfiguration, struct _tds__SetZeroConfigurationResponse *tds__SetZeroConfigurationResponse)
{
	TRACE("__tds__SetZeroConfiguration start\n");
	TRACE("__tds__SetZeroConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetIPAddressFilter(struct soap* soap, struct _tds__GetIPAddressFilter *tds__GetIPAddressFilter, struct _tds__GetIPAddressFilterResponse *tds__GetIPAddressFilterResponse)
{
	TRACE("__tds__GetIPAddressFilter start\n");
	TRACE("__tds__GetIPAddressFilter end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetIPAddressFilter(struct soap* soap, struct _tds__SetIPAddressFilter *tds__SetIPAddressFilter, struct _tds__SetIPAddressFilterResponse *tds__SetIPAddressFilterResponse)
{
	TRACE("__tds__SetIPAddressFilter start\n");
	TRACE("__tds__SetIPAddressFilter end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__AddIPAddressFilter(struct soap* soap, struct _tds__AddIPAddressFilter *tds__AddIPAddressFilter, struct _tds__AddIPAddressFilterResponse *tds__AddIPAddressFilterResponse)
{
	TRACE("__tds__AddIPAddressFilter start\n");
	TRACE("__tds__AddIPAddressFilter end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__RemoveIPAddressFilter(struct soap* soap, struct _tds__RemoveIPAddressFilter *tds__RemoveIPAddressFilter, struct _tds__RemoveIPAddressFilterResponse *tds__RemoveIPAddressFilterResponse)
{
	TRACE("__tds__RemoveIPAddressFilter start\n");
	TRACE("__tds__RemoveIPAddressFilter end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetAccessPolicy(struct soap* soap, struct _tds__GetAccessPolicy *tds__GetAccessPolicy, struct _tds__GetAccessPolicyResponse *tds__GetAccessPolicyResponse)
{
	TRACE("__tds__GetAccessPolicy start\n");
	TRACE("__tds__GetAccessPolicy end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetAccessPolicy(struct soap* soap, struct _tds__SetAccessPolicy *tds__SetAccessPolicy, struct _tds__SetAccessPolicyResponse *tds__SetAccessPolicyResponse)
{
	TRACE("__tds__SetAccessPolicy start\n");
	TRACE("__tds__SetAccessPolicy end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__CreateCertificate(struct soap* soap, struct _tds__CreateCertificate *tds__CreateCertificate, struct _tds__CreateCertificateResponse *tds__CreateCertificateResponse)
{
	TRACE("__tds__CreateCertificate start\n");
	TRACE("__tds__CreateCertificate end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetCertificates(struct soap* soap, struct _tds__GetCertificates *tds__GetCertificates, struct _tds__GetCertificatesResponse *tds__GetCertificatesResponse)
{
	TRACE("__tds__GetCertificates start\n");
	TRACE("__tds__GetCertificates end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetCertificatesStatus(struct soap* soap, struct _tds__GetCertificatesStatus *tds__GetCertificatesStatus, struct _tds__GetCertificatesStatusResponse *tds__GetCertificatesStatusResponse)
{
	TRACE("__tds__GetCertificatesStatus start\n");
	TRACE("__tds__GetCertificatesStatus end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetCertificatesStatus(struct soap* soap, struct _tds__SetCertificatesStatus *tds__SetCertificatesStatus, struct _tds__SetCertificatesStatusResponse *tds__SetCertificatesStatusResponse)
{
	TRACE("__tds__SetCertificatesStatus start\n");
	TRACE("__tds__SetCertificatesStatus end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__DeleteCertificates(struct soap* soap, struct _tds__DeleteCertificates *tds__DeleteCertificates, struct _tds__DeleteCertificatesResponse *tds__DeleteCertificatesResponse)
{
	TRACE("__tds__DeleteCertificates start\n");
	TRACE("__tds__DeleteCertificates end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetPkcs10Request(struct soap* soap, struct _tds__GetPkcs10Request *tds__GetPkcs10Request, struct _tds__GetPkcs10RequestResponse *tds__GetPkcs10RequestResponse)
{
	TRACE("__tds__GetPkcs10Request start\n");
	TRACE("__tds__GetPkcs10Request end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__LoadCertificates(struct soap* soap, struct _tds__LoadCertificates *tds__LoadCertificates, struct _tds__LoadCertificatesResponse *tds__LoadCertificatesResponse)
{
	TRACE("__tds__LoadCertificates start\n");
	TRACE("__tds__LoadCertificates end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetClientCertificateMode(struct soap* soap, struct _tds__GetClientCertificateMode *tds__GetClientCertificateMode, struct _tds__GetClientCertificateModeResponse *tds__GetClientCertificateModeResponse)
{
	TRACE("__tds__GetClientCertificateMode start\n");
	TRACE("__tds__GetClientCertificateMode end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetClientCertificateMode(struct soap* soap, struct _tds__SetClientCertificateMode *tds__SetClientCertificateMode, struct _tds__SetClientCertificateModeResponse *tds__SetClientCertificateModeResponse)
{
	TRACE("__tds__SetClientCertificateMode start\n");
	TRACE("__tds__SetClientCertificateMode end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetRelayOutputs(struct soap* soap, struct _tds__GetRelayOutputs *tds__GetRelayOutputs, struct _tds__GetRelayOutputsResponse *tds__GetRelayOutputsResponse)
{
	TRACE("__tds__GetRelayOutputs start\n");
	TRACE("__tds__GetRelayOutputs end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetRelayOutputSettings(struct soap* soap, struct _tds__SetRelayOutputSettings *tds__SetRelayOutputSettings, struct _tds__SetRelayOutputSettingsResponse *tds__SetRelayOutputSettingsResponse)
{
	TRACE("__tds__SetRelayOutputSettings start\n");
	TRACE("__tds__SetRelayOutputSettings end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetRelayOutputState(struct soap* soap, struct _tds__SetRelayOutputState *tds__SetRelayOutputState, struct _tds__SetRelayOutputStateResponse *tds__SetRelayOutputStateResponse)
{
	TRACE("__tds__SetRelayOutputState start\n");
	TRACE("__tds__SetRelayOutputState end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SendAuxiliaryCommand(struct soap* soap, struct _tds__SendAuxiliaryCommand *tds__SendAuxiliaryCommand, struct _tds__SendAuxiliaryCommandResponse *tds__SendAuxiliaryCommandResponse)
{
	TRACE("__tds__SendAuxiliaryCommand start\n");
	TRACE("__tds__SendAuxiliaryCommand end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetCACertificates(struct soap* soap, struct _tds__GetCACertificates *tds__GetCACertificates, struct _tds__GetCACertificatesResponse *tds__GetCACertificatesResponse)
{
	TRACE("__tds__GetCACertificates start\n");
	TRACE("__tds__GetCACertificates end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__LoadCertificateWithPrivateKey(struct soap* soap, struct _tds__LoadCertificateWithPrivateKey *tds__LoadCertificateWithPrivateKey, struct _tds__LoadCertificateWithPrivateKeyResponse *tds__LoadCertificateWithPrivateKeyResponse)
{
	TRACE("__tds__LoadCertificateWithPrivateKey start\n");
	TRACE("__tds__LoadCertificateWithPrivateKey end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetCertificateInformation(struct soap* soap, struct _tds__GetCertificateInformation *tds__GetCertificateInformation, struct _tds__GetCertificateInformationResponse *tds__GetCertificateInformationResponse)
{
	TRACE("__tds__GetCertificateInformation start\n");
	TRACE("__tds__GetCertificateInformation end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__LoadCACertificates(struct soap* soap, struct _tds__LoadCACertificates *tds__LoadCACertificates, struct _tds__LoadCACertificatesResponse *tds__LoadCACertificatesResponse)
{
	TRACE("__tds__LoadCACertificates start\n");
	TRACE("__tds__LoadCACertificates end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__CreateDot1XConfiguration(struct soap* soap, struct _tds__CreateDot1XConfiguration *tds__CreateDot1XConfiguration, struct _tds__CreateDot1XConfigurationResponse *tds__CreateDot1XConfigurationResponse)
{
	TRACE("__tds__CreateDot1XConfiguration start\n");
	TRACE("__tds__CreateDot1XConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetDot1XConfiguration(struct soap* soap, struct _tds__SetDot1XConfiguration *tds__SetDot1XConfiguration, struct _tds__SetDot1XConfigurationResponse *tds__SetDot1XConfigurationResponse)
{
	TRACE("__tds__SetDot1XConfiguration start\n");
	TRACE("__tds__SetDot1XConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDot1XConfiguration(struct soap* soap, struct _tds__GetDot1XConfiguration *tds__GetDot1XConfiguration, struct _tds__GetDot1XConfigurationResponse *tds__GetDot1XConfigurationResponse)
{
	TRACE("__tds__GetDot1XConfiguration start\n");
	TRACE("__tds__GetDot1XConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDot1XConfigurations(struct soap* soap, struct _tds__GetDot1XConfigurations *tds__GetDot1XConfigurations, struct _tds__GetDot1XConfigurationsResponse *tds__GetDot1XConfigurationsResponse)
{
	TRACE("__tds__GetDot1XConfigurations start\n");
	TRACE("__tds__GetDot1XConfigurations end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__DeleteDot1XConfiguration(struct soap* soap, struct _tds__DeleteDot1XConfiguration *tds__DeleteDot1XConfiguration, struct _tds__DeleteDot1XConfigurationResponse *tds__DeleteDot1XConfigurationResponse)
{
	TRACE("__tds__DeleteDot1XConfiguration start\n");
	TRACE("__tds__DeleteDot1XConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDot11Capabilities(struct soap* soap, struct _tds__GetDot11Capabilities *tds__GetDot11Capabilities, struct _tds__GetDot11CapabilitiesResponse *tds__GetDot11CapabilitiesResponse)
{
	TRACE("__tds__GetDot11Capabilities start\n");
	TRACE("__tds__GetDot11Capabilities end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDot11Status(struct soap* soap, struct _tds__GetDot11Status *tds__GetDot11Status, struct _tds__GetDot11StatusResponse *tds__GetDot11StatusResponse)
{
	TRACE("__tds__GetDot11Status start\n");
	TRACE("__tds__GetDot11Status end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__ScanAvailableDot11Networks(struct soap* soap, struct _tds__ScanAvailableDot11Networks *tds__ScanAvailableDot11Networks, struct _tds__ScanAvailableDot11NetworksResponse *tds__ScanAvailableDot11NetworksResponse)
{
	TRACE("__tds__ScanAvailableDot11Networks start\n");
	TRACE("__tds__ScanAvailableDot11Networks end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetSystemUris(struct soap* soap, struct _tds__GetSystemUris *tds__GetSystemUris, struct _tds__GetSystemUrisResponse *tds__GetSystemUrisResponse)
{
	TRACE("__tds__GetSystemUris start\n");
	TRACE("__tds__GetSystemUris end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__StartFirmwareUpgrade(struct soap* soap, struct _tds__StartFirmwareUpgrade *tds__StartFirmwareUpgrade, struct _tds__StartFirmwareUpgradeResponse *tds__StartFirmwareUpgradeResponse)
{
	TRACE("__tds__StartFirmwareUpgrade start\n");
	TRACE("__tds__StartFirmwareUpgrade end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__StartSystemRestore(struct soap* soap, struct _tds__StartSystemRestore *tds__StartSystemRestore, struct _tds__StartSystemRestoreResponse *tds__StartSystemRestoreResponse)
{
	TRACE("__tds__StartSystemRestore start\n");
	TRACE("__tds__StartSystemRestore end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __timg__GetServiceCapabilities(struct soap* soap, struct _timg__GetServiceCapabilities *timg__GetServiceCapabilities, struct _timg__GetServiceCapabilitiesResponse *timg__GetServiceCapabilitiesResponse)
{
	TRACE("__timg__GetServiceCapabilities start\n");
	TRACE("__timg__GetServiceCapabilities end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __timg__GetImagingSettings(struct soap* soap, struct _timg__GetImagingSettings *timg__GetImagingSettings, struct _timg__GetImagingSettingsResponse *timg__GetImagingSettingsResponse)
{
	TRACE("__timg__GetImagingSettings start\n");
	TRACE("__timg__GetImagingSettings end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __timg__SetImagingSettings(struct soap* soap, struct _timg__SetImagingSettings *timg__SetImagingSettings, struct _timg__SetImagingSettingsResponse *timg__SetImagingSettingsResponse)
{
	TRACE("__timg__SetImagingSettings start\n");
	TRACE("__timg__SetImagingSettings end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __timg__GetOptions(struct soap* soap, struct _timg__GetOptions *timg__GetOptions, struct _timg__GetOptionsResponse *timg__GetOptionsResponse)
{
	TRACE("__timg__GetOptions start\n");
	TRACE("__timg__GetOptions end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __timg__Move(struct soap* soap, struct _timg__Move *timg__Move, struct _timg__MoveResponse *timg__MoveResponse)
{
	TRACE("__timg__Move start\n");
	TRACE("__timg__Move end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __timg__Stop(struct soap* soap, struct _timg__Stop *timg__Stop, struct _timg__StopResponse *timg__StopResponse)
{
	TRACE("__timg__Stop start\n");
	TRACE("__timg__Stop end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __timg__GetStatus(struct soap* soap, struct _timg__GetStatus *timg__GetStatus, struct _timg__GetStatusResponse *timg__GetStatusResponse)
{
	TRACE("__timg__GetStatus start\n");
	TRACE("__timg__GetStatus end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __timg__GetMoveOptions(struct soap* soap, struct _timg__GetMoveOptions *timg__GetMoveOptions, struct _timg__GetMoveOptionsResponse *timg__GetMoveOptionsResponse)
{
	TRACE("__timg__GetMoveOptions start\n");
	TRACE("__timg__GetMoveOptions end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tls__GetServiceCapabilities(struct soap* soap, struct _tls__GetServiceCapabilities *tls__GetServiceCapabilities, struct _tls__GetServiceCapabilitiesResponse *tls__GetServiceCapabilitiesResponse)
{
	TRACE("__tls__GetServiceCapabilities start\n");
	TRACE("__tls__GetServiceCapabilities end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tls__GetLayout(struct soap* soap, struct _tls__GetLayout *tls__GetLayout, struct _tls__GetLayoutResponse *tls__GetLayoutResponse)
{
	TRACE("__tls__GetLayout start\n");
	TRACE("__tls__GetLayout end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tls__SetLayout(struct soap* soap, struct _tls__SetLayout *tls__SetLayout, struct _tls__SetLayoutResponse *tls__SetLayoutResponse)
{
	TRACE("__tls__SetLayout start\n");
	TRACE("__tls__SetLayout end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tls__GetDisplayOptions(struct soap* soap, struct _tls__GetDisplayOptions *tls__GetDisplayOptions, struct _tls__GetDisplayOptionsResponse *tls__GetDisplayOptionsResponse)
{
	TRACE("__tls__GetDisplayOptions start\n");
	TRACE("__tls__GetDisplayOptions end\n");

	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tls__GetPaneConfigurations(struct soap* soap, struct _tls__GetPaneConfigurations *tls__GetPaneConfigurations, struct _tls__GetPaneConfigurationsResponse *tls__GetPaneConfigurationsResponse)
{
	TRACE("__tls__GetPaneConfigurations start\n");
	TRACE("__tls__GetPaneConfigurations end\n");

	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tls__GetPaneConfiguration(struct soap* soap, struct _tls__GetPaneConfiguration *tls__GetPaneConfiguration, struct _tls__GetPaneConfigurationResponse *tls__GetPaneConfigurationResponse)
{
	TRACE("__tls__GetPaneConfiguration start\n");
	TRACE("__tls__GetPaneConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tls__SetPaneConfigurations(struct soap* soap, struct _tls__SetPaneConfigurations *tls__SetPaneConfigurations, struct _tls__SetPaneConfigurationsResponse *tls__SetPaneConfigurationsResponse)
{
	TRACE("__tls__SetPaneConfigurations start\n");
	TRACE("__tls__SetPaneConfigurations end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tls__SetPaneConfiguration(struct soap* soap, struct _tls__SetPaneConfiguration *tls__SetPaneConfiguration, struct _tls__SetPaneConfigurationResponse *tls__SetPaneConfigurationResponse)
{
	TRACE("__tls__SetPaneConfiguration start\n");
	TRACE("__tls__SetPaneConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tls__CreatePaneConfiguration(struct soap* soap, struct _tls__CreatePaneConfiguration *tls__CreatePaneConfiguration, struct _tls__CreatePaneConfigurationResponse *tls__CreatePaneConfigurationResponse)
{
	TRACE("__tls__CreatePaneConfiguration start\n");
	TRACE("__tls__CreatePaneConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tls__DeletePaneConfiguration(struct soap* soap, struct _tls__DeletePaneConfiguration *tls__DeletePaneConfiguration, struct _tls__DeletePaneConfigurationResponse *tls__DeletePaneConfigurationResponse)
{
	TRACE("__tls__DeletePaneConfiguration start\n");
	TRACE("__tls__DeletePaneConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetServiceCapabilities(struct soap* soap, struct _tmd__GetServiceCapabilities *tmd__GetServiceCapabilities, struct _tmd__GetServiceCapabilitiesResponse *tmd__GetServiceCapabilitiesResponse)
{
	TRACE("__tmd__GetServiceCapabilities start\n");
	TRACE("__tmd__GetServiceCapabilities end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetRelayOutputOptions(struct soap* soap, struct _tmd__GetRelayOutputOptions *tmd__GetRelayOutputOptions, struct _tmd__GetRelayOutputOptionsResponse *tmd__GetRelayOutputOptionsResponse)
{
	TRACE("__tmd__GetRelayOutputOptions start\n");
	TRACE("__tmd__GetRelayOutputOptions end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetAudioSources(struct soap* soap, struct _trt__GetAudioSources *trt__GetAudioSources, struct _trt__GetAudioSourcesResponse *trt__GetAudioSourcesResponse)
{
	TRACE("__tmd__GetAudioSources start\n");
	TRACE("__tmd__GetAudioSources end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetAudioOutputs(struct soap* soap, struct _trt__GetAudioOutputs *trt__GetAudioOutputs, struct _trt__GetAudioOutputsResponse *trt__GetAudioOutputsResponse)
{
	TRACE("__tmd__GetAudioOutputs start\n");
	TRACE("__tmd__GetAudioOutputs end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetVideoSources(struct soap* soap, struct _trt__GetVideoSources *trt__GetVideoSources, struct _trt__GetVideoSourcesResponse *trt__GetVideoSourcesResponse)
{
	TRACE("__tmd__GetVideoSources start\n");
	int size1 = 1;
	trt__GetVideoSourcesResponse->__sizeVideoSources = size1;
	trt__GetVideoSourcesResponse->VideoSources = (struct tt__VideoSource*)soap_malloc(soap,sizeof(struct tt__VideoSource) * size1);
	trt__GetVideoSourcesResponse->VideoSources[0].Framerate = 30;
	trt__GetVideoSourcesResponse->VideoSources[0].Resolution = (struct tt__VideoResolution*)soap_malloc(soap,sizeof(struct tt__VideoResolution));
	trt__GetVideoSourcesResponse->VideoSources[0].Resolution->Height = 720;
	trt__GetVideoSourcesResponse->VideoSources[0].Resolution->Width = 1280;

	trt__GetVideoSourcesResponse->VideoSources[0].token = (char*)soap_malloc(soap,sizeof(char) * INFO_LENGTH);
	strcpy( trt__GetVideoSourcesResponse->VideoSources[0].token, "GhostyuSource_token");

	trt__GetVideoSourcesResponse->VideoSources[0].Imaging = (struct tt__ImagingSettings*)soap_malloc(soap,sizeof(struct tt__ImagingSettings));
	trt__GetVideoSourcesResponse->VideoSources[0].Imaging->Brightness = (float*)soap_malloc(soap,sizeof(float));
	trt__GetVideoSourcesResponse->VideoSources[0].Imaging->Brightness[0] = 128;
	trt__GetVideoSourcesResponse->VideoSources[0].Imaging->ColorSaturation = (float*)soap_malloc(soap,sizeof(float));
	trt__GetVideoSourcesResponse->VideoSources[0].Imaging->ColorSaturation[0] = 128;
	trt__GetVideoSourcesResponse->VideoSources[0].Imaging->Contrast = (float*)soap_malloc(soap, sizeof(float));
	trt__GetVideoSourcesResponse->VideoSources[0].Imaging->Contrast[0] = 128;
	trt__GetVideoSourcesResponse->VideoSources[0].Imaging->IrCutFilter = (enum tt__IrCutFilterMode*)soap_malloc(soap,sizeof(enum tt__IrCutFilterMode));
	*(trt__GetVideoSourcesResponse->VideoSources[0].Imaging->IrCutFilter) = tt__IrCutFilterMode__ON;
	trt__GetVideoSourcesResponse->VideoSources[0].Imaging->Sharpness = (float*)soap_malloc(soap,sizeof(float));
	trt__GetVideoSourcesResponse->VideoSources[0].Imaging->Sharpness[0] = 128;
	trt__GetVideoSourcesResponse->VideoSources[0].Imaging->BacklightCompensation = (struct tt__BacklightCompensation*)soap_malloc(soap,sizeof(struct tt__BacklightCompensation));
	trt__GetVideoSourcesResponse->VideoSources[0].Imaging->BacklightCompensation->Mode = tt__BacklightCompensationMode__OFF;
	trt__GetVideoSourcesResponse->VideoSources[0].Imaging->BacklightCompensation->Level = 20;
	trt__GetVideoSourcesResponse->VideoSources[0].Imaging->Exposure = NULL;
	trt__GetVideoSourcesResponse->VideoSources[0].Imaging->Focus = NULL;
	trt__GetVideoSourcesResponse->VideoSources[0].Imaging->WideDynamicRange = (struct tt__WideDynamicRange*)soap_malloc(soap,sizeof(struct tt__WideDynamicRange));
	trt__GetVideoSourcesResponse->VideoSources[0].Imaging->WideDynamicRange->Mode = tt__WideDynamicMode__OFF;
	trt__GetVideoSourcesResponse->VideoSources[0].Imaging->WideDynamicRange->Level = 20;
	trt__GetVideoSourcesResponse->VideoSources[0].Imaging->WhiteBalance = (struct tt__WhiteBalance*)soap_malloc(soap,sizeof(struct tt__WhiteBalance));
	trt__GetVideoSourcesResponse->VideoSources[0].Imaging->WhiteBalance->Mode = tt__WhiteBalanceMode__AUTO;
	trt__GetVideoSourcesResponse->VideoSources[0].Imaging->WhiteBalance->CrGain = 0;
	trt__GetVideoSourcesResponse->VideoSources[0].Imaging->WhiteBalance->CbGain = 0;
	trt__GetVideoSourcesResponse->VideoSources[0].Imaging->Extension = NULL;
	trt__GetVideoSourcesResponse->VideoSources[0].Extension = NULL;

	TRACE("__tmd__GetVideoSources end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetVideoOutputs(struct soap* soap, struct _tmd__GetVideoOutputs *tmd__GetVideoOutputs, struct _tmd__GetVideoOutputsResponse *tmd__GetVideoOutputsResponse)
{
	TRACE("__tmd__GetVideoOutputs start\n");
	TRACE("__tmd__GetVideoOutputs end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetVideoSourceConfiguration(struct soap* soap, struct _tmd__GetVideoSourceConfiguration *tmd__GetVideoSourceConfiguration, struct _tmd__GetVideoSourceConfigurationResponse *tmd__GetVideoSourceConfigurationResponse)
{
	TRACE("__tmd__GetVideoSourceConfiguration start\n");
	TRACE("__tmd__GetVideoSourceConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetVideoOutputConfiguration(struct soap* soap, struct _tmd__GetVideoOutputConfiguration *tmd__GetVideoOutputConfiguration, struct _tmd__GetVideoOutputConfigurationResponse *tmd__GetVideoOutputConfigurationResponse)
{
	TRACE("__tmd__GetVideoOutputConfiguration start\n");
	TRACE("__tmd__GetVideoOutputConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetAudioSourceConfiguration(struct soap* soap, struct _tmd__GetAudioSourceConfiguration *tmd__GetAudioSourceConfiguration, struct _tmd__GetAudioSourceConfigurationResponse *tmd__GetAudioSourceConfigurationResponse)
{
	TRACE("__tmd__GetAudioSourceConfiguration start\n");
	TRACE("__tmd__GetAudioSourceConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetAudioOutputConfiguration(struct soap* soap, struct _tmd__GetAudioOutputConfiguration *tmd__GetAudioOutputConfiguration, struct _tmd__GetAudioOutputConfigurationResponse *tmd__GetAudioOutputConfigurationResponse)
{
	TRACE("__tmd__GetAudioOutputConfiguration start\n");
	TRACE("__tmd__GetAudioOutputConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__SetVideoSourceConfiguration(struct soap* soap, struct _tmd__SetVideoSourceConfiguration *tmd__SetVideoSourceConfiguration, struct _tmd__SetVideoSourceConfigurationResponse *tmd__SetVideoSourceConfigurationResponse)
{
	TRACE("__tmd__SetVideoSourceConfiguration start\n");
	TRACE("__tmd__SetVideoSourceConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__SetVideoOutputConfiguration(struct soap* soap, struct _tmd__SetVideoOutputConfiguration *tmd__SetVideoOutputConfiguration, struct _tmd__SetVideoOutputConfigurationResponse *tmd__SetVideoOutputConfigurationResponse)
{
	TRACE("__tmd__SetVideoOutputConfiguration start\n");
	TRACE("__tmd__SetVideoOutputConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__SetAudioSourceConfiguration(struct soap* soap, struct _tmd__SetAudioSourceConfiguration *tmd__SetAudioSourceConfiguration, struct _tmd__SetAudioSourceConfigurationResponse *tmd__SetAudioSourceConfigurationResponse)
{
	TRACE("__tmd__SetAudioSourceConfiguration start\n");
	TRACE("__tmd__SetAudioSourceConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__SetAudioOutputConfiguration(struct soap* soap, struct _tmd__SetAudioOutputConfiguration *tmd__SetAudioOutputConfiguration, struct _tmd__SetAudioOutputConfigurationResponse *tmd__SetAudioOutputConfigurationResponse)
{
	TRACE("__tmd__SetAudioOutputConfiguration start\n");
	TRACE("__tmd__SetAudioOutputConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetVideoSourceConfigurationOptions(struct soap* soap, struct _tmd__GetVideoSourceConfigurationOptions *tmd__GetVideoSourceConfigurationOptions, struct _tmd__GetVideoSourceConfigurationOptionsResponse *tmd__GetVideoSourceConfigurationOptionsResponse)
{
	TRACE("__tmd__GetVideoSourceConfigurationOptions start\n");
	TRACE("__tmd__GetVideoSourceConfigurationOptions end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetVideoOutputConfigurationOptions(struct soap* soap, struct _tmd__GetVideoOutputConfigurationOptions *tmd__GetVideoOutputConfigurationOptions, struct _tmd__GetVideoOutputConfigurationOptionsResponse *tmd__GetVideoOutputConfigurationOptionsResponse)
{
	TRACE("__tmd__GetVideoOutputConfigurationOptions start\n");
	TRACE("__tmd__GetVideoOutputConfigurationOptions end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetAudioSourceConfigurationOptions(struct soap* soap, struct _tmd__GetAudioSourceConfigurationOptions *tmd__GetAudioSourceConfigurationOptions, struct _tmd__GetAudioSourceConfigurationOptionsResponse *tmd__GetAudioSourceConfigurationOptionsResponse)
{
	TRACE("__tmd__GetAudioSourceConfigurationOptions start\n");
	TRACE("__tmd__GetAudioSourceConfigurationOptions end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetAudioOutputConfigurationOptions(struct soap* soap, struct _tmd__GetAudioOutputConfigurationOptions *tmd__GetAudioOutputConfigurationOptions, struct _tmd__GetAudioOutputConfigurationOptionsResponse *tmd__GetAudioOutputConfigurationOptionsResponse)
{
	TRACE("__tmd__GetAudioOutputConfigurationOptions start\n");
	TRACE("__tmd__GetAudioOutputConfigurationOptions end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetRelayOutputs(struct soap* soap, struct _tds__GetRelayOutputs *tds__GetRelayOutputs, struct _tds__GetRelayOutputsResponse *tds__GetRelayOutputsResponse)
{
	TRACE("__tmd__GetRelayOutputs start\n");
	TRACE("__tmd__GetRelayOutputs end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__SetRelayOutputSettings(struct soap* soap, struct _tmd__SetRelayOutputSettings *tmd__SetRelayOutputSettings, struct _tmd__SetRelayOutputSettingsResponse *tmd__SetRelayOutputSettingsResponse)
{
	TRACE("__tmd__SetRelayOutputSettings start\n");
	TRACE("__tmd__SetRelayOutputSettings end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__SetRelayOutputState(struct soap* soap, struct _tds__SetRelayOutputState *tds__SetRelayOutputState, struct _tds__SetRelayOutputStateResponse *tds__SetRelayOutputStateResponse)
{
	TRACE("__tmd__SetRelayOutputState start\n");
	TRACE("__tmd__SetRelayOutputState end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetDigitalInputs(struct soap* soap, struct _tmd__GetDigitalInputs *tmd__GetDigitalInputs, struct _tmd__GetDigitalInputsResponse *tmd__GetDigitalInputsResponse)
{
	TRACE("__tmd__GetDigitalInputs start\n");
	TRACE("__tmd__GetDigitalInputs end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetSerialPorts(struct soap* soap, struct _tmd__GetSerialPorts *tmd__GetSerialPorts, struct _tmd__GetSerialPortsResponse *tmd__GetSerialPortsResponse)
{
	TRACE("__tmd__GetSerialPorts start\n");
	TRACE("__tmd__GetSerialPorts end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetSerialPortConfiguration(struct soap* soap, struct _tmd__GetSerialPortConfiguration *tmd__GetSerialPortConfiguration, struct _tmd__GetSerialPortConfigurationResponse *tmd__GetSerialPortConfigurationResponse)
{
	TRACE("__tmd__GetSerialPortConfiguration start\n");
	TRACE("__tmd__GetSerialPortConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__SetSerialPortConfiguration(struct soap* soap, struct _tmd__SetSerialPortConfiguration *tmd__SetSerialPortConfiguration, struct _tmd__SetSerialPortConfigurationResponse *tmd__SetSerialPortConfigurationResponse)
{
	TRACE("__tmd__SetSerialPortConfiguration start\n");
	TRACE("__tmd__SetSerialPortConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetSerialPortConfigurationOptions(struct soap* soap, struct _tmd__GetSerialPortConfigurationOptions *tmd__GetSerialPortConfigurationOptions, struct _tmd__GetSerialPortConfigurationOptionsResponse *tmd__GetSerialPortConfigurationOptionsResponse)
{
	TRACE("__tmd__GetSerialPort start\n");
	TRACE("__tmd__GetSerialPort end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__SendReceiveSerialCommand(struct soap* soap, struct _tmd__SendReceiveSerialCommand *tmd__SendReceiveSerialCommand, struct _tmd__SendReceiveSerialCommandResponse *tmd__SendReceiveSerialCommandResponse)
{
	TRACE("__tmd__SendReceiveSerialCommand start\n");
	TRACE("__tmd__SendReceiveSerialCommand end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__GetServiceCapabilities(struct soap* soap, struct _tptz__GetServiceCapabilities *tptz__GetServiceCapabilities, struct _tptz__GetServiceCapabilitiesResponse *tptz__GetServiceCapabilitiesResponse)
{
	TRACE("__tptz__GetServiceCapabilities start\n");
	TRACE("__tptz__GetServiceCapabilities end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__GetConfigurations(struct soap* soap, struct _tptz__GetConfigurations *tptz__GetConfigurations, struct _tptz__GetConfigurationsResponse *tptz__GetConfigurationsResponse)
{
	TRACE("__tptz__GetConfigurations start\n");
	TRACE("__tptz__GetConfigurations end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__GetPresets(struct soap* soap, struct _tptz__GetPresets *tptz__GetPresets, struct _tptz__GetPresetsResponse *tptz__GetPresetsResponse)
{
	TRACE("__tptz__GetPresets start\n");
	TRACE("__tptz__GetPresets end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__SetPreset(struct soap* soap, struct _tptz__SetPreset *tptz__SetPreset, struct _tptz__SetPresetResponse *tptz__SetPresetResponse)
{
	TRACE("__tptz__SetPreset start\n");
	TRACE("__tptz__SetPreset end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__RemovePreset(struct soap* soap, struct _tptz__RemovePreset *tptz__RemovePreset, struct _tptz__RemovePresetResponse *tptz__RemovePresetResponse)
{
	TRACE("__tptz__RemovePreset start\n");
	TRACE("__tptz__RemovePreset end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__GotoPreset(struct soap* soap, struct _tptz__GotoPreset *tptz__GotoPreset, struct _tptz__GotoPresetResponse *tptz__GotoPresetResponse)
{
	TRACE("__tptz__GotoPreset start\n");
	TRACE("__tptz__GotoPreset end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__GetStatus(struct soap* soap, struct _tptz__GetStatus *tptz__GetStatus, struct _tptz__GetStatusResponse *tptz__GetStatusResponse)
{
	TRACE("__tptz__GetStatus start\n");
	TRACE("__tptz__GetStatus end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__GetConfiguration(struct soap* soap, struct _tptz__GetConfiguration *tptz__GetConfiguration, struct _tptz__GetConfigurationResponse *tptz__GetConfigurationResponse)
{
	TRACE("__tptz__GetConfiguration start\n");
	TRACE("__tptz__GetConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__GetNodes(struct soap* soap, struct _tptz__GetNodes *tptz__GetNodes, struct _tptz__GetNodesResponse *tptz__GetNodesResponse)
{
	TRACE("__tptz__GetNodes start\n");
	TRACE("__tptz__GetNodes end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__GetNode(struct soap* soap, struct _tptz__GetNode *tptz__GetNode, struct _tptz__GetNodeResponse *tptz__GetNodeResponse)
{
	TRACE("__tptz__GetNode start\n");
	TRACE("__tptz__GetNode end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__SetConfiguration(struct soap* soap, struct _tptz__SetConfiguration *tptz__SetConfiguration, struct _tptz__SetConfigurationResponse *tptz__SetConfigurationResponse)
{
	TRACE("__tptz__SetConfiguration start\n");
	TRACE("__tptz__SetConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__GetConfigurationOptions(struct soap* soap, struct _tptz__GetConfigurationOptions *tptz__GetConfigurationOptions, struct _tptz__GetConfigurationOptionsResponse *tptz__GetConfigurationOptionsResponse)
{
	TRACE("__tptz__GetConfigurationOptions start\n");
	TRACE("__tptz__GetConfigurationOptions end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__GotoHomePosition(struct soap* soap, struct _tptz__GotoHomePosition *tptz__GotoHomePosition, struct _tptz__GotoHomePositionResponse *tptz__GotoHomePositionResponse)
{
	TRACE("__tptz__GotoHomePosition start\n");
	TRACE("__tptz__GotoHomePosition end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__SetHomePosition(struct soap* soap, struct _tptz__SetHomePosition *tptz__SetHomePosition, struct _tptz__SetHomePositionResponse *tptz__SetHomePositionResponse)
{
	TRACE("__tptz__SetHomePosition start\n");
	TRACE("__tptz__SetHomePosition end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__ContinuousMove(struct soap* soap, struct _tptz__ContinuousMove *tptz__ContinuousMove, struct _tptz__ContinuousMoveResponse *tptz__ContinuousMoveResponse)
{
	TRACE("__tptz__ContinuousMove start\n");
	TRACE("__tptz__ContinuousMove end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__RelativeMove(struct soap* soap, struct _tptz__RelativeMove *tptz__RelativeMove, struct _tptz__RelativeMoveResponse *tptz__RelativeMoveResponse)
{
	TRACE("__tptz__RelativeMove start\n");
	TRACE("__tptz__RelativeMove end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__SendAuxiliaryCommand(struct soap* soap, struct _tptz__SendAuxiliaryCommand *tptz__SendAuxiliaryCommand, struct _tptz__SendAuxiliaryCommandResponse *tptz__SendAuxiliaryCommandResponse)
{
	TRACE("__tptz__SendAuxiliaryCommand start\n");
	TRACE("__tptz__SendAuxiliaryCommand end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__AbsoluteMove(struct soap* soap, struct _tptz__AbsoluteMove *tptz__AbsoluteMove, struct _tptz__AbsoluteMoveResponse *tptz__AbsoluteMoveResponse)
{
	TRACE("__tptz__AbsoluteMove start\n");
	TRACE("__tptz__AbsoluteMove end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__Stop(struct soap* soap, struct _tptz__Stop *tptz__Stop, struct _tptz__StopResponse *tptz__StopResponse)
{
	TRACE("__tptz__Stop start\n");
	TRACE("__tptz__Stop end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__GetPresetTours(struct soap* soap, struct _tptz__GetPresetTours *tptz__GetPresetTours, struct _tptz__GetPresetToursResponse *tptz__GetPresetToursResponse)
{
	TRACE("__tptz__GetPresetTours start\n");
	TRACE("__tptz__GetPresetTours end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__GetPresetTour(struct soap* soap, struct _tptz__GetPresetTour *tptz__GetPresetTour, struct _tptz__GetPresetTourResponse *tptz__GetPresetTourResponse)
{
	TRACE("__tptz__GetPresetTour start\n");
	TRACE("__tptz__GetPresetTour end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__GetPresetTourOptions(struct soap* soap, struct _tptz__GetPresetTourOptions *tptz__GetPresetTourOptions, struct _tptz__GetPresetTourOptionsResponse *tptz__GetPresetTourOptionsResponse)
{
	TRACE("__tptz__GetPresetTourOptions start\n");
	TRACE("__tptz__GetPresetTourOptions end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__CreatePresetTour(struct soap* soap, struct _tptz__CreatePresetTour *tptz__CreatePresetTour, struct _tptz__CreatePresetTourResponse *tptz__CreatePresetTourResponse)
{
	TRACE("__tptz__CreatePresetTour start\n");
	TRACE("__tptz__CreatePresetTour end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__ModifyPresetTour(struct soap* soap, struct _tptz__ModifyPresetTour *tptz__ModifyPresetTour, struct _tptz__ModifyPresetTourResponse *tptz__ModifyPresetTourResponse)
{
	TRACE("__tptz__ModifyPresetTour start\n");
	TRACE("__tptz__ModifyPresetTour end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__OperatePresetTour(struct soap* soap, struct _tptz__OperatePresetTour *tptz__OperatePresetTour, struct _tptz__OperatePresetTourResponse *tptz__OperatePresetTourResponse)
{
	TRACE("__tptz__OperatePresetTour start\n");
	TRACE("__tptz__OperatePresetTour end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__RemovePresetTour(struct soap* soap, struct _tptz__RemovePresetTour *tptz__RemovePresetTour, struct _tptz__RemovePresetTourResponse *tptz__RemovePresetTourResponse)
{
	TRACE("__tptz__RemovePresetTour start\n");
	TRACE("__tptz__RemovePresetTour end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__GetCompatibleConfigurations(struct soap* soap, struct _tptz__GetCompatibleConfigurations *tptz__GetCompatibleConfigurations, struct _tptz__GetCompatibleConfigurationsResponse *tptz__GetCompatibleConfigurationsResponse)
{
	TRACE("__tptz__GetCompatibleConfigurations start\n");
	TRACE("__tptz__GetCompatibleConfigurations end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trc__GetServiceCapabilities(struct soap* soap, struct _trc__GetServiceCapabilities *trc__GetServiceCapabilities, struct _trc__GetServiceCapabilitiesResponse *trc__GetServiceCapabilitiesResponse)
{
	TRACE("__trc__GetServiceCapabilities start\n");
	TRACE("__trc__GetServiceCapabilities end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trc__CreateRecording(struct soap* soap, struct _trc__CreateRecording *trc__CreateRecording, struct _trc__CreateRecordingResponse *trc__CreateRecordingResponse)
{
	TRACE("__trc__CreateRecording start\n");
	TRACE("__trc__CreateRecording end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trc__DeleteRecording(struct soap* soap, struct _trc__DeleteRecording *trc__DeleteRecording, struct _trc__DeleteRecordingResponse *trc__DeleteRecordingResponse)
{
	TRACE("__trc__DeleteRecording start\n");
	TRACE("__trc__DeleteRecording end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trc__GetRecordings(struct soap* soap, struct _trc__GetRecordings *trc__GetRecordings, struct _trc__GetRecordingsResponse *trc__GetRecordingsResponse)
{
	TRACE("__trc__GetRecordings start\n");
	TRACE("__trc__GetRecordings end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trc__SetRecordingConfiguration(struct soap* soap, struct _trc__SetRecordingConfiguration *trc__SetRecordingConfiguration, struct _trc__SetRecordingConfigurationResponse *trc__SetRecordingConfigurationResponse)
{
	TRACE("__trc__SetRecordingConfiguration start\n");
	TRACE("__trc__SetRecordingConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trc__GetRecordingConfiguration(struct soap* soap, struct _trc__GetRecordingConfiguration *trc__GetRecordingConfiguration, struct _trc__GetRecordingConfigurationResponse *trc__GetRecordingConfigurationResponse)
{
	TRACE("__trc__GetRecordingConfiguration start\n");
	TRACE("__trc__GetRecordingConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trc__GetRecordingOptions(struct soap* soap, struct _trc__GetRecordingOptions *trc__GetRecordingOptions, struct _trc__GetRecordingOptionsResponse *trc__GetRecordingOptionsResponse)
{
	TRACE("__trc__GetRecordingOptions start\n");
	TRACE("__trc__GetRecordingOptions end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trc__CreateTrack(struct soap* soap, struct _trc__CreateTrack *trc__CreateTrack, struct _trc__CreateTrackResponse *trc__CreateTrackResponse)
{
	TRACE("__trc__CreateTrack start\n");
	TRACE("__trc__CreateTrack end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trc__DeleteTrack(struct soap* soap, struct _trc__DeleteTrack *trc__DeleteTrack, struct _trc__DeleteTrackResponse *trc__DeleteTrackResponse)
{
	TRACE("__trc__DeleteTrack start\n");
	TRACE("__trc__DeleteTrack end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trc__GetTrackConfiguration(struct soap* soap, struct _trc__GetTrackConfiguration *trc__GetTrackConfiguration, struct _trc__GetTrackConfigurationResponse *trc__GetTrackConfigurationResponse)
{
	TRACE("__trc__GetTrackConfiguration start\n");
	TRACE("__trc__GetTrackConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trc__SetTrackConfiguration(struct soap* soap, struct _trc__SetTrackConfiguration *trc__SetTrackConfiguration, struct _trc__SetTrackConfigurationResponse *trc__SetTrackConfigurationResponse)
{
	TRACE("__trc__SetTrackConfiguration start\n");
	TRACE("__trc__SetTrackConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trc__CreateRecordingJob(struct soap* soap, struct _trc__CreateRecordingJob *trc__CreateRecordingJob, struct _trc__CreateRecordingJobResponse *trc__CreateRecordingJobResponse)
{
	TRACE("__trc__CreateRecordingJob start\n");
	TRACE("__trc__CreateRecordingJob end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trc__DeleteRecordingJob(struct soap* soap, struct _trc__DeleteRecordingJob *trc__DeleteRecordingJob, struct _trc__DeleteRecordingJobResponse *trc__DeleteRecordingJobResponse)
{
	TRACE("__trc__DeleteRecordingJob start\n");
	TRACE("__trc__DeleteRecordingJob end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trc__GetRecordingJobs(struct soap* soap, struct _trc__GetRecordingJobs *trc__GetRecordingJobs, struct _trc__GetRecordingJobsResponse *trc__GetRecordingJobsResponse)
{
	TRACE("__trc__GetRecordingJobs start\n");
	TRACE("__trc__GetRecordingJobs end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trc__SetRecordingJobConfiguration(struct soap* soap, struct _trc__SetRecordingJobConfiguration *trc__SetRecordingJobConfiguration, struct _trc__SetRecordingJobConfigurationResponse *trc__SetRecordingJobConfigurationResponse)
{
	TRACE("__trc__SetRecordingJobConfiguration start\n");
	TRACE("__trc__SetRecordingJobConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trc__GetRecordingJobConfiguration(struct soap* soap, struct _trc__GetRecordingJobConfiguration *trc__GetRecordingJobConfiguration, struct _trc__GetRecordingJobConfigurationResponse *trc__GetRecordingJobConfigurationResponse)
{
	TRACE("__trc__GetRecordingJobConfiguration start\n");
	TRACE("__trc__GetRecordingJobConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trc__SetRecordingJobMode(struct soap* soap, struct _trc__SetRecordingJobMode *trc__SetRecordingJobMode, struct _trc__SetRecordingJobModeResponse *trc__SetRecordingJobModeResponse)
{
	TRACE("__trc__SetRecordingJobMode start\n");
	TRACE("__trc__SetRecordingJobMode end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trc__GetRecordingJobState(struct soap* soap, struct _trc__GetRecordingJobState *trc__GetRecordingJobState, struct _trc__GetRecordingJobStateResponse *trc__GetRecordingJobStateResponse)
{
	TRACE("__trc__GetRecordingJobState start\n");
	TRACE("__trc__GetRecordingJobState end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trp__GetServiceCapabilities(struct soap* soap, struct _trp__GetServiceCapabilities *trp__GetServiceCapabilities, struct _trp__GetServiceCapabilitiesResponse *trp__GetServiceCapabilitiesResponse)
{
	TRACE("__trp__GetServiceCapabilities start\n");
	TRACE("__trp__GetServiceCapabilities end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trp__GetReplayUri(struct soap* soap, struct _trp__GetReplayUri *trp__GetReplayUri, struct _trp__GetReplayUriResponse *trp__GetReplayUriResponse)
{
	TRACE("__trp__GetReplayUri start\n");
	TRACE("__trp__GetReplayUri end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trp__GetReplayConfiguration(struct soap* soap, struct _trp__GetReplayConfiguration *trp__GetReplayConfiguration, struct _trp__GetReplayConfigurationResponse *trp__GetReplayConfigurationResponse)
{
	TRACE("__trp__GetReplayConfiguration start\n");
	TRACE("__trp__GetReplayConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trp__SetReplayConfiguration(struct soap* soap, struct _trp__SetReplayConfiguration *trp__SetReplayConfiguration, struct _trp__SetReplayConfigurationResponse *trp__SetReplayConfigurationResponse)
{
	TRACE("__trp__SetReplayConfiguration start\n");
	TRACE("__trp__SetReplayConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetServiceCapabilities(struct soap* soap, struct _trt__GetServiceCapabilities *trt__GetServiceCapabilities, struct _trt__GetServiceCapabilitiesResponse *trt__GetServiceCapabilitiesResponse)
{
	TRACE("__trt__GetServiceCapabilities start\n");
	TRACE("__trt__GetServiceCapabilities end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoSources(struct soap* soap, struct _trt__GetVideoSources *trt__GetVideoSources, struct _trt__GetVideoSourcesResponse *trt__GetVideoSourcesResponse)
{
	TRACE("__trt__GetVideoSources start\n");
	TRACE("__trt__GetVideoSources end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioSources(struct soap* soap, struct _trt__GetAudioSources *trt__GetAudioSources, struct _trt__GetAudioSourcesResponse *trt__GetAudioSourcesResponse)
{
	TRACE("__trt__GetAudioSources start\n");
	TRACE("__trt__GetAudioSources end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioOutputs(struct soap* soap, struct _trt__GetAudioOutputs *trt__GetAudioOutputs, struct _trt__GetAudioOutputsResponse *trt__GetAudioOutputsResponse)
{
	TRACE("__trt__GetAudioOutputs start\n");
	TRACE("__trt__GetAudioOutputs end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__CreateProfile(struct soap* soap, struct _trt__CreateProfile *trt__CreateProfile, struct _trt__CreateProfileResponse *trt__CreateProfileResponse)
{
	TRACE("__trt__CreateProfile start\n");
	if( trt__CreateProfile != NULL)
	{
		if( g_uProfileCount < SIZE_PROFILE)
		{
			if( trt__CreateProfile->Name != NULL)
			{
				g_ProfileList[g_uProfileCount].Name = (char*)malloc(sizeof(char) * SMALL_INFO_LENGTH);
				strcpy( g_ProfileList[g_uProfileCount].Name,trt__CreateProfile->Name);
			}
			if( trt__CreateProfile->Token != NULL)
			{
				g_ProfileList[g_uProfileCount].token = (char*)malloc(sizeof(char) * SMALL_INFO_LENGTH);
				strcpy( g_ProfileList[g_uProfileCount].token, trt__CreateProfile->Token);
			}
			if ( trt__CreateProfileResponse != NULL)
			{
				trt__CreateProfileResponse->Profile = (struct tt__Profile*)soap_malloc(soap,sizeof(struct tt__Profile));
//				g_CopyProfile(trt__CreateProfileResponse->Profile,&g_ProfileList[g_uProfileCount]);
			}
			g_uProfileCount++;
		}
	}
	TRACE("__trt__CreateProfile end\n");
	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetProfile(struct soap* soap, struct _trt__GetProfile *trt__GetProfile, struct _trt__GetProfileResponse *trt__GetProfileResponse)
{
	TRACE("__trt__GetProfile start\n");
	TRACE("__trt__GetProfile end\n");
	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetProfiles(struct soap* soap, struct _trt__GetProfiles *trt__GetProfiles, struct _trt__GetProfilesResponse *trt__GetProfilesResponse)
{
	TRACE("__trt__GetProfiles start\n");
	if( trt__GetProfilesResponse != NULL)
	{
		trt__GetProfilesResponse->__sizeProfiles = g_uProfileCount;
		trt__GetProfilesResponse->Profiles = (struct tt__Profile*)soap_malloc(soap,sizeof(struct tt__Profile) * g_uProfileCount);
		int i = 0;
		for( i = 0; i < g_uProfileCount; i++)
		{
			g_CopyProfile(soap,&(trt__GetProfilesResponse->Profiles[i]),&(g_ProfileList[i]));
		}
	}
	else
	{
		TRACE("__trt__GetProfiles,trt__GetProfilesResponse == NULL\n");
	}
	TRACE("__trt__GetProfiles end\n");
	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __trt__AddVideoEncoderConfiguration(struct soap* soap, struct _trt__AddVideoEncoderConfiguration *trt__AddVideoEncoderConfiguration, struct _trt__AddVideoEncoderConfigurationResponse *trt__AddVideoEncoderConfigurationResponse)
{
	TRACE("__trt__AddVideoEncoderConfiguration start\n");
	TRACE("__trt__AddVideoEncoderConfiguration end\n");
	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __trt__AddVideoSourceConfiguration(struct soap* soap, struct _trt__AddVideoSourceConfiguration *trt__AddVideoSourceConfiguration, struct _trt__AddVideoSourceConfigurationResponse *trt__AddVideoSourceConfigurationResponse)
{
	TRACE("__trt__AddVideoSourceConfiguration start\n");
	TRACE("__trt__AddVideoSourceConfiguration end\n");
	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __trt__AddAudioEncoderConfiguration(struct soap* soap, struct _trt__AddAudioEncoderConfiguration *trt__AddAudioEncoderConfiguration, struct _trt__AddAudioEncoderConfigurationResponse *trt__AddAudioEncoderConfigurationResponse)
{
	TRACE("__trt__AddAudioEncoderConfiguration start\n");
	TRACE("__trt__AddAudioEncoderConfiguration end\n");
	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __trt__AddAudioSourceConfiguration(struct soap* soap, struct _trt__AddAudioSourceConfiguration *trt__AddAudioSourceConfiguration, struct _trt__AddAudioSourceConfigurationResponse *trt__AddAudioSourceConfigurationResponse)
{
	TRACE("__trt__AddAudioSourceConfiguration start\n");
	TRACE("__trt__AddAudioSourceConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__AddPTZConfiguration(struct soap* soap, struct _trt__AddPTZConfiguration *trt__AddPTZConfiguration, struct _trt__AddPTZConfigurationResponse *trt__AddPTZConfigurationResponse)
{
	TRACE("__trt__AddPTZConfiguration start\n");
	TRACE("__trt__AddPTZConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__AddVideoAnalyticsConfiguration(struct soap* soap, struct _trt__AddVideoAnalyticsConfiguration *trt__AddVideoAnalyticsConfiguration, struct _trt__AddVideoAnalyticsConfigurationResponse *trt__AddVideoAnalyticsConfigurationResponse)
{
	TRACE("__trt__AddVideoAnalyticsConfiguration start\n");
	TRACE("__trt__AddVideoAnalyticsConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__AddMetadataConfiguration(struct soap* soap, struct _trt__AddMetadataConfiguration *trt__AddMetadataConfiguration, struct _trt__AddMetadataConfigurationResponse *trt__AddMetadataConfigurationResponse)
{
	TRACE("__trt__AddMetadataConfiguration start\n");
	TRACE("__trt__AddMetadataConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__AddAudioOutputConfiguration(struct soap* soap, struct _trt__AddAudioOutputConfiguration *trt__AddAudioOutputConfiguration, struct _trt__AddAudioOutputConfigurationResponse *trt__AddAudioOutputConfigurationResponse)
{
	TRACE("__trt__AddAudioOutputConfiguration start\n");
	TRACE("__trt__AddAudioOutputConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__AddAudioDecoderConfiguration(struct soap* soap, struct _trt__AddAudioDecoderConfiguration *trt__AddAudioDecoderConfiguration, struct _trt__AddAudioDecoderConfigurationResponse *trt__AddAudioDecoderConfigurationResponse)
{
	TRACE("__trt__AddAudioDecoderConfiguration start\n");
	TRACE("__trt__AddAudioDecoderConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveVideoEncoderConfiguration(struct soap* soap, struct _trt__RemoveVideoEncoderConfiguration *trt__RemoveVideoEncoderConfiguration, struct _trt__RemoveVideoEncoderConfigurationResponse *trt__RemoveVideoEncoderConfigurationResponse)
{
	TRACE("__trt__RemoveVideoEncoderConfiguration start\n");
	TRACE("__trt__RemoveVideoEncoderConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveVideoSourceConfiguration(struct soap* soap, struct _trt__RemoveVideoSourceConfiguration *trt__RemoveVideoSourceConfiguration, struct _trt__RemoveVideoSourceConfigurationResponse *trt__RemoveVideoSourceConfigurationResponse)
{
	TRACE("__trt__RemoveVideoSourceConfiguration start\n");
	TRACE("__trt__RemoveVideoSourceConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveAudioEncoderConfiguration(struct soap* soap, struct _trt__RemoveAudioEncoderConfiguration *trt__RemoveAudioEncoderConfiguration, struct _trt__RemoveAudioEncoderConfigurationResponse *trt__RemoveAudioEncoderConfigurationResponse)
{
	TRACE("__trt__RemoveAudioEncoderConfiguration start\n");
	TRACE("__trt__RemoveAudioEncoderConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveAudioSourceConfiguration(struct soap* soap, struct _trt__RemoveAudioSourceConfiguration *trt__RemoveAudioSourceConfiguration, struct _trt__RemoveAudioSourceConfigurationResponse *trt__RemoveAudioSourceConfigurationResponse)
{
	TRACE("__trt__RemoveAudioSourceConfiguration start\n");
	TRACE("__trt__RemoveAudioSourceConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__RemovePTZConfiguration(struct soap* soap, struct _trt__RemovePTZConfiguration *trt__RemovePTZConfiguration, struct _trt__RemovePTZConfigurationResponse *trt__RemovePTZConfigurationResponse)
{
	TRACE("__trt__RemovePTZConfiguration start\n");
	TRACE("__trt__RemovePTZConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveVideoAnalyticsConfiguration(struct soap* soap, struct _trt__RemoveVideoAnalyticsConfiguration *trt__RemoveVideoAnalyticsConfiguration, struct _trt__RemoveVideoAnalyticsConfigurationResponse *trt__RemoveVideoAnalyticsConfigurationResponse)
{
	TRACE("__trt__RemoveVideoAnalyticsConfiguration start\n");
	TRACE("__trt__RemoveVideoAnalyticsConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveMetadataConfiguration(struct soap* soap, struct _trt__RemoveMetadataConfiguration *trt__RemoveMetadataConfiguration, struct _trt__RemoveMetadataConfigurationResponse *trt__RemoveMetadataConfigurationResponse)
{
	TRACE("__trt__RemoveMetadataConfiguration start\n");
	TRACE("__trt__RemoveMetadataConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveAudioOutputConfiguration(struct soap* soap, struct _trt__RemoveAudioOutputConfiguration *trt__RemoveAudioOutputConfiguration, struct _trt__RemoveAudioOutputConfigurationResponse *trt__RemoveAudioOutputConfigurationResponse)
{
	TRACE("__trt__RemoveAudioOutputConfiguration start\n");
	TRACE("__trt__RemoveAudioOutputConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveAudioDecoderConfiguration(struct soap* soap, struct _trt__RemoveAudioDecoderConfiguration *trt__RemoveAudioDecoderConfiguration, struct _trt__RemoveAudioDecoderConfigurationResponse *trt__RemoveAudioDecoderConfigurationResponse)
{
	TRACE("__trt__RemoveAudioDecoderConfiguration start\n");
	TRACE("__trt__RemoveAudioDecoderConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__DeleteProfile(struct soap* soap, struct _trt__DeleteProfile *trt__DeleteProfile, struct _trt__DeleteProfileResponse *trt__DeleteProfileResponse)
{
	TRACE("__trt__DeleteProfile start\n");
	TRACE("__trt__DeleteProfile end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoSourceConfigurations(struct soap* soap, struct _trt__GetVideoSourceConfigurations *trt__GetVideoSourceConfigurations, struct _trt__GetVideoSourceConfigurationsResponse *trt__GetVideoSourceConfigurationsResponse)
{
	TRACE("__trt__GetVideoSourceConfigurations start\n");
	TRACE("__trt__GetVideoSourceConfigurations end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoEncoderConfigurations(struct soap* soap, struct _trt__GetVideoEncoderConfigurations *trt__GetVideoEncoderConfigurations, struct _trt__GetVideoEncoderConfigurationsResponse *trt__GetVideoEncoderConfigurationsResponse)
{
	TRACE("__trt__GetVideoEncoderConfigurations start\n");
	TRACE("__trt__GetVideoEncoderConfigurations end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioSourceConfigurations(struct soap* soap, struct _trt__GetAudioSourceConfigurations *trt__GetAudioSourceConfigurations, struct _trt__GetAudioSourceConfigurationsResponse *trt__GetAudioSourceConfigurationsResponse)
{
	TRACE("__trt__GetAudioSourceConfigurations start\n");
	TRACE("__trt__GetAudioSourceConfigurations end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioEncoderConfigurations(struct soap* soap, struct _trt__GetAudioEncoderConfigurations *trt__GetAudioEncoderConfigurations, struct _trt__GetAudioEncoderConfigurationsResponse *trt__GetAudioEncoderConfigurationsResponse)
{
	TRACE("__trt__GetAudioEncoderConfigurations start\n");
	TRACE("__trt__GetAudioEncoderConfigurations end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoAnalyticsConfigurations(struct soap* soap, struct _trt__GetVideoAnalyticsConfigurations *trt__GetVideoAnalyticsConfigurations, struct _trt__GetVideoAnalyticsConfigurationsResponse *trt__GetVideoAnalyticsConfigurationsResponse)
{
	TRACE("__trt__GetVideoAnalyticsConfigurations start\n");
	TRACE("__trt__GetVideoAnalyticsConfigurations end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetMetadataConfigurations(struct soap* soap, struct _trt__GetMetadataConfigurations *trt__GetMetadataConfigurations, struct _trt__GetMetadataConfigurationsResponse *trt__GetMetadataConfigurationsResponse)
{
	TRACE("__trt__GetMetadataConfigurations start\n");
	TRACE("__trt__GetMetadataConfigurations end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioOutputConfigurations(struct soap* soap, struct _trt__GetAudioOutputConfigurations *trt__GetAudioOutputConfigurations, struct _trt__GetAudioOutputConfigurationsResponse *trt__GetAudioOutputConfigurationsResponse)
{
	TRACE("__trt__GetAudioOutputConfigurations start\n");
	TRACE("__trt__GetAudioOutputConfigurations end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioDecoderConfigurations(struct soap* soap, struct _trt__GetAudioDecoderConfigurations *trt__GetAudioDecoderConfigurations, struct _trt__GetAudioDecoderConfigurationsResponse *trt__GetAudioDecoderConfigurationsResponse)
{
	TRACE("__trt__GetAudioDecoderConfigurations start\n");
	TRACE("__trt__GetAudioDecoderConfigurations end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoSourceConfiguration(struct soap* soap, struct _trt__GetVideoSourceConfiguration *trt__GetVideoSourceConfiguration, struct _trt__GetVideoSourceConfigurationResponse *trt__GetVideoSourceConfigurationResponse)
{
	TRACE("__trt__GetVideoSourceConfiguration start\n");
	TRACE("__trt__GetVideoSourceConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoEncoderConfiguration(struct soap* soap, struct _trt__GetVideoEncoderConfiguration *trt__GetVideoEncoderConfiguration, struct _trt__GetVideoEncoderConfigurationResponse *trt__GetVideoEncoderConfigurationResponse)
{
	TRACE("__trt__GetVideoEncoderConfiguration start\n");
	TRACE("__trt__GetVideoEncoderConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioSourceConfiguration(struct soap* soap, struct _trt__GetAudioSourceConfiguration *trt__GetAudioSourceConfiguration, struct _trt__GetAudioSourceConfigurationResponse *trt__GetAudioSourceConfigurationResponse)
{
	TRACE("__trt__GetAudioSourceConfiguration start\n");
	TRACE("__trt__GetAudioSourceConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioEncoderConfiguration(struct soap* soap, struct _trt__GetAudioEncoderConfiguration *trt__GetAudioEncoderConfiguration, struct _trt__GetAudioEncoderConfigurationResponse *trt__GetAudioEncoderConfigurationResponse)
{
	TRACE("__trt__GetAudioEncoderConfiguration start\n");
	TRACE("__trt__GetAudioEncoderConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoAnalyticsConfiguration(struct soap* soap, struct _trt__GetVideoAnalyticsConfiguration *trt__GetVideoAnalyticsConfiguration, struct _trt__GetVideoAnalyticsConfigurationResponse *trt__GetVideoAnalyticsConfigurationResponse)
{
	TRACE("__trt__GetVideoAnalyticsConfiguration start\n");
	TRACE("__trt__GetVideoAnalyticsConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetMetadataConfiguration(struct soap* soap, struct _trt__GetMetadataConfiguration *trt__GetMetadataConfiguration, struct _trt__GetMetadataConfigurationResponse *trt__GetMetadataConfigurationResponse)
{
	TRACE("__trt__GetMetadataConfiguration start\n");
	TRACE("__trt__GetMetadataConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioOutputConfiguration(struct soap* soap, struct _trt__GetAudioOutputConfiguration *trt__GetAudioOutputConfiguration, struct _trt__GetAudioOutputConfigurationResponse *trt__GetAudioOutputConfigurationResponse)
{
	TRACE("__trt__GetAudioOutputConfiguration start\n");
	TRACE("__trt__GetAudioOutputConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioDecoderConfiguration(struct soap* soap, struct _trt__GetAudioDecoderConfiguration *trt__GetAudioDecoderConfiguration, struct _trt__GetAudioDecoderConfigurationResponse *trt__GetAudioDecoderConfigurationResponse)
{
	TRACE("__trt__GetAudioDecoderConfiguration start\n");
	TRACE("__trt__GetAudioDecoderConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleVideoEncoderConfigurations(struct soap* soap, struct _trt__GetCompatibleVideoEncoderConfigurations *trt__GetCompatibleVideoEncoderConfigurations, struct _trt__GetCompatibleVideoEncoderConfigurationsResponse *trt__GetCompatibleVideoEncoderConfigurationsResponse)
{
	TRACE("__trt__GetCompatibleVideoEncoderConfigurations start\n");
	TRACE("__trt__GetCompatibleVideoEncoderConfigurations end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleVideoSourceConfigurations(struct soap* soap, struct _trt__GetCompatibleVideoSourceConfigurations *trt__GetCompatibleVideoSourceConfigurations, struct _trt__GetCompatibleVideoSourceConfigurationsResponse *trt__GetCompatibleVideoSourceConfigurationsResponse)
{
	TRACE("__trt__GetCompatibleVideoSourceConfigurations start\n");
	TRACE("__trt__GetCompatibleVideoSourceConfigurations end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleAudioEncoderConfigurations(struct soap* soap, struct _trt__GetCompatibleAudioEncoderConfigurations *trt__GetCompatibleAudioEncoderConfigurations, struct _trt__GetCompatibleAudioEncoderConfigurationsResponse *trt__GetCompatibleAudioEncoderConfigurationsResponse)
{
	TRACE("__trt__GetCompatibleAudioEncoderConfigurations start\n");
	TRACE("__trt__GetCompatibleAudioEncoderConfigurations end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleAudioSourceConfigurations(struct soap* soap, struct _trt__GetCompatibleAudioSourceConfigurations *trt__GetCompatibleAudioSourceConfigurations, struct _trt__GetCompatibleAudioSourceConfigurationsResponse *trt__GetCompatibleAudioSourceConfigurationsResponse)
{
	TRACE("__trt__GetCompatibleAudioSourceConfigurations start\n");
	TRACE("__trt__GetCompatibleAudioSourceConfigurations end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleVideoAnalyticsConfigurations(struct soap* soap, struct _trt__GetCompatibleVideoAnalyticsConfigurations *trt__GetCompatibleVideoAnalyticsConfigurations, struct _trt__GetCompatibleVideoAnalyticsConfigurationsResponse *trt__GetCompatibleVideoAnalyticsConfigurationsResponse)
{
	TRACE("__trt__GetCompatibleVideoAnalyticsConfigurations start\n");
	TRACE("__trt__GetCompatibleVideoAnalyticsConfigurations end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleMetadataConfigurations(struct soap* soap, struct _trt__GetCompatibleMetadataConfigurations *trt__GetCompatibleMetadataConfigurations, struct _trt__GetCompatibleMetadataConfigurationsResponse *trt__GetCompatibleMetadataConfigurationsResponse)
{
	TRACE("__trt__GetCompatibleMetadataConfigurations start\n");
	TRACE("__trt__GetCompatibleMetadataConfigurations end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleAudioOutputConfigurations(struct soap* soap, struct _trt__GetCompatibleAudioOutputConfigurations *trt__GetCompatibleAudioOutputConfigurations, struct _trt__GetCompatibleAudioOutputConfigurationsResponse *trt__GetCompatibleAudioOutputConfigurationsResponse)
{
	TRACE("__trt__GetCompatibleAudioOutputConfigurations start\n");
	TRACE("__trt__GetCompatibleAudioOutputConfigurations end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleAudioDecoderConfigurations(struct soap* soap, struct _trt__GetCompatibleAudioDecoderConfigurations *trt__GetCompatibleAudioDecoderConfigurations, struct _trt__GetCompatibleAudioDecoderConfigurationsResponse *trt__GetCompatibleAudioDecoderConfigurationsResponse)
{
	TRACE("__trt__GetCompatibleAudioDecoderConfigurations start\n");
	TRACE("__trt__GetCompatibleAudioDecoderConfigurations end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__SetVideoSourceConfiguration(struct soap* soap, struct _trt__SetVideoSourceConfiguration *trt__SetVideoSourceConfiguration, struct _trt__SetVideoSourceConfigurationResponse *trt__SetVideoSourceConfigurationResponse)
{
	TRACE("__trt__SetVideoSourceConfiguration start\n");
	TRACE("__trt__SetVideoSourceConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__SetVideoEncoderConfiguration(struct soap* soap, struct _trt__SetVideoEncoderConfiguration *trt__SetVideoEncoderConfiguration, struct _trt__SetVideoEncoderConfigurationResponse *trt__SetVideoEncoderConfigurationResponse)
{
	TRACE("__trt__SetVideoEncoderConfiguration start\n");
	TRACE("__trt__SetVideoEncoderConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__SetAudioSourceConfiguration(struct soap* soap, struct _trt__SetAudioSourceConfiguration *trt__SetAudioSourceConfiguration, struct _trt__SetAudioSourceConfigurationResponse *trt__SetAudioSourceConfigurationResponse)
{
	TRACE("__trt__SetAudioSourceConfiguration start\n");
	TRACE("__trt__SetAudioSourceConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__SetAudioEncoderConfiguration(struct soap* soap, struct _trt__SetAudioEncoderConfiguration *trt__SetAudioEncoderConfiguration, struct _trt__SetAudioEncoderConfigurationResponse *trt__SetAudioEncoderConfigurationResponse)
{
	TRACE("__trt__SetAudioEncoderConfiguration start\n");
	TRACE("__trt__SetAudioEncoderConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__SetVideoAnalyticsConfiguration(struct soap* soap, struct _trt__SetVideoAnalyticsConfiguration *trt__SetVideoAnalyticsConfiguration, struct _trt__SetVideoAnalyticsConfigurationResponse *trt__SetVideoAnalyticsConfigurationResponse)
{
	TRACE("__trt__SetVideoAnalyticsConfiguration start\n");
	TRACE("__trt__SetVideoAnalyticsConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__SetMetadataConfiguration(struct soap* soap, struct _trt__SetMetadataConfiguration *trt__SetMetadataConfiguration, struct _trt__SetMetadataConfigurationResponse *trt__SetMetadataConfigurationResponse)
{
	TRACE("__trt__SetMetadataConfiguration start\n");
	TRACE("__trt__SetMetadataConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__SetAudioOutputConfiguration(struct soap* soap, struct _trt__SetAudioOutputConfiguration *trt__SetAudioOutputConfiguration, struct _trt__SetAudioOutputConfigurationResponse *trt__SetAudioOutputConfigurationResponse)
{
	TRACE("__trt__SetAudioOutputConfiguration start\n");
	TRACE("__trt__SetAudioOutputConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__SetAudioDecoderConfiguration(struct soap* soap, struct _trt__SetAudioDecoderConfiguration *trt__SetAudioDecoderConfiguration, struct _trt__SetAudioDecoderConfigurationResponse *trt__SetAudioDecoderConfigurationResponse)
{
	TRACE("__trt__SetAudioDecoderConfiguration start\n");
	TRACE("__trt__SetAudioDecoderConfiguration end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoSourceConfigurationOptions(struct soap* soap, struct _trt__GetVideoSourceConfigurationOptions *trt__GetVideoSourceConfigurationOptions, struct _trt__GetVideoSourceConfigurationOptionsResponse *trt__GetVideoSourceConfigurationOptionsResponse)
{
	TRACE("__trt__GetVideoSourceConfigurationOptions start\n");
	TRACE("__trt__GetVideoSourceConfigurationOptions end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoEncoderConfigurationOptions(struct soap* soap, struct _trt__GetVideoEncoderConfigurationOptions *trt__GetVideoEncoderConfigurationOptions, struct _trt__GetVideoEncoderConfigurationOptionsResponse *trt__GetVideoEncoderConfigurationOptionsResponse)
{
	TRACE("__trt__GetVideoEncoderConfigurationOptions start\n");
	TRACE("__trt__GetVideoEncoderConfigurationOptions end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioSourceConfigurationOptions(struct soap* soap, struct _trt__GetAudioSourceConfigurationOptions *trt__GetAudioSourceConfigurationOptions, struct _trt__GetAudioSourceConfigurationOptionsResponse *trt__GetAudioSourceConfigurationOptionsResponse)
{
	TRACE("__trt__GetAudioSourceConfigurationOptions start\n");
	TRACE("__trt__GetAudioSourceConfigurationOptions end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioEncoderConfigurationOptions(struct soap* soap, struct _trt__GetAudioEncoderConfigurationOptions *trt__GetAudioEncoderConfigurationOptions, struct _trt__GetAudioEncoderConfigurationOptionsResponse *trt__GetAudioEncoderConfigurationOptionsResponse)
{
	TRACE("__trt__GetAudioEncoderConfigurationOptions start\n");
	TRACE("__trt__GetAudioEncoderConfigurationOptions end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetMetadataConfigurationOptions(struct soap* soap, struct _trt__GetMetadataConfigurationOptions *trt__GetMetadataConfigurationOptions, struct _trt__GetMetadataConfigurationOptionsResponse *trt__GetMetadataConfigurationOptionsResponse)
{
	TRACE("__trt__GetMetadataConfigurationOptions start\n");
	TRACE("__trt__GetMetadataConfigurationOptions end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioOutputConfigurationOptions(struct soap* soap, struct _trt__GetAudioOutputConfigurationOptions *trt__GetAudioOutputConfigurationOptions, struct _trt__GetAudioOutputConfigurationOptionsResponse *trt__GetAudioOutputConfigurationOptionsResponse)
{
	TRACE("__trt__GetAudioOutputConfigurationOptions start\n");
	TRACE("__trt__GetAudioOutputConfigurationOptions end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioDecoderConfigurationOptions(struct soap* soap, struct _trt__GetAudioDecoderConfigurationOptions *trt__GetAudioDecoderConfigurationOptions, struct _trt__GetAudioDecoderConfigurationOptionsResponse *trt__GetAudioDecoderConfigurationOptionsResponse)
{
	TRACE("__trt__GetAudioDecoderConfigurationOptions start\n");
	TRACE("__trt__GetAudioDecoderConfigurationOptions end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetGuaranteedNumberOfVideoEncoderInstances(struct soap* soap, struct _trt__GetGuaranteedNumberOfVideoEncoderInstances *trt__GetGuaranteedNumberOfVideoEncoderInstances, struct _trt__GetGuaranteedNumberOfVideoEncoderInstancesResponse *trt__GetGuaranteedNumberOfVideoEncoderInstancesResponse)
{
	TRACE("__trt__GetGuaranteedNumberOfVideoEncoderInstances start\n");
	TRACE("__trt__GetGuaranteedNumberOfVideoEncoderInstances end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetStreamUri(struct soap* soap, struct _trt__GetStreamUri *trt__GetStreamUri, struct _trt__GetStreamUriResponse *trt__GetStreamUriResponse)
{
	TRACE("__trt__GetStreamUri start\n");
	char cURI[INFO_LENGTH] = {0};
	g_GetMediaURI(cURI,INFO_LENGTH - 1);
	trt__GetStreamUriResponse->MediaUri = (struct tt__MediaUri*)soap_malloc(soap,sizeof(struct tt__MediaUri));
	trt__GetStreamUriResponse->MediaUri->Uri = (char*)soap_malloc(soap,sizeof(char) * INFO_LENGTH);
	strcpy( trt__GetStreamUriResponse->MediaUri->Uri,cURI);
	trt__GetStreamUriResponse->MediaUri->Timeout = 200;
	trt__GetStreamUriResponse->MediaUri->InvalidAfterConnect = xsd__boolean__false_;
	trt__GetStreamUriResponse->MediaUri->InvalidAfterReboot = xsd__boolean__false_;
	TRACE("__trt__GetStreamUri end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__StartMulticastStreaming(struct soap* soap, struct _trt__StartMulticastStreaming *trt__StartMulticastStreaming, struct _trt__StartMulticastStreamingResponse *trt__StartMulticastStreamingResponse)
{
	TRACE("__trt__StartMulticastStreaming start\n");
	TRACE("__trt__StartMulticastStreaming end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__StopMulticastStreaming(struct soap* soap, struct _trt__StopMulticastStreaming *trt__StopMulticastStreaming, struct _trt__StopMulticastStreamingResponse *trt__StopMulticastStreamingResponse)
{
	TRACE("__trt__StopMulticastStreaming start\n");
	TRACE("__trt__StopMulticastStreaming end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__SetSynchronizationPoint(struct soap* soap, struct _trt__SetSynchronizationPoint *trt__SetSynchronizationPoint, struct _trt__SetSynchronizationPointResponse *trt__SetSynchronizationPointResponse)
{
	TRACE("__trt__SetSynchronizationPoint start\n");
	TRACE("__trt__SetSynchronizationPoint end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetSnapshotUri(struct soap* soap, struct _trt__GetSnapshotUri *trt__GetSnapshotUri, struct _trt__GetSnapshotUriResponse *trt__GetSnapshotUriResponse)
{
	TRACE("__trt__GetSnapshotUri start\n");
	TRACE("__trt__GetSnapshotUri end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoSourceModes(struct soap* soap, struct _trt__GetVideoSourceModes *trt__GetVideoSourceModes, struct _trt__GetVideoSourceModesResponse *trt__GetVideoSourceModesResponse)
{
	TRACE("__trt__GetVideoSourceModes start\n");
	TRACE("__trt__GetVideoSourceModes end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__SetVideoSourceMode(struct soap* soap, struct _trt__SetVideoSourceMode *trt__SetVideoSourceMode, struct _trt__SetVideoSourceModeResponse *trt__SetVideoSourceModeResponse)
{
	TRACE("__trt__SetVideoSourceMode start\n");
	TRACE("__trt__SetVideoSourceMode end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetOSDs(struct soap* soap, struct _trt__GetOSDs *trt__GetOSDs, struct _trt__GetOSDsResponse *trt__GetOSDsResponse)
{
	TRACE("__trt__GetOSDs start\n");
	TRACE("__trt__GetOSDs end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetOSD(struct soap* soap, struct _trt__GetOSD *trt__GetOSD, struct _trt__GetOSDResponse *trt__GetOSDResponse)
{
	TRACE("__trt__GetOSD start\n");
	TRACE("__trt__GetOSD end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetOSDOptions(struct soap* soap, struct _trt__GetOSDOptions *trt__GetOSDOptions, struct _trt__GetOSDOptionsResponse *trt__GetOSDOptionsResponse)
{
	TRACE("__trt__GetOSDOptions start\n");
	TRACE("__trt__GetOSDOptions end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__SetOSD(struct soap* soap, struct _trt__SetOSD *trt__SetOSD, struct _trt__SetOSDResponse *trt__SetOSDResponse)
{
	TRACE("__trt__SetOSD start\n");
	TRACE("__trt__SetOSD end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__CreateOSD(struct soap* soap, struct _trt__CreateOSD *trt__CreateOSD, struct _trt__CreateOSDResponse *trt__CreateOSDResponse)
{
	TRACE("__trt__CreateOSD start\n");
	TRACE("__trt__CreateOSD end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__DeleteOSD(struct soap* soap, struct _trt__DeleteOSD *trt__DeleteOSD, struct _trt__DeleteOSDResponse *trt__DeleteOSDResponse)
{
	TRACE("__trt__DeleteOSD start\n");
	TRACE("__trt__DeleteOSD end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trv__GetServiceCapabilities(struct soap* soap, struct _trv__GetServiceCapabilities *trv__GetServiceCapabilities, struct _trv__GetServiceCapabilitiesResponse *trv__GetServiceCapabilitiesResponse)
{
	TRACE("__trv__GetServiceCapabilities start\n");
	TRACE("__trv__GetServiceCapabilities end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trv__GetReceivers(struct soap* soap, struct _trv__GetReceivers *trv__GetReceivers, struct _trv__GetReceiversResponse *trv__GetReceiversResponse)
{
	TRACE("__trv__GetReceivers start\n");
	TRACE("__trv__GetReceivers end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trv__GetReceiver(struct soap* soap, struct _trv__GetReceiver *trv__GetReceiver, struct _trv__GetReceiverResponse *trv__GetReceiverResponse)
{
	TRACE("__trv__GetReceiver start\n");
	TRACE("__trv__GetReceiver end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trv__CreateReceiver(struct soap* soap, struct _trv__CreateReceiver *trv__CreateReceiver, struct _trv__CreateReceiverResponse *trv__CreateReceiverResponse)
{
	TRACE("__trv__CreateReceiver start\n");
	TRACE("__trv__CreateReceiver end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trv__DeleteReceiver(struct soap* soap, struct _trv__DeleteReceiver *trv__DeleteReceiver, struct _trv__DeleteReceiverResponse *trv__DeleteReceiverResponse)
{
	TRACE("__trv__DeleteReceiver start\n");
	TRACE("__trv__DeleteReceiver end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trv__ConfigureReceiver(struct soap* soap, struct _trv__ConfigureReceiver *trv__ConfigureReceiver, struct _trv__ConfigureReceiverResponse *trv__ConfigureReceiverResponse)
{
	TRACE("__trv__ConfigureReceiver start\n");
	TRACE("__trv__ConfigureReceiver end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trv__SetReceiverMode(struct soap* soap, struct _trv__SetReceiverMode *trv__SetReceiverMode, struct _trv__SetReceiverModeResponse *trv__SetReceiverModeResponse)
{
	TRACE("__trv__SetReceiverMode start\n");
	TRACE("__trv__SetReceiverMode end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trv__GetReceiverState(struct soap* soap, struct _trv__GetReceiverState *trv__GetReceiverState, struct _trv__GetReceiverStateResponse *trv__GetReceiverStateResponse)
{
	TRACE("__trv__GetReceiverState start\n");
	TRACE("__trv__GetReceiverState end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tse__GetServiceCapabilities(struct soap* soap, struct _tse__GetServiceCapabilities *tse__GetServiceCapabilities, struct _tse__GetServiceCapabilitiesResponse *tse__GetServiceCapabilitiesResponse)
{
	TRACE("__tse__GetServiceCapabilities start\n");
	TRACE("__tse__GetServiceCapabilities end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tse__GetRecordingSummary(struct soap* soap, struct _tse__GetRecordingSummary *tse__GetRecordingSummary, struct _tse__GetRecordingSummaryResponse *tse__GetRecordingSummaryResponse)
{
	TRACE("__tse__GetRecordingSummary start\n");
	TRACE("__tse__GetRecordingSummary end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tse__GetRecordingInformation(struct soap* soap, struct _tse__GetRecordingInformation *tse__GetRecordingInformation, struct _tse__GetRecordingInformationResponse *tse__GetRecordingInformationResponse)
{
	TRACE("__tse__GetRecordingInformation start\n");
	TRACE("__tse__GetRecordingInformation end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tse__GetMediaAttributes(struct soap* soap, struct _tse__GetMediaAttributes *tse__GetMediaAttributes, struct _tse__GetMediaAttributesResponse *tse__GetMediaAttributesResponse)
{
	TRACE("__tse__GetMediaAttributes start\n");
	TRACE("__tse__GetMediaAttributes end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tse__FindRecordings(struct soap* soap, struct _tse__FindRecordings *tse__FindRecordings, struct _tse__FindRecordingsResponse *tse__FindRecordingsResponse)
{
	TRACE("__tse__FindRecordings start\n");
	TRACE("__tse__FindRecordings end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tse__GetRecordingSearchResults(struct soap* soap, struct _tse__GetRecordingSearchResults *tse__GetRecordingSearchResults, struct _tse__GetRecordingSearchResultsResponse *tse__GetRecordingSearchResultsResponse)
{
	TRACE("__tse__GetRecordingSearchResults start\n");
	TRACE("__tse__GetRecordingSearchResults end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tse__FindEvents(struct soap* soap, struct _tse__FindEvents *tse__FindEvents, struct _tse__FindEventsResponse *tse__FindEventsResponse)
{
	TRACE("__tse__FindEvents start\n");
	TRACE("__tse__FindEvents end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tse__GetEventSearchResults(struct soap* soap, struct _tse__GetEventSearchResults *tse__GetEventSearchResults, struct _tse__GetEventSearchResultsResponse *tse__GetEventSearchResultsResponse)
{
	TRACE("__tse__GetEventSearchResults start\n");
	TRACE("__tse__GetEventSearchResults end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tse__FindPTZPosition(struct soap* soap, struct _tse__FindPTZPosition *tse__FindPTZPosition, struct _tse__FindPTZPositionResponse *tse__FindPTZPositionResponse)
{
	TRACE("__tse__FindPTZPosition start\n");
	TRACE("__tse__FindPTZPosition end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tse__GetPTZPositionSearchResults(struct soap* soap, struct _tse__GetPTZPositionSearchResults *tse__GetPTZPositionSearchResults, struct _tse__GetPTZPositionSearchResultsResponse *tse__GetPTZPositionSearchResultsResponse)
{
	TRACE("__tse__GetPTZPositionSearchResults start\n");
	TRACE("__tse__GetPTZPositionSearchResults end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tse__GetSearchState(struct soap* soap, struct _tse__GetSearchState *tse__GetSearchState, struct _tse__GetSearchStateResponse *tse__GetSearchStateResponse)
{
	TRACE("__tse__GetSearchState start\n");
	TRACE("__tse__GetSearchState end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tse__EndSearch(struct soap* soap, struct _tse__EndSearch *tse__EndSearch, struct _tse__EndSearchResponse *tse__EndSearchResponse)
{
	TRACE("__tse__EndSearch start\n");
	TRACE("__tse__EndSearch end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tse__FindMetadata(struct soap* soap, struct _tse__FindMetadata *tse__FindMetadata, struct _tse__FindMetadataResponse *tse__FindMetadataResponse)
{
	TRACE("__tse__FindMetadata start\n");
	TRACE("__tse__FindMetadata end\n");
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tse__GetMetadataSearchResults(struct soap* soap, struct _tse__GetMetadataSearchResults *tse__GetMetadataSearchResults, struct _tse__GetMetadataSearchResultsResponse *tse__GetMetadataSearchResultsResponse)
{
	TRACE("__tse__GetMetadataSearchResults start\n");
	TRACE("__tse__GetMetadataSearchResults end\n");
	return SOAP_OK;
}




//---------------------------------------------------------------------------------------------------------------
SOAP_FMAC5 int SOAP_FMAC6 soap_send___wsdd__ProbeMatches(struct soap *soap, const char *soap_endpoint, const char *soap_action, struct wsdd__ProbeMatchesType *wsdd__ProbeMatches)
{	struct __wsdd__ProbeMatches soap_tmp___wsdd__ProbeMatches;
	if (!soap_action)
		soap_action = "http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01/ProbeMatches";
	soap->encodingStyle = NULL;
	soap_tmp___wsdd__ProbeMatches.wsdd__ProbeMatches = wsdd__ProbeMatches;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize___wsdd__ProbeMatches(soap, &soap_tmp___wsdd__ProbeMatches);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___wsdd__ProbeMatches(soap, &soap_tmp___wsdd__ProbeMatches, "-wsdd:ProbeMatches", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___wsdd__ProbeMatches(soap, &soap_tmp___wsdd__ProbeMatches, "-wsdd:ProbeMatches", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	return SOAP_OK;
}
