#include <stdio.h>
typedef void (*CALL_BACK_TEST)(void);
typedef struct {
	int a;
	CALL_BACK_TEST CallBackTest;
}Stu;
void test(void)
{
	printf("AAAA\n");
}
int main(void)
{
	Stu Stu1;
	Stu1.CallBackTest = test;
	Stu1.CallBackTest();
	return 0;
}
