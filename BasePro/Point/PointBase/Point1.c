#include <stdio.h>
int fun1(void *i)
{
    printf("i22:%c\n",*(char *)i);
	return 0;
}
int main()
{
    char i[1] = {'a'};
    
	fun1(i);
    printf("i11:%d\n",*i);
	return 0;
}
