#include <stdio.h>
int fun(int *pA)
{
	int b = 5;
    *pA = b;
	printf("AAA:%d\n", *pA);
	return 0;
}
int main(void)
{
	int a = 3;
    fun(&a);
	printf("BBB:%d\n", a);
	return 0;
}
