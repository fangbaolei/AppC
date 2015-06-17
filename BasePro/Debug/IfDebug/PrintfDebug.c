//============================================================================
// Name : debug.cpp
// Author : boyce
// Version : 1.0
// Copyright : pku
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <stdio.h>
#include <assert.h>

#define __DEBUG__ 1 

#if __DEBUG__
#define IPCAM_TRACE\
    do{\
        printf("[ %s, %s, %d ]=> ",__FILE__, __FUNCTION__,  __LINE__);\
        printf("\r\n");\
    }while(0)
#define IPCAM_DEBUG(msg...)\
    do{\
        printf("[ %s, %s, %d ]=> ",__FILE__, __FUNCTION__,  __LINE__);\
        printf(msg);\
        printf("\r\n");\
    }while(0)
#define IPCAM_ERROR(msg...)\
    do{\
        fprintf(stderr, "[ %s, %s, %d ]=> ",__FILE__,__FUNCTION__,  __LINE__);\
        printf(msg);\
        printf("\r\n");\
    }while(0)
#define IPCAM_ASSERT(exp...) assert(exp)   
#else
#define IPCAM_TRACE
#define IPCAM_DEBUG(msg...)  (void)(msg)
#define IPCAM_ERROR(msg...)  (void)(msg)
#define IPCAM_ASSERT(exp...) (void)(exp)
#endif

int main(int argc, char **argv) 
{
    // char str[]="Hello World";
    IPCAM_TRACE;
    IPCAM_DEBUG("aaa");
    IPCAM_ERROR("bbbb");
    // IPCAM_ASSERT("");
    return 0;
}
