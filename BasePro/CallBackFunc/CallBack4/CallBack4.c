#include <stdio.h>
typedef void (*CALL_BACK_TEST)(void);
void test1(void)
{
	printf("AAAA\n");
}
void test2(void)
{
	printf("BBBB\n");
}
int main(void)
{
	int i = 0;
    CALL_BACK_TEST CallBackTest;

	CALL_BACK_TEST CallBackArr[] = 
    {
    	test1,
        test2
    };
    for(i = 0; i< 2; i++)
	{
		CallBackTest = CallBackArr[i];
		CallBackTest();
	}
	return 0;
}
