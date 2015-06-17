#ifndef __RELAY_MANAGE_SERVER_H
#define __RELAY_MANAGE_SERVER_H


#define DEFAULT_SERVER_PORT	"8888"
#define SECOND_SERVER_PORT "9999"

#define MYSQL_ERROR "500 MYSQL ERROR"
#define RESPONSE_OK "200 OK"

#define MAX_MSG_LEN	512
#define SESSION_NUM_LEN 64
#define MAX_KEY_LENGHTH  32  //秘钥长度

#define CLIENT_TIMEOUT 100


#define uint32 unsigned int
#define uint16 unsigned short
#define uint8  unsigned char
#define int16  short

typedef struct SESSION_MAP{
	uint32 nsessionID;
	uint32 keyNum;
}SESSION_MAP;

typedef struct NET_MSG{
	uint32 msgType;
	uint32 msgDataLen;
}NET_MSG;




//relay statr*************************
typedef struct RELAY_CONN_REQUEST{
	uint32 port;
	uint32 SN;
}RELAY_CONN_REQUEST;

typedef struct RELAY_CONN_RESPONSE{
	uint32 port;
	uint8  portStatus;
}RELAY_CONN_RESPONSE;

typedef struct RELAY_CONNECT_RESPONSE_CODE{
	int16 statusCode;
}RELAY_CONNECT_RESPONSE_CODE;

//relay end****************************



//relay client****************************
typedef struct CLIENT_CONNECT_REQUEST{
	uint32 SN;
}CLIENT_CONNECT_REQUEST;

typedef struct CLIENT_CONNECT_RESPONSE{
	int16 statusCode;
}CLIENT_CONNECT_RESPONSE;
//relay client end*********************




typedef enum {
	//P2P SERVER
 	P2P_ALLOCATE_KEY_REQUEST				= 0x00002000U,
 	P2P_ALLOCATE_KEY_RESPONSE  				= 0x00003000U,
 	P2P_ALLOCATE_RELAYPORT_REQUEST 			= 0x00004000U,
 	P2P_ALLOCATE_RELAYPORT_RESPONSE 		= 0x00005000U,
 	P2P_ALLOCATE_RELAYPORT_ERROR 			= 0x00005001U,

	//RELAY SERVER
	RELAY_REGISTER_MSG 						= 0x00006000U,
	RELAY_REGISTER_SUC_MSG 					= 0x00007000U,
	RELAY_REGISTER_ERROR_MSG 				= 0x00008000U,
	RELAY_CONNECT_REQUEST_MSG 				= 0x00009000U,
	RELAY_CONNECT_RESPONSE_MSG 				= 0x0000A000U,	
	RELAY_CONNECT_RESPONSE_CODE_MSG 		= 0x0000A001U,
    RELAY_CONNECT_HEART_BEAT_MSG			= 0x0000A002U,
	
	CLIENT_CONNECT_REQUEST_MSG				= 0x0000B000U,
	CLIENT_CONNECT_RESPONSE_MSG 			= 0X0000B001U
}MSG_TYPE;



#endif
