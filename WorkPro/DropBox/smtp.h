#include <stdlib.h>    
#include <stdio.h>    
#include <string.h>    
#include <netdb.h>    
#include <sys/types.h>    
#include <sys/stat.h>    
#include <unistd.h>     
#include <fcntl.h>    
#include <sys/ioctl.h>    
#include <netinet/in.h>    
#include <sys/socket.h>    
#include <linux/if_ether.h>    
#include <net/if.h>    
#include <errno.h>  
#include <time.h>
int sockfd;

typedef struct Smtp_Email
{
	char *pHost;	/* 服务器域名 */
	char *pLoginName;	/* 发送 账号 */
	char *pLoginPassword;	/* 登陆密码 */
	char *pSendFrom;	/*  发送 账号 */ 
	char *pSendTo;	/* 接收账号 */
	char *pDate;	/*  发送时间，时区+800 表示北京时间 */
	char *pEmailSubject;	/*  邮件名  */
	char *pMessage;	/*  邮件显示的内容 */
	char *pFileName;	/*  邮件附件 ，不发附件则为 NULL */
	unsigned short port;	/* 端口 */
}st_smtp;

char  BaseToChr( unsigned char n );
int Base64Encode( char * const aDest, const unsigned char * aSrc, int aLen );
int Base64_Code(unsigned char *s,unsigned char *d);
int GetResponse();
int Smtp_ConnectHost(const char *hostname,unsigned short port);
int Smtp_Login(char *username,char *password);  
int Smtp_SendMessage(const char *from,const char *to,const char *date,const char *subject,const char *data);   
int Smtp_SendFile(const char *filename );        
int Smtp_Quit();
int Smtp_SendEmail(st_smtp *s);
   
