#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_t pthid;
void *thrd_func(void *arg)
{
    printf("New process:  PID: %d,TID: %lu\n",getpid(),pthread_self()); //why pthread_self
    printf("New process:  PID: %d,TID: %lu\n",getpid(),pthid); 
    pthread_exit(NULL); //退出线程
	return NULL;
}

int main(void)
{
    // 创建线程pthid，且线程函数由thrd_func指向，是thrd_func的入口点，即马上执行此线程函数
    if(pthread_create(&pthid,NULL,thrd_func,NULL)!=0) 
    {
        printf("Create thread error!\n");
        exit(1);
    }
    printf("TID in pthread_create function: %lu\n", pthid);
    printf("Main process: PID: %d,TID: %lu\n", getpid(), pthread_self()); 
    while(1); //race
    return 0;
}

