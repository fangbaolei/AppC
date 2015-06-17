#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<netdb.h>
#include<errno.h>
#include<arpa/inet.h>
#include<sys/stat.h>
#include<unistd.h>
#include<termios.h>

#define TRUE 1
#define FALSE 0
struct sockaddr_in ftp_server,local_host;
struct hostent * server_hostent;
int sock_control;

typedef struct ftp_client
{
	int port; /* ftp 端口 */
	char ip[20]; /* ftp 服务器 ip */
	char user[32]; /* 用户名 */
	char password[32]; /*  密码 */
	char putFileName[128]; /* 上传文件的名字 */
	char getFileName[128]; /* 下载文件的名字 */
	int getCoverFalgs;  /* 如果下载的文件本地已经存在，是否需要覆盖，TRUE覆盖 ,FALSE不覆盖 */
	char ftpDir[128];	/* ftp 服务器上的文件存放目录 */
	char localDir[128];	/* 本地的文件存放目录 */	
}st_ftp;

void cmd_err_exit(char* error_message,int error_code)
{
	printf("%s error code: %d\n",error_message,error_code);
	exit(error_code);
}

int ftp_connect(struct sockaddr_in *s_addr,int type)
{
	struct timeval outtime;
	int set;
	int s=socket(AF_INET,SOCK_STREAM,0);
	if(s<0)
		cmd_err_exit("Creat socket error",249);
	if(type==1)
	{
		outtime.tv_sec=0;
		outtime.tv_usec=300000;
	}
	else
	{
		outtime.tv_sec=5;
		outtime.tv_usec=0;
	}
	set=setsockopt(s,SOL_SOCKET,SO_RCVTIMEO,&outtime,sizeof(outtime));
	if(set!=0)
	{
		cmd_err_exit("set socket error",1);
	}
	if(connect(s,(struct sockaddr *)s_addr,sizeof(struct sockaddr_in))<0)
	{
		printf("Can't connet to the server:%s,port:%d\n",inet_ntoa(s_addr->sin_addr),ntohs(ftp_server.sin_port));
		close(s);
		exit(252);
	}
	else
	{
		printf("Successfully connect to server:%s,port:%d\n",inet_ntoa(s_addr->sin_addr),ntohs(ftp_server.sin_port));
	}
	return s;

}

/* send command to server with sock_fd */
int ftp_send_cmd(const char* s1,const char* s2,int sock_fd)
{
	char send_buf[256];
	memset(send_buf,0,sizeof(send_buf));
	int send_err,len;
	if(s1)
	{
		strcpy(send_buf,s1);
		if(s2)
		{
			strcat(send_buf,s2);
			strcat(send_buf,"\r\n");
		}
		else
		{
			strcat(send_buf,"\r\n");
		}
		len=strlen(send_buf);
		send_err=send(sock_fd,send_buf,len,0);
	}
	if(send_err<0)
	{
		printf("send error\n");
	}
	return send_err;
}

int ftp_get_reply(int sock_fd)
{
	static int reply_code=0,count=0;
	char rcv_buff[512];
	memset(rcv_buff,0,sizeof(rcv_buff));
	count=read(sock_fd,rcv_buff,510);
	if(count>0)
	{
		reply_code=atoi(rcv_buff);
		return reply_code;
	}
	return 0;
}

int get_port()
{
	char port_respond[512];
	memset(port_respond,0,sizeof(port_respond));
	char *temp;
	int count,port_num;
	/* 请求服务器等待数据连接 */
	ftp_send_cmd("PASV",NULL,sock_control);/* 进入被动模式 */
	count=read(sock_control,port_respond,510);
	if(count<=0)
		return 0;
	port_respond[count]='\0';
	if(atoi(port_respond)==227)/* 确定进入被动模式 */
	{
		/* 如果 返回的数据是(127,0,0,1,4,18) ， 那么  port_num = 4 * 256 + 18 */
		temp=strrchr(port_respond,',');
		port_num=atoi(temp+1);
		*temp='\0';
		temp=strrchr(port_respond,',');
		port_num+=atoi(temp+1)*256;
		return port_num;
	}
	return 0;
}

int ftp_connect_data()
{
	int data_port = get_port();
	if(data_port != 0)
	{
		ftp_server.sin_port=htons(data_port);
	}
	return(ftp_connect(&ftp_server, 0));
}

void ftp_quit()
{
	int error;
	ftp_send_cmd("QUIT",NULL,sock_control);
	error = ftp_get_reply(sock_control);	
	printf("ftp reply number:<%d>, fun<%s> line<%d>\n",error,__FUNCTION__,__LINE__);
	close(sock_control);
}

void ftp_cmd_filename(char * usr_cmd, char * src_file, char * dst_file)
{	
	int length,  flag = 0;
	int i = 0, j = 0;
	char * cmd_src;
	cmd_src = strchr(usr_cmd, ' ');
	if(cmd_src == NULL)
	{
		printf("command error!\n");
		return;
	}
	else
	{
		while(*cmd_src == ' ')
			cmd_src ++;
	}
	if(cmd_src == NULL || cmd_src == '\0')
	{
		printf("command error!\n");
	}
	else
	{	
		length = strlen(cmd_src);
		while(i <= length)/* be careful with space in the filename */
		{	
			if((*(cmd_src+i)) !=' ' && (*(cmd_src+i)) != '\\')
			{
				if(flag == 0)
					src_file[j] = *(cmd_src +i);
				else
					dst_file[j] = *(cmd_src +i);
				j++;
			}
			if((*(cmd_src+i)) == '\\' && (*(cmd_src+i+1)) !=' ')
			{
				if(flag == 0)
					src_file[j] = *(cmd_src +i);
				else
					dst_file[j] = *(cmd_src +i);
				j++;
			}
			if((*(cmd_src+i)) == ' ' && (*(cmd_src+i-1)) != '\\')
			{
				src_file[j] = '\0';
				flag = 1;
				j = 0;
			}
			if((*(cmd_src+i)) == '\\' && (*(cmd_src+i+1)) == ' ')
			{
				if(flag == 0)
					src_file[j] = ' ';
				else
					dst_file[j] = ' ';
				j++;
			}
			i++;
		};
	}
	if(flag == 0)
	{
		strcpy(dst_file, src_file);
	}
	else
	{
		dst_file[j] = '\0';
	}
}


int ftp_login(char * server_ip, int port, char * user, char * password)
{
	int error;
	if(port<=0||port>=(1<<16))
	{
		cmd_err_exit("Invalid port!",254);
	}
	bzero(&ftp_server,sizeof(struct sockaddr_in));
	ftp_server.sin_family=AF_INET;
	ftp_server.sin_port=htons(port);
	if(inet_addr(server_ip)!=-1)
	{
		ftp_server.sin_addr.s_addr=inet_addr(server_ip);
	}
	else
	{
		if((server_hostent=gethostbyname(server_ip))!=0)
		{
			memcpy(&ftp_server.sin_addr,server_hostent->h_addr,sizeof(ftp_server.sin_addr));
		}
		else
		{
			cmd_err_exit("Invalid address!",253);
		}
	}
	sock_control=ftp_connect(&ftp_server,1); /* 建立控制通道 */
	if((error=ftp_get_reply(sock_control))!=220)/* 对新用户准备好 */
	{
		cmd_err_exit("Connect error!",220);
	}
	if(ftp_send_cmd("USER ", user, sock_control) < 0)
	{
		cmd_err_exit("Can not send message",1);
	}
	error = ftp_get_reply(sock_control);	
	printf("ftp reply number:<%d>, fun<%s> line<%d>\n",error,__FUNCTION__,__LINE__);
	if(error == 331)
	{
		if(ftp_send_cmd("PASS ", password, sock_control) <= 0)
		{
			cmd_err_exit("Can not send message",1);
		}	
		else
		{
			error = ftp_get_reply(sock_control);
		}
		if(error != 230)
		{
			printf("Password error!\n");
			close(sock_control);
			return -1;
		}		
		printf("login succ!\n");
		return 0;		
	}
	else
	{
		printf("User error!\n");
		close(sock_control);
		return -2;
	}
}

// 切换ftp的目录
int local_cd(char *dir)
{
	if(NULL == dir)
	{
		printf("invalid dir.<%s><%d>\n",__FUNCTION__,__LINE__);
		return -1;
	}
	char localDir[1024];
	memset(localDir,0,sizeof(localDir));
	strncpy(localDir,dir,strlen(dir));
	localDir[strlen(dir)]='\0';
	if(chdir(localDir)<0)// cd 的系统调用函数
	{
		printf("chdir error!\n");
		return -1;
	}
	else
	{
		printf("local cd succ! localDir=%s\n",localDir);
	}
	return 0;
}

int ftp_cd(char *dir)
{
	int error;
	if(dir==NULL)
	{
		printf("command error!\n");
		return -1;
	}
	char ftpDir[1024];
	memset(ftpDir,0,sizeof(ftpDir));
	strncpy(ftpDir,dir,strlen(dir));
	ftpDir[strlen(dir)]='\0';
	ftp_send_cmd("CWD ",ftpDir,sock_control); /* 改变服务器上的工作目录　 */
	error = ftp_get_reply(sock_control);	
	printf("ftp reply number:<%d>, fun<%s> line<%d>\n",error,__FUNCTION__,__LINE__);
	if(error == 550)
	{
		printf("ftp file error !\n");
		return -1;
	}	
	printf("ftp cd succ! ftpDir=%s\n",ftpDir);
	return 0;
}


int ftp_get(st_ftp *s)
{
	int ret,error;
	int get_sock, set, new_sock, i = 0;
	char src_file[512],dst_file[512],rcv_buf[512],get_cmd[512];	
	int local_file;
	int count = 0;
	struct stat file_info;
	memset(src_file,0,sizeof(src_file));
	memset(dst_file,0,sizeof(dst_file));	
	memset(rcv_buf,0,sizeof(rcv_buf));
	memset(get_cmd,0,sizeof(get_cmd));
	sprintf(get_cmd,"get %s",s->getFileName);

	if((ret = ftp_login(s->ip, s->port, s->user, s->password)) == -1)
	{
		printf("Password error!\n");
		return -1;
	}
	else if(ret == -2)
	{
		printf("User error!\n");
		return -1;
	}
	
	if(local_cd(s->localDir) != 0)
	{
		printf("local cd error !\n");		
		return -1;
	}

	if(ftp_cd(s->ftpDir) != 0)
	{
		printf("ftp cd error !\n");		
		return -1;
	}

	ftp_cmd_filename(get_cmd, src_file, dst_file);
	
	if(!stat(dst_file, &file_info))
	{
		printf("local file %s exists: %d bytes\n", dst_file, (int)file_info.st_size);
		if(!s->getCoverFalgs)
		{
			close(sock_control);
			return -1;
		}
	}
	
	local_file = open(dst_file, O_CREAT|O_TRUNC|O_WRONLY);
	if(local_file < 0)
	{
		printf("creat local file %s error!\n", dst_file);
		close(sock_control);
		return -2;
	}
	get_sock = ftp_connect_data();
	if(get_sock < 0)
	{
		printf("socket error!\n");
		close(sock_control);
		return -3;
	}
	set = sizeof(local_host);
	
	ftp_send_cmd("TYPE I", NULL, sock_control);
	error = ftp_get_reply(sock_control);
	printf("ftp reply number:<%d>, fun<%s> line<%d>\n",error,__FUNCTION__,__LINE__);
	if(error != 200)
	{
		printf("commond :<TYPE I> error!,line<%d>\n",__LINE__);
		return -1;
	}
	
	ftp_send_cmd("RETR ", src_file, sock_control);/* 从服务器上找回（复制）文件　 */
	error = ftp_get_reply(sock_control);
	printf("ftp reply number:<%d>, fun<%s> line<%d>\n",error,__FUNCTION__,__LINE__);	
	if(error != 150)
	{
		printf("commond :<RETR> error!,line<%d>\n",__LINE__);
		return -1;
	}
	
	printf("get file begin,please wait ...\n");
	while(1)
	{
		count = read(get_sock, rcv_buf, sizeof(rcv_buf));
		if(count <= 0)
		{
			break;
		}	
		else
		{
			if((write(local_file, rcv_buf, count)) == -1)
			{
				printf("write err!\n");
				break;
			}
		}
	}
	printf("get file succ!\n");
	close(local_file);
	close(get_sock);
	ftp_get_reply(sock_control); 	
	ftp_quit();
	return 0;
}

int ftp_put(st_ftp *s)
{
	int ret,error;
	char src_file[512],dst_file[512],send_buff[512],put_cmd[512];
	struct stat file_info;
	int local_file;
	int file_put_sock,new_sock,count=0,i=0;
	int set=sizeof(local_host);
	
	memset(src_file,0,sizeof(src_file));
	memset(dst_file,0,sizeof(dst_file));	
	memset(send_buff,0,sizeof(send_buff));
	memset(put_cmd,0,sizeof(put_cmd));
	sprintf(put_cmd,"put %s",s->putFileName);
	
	if((ret = ftp_login(s->ip, s->port, s->user, s->password)) == -1) // 登录ftp
	{
		printf("Password error!\n");
		return -1;
	}
	else if(ret == -2)
	{
		printf("User error!\n");
		return -1;
	}
	
	if(local_cd(s->localDir) != 0) // 切换到本地目录
	{
		printf("local cd error !\n");		
		return -1;
	}

	if(ftp_cd(s->ftpDir) != 0)// 改变ftp服务器的目录
	{
		printf("ftp cd error !\n");		
		return -1;
	}
	
	ftp_cmd_filename(put_cmd,src_file,dst_file);// ftp操作命令
	if((stat(src_file,&file_info))<0) // 获取文件信息
	{
		printf("local file %s doesn't exist!\n",src_file);
		close(sock_control);
		return -1;
	}
	local_file=open(src_file,O_RDONLY);
	if(local_file<0)
	{		
		printf("Open file error\n");
		close(sock_control);
		return -2;
	}
	file_put_sock=ftp_connect_data();
	if(file_put_sock<0)
	{
		ftp_get_reply(sock_control);
		printf("Creat data socket error!\n");		
		close(local_file);
		close(sock_control);
		return -3;
	}	
	ftp_send_cmd("TYPE I",NULL,sock_control);/* 数据类型（A=ASCII，E=EBCDIC，I=binary） */
	error = ftp_get_reply(sock_control);
	printf("ftp reply number:<%d>, fun<%s> line<%d>\n",error,__FUNCTION__,__LINE__);	
	if(error != 200)
	{
		printf("commond :<TYPE I> error!,line<%d>\n",__LINE__);
		return -1;
	}
	
	ftp_send_cmd("STOR ",dst_file,sock_control);/* 储存（复制）文件到服务器上　 */
	error = ftp_get_reply(sock_control);
	printf("ftp reply number:<%d>, fun<%s> line<%d>\n",error,__FUNCTION__,__LINE__);	
	if(error != 150)
	{
		printf("commond :<STOR> error!,line<%d>\n",__LINE__);
		return -1;		
	}

	printf("put file begin,please wait ...\n");
	while(1)
	{
		count=read(local_file,send_buff,sizeof(send_buff));
		if(count<=0)
		{
			break;
		}
		else
		{
			if((write(file_put_sock,send_buff,count)) == -1)
			{
				printf("write err!\n");
				break;
			}
		}
	}	
	printf("put file succ!\n");
	close(local_file);
	close(file_put_sock);
	ftp_get_reply(sock_control);	
	ftp_quit();
	return 0;
}



int main(int argc,char *argv[])
{
	int ret;
	st_ftp s;
	memset(&s,0,sizeof(s));
	s.getCoverFalgs = TRUE;   /* 如果下载的文件本地已经存在，是否需要覆盖，TRUE覆盖 ,FALSE不覆盖 */
	s.port = 21;
	strcpy(s.ip,"192.168.0.28");
	strcpy(s.user,"rong");		
	strcpy(s.password,"111111");	
	strcpy(s.putFileName,"u.txt uuuu.txt"); /* 上传文件u.txt ,上传后修改名字为 uuuu.txt ( 为空 则不修改名字 ) */
	strcpy(s.getFileName,"h.txt hhhh.txt"); /* 下载文件h.txt ,下载后修改名字为 hhhh.txt ( 为空 则不修改名字 ) */
	strcpy(s.ftpDir,"hello");	/* ftp 服务器上的文件存放目录 */
	strcpy(s.localDir,"/home/rong/ftp");	/* 本地的文件存放目录 */	

/* 
	不修改名字:
	strcpy(s.putFileName,"u.txt"); 
	strcpy(s.getFileName,"h.txt");
*/	

	if((ret = ftp_put(&s)) != 0)
	{
		printf("ftp put error!\n");
	}
	
	if((ret = ftp_get(&s)) != 0)
	{
		printf("ftp get error!\n");
	}
	return 0;
}

