#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <stdio.h>

#define LIGHT_RED "\033[1;31m"
#define NONE "\033[m"

#define MAX_OUTPUT_COUNT (32)
unsigned int g_u32OutputStart = 0;
char g_szOutput[MAX_OUTPUT_COUNT][512];

#define GETPID() \
({ \
    long int __ret = syscall(224); \
    if(__ret == -1) \
    { \
        __ret = (long int)getpid(); \
    } \
    __ret; \
})

#define MA_TRACE_FAILED(fmt, ...) \
do \
{ \
    int errnocpy = errno;\
    time_t timet = time(NULL);\
    struct tm* ptimetm = localtime(&timet);\
    errno=errnocpy;\
    long int threadid = GETPID(); \
    snprintf(g_szOutput[g_u32OutputStart], sizeof(g_szOutput[0]), LIGHT_RED"%04d-%02d-%02d %02d:%02d:%02d %04ld FAILED %s:%s:%d "NONE""fmt"\n",\
            ptimetm->tm_year+1900, ptimetm->tm_mon+1, ptimetm->tm_mday, ptimetm->tm_hour, ptimetm->tm_min, ptimetm->tm_sec, \
            threadid, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
    g_szOutput[g_u32OutputStart][sizeof(g_szOutput[0]) - 2] = '\n'; \
    g_szOutput[g_u32OutputStart][sizeof(g_szOutput[0]) - 1] = 0; \
    printf("%s", g_szOutput[g_u32OutputStart]); \
    g_u32OutputStart ++; \
    g_u32OutputStart %= MAX_OUTPUT_COUNT; \
}while(0)

#define MA_RETURN(express, ret, fmt, ...) \
do \
{\
    if(!(express)) \
    { \
        MA_TRACE_FAILED(fmt, ##__VA_ARGS__); \
        return (ret); \
    } \
}while(0)

int test_return()
{
    int k = 1;
    MA_RETURN(k == 0, 0, "FALT!");
    return 0;
}

int main()
{
   test_return();
   return 0;
}
