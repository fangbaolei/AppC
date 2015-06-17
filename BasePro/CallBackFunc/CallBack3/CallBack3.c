#include <stdio.h>
typedef void (*CALL_BACK_TEST)(void);
void test1(void)
{
	printf("UUUU\n");
}
void test2(void)
{
    printf("NNNNNN\n");
	printf("UUUU\n");
}
int main(void)
{
	CALL_BACK_TEST CallBackTest;
	CallBackTest = test1;
    CallBackTest();
	CallBackTest = test2;
    CallBackTest();
	return 0;
}
