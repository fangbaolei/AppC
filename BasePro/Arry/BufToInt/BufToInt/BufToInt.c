#include <stdio.h>
int main(void)
{
	char buf[4]= {0xe6,0x04,0x00,0x00};
    int  val = 0;
	val = *(int *)buf;
    printf("VVVVV:%d\n",val);
	return 0;
}
