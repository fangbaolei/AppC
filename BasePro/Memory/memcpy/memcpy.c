#include <stdio.h>
#include <string.h>
#include <memory.h>
int main(void)
{
	char str1[5] = "abcd";
    char str2[3] = "ef";  
    memcpy(str1, str2, strlen(str2));
    printf("str1 = %s\n", str1);
    return 0;
}
