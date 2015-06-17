// 枚举作为函数参数
#include <stdio.h>
typedef enum NUM{
	STU_NUM0 = 0,
	STU_NUM1
}g_NUM;
void test(g_NUM num)
{
	printf("num:%d\n",num);
}
int main(void)
{
	int i = 0;
	for(i = 0; i < 2; i++)
	{
	    test(i);
	}
	//printf("num0 = %d;num1 = %d\n", STU_NUM0, STU_NUM1);
	return 0;
}
