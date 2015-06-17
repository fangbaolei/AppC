#include <stdio.h>
#include <string.h>
int main(void)
{
    char *SendMail = "kkk;gggg;mmmm";
    char Mail[40] = {0};
    char Cc[40] = {0};
    char *p;
    sprintf(Mail,"%s",SendMail);
    printf("Mail:%s\n",Mail);
    p = strtok(Mail, ";");
    while(p != NULL)
    {
		printf("%s\n", p);
        sprintf(Cc,"RCPT TO:<%s>\r\n", p);
        printf("%s\n", Cc);
        p = strtok(NULL, ";");
    }
    printf("Mail111:%s\n",Mail);
    return 0;
}
