#include <stdio.h>
int main()
{
	char *str1 = "aaaa\n";
    char *str2 = "bbbb\n";
    FILE *fp;
    if((fp = fopen("1.txt", "w+r")) == NULL)
    {
        printf("Open Error");
        return -1;
    }
    fputs(str1, fp);
    fputs(str2, fp);
    fclose(fp);
    return 0;

}
