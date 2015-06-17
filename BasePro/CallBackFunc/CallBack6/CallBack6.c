#include <stdio.h>
#include <string.h>
typedef int (*DbTblCreate)(char* TblName, char* TblInitPara);
typedef struct DbTblInit{
    char *TblName;
    char *TblInitPara;
    DbTblCreate TblCreate;
}DbTblInit;
static int test(char* TblName, char* TblInitPara)
{
	printf("TblName:%s   TblInitPara:%s\n",TblName,TblInitPara);
	return 0;
}
int main(void)
{
	char kk[10] = {0};
	char jj[10] = {0};
	int i = 0;
	int num = 0;
	DbTblInit TblInit[] =
	{
	    {"ntpCfg","dddd",test}
	};
	num = sizeof(TblInit)/sizeof(DbTblInit);
	for(i = 0;i < num; i++)
	{
		strcpy(kk,TblInit[i].TblName);
		strcpy(jj,TblInit[i].TblInitPara);
		TblInit[i].TblCreate(kk,jj);
    }
	return 0;
}
