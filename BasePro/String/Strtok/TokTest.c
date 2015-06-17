#include <string.h>
#include <stdio.h>
int main(void)
{
   char input[10] = "abc,d,dd";
   char *p;
   p = strtok(input, ",");
   if (p)   printf("%s\n", p);
   p = strtok(NULL, ",");
   if (p)   printf("%s\n", p);
   return 0;
}

