#include <stdio.h>
int main()
{
    int a = 10;
    FILE *fp;
    if((fp = fopen("1.txt", "w+r")) == NULL)
    {   
        printf("Open Error");
        return -1; 
    }   
    fscanf(fp,"%d", &a);
    fclose(fp);
    return 0;

}

