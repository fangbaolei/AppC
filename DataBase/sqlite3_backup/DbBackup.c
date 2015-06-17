#include <stdio.h>
#include <sqlite3.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <memory.h>
#define DATABASE_FILE		"/data/system.db"
// 查询重要的表单数据
int DbTblChk(sqlite3 *db)
{
	unsigned char i = 0;
	int result = 0;
	char **dbResult = NULL;
   	int nRow = 0, nColumn = 0;
    // 打开system.db中的一些比较重要的表单
    // 如果修改了这些表单名称，请及时修改此处对应的表单名称。
	char *sqlcmd[7] = {
	"select * from userInfo", 
	"select * from SystemInfo",
	"select * from networkInfo",
	"select * from netManageInfo",
	"select * from CommCfgInfo",
	"select * from RecordChannelTime",
	"select * from RecordChannelInfo"
	};
	char sqlcmd1[256] = {0};
    // 读数据库
	for(i = 0; i < 7; i++)
	{
		result = sqlite3_get_table(db, sqlcmd[i], &dbResult, &nRow, &nColumn, NULL);
		if(SQLITE_OK != result)//查询某个表单失败，恢复数据库并退出。
		{
			sqlite3_free_table(dbResult);
			return -1;
		}
		sqlite3_free_table(dbResult);
	}
    // 写数据库
	memset(sqlcmd1,0,sizeof(sqlcmd1));
	sprintf(sqlcmd1,"update DbBkTestTbl set  BackupTest='%s' where idx=0","Backup Test!");
	if(SQLITE_OK != sqlite3_exec(db, sqlcmd1, NULL, NULL, NULL))
	{
		printf("sqlite3_exec error!  %s  %d \n",__FILE__,__LINE__);
		return -1;
	}
	return 0;
}
//  数据库备份
void DbBackup(void)
{
	sqlite3 *db;
	int ret = 0;
	if(SQLITE_OK != sqlite3_open(DATABASE_FILE, &db))//数据库打开失败,恢复数据库。
	{
		sqlite3_close(db);
		system("cp /config/system.db /data -f");
		printf("Database is damaged, and have recovered! %s  %d \n",__FILE__,__LINE__);
	}
	else
	{
		ret = DbTblChk(db);
		if(ret == -1) //数据库损坏，恢复数据库
		{	
		   system("cp /config/system.db /data -f");
		   printf("Database is damaged, and have recovered!  %s  %d \n",__FILE__,__LINE__);
		}
		else
		{
			system("cp /data/system.db /config -f");// 数据库正常,备份当前的数据库。
		    printf("Database is OK, backup!! %s  %d \n",__FILE__,__LINE__);
		}
		sqlite3_close(db);
	}
}
//数据库读写测试
static void db_create_DbBkTestTbl(sqlite3 *db)
{
	char sql_cmd[256] = {0};
	memset(sql_cmd,0,sizeof(sql_cmd));
	sprintf(sql_cmd,"%s",
		"CREATE TABLE [DbBkTestTbl](\
		[idx] INT(1) PRIMARY KEY NOT NULL,\
		[BackupTest] CHAR(32) NOT NULL);"
		);
	if(sqlite3_exec(db,sql_cmd,NULL,NULL,NULL) != SQLITE_OK)
	{
		printf("sqlite3_exec error!  %s  %d \n",__FILE__,__LINE__);
		return ;
	}
	memset(sql_cmd,0,sizeof(sql_cmd));
	sprintf(sql_cmd,"INSERT INTO DbBkTestTbl VALUES (0,\" Backup Test!\");");
	if(sqlite3_exec(db,sql_cmd,NULL,NULL,NULL) != SQLITE_OK)
	{
		printf("insert failed %s  %d \n",__FILE__,__LINE__);
	}
}
//数据库初始化
void DbInit(void)
{
	char sql_cmd[128] = {0};
	char **dbResult;
	int nRow = 0, nColumn = 0;
    sqlite3 *db;
    static pthread_mutex_t databaseMutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&databaseMutex);
	if(SQLITE_OK != sqlite3_open(DATABASE_FILE, &db))
	{
		sqlite3_close(db);
		pthread_mutex_unlock(&databaseMutex);
	}
	memset(sql_cmd,0,sizeof(sql_cmd));
	sprintf(sql_cmd,"select * from DbBkTestTbl");
	if(sqlite3_get_table(db, sql_cmd, &dbResult, &nRow, &nColumn, NULL) != SQLITE_OK)
	{
		db_create_DbBkTestTbl(db);
	}
	pthread_mutex_unlock(&databaseMutex);

	sqlite3_free_table(dbResult);
}
int main(void)
{
	DbInit();
	DbBackup();
	return 0;
}
