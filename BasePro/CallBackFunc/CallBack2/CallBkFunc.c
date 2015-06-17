#include <stdio.h>
void test1(int a)
{
	printf("NNNNN\n");
    printf("aaa:%d\n",a);
}
void test2(int b)
{
    printf("bbb:%d\n",b);
}
int Call1(int c, void (*pfun)(int c))
{
    (*pfun)(c);
	return 0;
}
void test3(void)
{
	printf("cccc\n");
}
int Call2(void (*pfun)())
{
	(*pfun)();
	return 0;
}
int main(void)
{
	Call1(50,test1);
	Call1(70,test2);
    Call2(test3);
}
