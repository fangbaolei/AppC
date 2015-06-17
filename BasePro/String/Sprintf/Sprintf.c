#include <stdio.h>
int main(void)
{
	int num;
	char buf[10];
	char str1[20] = "abc";
	char str2[5] = "ddd";
	char str3[32] = {0};
	num = sprintf(buf, "%s", "ttttt");
	printf("num = %d\n", num);
	sprintf(str3,"%s   ##  %s",str2,str1);
	printf("str1:%s\n",str3);
	return 0;
}
