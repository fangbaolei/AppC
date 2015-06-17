#include <stdio.h>
#include <world.h>
int main(void)
{
	fprintf(stderr, "hello %s:%d\n",__FILE__,__LINE__);
	return 0;
}
