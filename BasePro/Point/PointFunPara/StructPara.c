#include <stdio.h>
struct Stu{
    char i;
    char addr[20];
};
int fun(struct Stu *stu)
{
	printf("name:%d\n",stu->i);
	printf("addr:%s\n",stu->addr);
	return 0;
}
int main(void)
{	
	struct Stu Stu1 = {5,"bb"};
    fun(&Stu1);
	return 0;
}
