#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
void SigHan(int SigType)
{
	if(SigType == SIGINT)// ctrl + c
	{
		printf("signal SIGINT!!\n");
		exit(0);
	}
    if(SigType == SIGTERM)// kill
    {
        printf("Signal SIGTERM!\n");    
		exit(0);
    }
}
int main(void)
{
	signal(SIGINT, SigHan);
	signal(SIGTERM, SigHan);
	while(1)
	{
		printf("TTTT\n");
		sleep(1);
	}
	return 0;
}
