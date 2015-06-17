#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
sqlite3 * SqliteOpen(sqlite3 *db)
{
    int result;
 
    //æ‰“å¼€æŒ‡å®šçš„æ•°æ®åº“æ–‡ä»¶,å¦‚æœä¸å­˜åœ¨å°†åˆ›å»ºä¸€ä¸ªåŒåçš„æ•°æ®åº“æ–‡ä»¶
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
	char *SqlCmd ="create table Stu(id int, name varchar(255))";
	result=sqlite3_exec( db, SqlCmd , NULL, NULL, &errmsg); 
	if( result != SQLITE_OK ) 
	{
		 fprintf(stderr, "Create table database error: %s\n", sqlite3_errmsg(db));
		//¹Ø±ÕÊı¾İ¿â 
		sqlite3_close(db); 
		return -1;
	}
	else
	{
 		printf("Create Database table success!\n");
	}
	return 0;
}
int SqliteInsert(sqlite3 *db)
{
       int result;
	char *errmsg = 0;
	char *SqlCmd ="insert into stu values(55, 'abc')";
	result=sqlite3_exec( db, SqlCmd , NULL, NULL, &errmsg); 
	if( result != SQLITE_OK ) 
	{
		 fprintf(stderr, "Insert value error: %s\n", sqlite3_errmsg(db));
		//¹Ø±ÕÊı¾İ¿â 
		sqlite3_close(db); 
		return -1;
	}
	else
	{
 		printf("Insert value success!\n");
	}
	sqlite3_close(db); 
	return 0;
}
int SqliteDelete(sqlite3 *db)
{
       int result;
	char *errmsg = 0;
	char *SqlCmd ="DELETE  FROM stu WHERE name = 'abc'";
	result=sqlite3_exec( db, SqlCmd , NULL, NULL, &errmsg); 
	if( result != SQLITE_OK ) 
	{
		 fprintf(stderr, "DELETE value error: %s\n", sqlite3_errmsg(db));
		//¹Ø±ÕÊı¾İ¿â 
		sqlite3_close(db); 
		return -1;
	}
	else
	{
 		printf("DELETE value success!\n");
	}
	sqlite3_close(db); 
	return 0;
}
int main( void )
{
    sqlite3 *dbOpen=NULL;
    sqlite3 *db = NULL;
    db = SqliteOpen(dbOpen);
    //SqliteCreate(db);
    //SqliteInsert(db);
    SqliteDelete(db);
}

