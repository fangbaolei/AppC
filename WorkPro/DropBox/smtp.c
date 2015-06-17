#include "smtp.h"


char  BaseToChr( unsigned char n )   
{   
    n &= 0x3F;   
    if ( n < 26 )   
        return ( char )( n + 'A' );   
    else if ( n < 52 )   
        return ( char )( n - 26 + 'a' );   
    else if ( n < 62 )   
        return ( char )( n - 52 + '0' );   
    else if ( n == 62 )   
        return '+';   
    else   
        return '/';   
}   

int Base64Encode( char * const aDest, const unsigned char * aSrc, int aLen )   
{   
    char        * p = aDest;   
    int           i;   
    unsigned char t;   
   
    for ( i = 0; i < aLen; i++ )   
    {   
        switch ( i % 3 )   
        {   
        case 0 :   
            *p++ = BaseToChr( *aSrc >> 2 );   
            t = ( *aSrc++ << 4 ) & 0x3F;   
            break;   
        case 1 :   
            *p++ = BaseToChr( t | ( *aSrc >> 4 ) );   
            t = ( *aSrc++ << 2 ) & 0x3F;   
            break;   
        case 2 :   
            *p++ = BaseToChr( t | ( *aSrc >> 6 ) );   
            *p++ = BaseToChr( *aSrc++ );   
            break;   
        }   
    }   
    if ( aLen % 3 != 0 )   
    {   
        *p++ = BaseToChr( t );   
        if ( aLen % 3 == 1 )   
            *p++ = '=';   
        *p++ = '=';   
    }   
    *p = 0;
    return ( p - aDest );
}   

int Base64_Code(unsigned char *s,unsigned char *d)   
{   
        char CharSet[64]=   
        {   
                'A','B','C','D','E','F','G','H',   
                'I','J','K','L','M','N','O','P',   
                'Q','R','S','T','U','V','W','X',   
                'Y','Z','a','b','c','d','e','f',   
                'g','h','i','j','k','l','m','n',   
                'o','p','q','r','s','t','u','v',   
                'w','x','y','z','0','1','2','3',   
                '4','5','6','7','8','9','+','/'   
        };   
        unsigned char In[3];   
        unsigned char Out[4];   
        int cnt=0;   
        if(!s||!d) return 0;   
        for(;*s!=0;)   
        {   
                if(cnt+4>76)   
                {   
                        *d++='\n';   
                        cnt=0;   
                }   
                if(strlen((char*)s) >=3)   
                {   
                        In[0]=*s;   
                        In[1]=*(s+1);   
                        In[2]=*(s+2);   
                        Out[0]=In[0]>>2;   
                        Out[1]=(In[0]&0x03)<<4|(In[1]&0xf0)>>4;   
                        Out[2]=(In[1]&0x0f)<<2|(In[2]&0xc0)>>6;   
                        Out[3]=In[2]&0x3f;   
                        *d=CharSet[Out[0]];   
                        *(d+1)=CharSet[Out[1]];   
                        *(d+2)=CharSet[Out[2]];   
                        *(d+3)=CharSet[Out[3]];   
                        s+=3;   
                        d+=4;   
                }   
                else if(strlen((char*)s)==1)   
                {   
                        In[0]=*s;   
                        Out[0]=In[0]>>2;   
                        Out[1]=(In[0]&0x03)<<4|0;   
                        *d=CharSet[Out[0]];   
                        *(d+1)=CharSet[Out[1]];   
                        *(d+2)='=';   
                        *(d+3)='=';   
                        s+=1;   
                        d+=4;   
                }   
                else if(strlen((char*)s)==2)   
                {   
                        In[0]=*s;   
                        In[1]=*(s+1);   
                        Out[0]=In[0]>>2;   
                        Out[1]=(In[0]&0x03)<<4|(In[1]&0xf0)>>4;   
                        Out[2]=(In[1]&0x0f)<<2|0;   
                        *d=CharSet[Out[0]];   
                        *(d+1)=CharSet[Out[1]];   
                        *(d+2)=CharSet[Out[2]];   
                        *(d+3)='=';   
                        s+=2;   
                        d+=4;   
                }   
                cnt+=4;   
        }   
        *d='\0';   
        return 1;   
}   

int GetResponse()   
{     
	int ret;
	char recv_data[512];
	memset(recv_data,0,sizeof(recv_data));
	struct timeval timeout;
	timeout.tv_sec = 10;
	timeout.tv_usec = 0;
	setsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,&timeout,sizeof(timeout));
	if((ret = recv(sockfd,recv_data,1024,0)) == -1)   
	{   
		printf("receive nothing\n");   
		return -1;   
	}   
	recv_data[ret]='\0';   
	printf("Response data:%s\n",recv_data);
	if(*recv_data == '5')   
	{   
		printf("the order is not support smtp host\n ");   
		return -1;   
	}   
	return 0;   
}   
   
   
int Smtp_ConnectHost(const char *hostname,unsigned short port)   
{   
	struct sockaddr_in sockaddr;
	struct hostent *host;
	sockfd = socket(AF_INET,SOCK_STREAM,0);   
	if(sockfd == -1)   
	{	
		printf("CreateSocket error\n");   
		close(sockfd);	 
		return -1;	 
	}	

	if(hostname == NULL)   
		return -1;   
	if((host = gethostbyname(hostname)) == NULL)
	{
		printf("gethostbyname error !\n");   
		return -1;
	}
	memset(&sockaddr,0,sizeof(struct sockaddr));   
	sockaddr.sin_family = AF_INET;   
	sockaddr.sin_port   = htons(port);   
	memcpy(&sockaddr.sin_addr,host->h_addr,sizeof(struct in_addr));

	if((connect(sockfd,(struct sockaddr *)&sockaddr,sizeof(struct sockaddr))) == -1)   
	{ 
		printf("connect error\n");   
		close(sockfd);   
		return -1;   
	}
	if(GetResponse() == -1)
	{
		close(sockfd);   
		return -1;   
	}
	return 0;   
}  

int Smtp_Login(char *username,char *password)   
{   
	char *pSendCmd = NULL;
	char tmpbuf[100];
	char UserDst[40],PassDst[40];	
	memset(tmpbuf,0,sizeof(tmpbuf));
	memset(UserDst,0,sizeof(UserDst));
	memset(PassDst,0,sizeof(PassDst));
	
	char *pUser,*pPass;   
	if(username == NULL || password == NULL)   
	return -1;   
	pUser = username;   
	pPass = password;   
	Base64_Code((unsigned char *)pUser,(unsigned char *)UserDst);   
	Base64_Code((unsigned char *)pPass,(unsigned char *)PassDst);   

	pSendCmd = "HELO Localhost\r\n";   
	if((send(sockfd,pSendCmd,strlen(pSendCmd),0)) == -1)   
	{
		close(sockfd);   
		return -1;   
	}      
	if(GetResponse() == -1)   
	{		
		close(sockfd);	 
		return -1;
	}

	pSendCmd = "AUTH LOGIN\r\n";   
	if((send(sockfd,pSendCmd,strlen(pSendCmd),0)) == -1)   
	{   
		close(sockfd);   
		return -1;   
	}   
	if(GetResponse() == -1)   
	{		
		close(sockfd);	 
		return -1;
	}
	sprintf(tmpbuf,"%s\r\n",UserDst);
	if((send(sockfd,(char *)tmpbuf,strlen(tmpbuf),0)) == -1)   
	{   
		close(sockfd);   
		return -1;   
	}   

	if(GetResponse() == -1)   
	{		
		close(sockfd);	 
		return -1;
	}

	sprintf(tmpbuf,"%s\r\n",PassDst);
	if((send(sockfd,(char *)tmpbuf,strlen(tmpbuf),0)) == -1)   
	{   
		close(sockfd);   
		return -1;   
	}   
	if(GetResponse() == -1)  
	{		
		close(sockfd);   
		return -1;
	}
	return 0;   
}   

int Smtp_SendMessage(const char *from,const char *to,const char *date,const char *subject,const char *data)   
{   
	char *pSendCmd = NULL;
	char Date[40],Subject[40],tmpbuf[100],From[40],To[40];;
	memset(Date,0,sizeof(Date));
	memset(Subject,0,sizeof(Subject));	
	memset(From,0,sizeof(From));	
	memset(To,0,sizeof(To));	
	memset(tmpbuf,0,sizeof(tmpbuf));	

	if(from == NULL || to == NULL || date == NULL || subject == NULL)   
	{   
		close(sockfd);   
		return -1;   
	} 
	
	sprintf(From,"MAIL FROM: <%s>\r\n",from);   
	if((send(sockfd,From,strlen(From),0)) == -1)   
	{   
		close(sockfd);   
		return -1;   
	}   
	
	if(GetResponse() == -1)   
	{		
		close(sockfd);	 
		return -1;
	}

	sprintf(To,"RCPT TO: <%s>\r\n",to);   
	if((send(sockfd,To,strlen(To),0)) == -1)   
	{   
		close(sockfd);   
		return -1;   
	}   
	if(GetResponse() == -1)   
	{		
		close(sockfd);	 
		return -1;
	}

	pSendCmd = "DATA \r\n"; 
	if((send(sockfd,pSendCmd,strlen(pSendCmd),0)) == -1)   
	{   
		close(sockfd);   
		return -1;   
	} 
	if(GetResponse() == -1)   
	{		
		close(sockfd);	 
		return -1;
	}

	sprintf(From,"From: %s\r\n",from); 
	if((send(sockfd,From,strlen(From),0)) == -1)   
	{   
		close(sockfd);   
		return -1;   
	}   

	sprintf(To,"To: %s\r\n",to);
	if((send(sockfd,To,strlen(To),0)) == -1)   
	{   
		close(sockfd);   
		return -1;   
	}   

	sprintf(Date,"Date: %s\r\n",date);
	if((send(sockfd,Date,strlen(Date),0)) == -1)   
	{   
		close(sockfd);   
		return -1;   
	}   

	sprintf(Subject,"Subject: %s\r\n",subject);
	if((send(sockfd,Subject,strlen(Subject),0)) == -1)   
	{   
		close(sockfd);   
		return -1;   
	}   

	sprintf(tmpbuf,"MIME-Version: 1.0\r\n");
	if((send(sockfd,tmpbuf,strlen(tmpbuf),0)) == -1)   
	{   
		close(sockfd);   
		return -1;   
	}  
	
	sprintf(tmpbuf,"Content-Type: multipart/mixed;boundary=\"boundary=_LINE\"\r\n"); 
	if((send(sockfd,tmpbuf,strlen(tmpbuf),0)) == -1)   
	{   
		close(sockfd);   
		return -1;   
	}
	
	sprintf(tmpbuf,"Content-Transfer-Encoding: 7bit\r\n");
	if((send(sockfd,tmpbuf,strlen(tmpbuf),0)) == -1)   
	{   
		close(sockfd);   
		return -1;   
	}  
	
	pSendCmd = "This is a MIME Encoded Message\r\n";
	if((send(sockfd,pSendCmd,strlen(pSendCmd),0)) == -1)   
	{   
		close(sockfd);   
		return -1;   
	}  
	
	pSendCmd = "\r\n";
	if((send(sockfd,pSendCmd,strlen(pSendCmd),0)) == -1)   
	{   
		close(sockfd);   
		return -1;   
	}   
	sprintf(tmpbuf,"--boundary=_LINE\r\n");
	if((send(sockfd,tmpbuf,strlen(tmpbuf),0)) == -1)   
	{   
		close(sockfd);   
		return -1;   
	}   
	
	sprintf(tmpbuf,"Content-Type: text/plain; charset=us-ascii\r\n");
	if((send(sockfd,tmpbuf,strlen(tmpbuf),0)) == -1)   
	{   
		close(sockfd);   
		return -1;   
	}  
	
	sprintf(tmpbuf,"Content-Transfer-Encoding: 7bit\r\n");
	if((send(sockfd,tmpbuf,strlen(tmpbuf),0)) == -1)   
	{   
		close(sockfd);   
		return -1;   
	}  
	
	pSendCmd = "\r\n";
	if((send(sockfd,pSendCmd,strlen(pSendCmd),0)) == -1)   
	{   
		close(sockfd);   
		return -1;   
	}
	
	if((send(sockfd,(char *)data,strlen(data),0)) == -1)   
	{   
		close(sockfd);   
		return -1;   
	}   

	return 0;   
}   
   
int Smtp_SendFile(const char *filename )   
{   
	int  len;   
	char *pSendCmd = NULL;
	int stringlen = 0;   
	int timedelay,timedelay1;	
	char attachname[1000],Filename[100],tmpbuf[100];
	unsigned char datasrc[58],datades[100];
	memset(attachname,0,sizeof(attachname));
	memset(Filename,0,sizeof(Filename));
	memset(tmpbuf,0,sizeof(tmpbuf));
	memset(datasrc,0,sizeof(datasrc));
	memset(datades,0,sizeof(datades));
	
	FILE *fp=NULL;           
	fp = fopen(filename,"rb");   
	if(fp==NULL)   
	{   
		printf("can not open file");   
		return -1;   
	}   

	fseek(fp,0,SEEK_END);   
	len = ftell(fp);   
	fseek(fp,0,SEEK_SET);   

	pSendCmd = "\r\n";
	if((send(sockfd,pSendCmd,strlen(pSendCmd),0)) == -1)   
	{   
		close(sockfd);   
		return -1;   
	}	
	
	pSendCmd = "--boundary=_LINE\r\n";
	if((send(sockfd,pSendCmd,strlen(pSendCmd),0)) == -1)   
	{   
		printf("send error");   
		close(sockfd);   
		return -1;   
	}
		
	sprintf(Filename,"Content-Type: text/plain;name=\"%s\"\r\n",filename);
	if((send(sockfd,Filename,strlen(Filename),0)) == -1)   
	{   
		printf("sendfilenameerror");   
		close(sockfd);   
		return -1;   
	}  	
	
	pSendCmd = "Content-Transfer-Encoding: base64\r\n";
	if((send(sockfd,pSendCmd,strlen(pSendCmd),0)) == -1)   
	{   
		printf("sendcodemethoderror");   
		close(sockfd);   
		return -1;   
	}   

	sprintf(attachname,"Content-Disposition: attachment;filename=\"%s\"\r\n",filename);
	if((send(sockfd,attachname,strlen(attachname),0)) == -1)   
	{   
		printf("sendfilenameerror");   
		close(sockfd);   
		return -1;   
	}  
	
	pSendCmd = "\r\n";
	if((send(sockfd,pSendCmd,strlen(pSendCmd),0)) == -1)   
	{   
		close(sockfd);   
		return -1;   
	} 
	printf("Sending file,please wait ...\n");   

	while(!feof(fp))   
	{                   
		if(len>=57)   
		{   
			fread(datasrc,57,1,fp);   
			datasrc[57]='\0';   
			stringlen = 57;   
			len -= 57;   
		}   
		else if(len>0)   
		{   
			fread(datasrc,len,1,fp);   
			datasrc[len]='\0';   
			stringlen = len;   
			len = 0;   
		}   
		else 
		{
			break;
		}		
		Base64Encode((unsigned char *)datades,(unsigned char *)datasrc,stringlen);   
		for( timedelay=0;timedelay<1000;timedelay++)   
			for( timedelay1=0;timedelay1<1000;timedelay1++);
		if((send(sockfd,(char *)datades,strlen((char *)datades),0)) == -1)   
		{   
			printf("sendbase64dataerror");   
			close(sockfd);  
			fclose(fp);
			return -1;   
		}   
	}   
	fclose(fp);   	
		
	pSendCmd = "\r\n";
	if((send(sockfd,pSendCmd,strlen(pSendCmd),0)) == -1)   
	{   
		close(sockfd);   
		return -1;   
	} 	
	sprintf(tmpbuf,"--boundary=_LINE--");
	if((send(sockfd,tmpbuf,strlen(tmpbuf),0)) == -1)   
	{   
		close(sockfd);   
		return -1;   
	}

	printf("Send file ok\n");   
	return 0;   
}   
   
int Smtp_Quit()   
{   
	char *pSendCmd = NULL;
	pSendCmd = "\r\n";
	if((send(sockfd,pSendCmd,strlen(pSendCmd),0)) == 1)   
	{   
		close(sockfd);   
		return -1;   
	}   
	pSendCmd = "\r\n.\r\n";
	if((send(sockfd,pSendCmd,strlen(pSendCmd),0)) == -1)   
	{  
		close(sockfd);   
		return -1;   
	}   
	if(GetResponse() == -1)   
	{		
		close(sockfd);	 
		return -1;
	}

	pSendCmd = "QUIT\r\n";
	if((send(sockfd,pSendCmd,strlen(pSendCmd),0)) == -1)   
	{   
		close(sockfd);   
		return -1;   
	}   
	if(GetResponse() == -1)   
	{		
		close(sockfd);	 
		return -1;
	}
	if(sockfd != -1)   
	{   
		close(sockfd);   
	}   
	return 0;   
}  

int Smtp_SendEmail(st_smtp *s)
{
	if(Smtp_ConnectHost(s->pHost,s->port) == -1)   
	{   
		printf("can not connect the host\n");   
		return -1;   
	}   
	printf("connect the smtp host\n");   

	if(Smtp_Login(s->pLoginName,s->pLoginPassword) == -1)   
	{   
		printf("login error\n");   
		return -1;   
	}   
	printf("login\n"); 

	if(Smtp_SendMessage(s->pSendFrom,s->pSendTo,s->pDate,s->pEmailSubject,s->pMessage) == -1)   
	{   
		printf("send mail error\n");   
		return -1;   
	}   
	printf("send message succ! \n");

	if(NULL != s->pFileName)
	{
		if(Smtp_SendFile(s->pFileName) == -1)	
		{	
			printf("send file error\n");
			return -1;
		}	
		printf("send file succ! \n");
	}
	
	if(Smtp_Quit() == -1)   
	{   
		printf("Quit error\n");   
		return -1;   
	}   
	printf("send over\n");   
	return 0;
}
   
