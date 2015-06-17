#include <stdio.h>
int main(void)
{
	unsigned char buf[4] = {0x00,0x12,0xd6,0x87};
	unsigned int a = 0;
    a = (buf[0]<<24)|(buf[1]<<16)|(buf[2]<<8)|buf[3];
	printf("a = %d\n",a);
	return 0;	
}
