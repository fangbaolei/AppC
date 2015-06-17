#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void)
{
	char *Path="AABBCC";
	char PathArr[strlen(Path)];
    printf("Path:%s\n",Path);
    memset(PathArr,0,sizeof(PathArr));
	printf("PathArr:%s\n",PathArr);
	strcpy(PathArr,Path);
	printf("PathArr11:%s\n",PathArr);
    printf("<func:%s><line:%d>\n",__FUNCTION__,__LINE__);
	return 0;
}
