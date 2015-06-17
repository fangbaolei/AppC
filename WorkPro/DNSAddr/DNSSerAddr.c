#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#define BUF_LEN 1024
// 查找字符串s1最后一次出现在s2的位置
char *LastPos(char* s1, char* s2) 
{
     int i;
     int s1_len = strlen(s1);
     int end = strlen(s2) - s1_len;
     char *last_index = NULL;
     for (i = 0; i <= end; i++)
     {
         if (!strncmp(s1, s2 + i, s1_len))
         {
             last_index = s2 + i;
         }
     }
     return last_index;
}
// 获取DNS服务器的IP地址
int GetDNSAddr(char *Dns1, char *Dns2)
{
    FILE *fp = NULL;
    char ReadBuf[BUF_LEN] = {0};
    int len = 0;
    char *DNSName = "nameserver ";
    char *Lastp = NULL;
    char i = 0;

    fp = fopen("resolv.conf", "r");
    if(fp == NULL)
    {
        printf("open resolv.conf error\r\n");
        return -1;
    }
    while(fgets(ReadBuf, BUF_LEN, fp) != NULL)
    {
         len = strlen(ReadBuf);
         ReadBuf[len -1] = '\0';
         if(!strncmp(ReadBuf, DNSName, sizeof(DNSName)))// nameserver一行中，头尾均不能出现空格, 且nameserver必须全为小写 
         {
              i++;
              Lastp = LastPos(" ", ReadBuf);// 定位到了域名服务器地址的前一个空格 
              if(i == 1)
              {
                  sprintf(Dns1, "%s", Lastp+1);
              }
              else if(i == 2)
              {
                  sprintf(Dns2, "%s", Lastp+1);
              }
         }
    }
    if(i == 0)// 配置文件中没有nameserver
    {
        printf("No nameserver!\n");
    }
    fclose(fp);
}
// 设置DNS的配置文件
#if 1
int SetDNSAddr(char *Dns1, char *Dns2)
{
    FILE *fp = NULL;
    char ReadBuf[256] = {0};
    int len = 0;
    char *StrBuf = 0;
    char *Lastp = NULL;
    char i = 0;

    fp = fopen("resolv1.conf", "r+w");
    if(fp == NULL)
    {
        printf("open resolv1.conf error\r\n");
        return -1;
    }
    if(Dns1 != NULL)
    {
        sprintf(ReadBuf, "nameserver %s\n", Dns1);
        fputs(ReadBuf, fp);
    }
    if(Dns2 != NULL)
    {
         sprintf(ReadBuf, "nameserver %s\n", Dns2);
         fputs(ReadBuf, fp);
    }
    fclose(fp);

}
#endif
int main(void)
{
   char Dns1[32] = {0}, Dns2[32] = {0};
   GetDNSAddr(Dns1, Dns2);
   SetDNSAddr(Dns1, Dns2);
   printf("***dfsdfDNS1***:%s\n", Dns1);
   printf("***DNS2***:%s\n", Dns2);
   return 0;
}
