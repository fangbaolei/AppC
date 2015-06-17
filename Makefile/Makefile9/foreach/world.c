#include <stdio.h>
int word(void)
{
	fprintf(stderr, "world %s:%d\n",__FILE__,__LINE__);
	return 0;
}
