#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>
int main(void)
{
	char Str[50] = {0};
	char Arr[10] = {0};
	int i = 0;
	int num[3] = {0};
	char *p;
	for(i = 0; i < 3;i++)
	{
		memset(Arr,0,sizeof(Arr));
		sprintf(Arr,"%d",i);
	    strcat(Str,Arr);	
		strcat(Str,";");
	}
	printf("Str:%s\n",Str);
	p = strtok(Str,";");
	while(p != NULL)
	{
		//printf("tokStr:%s",p);
		num[i++] = atoi(p);
		p = strtok(NULL,";");
	}
	for(i = 0;i < 3;i ++)
	{
		printf("NUM[%d]:%d\n",i,num[i]);
	}
	return 0;
}
