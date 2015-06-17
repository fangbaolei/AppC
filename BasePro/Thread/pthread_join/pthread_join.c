// pthread_join是一个阻塞函数，它会等待线程退出，才能释放该线程的资源。
// pthread_create函数的第二个参数是NULL时，表明该线程是joinable的，此时应该使用pthread_join函数释放该线程的资源。
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thrd_func1(void *arg);
void *thrd_func2(void *arg);

int main(){
    pthread_t tid1,tid2;
    void *tret;
    // 创建线程tid1，线程函数thrd_func1
    if (pthread_create(&tid1,NULL,thrd_func1,NULL)!=0) 
	{
        printf("Create thread 1 error!\n");
        exit(1);
    }
    // 创建线程tid2,线程函数thrd_func2
    if (pthread_create(&tid2,NULL,thrd_func2,NULL)!=0) {
        printf("Create thread 2 error!\n");
        exit(1);
    }
    // 等待线程tid1结束，线程函数返回值放在tret中
    if (pthread_join(tid1,&tret)!=0){
        printf("Join thread 1 error!\n");
        exit(1);
    }

    printf("Thread 1 exit code: %d\n",(int *)tret);
    // 等待tid2结束，线程函数返回值放在tret中
    if (pthread_join(tid2,&tret)!=0){
        printf("Join thread 2 error!\n");
        exit(1);
    }

    printf("Thread 2 exit code: %d\n",(int *)tret);

    return 0;
}

void *thrd_func1(void *arg){
    printf("Thread 1 returning!\n");
//    sleep(3);
    return ((void *)1); // 自动退出线程
}

void *thrd_func2(void *arg){
    printf("Thread 2 exiting!\n");
    pthread_exit((void *)2);  // 线程主动退出，返回(void *)2
}
