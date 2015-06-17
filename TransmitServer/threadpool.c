#include "threadpool.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


ThreadPoolTask* TP_CreateThreadPoolTask()
{
    ThreadPoolTask *task;

    task = TP_MALLOC(ThreadPoolTask);
    if(0 != task){
        memset(task,0,sizeof(ThreadPoolTask));
        task->m_needFree = 0;
        task->m_run = 0;
        task->m_arge = 0;
        task->m_next = 0;
    }
    return task;
}

void TP_DeleteThreadPoolTask(ThreadPoolTask* task)
{
    if(0 == task) return;
    if(task->m_needFree)
    TP_FREE(task->m_arge);
    TP_FREE(task);
}

void TP_SetTaskArg(ThreadPoolTask* task, void* arge, int size)
{
    if(0==task) return;
    if(1==task->m_needFree){TP_FREE(task->m_arge);}

    if(0!=arge){
        if(size>0){
            task->m_arge = (void*)malloc(size);
            memcpy(task->m_arge,arge,size);
            task->m_needFree = 1;
        }else{
            task->m_arge = arge;
            task->m_needFree = 0;
        }
    }
}


/*pool*/
// �����̳߳�
ThreadPool* TP_CreateThreadPool(int maxThrNum)
{
    ThreadPool* pool;
    pool = TP_MALLOC(ThreadPool);
    if(0!=pool){
        memset(pool,0,sizeof(ThreadPool));
        pthread_mutex_init(&pool->m_taskLock, 0);
        pthread_cond_init (&pool->m_taskReady, 0);

        pool->m_waitForDestroy = 0;
        pool->m_taskHeader = 0;
        /*thr*/
        pool->m_maxThrNum = (maxThrNum>0)?maxThrNum:10;// ���10���߳�
        pool->m_thrGroup = (pthread_t*)malloc(sizeof(pthread_t)*pool->m_maxThrNum);// ����һ���̳߳أ����������m_maxThrNum���̣߳����ѵ�ǰ�߳�ָ��ָ����̳߳ؿռ䡣
        if(0==pool->m_thrGroup){
            TP_FREE(pool);
        }else{
            /*create thread*/
            int i;
            for(i=0;i<pool->m_maxThrNum;i++){
                pthread_create(pool->m_thrGroup+i,0,(TP_FUN)(TP_Process),(void*)pool);// ����m_maxThrNum���̡߳�
            }
        }
    }
    return pool;
}

void TP_DeleteThreadPool(ThreadPool *pool)
{
    int i;
    if(0==pool) return;
    /*把结束标志置1*/
    pool->m_waitForDestroy = 1;
    /*唤醒所有等待线程，线程池要销毁了*/
    pthread_cond_broadcast (&pool->m_taskReady);
    /*阻塞等待线程退出，为子线程收尸*/
    for(i=0;i<pool->m_maxThrNum;i++){
        pthread_join (pool->m_thrGroup[i], 0);
    }
    TP_FREE(pool->m_thrGroup);

    /*清除任务队列*/
    TP_CleanTask(pool);

    /*销毁条件变量和互斥量*/
    pthread_mutex_destroy(&pool->m_taskLock);
    pthread_cond_destroy(&pool->m_taskReady);
}

int TP_PushTask(ThreadPool*pool, ThreadPoolTask *task)
{
    if(0==task || 0==task->m_run) return -1;
    if(0==pool) return -1;

    /*加锁*/
    pthread_mutex_lock(&pool->m_taskLock);
    /*把任务添加到队尾*/

    ThreadPoolTask *p = pool->m_taskHeader;
    if(0==p){
        pool->m_taskHeader = task;
    }else{
        while(p->m_next){
            p = p->m_next;
        }
        p->m_next = task;
    }
    /*解锁*/
    pthread_mutex_unlock(&pool->m_taskLock);
    /*唤醒一个正在等待的线程,
    如果所有线程都在激活状态这句则没有作用*/
    pthread_cond_signal(&pool->m_taskReady);
    return 0;
}

int TP_PushTaskEx(ThreadPool* pool,TP_FUN fun,void* arge,int size)
{
    if(0==pool || 0==fun) return -1;
    ThreadPoolTask *task = TP_CreateThreadPoolTask();
    if(0==task) return -1;
    task->m_run = fun;
    TP_SetTaskArg(task,arge,size);
    return TP_PushTask(pool,task);
}

ThreadPoolTask* TP_PopTask(ThreadPool* pool)
{
    ThreadPoolTask *p;
    if(0== pool) return 0;
    /*加锁*/
    pthread_mutex_lock(&pool->m_taskLock);
    /*如果现在任务链表中没有任务并且没有打算销毁线程池则等待*/
    while(0==pool->m_taskHeader && 0==pool->m_waitForDestroy){
        //printf("wait----- 0x%x\n",(unsigned int) pthread_self());
        pthread_cond_wait(&pool->m_taskReady,&pool->m_taskLock);
    }
    /*取得队头任务*/
    p = pool->m_taskHeader;
    if(0!=p){
        pool->m_taskHeader = pool->m_taskHeader->m_next;
    }
    /*解锁*/
    pthread_mutex_unlock(&pool->m_taskLock);
    return p;
}

void TP_CleanTask(ThreadPool *pool)
{
    if(0==pool) return;
    /*清除任务链中所有的任务*/
    /*加锁*/
    pthread_mutex_lock(&pool->m_taskLock);
    ThreadPoolTask *p = pool->m_taskHeader;
    ThreadPoolTask *j;
    while(NULL!=p){
        j = p;
        p = p->m_next;
        TP_DeleteThreadPoolTask(j);
    }
    pool->m_taskHeader = 0;
    /*解锁*/
    pthread_mutex_unlock(&pool->m_taskLock);
}


void TP_Process(ThreadPool* pool)
{
    ThreadPoolTask *task;
    if(0==pool) return;

    while(0 == pool->m_waitForDestroy){
        task = TP_PopTask(pool);
        if(0==task || 0==task->m_run){
            if(1==pool->m_waitForDestroy) break;
        }else{
            /*如果正确地获取到了task则执行这个task*/
            TP_FUN fun = task->m_run;
            void *arg = task->m_arge;
            (*fun)(arg);
            /*执行完毕后销毁这个task*/
            TP_DeleteThreadPoolTask(task);
        }
    }
}


