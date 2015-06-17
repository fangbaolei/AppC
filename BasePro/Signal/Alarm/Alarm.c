#include <stdio.h>
#include <signal.h>
#include <time.h>
void sigAlarm1SFunction(int sig)
{
	printf("DDDD\n");
	signal(SIGALRM,sigAlarm1SFunction);
//	alarm(1);
}
int main(void)
{
	signal(SIGALRM,sigAlarm1SFunction);
	alarm(3);	
	while(1)
	{
		printf("AAAAAi\n");
		sleep(1);	
	}
	return 0;
}
