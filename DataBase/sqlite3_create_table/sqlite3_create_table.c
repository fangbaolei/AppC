#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
sqlite3 * SqliteOpen(sqlite3 *db)
{
    int result;
 
    //打开指定的数据库文件,如果不存在将创建一个同名的数据库文件
    result = sqlite3_open("test.db", &db);
    if(result != SQLITE_OK)
    {
   	    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	    sqlite3_close(db);
	    return NULL;
     }
     else 
     {
    	     printf("Open Database test.db success!\n");
     }
     return db;
}
int SqliteCreate(sqlite3 *db)
{
       int result;
	char *errmsg = 0;
	char *SqlCmd ="create table Table1(id int primary key,msg varchar(128))";
	result=sqlite3_exec( db, SqlCmd , NULL, NULL, &errmsg); 
	if( result != SQLITE_OK ) 
	{
		 fprintf(stderr, "Create table database error: %s\n", sqlite3_errmsg(db));
		//�ر����ݿ� 
		sqlite3_close(db); 
		return -1;
	}
	else
	{
 		printf("Create Database table success!\n");
	}
	sqlite3_close(db); 
	return 0;
}
int main( void )
{
    sqlite3 *dbOpen=NULL;
    sqlite3 *db = NULL;
    db = SqliteOpen(dbOpen);
    SqliteCreate(db);
}

