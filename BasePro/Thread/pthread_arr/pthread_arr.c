//线程通过设置attr属性，使线程自己释放资源，而不需要使用pthread_join函数
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
void*start_run(void*arg)
{
	while(1)
	{
		printf("ddddd\n");
		sleep(1);	
	}
}
 
int main(void)
{
	int iRet=0;
	pthread_t thread_id;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	iRet = pthread_create(&thread_id,&attr,start_run,NULL);//第二个参数不为NULL时，表明该线程是detached，则在关闭该线程时，应该使用destroy方式释放资源。
	if(iRet != 0)
	{
		pthread_attr_destroy(&attr);
	}
	sleep(5);
	exit(0);
	return 0;
}

