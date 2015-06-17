//============================================================================
// Name : debug.cpp
// Author : boyce
// Version : 1.0
// Copyright : pku
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <stdio.h>
#define Printf(fmt...)\
        do{\
            printf("File:%s - Func:%s() - Line:%d - Info:", __FILE__,__FUNCTION__, __LINE__);\
            printf("\033[0;31m");\
            printf(fmt);\
            printf("\033[0;39m");\
            fflush(stdout);\
        }while(0)

int main(int argc, char **argv) 
{
    char str[]="Hello World";
    Printf("%s\n",str);
    printf("aaaa\n");
    return 0;
}
