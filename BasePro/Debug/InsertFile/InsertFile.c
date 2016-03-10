#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <stdio.h>

#define MAX_OUTPUT_COUNT (32)
unsigned int g_u32OutputStart = 0;
char g_szOutput[MAX_OUTPUT_COUNT][512];

#define BLUE "\033[0;32;34m"
#define LIGHT_RED "\033[1;31m"
#define NONE "\033[m"


#define GETPID() \
({ \
    long int __ret = syscall(224); \
    if(__ret == -1) \
    { \
        __ret = (long int)getpid(); \
    } \
    __ret; \
})


#define MA_ASSERT_FILE_TXT "assert.txt"
#define MA_ASSERT_FILE_FTP "assert.ftp"
#define MA_ASSERT(express, fmt, ...) \
do \
{ \
    if(!(express)) \
    { \
        int errnocpy = errno;\
        time_t timet = time(NULL);\
        struct tm* ptimetm = localtime(&timet);\
        errno=errnocpy;\
        long int threadid = GETPID(); \
        snprintf(g_szOutput[g_u32OutputStart], sizeof(g_szOutput[0]), BLUE"%04d-%02d-%02d %02d:%02d:%02d %04ld ASSERT %s:%s:%d "NONE""fmt"\n",\
                ptimetm->tm_year+1900, ptimetm->tm_mon+1, ptimetm->tm_mday, ptimetm->tm_hour, ptimetm->tm_min, ptimetm->tm_sec, \
                threadid, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
        g_szOutput[g_u32OutputStart][sizeof(g_szOutput[0]) - 2] = '\n'; \
        g_szOutput[g_u32OutputStart][sizeof(g_szOutput[0]) - 1] = 0; \
        printf("%s", g_szOutput[g_u32OutputStart]); \
        g_u32OutputStart ++; \
        g_u32OutputStart %= MAX_OUTPUT_COUNT; \
        unsigned int i; \
        FILE* pTxtFp = fopen(MA_ASSERT_FILE_TXT, "w+"); \
        FILE* pFtpFp = fopen(MA_ASSERT_FILE_FTP, "w+"); \
        if(pTxtFp != NULL && pFtpFp != NULL) \
        { \
            for(i = g_u32OutputStart; i < MAX_OUTPUT_COUNT; i++) \
            { \
                fwrite(g_szOutput[i], 1, strlen(g_szOutput[i]), pTxtFp); \
                fwrite(g_szOutput[i], 1, strlen(g_szOutput[i]), pFtpFp); \
            } \
            for(i = 0; i < g_u32OutputStart; i++) \
            { \
                fwrite(g_szOutput[i], 1, strlen(g_szOutput[i]), pTxtFp); \
                fwrite(g_szOutput[i], 1, strlen(g_szOutput[i]), pFtpFp); \
            } \
            fclose(pTxtFp); \
            fclose(pFtpFp); \
        } \
    } \
}while(0)

int  test_assert()
{
    int a = 1;
    MA_ASSERT(a == 0, "bbbbb");
    MA_ASSERT(a == 0, "cccc");
    return 0;
}

int main()
{
    test_assert();
    return 0;
}
