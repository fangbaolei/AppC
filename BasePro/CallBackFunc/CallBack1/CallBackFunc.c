#include <stdio.h>
typedef int (*CallBackFun)(int a);
void test1(void)
{
	printf("aaaa1111\n");
}
int test2(int num)
{
	printf("bbbbb222:%d\n",num);
	return 0;
}
int Call1(void (*pfun)())
{
    (*pfun)();
	return 0;
}
int Call2(CallBackFun pCallBack, int b)
{
	pCallBack(b);
	return 0;
}
int Call3(CallBackFun pCallBack)
{
	int c = 6;
	pCallBack(c);
	return 0;
}
int main(void)
{
	Call1(test1);
	Call2(test2,5);
	Call3(test2);
	return 0;
}
