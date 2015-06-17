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
	char *pHost;	/* ���������� */
	char *pLoginName;	/* ���� �˺� */
	char *pLoginPassword;	/* ��½���� */
	char *pSendFrom;	/*  ���� �˺� */ 
	char *pSendTo;	/* �����˺� */
	char *pDate;	/*  ����ʱ�䣬ʱ��+800 ��ʾ����ʱ�� */
	char *pEmailSubject;	/*  �ʼ���  */
	char *pMessage;	/*  �ʼ���ʾ������ */
	char *pFileName;	/*  �ʼ����� ������������Ϊ NULL */
	unsigned short port;	/* �˿� */
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
   
