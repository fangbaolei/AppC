#include <stdio.h>
#include <string.h>
typedef struct CbFuncs{
    int (*test1)(char *name, char *pw);
    int (*test2)(int len);
 
}CB_FUNCS;
static int get_test1(char *name, char *pw)
{
	printf("name:%s   pw:%s\n", name, pw);
	return 0;
}
static int get_test2(int len)
{
	printf("len:%d\n", len);
	return 0;
}
int main(void)
{
    CB_FUNCS CallbackFuncs = 
	{
	    .test1 = get_test1, // test1成员前面的点，表示将test1初始化。
	    .test2 = get_test2,
    };
	CallbackFuncs.test1("abc","123");
	CallbackFuncs.test2(456);
	return 0;
}
