#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#define BUF_LEN 1024
// 查找字符串s1最后一次出现在s2的位置
char *LastPos(char* s1, char* s2) 
{
     int i, s1_len = strlen(s1), end = strlen(s2) - s1_len;
     char* last_index = NULL;
     for (i = 0; i <= end; i++)
     {
         if (!strncmp(s1, s2 + i, s1_len))
         {
             last_index = s2 + i;
         }
     }
     return last_index;
 }
int main(void)
{
    FILE *fp;   
    char ReadBuf[BUF_LEN]; 
    int len;
    char *DNSName = "nameserver";
    char *p, *Lastp;
    fp = fopen("resolv.conf", "r+");
    if(fp == NULL)
    {
	printf("open resolv.conf error\r\n");
	return -1;
    }
    printf("File Open OK!\n");
    while(fgets(ReadBuf, BUF_LEN, fp) != NULL)
    {
           len = strlen(ReadBuf);
           ReadBuf[len -1] = '\0';
           if(!strncmp(ReadBuf, DNSName, 10))
           {
              //printf("======%s\n", p);
              printf("%s\n",ReadBuf);
              Lastp = LastPos(" ", ReadBuf);
              printf("*********%s\n", Lastp + 1);
              
           }
    }
    return 0;
}
