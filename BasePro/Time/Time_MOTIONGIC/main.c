/*CLOCK_MONOTONIC: 开机到当前时间。注意，是开机，而不是程序运行。
 *CLOCK_REALTIME:1970.1.1到当前到时间。
 *
 * */
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
int Time_Motionic(clockid_t _tclock_id)
{ 
    struct timespec stTime;
    clock_gettime(_tclock_id, &stTime);
    struct timeval stRet;
    stRet.tv_sec = stTime.tv_sec;
    stRet.tv_usec = stTime.tv_nsec/1000; 
    printf("sec:%d\nusec:%d\n",stRet.tv_sec, stRet.tv_usec); 
}
int main()
{
    Time_Motionic(CLOCK_MONOTONIC);
    Time_Motionic(CLOCK_REALTIME);
    return 0;    
}
