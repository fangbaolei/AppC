#ifndef __STACK__DEBUG_H__
#define __STACK__DEBUG_H__


#define DEBUG_H323_INFO   0
#undef DEBUG_H323_INFO

#define DEBUG_SIP_SIPMW_INTF   0
#define DEBUG_VIDEO_NETWORK_PAYLOAD   0

#define  ENABLE_RTP_DEBUG  1
#define  ENABLE_PROC_DEBUG 1
#define  ENABLE_ERR_DEBUG  1
#define  ENABLE_H323_DEBUG  1
#define  ENABLE_H323_ERR   1
#define  ENABLE_NAT_DEBUG  1
#define  ENABLE_SIP_DEBUG  1
#define  ENABLE_SDP_DEBUG  1
#define  ENABLE_FUNC_DEBUG  1  /* function debug , for temporary debug code  */
#define  ENABLE_H323_INTF   1
#define  ENABLE_SIP_INTF   1
#define  ENABLE_RTCP_ERR   1
#define  ENABLE_H263_DEBUG   1
#define  ENABLE_H264_DEBUG   1
#define  ENABLE_THREAD_TIMER_DEBUG   1
#define ENABLE_DEBUG_INFO 1

#define ENABLE_ERR_TO_DEBUG 1


#if ENABLE_THREAD_TIMER_DEBUG
#define DEBUG_THREAD_TIMER(Fmt...) do { printf("%s--%s() %d:", __FILE__,__FUNCTION__,__LINE__); printf(Fmt);}while (0)
#else   
#define  DEBUG_THREAD_TIMER(Fmt...) do { } while (0)
#endif


#if ENABLE_RTP_DEBUG
#define DEBUG_RTP(Fmt...) do { printf("%s--%s() %d:", __FILE__,__FUNCTION__,__LINE__); printf(Fmt);}while (0)
#else   
#define  DEBUG_RTP(Fmt...) do { } while (0)
#endif


#if ENABLE_PROC_DEBUG
#define DEBUG_PROC(Fmt...) do { printf("%s--%s() %d:", __FILE__,__FUNCTION__,__LINE__); printf(Fmt);}while (0)
#else   
#define  DEBUG_PROC(Fmt...) do { } while (0)
#endif

#if ENABLE_ERR_DEBUG
#define DEBUG_ERR(Fmt...) do { printf("ERR %s***%s() %d:", __FILE__,__FUNCTION__,__LINE__); printf(Fmt);}while (0)
#else   
#define  DEBUG_ERR(Fmt...) do { } while (0)
#endif

#if ENABLE_ERR_TO_DEBUG
#define DEBUG_TO_ERR(Fmt...) do { printf("ERR %s***%s() %d:", __FILE__,__FUNCTION__,__LINE__); printf(Fmt);}while (0)
#else   
#define  DEBUG_TO_ERR(Fmt...) do { } while (0)
#endif

#if ENABLE_ERR_DEBUG
#define DEBUG_MSG() do { printf("ERR %s***%s() %d\n", __FILE__,__FUNCTION__,__LINE__); }while (0)
#else   
#define  DEBUG_MSG() do { } while (0)
#endif

#if ENABLE_DEBUG_INFO
#define DEBUG_INFO(Fmt...) do { printf("%s--%s() %d:", __FILE__,__FUNCTION__,__LINE__); printf(Fmt);}while (0)
#else   
#define  DEBUG_INFO(Fmt...) do { } while (0)
#endif


#if ENABLE_H323_ERR
#define H323_ERR(Fmt...) do { printf("%s--%s() %d:", __FILE__,__FUNCTION__,__LINE__); printf(Fmt);}while (0)
#else   
#define  H323_ERR(Fmt...) do { } while (0)
#endif



#if ENABLE_NAT_DEBUG
#define DEBUG_NAT(Fmt...) do { printf("%s--%s() %d:", __FILE__,__FUNCTION__,__LINE__); printf(Fmt);}while (0)
#else   
#define  DEBUG_NAT(Fmt...) do { } while (0)
#endif


#if ENABLE_SIP_DEBUG
#define DEBUG_SIP(Fmt...) do { printf("%s--%s() %d:", __FILE__,__FUNCTION__,__LINE__); printf(Fmt);}while (0)
#else   
#define  DEBUG_SIP(Fmt...) do { } while (0)
#endif


#if ENABLE_SDP_DEBUG
#define DEBUG_SDP(Fmt...) do { printf("%s--%s() %d:",__FILE__, __FUNCTION__,__LINE__); printf(Fmt);}while (0)
#else   
#define  DEBUG_SDP(Fmt...) do { } while (0)
#endif



#if ENABLE_FUNC_DEBUG
#define DEBUG_FUNC(Fmt...) do { printf("%s++++%s() %d:",__FILE__, __FUNCTION__,__LINE__); printf(Fmt);}while (0)
#else   
#define  DEBUG_FUNC(Fmt...) do { } while (0)
#endif



#if ENABLE_H323_INTF
#define DEBUG_H323_INTF(Fmt...) do { printf("%s--  %s() %d:", __FILE__,__FUNCTION__,__LINE__); printf(Fmt);}while (0)
#else   
#define  DEBUG_H323_INTF(Fmt...) do { } while (0)
#endif


#if ENABLE_SIP_INTF
#define DEBUG_SIP_INTF(Fmt...) do { printf("%s--%s() %d:",__FILE__, __FUNCTION__,__LINE__); printf(Fmt);}while (0)
#else   
#define  DEBUG_SIP_INTF(Fmt...) do { } while (0)
#endif

#if ENABLE_RTCP_ERR
#define DEBUG_RTCP_ERR(Fmt...) do { printf("%s--%s() %d:",__FILE__, __FUNCTION__,__LINE__); printf(Fmt);}while (0)
#else   
#define  DEBUG_RTCP_ERR(Fmt...) do { } while (0)
#endif


#if ENABLE_H263_DEBUG
#define DEBUG_H263(Fmt...) do { printf("%s--%s() %d:", __FILE__,__FUNCTION__,__LINE__); printf(Fmt);}while (0)
#else   
#define  DEBUG_H263(Fmt...) do { } while (0)
#endif


#if ENABLE_H264_DEBUG
#define DEBUG_H264(Fmt...) do { printf("%s--%s() %d:", __FILE__,__FUNCTION__,__LINE__); printf(Fmt);}while (0)
#else   
#define  DEBUG_H264(Fmt...) do { } while (0)
#endif

#endif

