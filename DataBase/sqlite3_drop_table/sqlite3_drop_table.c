#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
/*************************
sqlite3_open:´ò¿ªÊı¾İ¿â£¬Èç¹ûÊı¾İ¿â²»´æÔÚ£¬¾Í´´½¨Ò»¸öĞÂµÄÊı¾İ¿â





**************************/
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
/*************************
sqlite3_exec:Ö´ĞĞÊı¾İ¿â²Ù×÷ÃüÁî
create table:´´½¨±í




**************************/
int SqliteCreateTbl(sqlite3 *db)
{
       int result;
	char *errmsg = 0;
	char *SqlCmd ="create table Table1(id int, name int,addr int)";
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
	sqlite3_close(db); 
	return 0;
}

/*************************
sqlite3_exec:Ö´ĞĞÊı¾İ¿â²Ù×÷ÃüÁî
create table:´´½¨±í




**************************/
int SqliteDropTbl(sqlite3 *db)
{
       int result;
	char *errmsg = 0;
	char *SqlCmd ="drop table Table1";
	result=sqlite3_exec( db, SqlCmd , NULL, NULL, &errmsg); 
	if( result != SQLITE_OK ) 
	{
		 fprintf(stderr, "Drop table  error: %s\n", sqlite3_errmsg(db));
		//¹Ø±ÕÊı¾İ¿â 
		sqlite3_close(db); 
		return -1;
	}
	else
	{
 		printf("Drop database table success!\n");
	}
	sqlite3_close(db); 
	return 0;


}

int main( void )
{
    sqlite3 *dbOpen=NULL;
    sqlite3 *db = NULL;
    db = SqliteOpen(dbOpen);
    SqliteCreateTbl(db);
    //SqliteDropTbl(db);
}

