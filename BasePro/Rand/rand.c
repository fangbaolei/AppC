#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int RandInt6(char *chRand)
{
	int a = 0;
	srand(time(NULL));
	a = rand()%90000 + 100000 * (rand() % 9 + 1); 
	printf("a = %d\n",a);
	sprintf(chRand, "%d", a); 
	printf("Pwd = %s\n",chRand);
	return 0;
}
int main()
{
	char b[8] = {0};
	#if 0
	srand(time(NULL));
	int a = 0;
	char b[7] = {0};
	a = rand()%90000 + 100000 * (rand() % 9 + 1);
	printf("a = %d\n",a);
	sprintf(b, "%d", a);
#endif
	RandInt6(b);
	printf("b = %s\n",b);
	return 0;
}
