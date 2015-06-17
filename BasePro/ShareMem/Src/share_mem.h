#ifndef __SHARE_MEM_H__
#define __SHARE_MEM_H__
#ifdef __cplusplus
extern "C" {
#endif 

#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define PROC_MEM_SIZE 4096*3 // 一块共享内存大小
#define MAX_SHARE_PROC  12   // 共享内存的个数

#define PROC_MEM_KEY  0x01   // 共享内存的键值

int ShareMemInit(int key);
int pShareMemInit(int key);
void ShareMemRead(int offset,void *buf, int length);
void ShareMemWrite(int offset,void *buf, int length);
#ifdef __cplusplus
}
#endif
#endif
