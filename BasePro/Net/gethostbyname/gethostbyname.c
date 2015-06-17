#include <netdb.h>
#include <string.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
    struct hostent *ht = NULL;
    char host[20] = "www.google.com";
    int i = 0;
    ht = gethostbyname(host);
    if (ht)
    {
        printf("Host:%s \n", host);  /* 原始域名 */
        /* 打印IP地址 */
        printf("IP Address:\n");
        for (i = 0;; i++)
        {
            if (ht->h_addr_list[i] != NULL)
            {                   /* 不是IP地址数组的结尾 */
                printf("IP:%s\n", (char *)inet_ntoa((unsigned int *)ht->h_addr_list[i]));   /*打印IP地址 */
            }
            else
            {                   /*达到结尾 */
                break;          /*退出for循环 */
            }
        }
        /* 打印域名地址 */
        printf("Domain Name:\n");
        for (i = 0;; i++)
        {                       /*循环 */
            if (ht->h_aliases[i] != NULL)
            {                   /* 没有到达域名数组的结尾 */
                printf("alias %d:%s\n", i, ht->h_aliases[i]);   /* 打印域名 */
            }
            else
            {                   /*结尾 */
                printf("\n");
                break;          /*退出循环 */
            }
        }
    }
    return 0;
}

