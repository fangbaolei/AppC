�����ܣ��ϴ������ء�
1,���ṹ�壺
typedef struct ftp_client
{
	int port; /* ftp �˿� */
	char ip[20]; /* ftp ������ ip */
	char user[32]; /* �û��� */
	char password[32]; /*  ���� */
	char putFileName[128]; /* �ϴ��ļ������� */
	char getFileName[128]; /* �����ļ������� */
	int getCoverFalgs;  /* ������ص��ļ������Ѿ����ڣ��Ƿ���Ҫ���ǣ�TRUE���� ,FALSE������ */
	char ftpDir[128];	/* ftp �������ϵ��ļ����Ŀ¼ */
	char localDir[128];	/* ���ص��ļ����Ŀ¼ */	
}st_ftp;


2������һ��ftp���������û��� rong������ 111111

3��������ip��192.168.0.28    ftp�˿ڣ�21

4��ָ�� ftp�������� �� ���ص��ļ����Ŀ¼��  

5���ϴ������ļ������� ftp_put(st_ftp *s)
	
6������ftp���������ļ������� ftp_get(st_ftp *s)

���ӣ�
	st_ftp s;
	memset(&s,0,sizeof(s));
	s.getCoverFalgs = TRUE;   /* ������ص��ļ������Ѿ����ڣ��Ƿ���Ҫ���ǣ�TRUE���� ,FALSE������ */
	s.port = 21;
	strcpy(s.ip,"192.168.0.28");
	strcpy(s.user,"rong");		
	strcpy(s.password,"111111");	
	strcpy(s.putFileName,"u.txt uuuu.txt"); /* �ϴ��ļ�u.txt ,�ϴ����޸�����Ϊ uuuu.txt ( Ϊ�� ���޸����� ) */
	strcpy(s.getFileName,"h.txt hhhh.txt"); /* �����ļ�h.txt ,���غ��޸�����Ϊ hhhh.txt ( Ϊ�� ���޸����� ) */
	strcpy(s.ftpDir,"hello");	/* ftp �������ϵ��ļ����Ŀ¼ */
	strcpy(s.localDir,"/home/rong/ftp");	/* ���ص��ļ����Ŀ¼ */	

/* 
	���޸�����:
	strcpy(s.putFileName,"u.txt"); 
	strcpy(s.getFileName,"h.txt");
*/	





















































