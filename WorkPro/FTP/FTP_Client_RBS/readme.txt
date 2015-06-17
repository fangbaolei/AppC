程序功能：上传，下载。
1,填充结构体：
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


2，建立一个ftp服务器的用户名 rong，密码 111111

3，服务器ip：192.168.0.28    ftp端口：21

4，指定 ftp服务器上 和 本地的文件存放目录。  

5，上传本地文件：调用 ftp_put(st_ftp *s)
	
6，下载ftp服务器的文件：调用 ftp_get(st_ftp *s)

例子：
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





















































