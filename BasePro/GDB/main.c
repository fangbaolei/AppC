#include <stdio.h>
#include "sum.h"
int main(int argc, char *argv[])
{
	int a = 1, b = 2, result = 0;
	//sprintf(a, "%d", argv[1]);
	//sprintf(b, "%d", argv[2]);
	printf("a = %d, b = %d\n", a, b);
//	printf("argv[1] = %s, argv[2] = %s\n", argv[1], argv[2]);
	result = sum(a, b);
	printf("result = %d\n", result);
	return 0;
}
