#ifndef _TCP_SERVER_H
#define _TCP_SERVER_H
#ifdef __cplusplus
extern "C" {
#endif
/*
宏定义函数:
1. 函数参数和返回值不需要类型
2. 函数参数与指针传递类似，而不是值传递。



*/
#define MAC_CLOSE_SOCK(sock) if(-1!=sock){shutdown(sock,2); close(sock); sock = -1;}


#ifdef __cplusplus
}
#endif
#endif
