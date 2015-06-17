#include <stdio.h>
int test1(void *data)
{
	int a = *(int *)data;
	printf("a = %d\n", a);
	return 0;
}
int test2(void *data)
{
	char *str = (char *)data;
	printf("str = %s\n", str);
	return 0;
}
int main(void)
{
	int num = 4;
    char *str1 = "abc"; 
	test1(&num);
	test2(str1);
	return 0;
}
