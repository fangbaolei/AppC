#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int main( void )
{
    sqlite3 *db=NULL;
    int ret;
 
    //打开指定的数据库文件,如果不存在将创建一个同名的数据库文件
    ret = sqlite3_open("test.db", &db);
    if(ret)
    {
   	    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
     	sqlite3_close(db);
     	return -1;
 	}
 	else 
 	{
    	 printf("Open Database test.db success!\n");
 	}

 	sqlite3_close(db); //关闭数据库
 	return 0;
}

