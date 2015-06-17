#include <stdio.h>
#include <memory.h>
#define AV_FILE_PATH "./test.txt"
int main(void)
{
	FILE* fp = NULL;
	char FileBuf[128] = {0};
	size_t bytes_read = 0;
	long  nSize = 0;
	fp = fopen(AV_FILE_PATH, "rb");
	if(fp == NULL)
	{
	    printf("Open file failed \n");
	    fclose(fp);
	    return -1;
	}
	fseek(fp,0,SEEK_END);
	nSize = ftell(fp);
	fseek(fp,0,SEEK_SET);
	printf("nSize:%ld\n\n",nSize);
	while(1)
	{
		memset(FileBuf, 0, sizeof(FileBuf));
		bytes_read = fread(FileBuf,1, 100, fp);
		if(bytes_read > 0)
		{
			printf("%s",FileBuf);
		}
		else
		{
			fclose(fp);
			break;
		}
	}
	return 0;

}
