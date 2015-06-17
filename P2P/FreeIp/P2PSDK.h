
#ifdef __cplusplus
extern "C" {
#endif

#ifndef __P2PSDK_H__
#define __P2PSDK_H__



//#include <string>
#include <stdio.h>
#define MAX_MSG_DATA_LEN 512

#ifdef _MSC_VER_
#pragma pack(push, 1)
#define PP_PACKED
#elif defined(__GNUC__)
#define PP_PACKED __attribute__ ((packed))
#else
#define PP_PACKED
#endif

typedef struct 
{    
    short           resultCode;  //     返回结果代码
    
}PP_PACKED NetMsgResHeader;

// 实时视频帧和录像回放视频帧前的帧头
typedef struct 
{
    unsigned int  timeStamp ; // 时间戳，从回放的开始时间经过的毫秒数
    unsigned int  videoLen;   // 视频帧长度 (不包括帧头)
    unsigned char bIframe;    // 是否是关键帧。0： 非关键帧 1:关键帧
    unsigned char reserved[7]; // 保留
}PP_PACKED P2P_FrameHeader;

//***************************** 实时流相关消息 ********************************
// 打开实时流消息
typedef struct PlayRealStreamMsg
{
    short streamType;  // 1:主码流 2:副码流
    short channelNo;  // 通道号
}PlayRealStreamMsg;

// 停止实时流消息
typedef struct StopRealStreamMsg
{
    short streamType;  // 1:主码流 2:副码流
    short channelNo;  // 通道号
}StopRealStreamMsg;

// 实时流请求应答
typedef struct 
{
    NetMsgResHeader header;
    // 可能需要扩展其它属性
}PP_PACKED PlayRealStreamMsgRes;

// 关闭实时流请求应答
typedef struct 
{
    NetMsgResHeader header;
    // 可能需要扩展其它属性
}PP_PACKED StopRealStreamMsgRes;


//***************************** 录像回放相关消息 ****************************

// 录像回放消息
typedef struct 
{
	short       channelNo;      // 通道号
	short       frameType;		 // 帧类型(0:视频,1:音频,2:音视频) 
	unsigned    startTime;	     // 开始时间
	unsigned    endTime;		 // 结束时间
}PP_PACKED PlayRecordMsg;

// 录像回放应答消息
typedef struct 
{
    NetMsgResHeader header;
    // 可能需要扩展其它属性
}PP_PACKED PlayRecordResMsg;

typedef enum {
	PB_PLAY		        		= 0,	//播放
	PB_PAUSE			    	= 1,	//暂停
	PB_STOP						= 2,	//停止
	PB_STEPFORWARD				= 3,	//单帧进
	PB_STEPBACKWARD			= 4,	//单帧退
	PB_FORWARD					= 5,	//快进
	PB_BACKWARD				= 6,	//快退
}PlayBackControl;

// 录像回放控制消息
typedef struct 
{
    PlayBackControl ctrl;
}PP_PACKED PlayRecordCtrlMsg;

// 录像回放控制应答消息
typedef struct 
{
    NetMsgResHeader header;
}PP_PACKED PlayRecordCtrlResMsg;
//************************************************************************

// 消息类型
typedef enum
{
    UNKOWN_MSG =0, 
    PLAY_REAL_STREAM = 1 ,
    PLAY_REAL_STREAM_RES =2 ,
    STOP_REAL_STREAM = 3 ,
    STOP_REAL_STREAM_RES =4  ,
    PLAY_RECORD_STREAM = 5,   // 请求回放录像流消息类型
    PLAY_RECORD_STREAM_RES = 6,
    PLAY_RECORD_CTRL = 7 ,    // 录像回放控制命令，包括暂停、快进快退等。
    PLAY_RECORD_CTRL_RES = 8,
    RELAY_STREAM_DATA = 9,
}MsgType;
// 请求消息
typedef struct _NetMsg
{
	unsigned short  msgType;
    unsigned short  msgDataLen;
	unsigned char   msgData[MAX_MSG_DATA_LEN]; 
	/*_NetMsg()
	{
		msgType = 0;
        msgDataLen = 0;
		for(int i = 0;i < MAX_MSG_DATA_LEN;i++)
		{
			msgData[i] = '\0';
		}
	}*/
}PP_PACKED NetMsg;

// 消息应答
typedef struct _NetMsgRes
{
    unsigned short  msgType; // 消息类型
    unsigned short  msgDataLen;                  // 应用层消息体长度
	unsigned char   msgData[MAX_MSG_DATA_LEN];   //  应用层消息体数据
}PP_PACKED NetMsgRes;

#ifdef _MSC_VER_
#pragma pack(pop)
#endif

#endif
#ifdef __cplusplus
}
#endif
