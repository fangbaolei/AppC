#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <pthread.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define TP_FREE(P) if(0!=P){free(P); P=0;}
#define TP_MALLOC(T) ((T *)malloc(sizeof( T )));

typedef void* (*TP_FUN)(void*);

typedef struct ThreadPoolTask{
    int m_needFree;

    TP_FUN m_run;
    void *m_arge;
    struct ThreadPoolTask *m_next;
}ThreadPoolTask;

/*task*/
ThreadPoolTask* TP_CreateThreadPoolTask();
void TP_DeleteThreadPoolTask(ThreadPoolTask*);
void TP_SetTaskArg(ThreadPoolTask*, void*, int);

/*pool*/
typedef struct ThreadPool{
    pthread_mutex_t m_taskLock;
    pthread_cond_t m_taskReady;
    pthread_t *m_thrGroup;

    int m_maxThrNum;
    int m_waitForDestroy;

    ThreadPoolTask * m_taskHeader;
}ThreadPool;

ThreadPool* TP_CreateThreadPool(int);
void TP_DeleteThreadPool(ThreadPool*);


int TP_PushTask(ThreadPool*, ThreadPoolTask*);
int TP_PushTaskEx(ThreadPool*,TP_FUN,void*,int);
ThreadPoolTask* TP_PopTask(ThreadPool*);
void TP_CleanTask(ThreadPool*);

void TP_Process(ThreadPool*);

#ifdef __cplusplus
}
#endif
#endif
