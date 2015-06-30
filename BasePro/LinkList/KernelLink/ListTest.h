#ifndef __LIST_TEST__H__
#define __LIST_TEST__H__
#ifdef __cplusplus
extern "C" {
#endif 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylist.h"

typedef struct ChnInfo{
    char *name;    
    struct kernel_list_head list;
}ChnInfo;

#ifdef __cplusplus
}
#endif
#endif

