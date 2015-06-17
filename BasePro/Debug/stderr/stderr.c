#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thrd_func1(void *arg)
{
    int i = 0;
    printf("Thread 1 returning!\n");
    while(1)
    {   
        //stderr一般用在多线程中打印信息，printf只能在当前进程中打印，如果这里使用printf，是不会实时看到输出信息的。
        fprintf(stderr,"second:%d   %s:%d\n",i++,__FILE__,__LINE__);
        sleep(1);
        if(i >= 10) 
        break;  
    }   
    pthread_exit((void *)1); // 自动退出线程
}
int main(void)
{
    pthread_t tid1;
    void *tret;
    // 创建线程tid1，线程函数thrd_func1
    if (pthread_create(&tid1,NULL,thrd_func1,NULL)!=0) 
    {   
        printf("Create thread 1 error!\n");
        exit(1);
    }   
    // 等待线程tid1结束，线程函数返回值放在tret中
    if (pthread_join(tid1,&tret)!=0)
    {
        printf("Join thread 1 error!\n");
        exit(1);
    }
    printf("Thread 1 exit code: %d\n",(int)tret);
    return 0;
}

