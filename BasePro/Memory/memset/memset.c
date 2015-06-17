#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
typedef struct Stu{
	char name[10];
	int  age;
}Student;
int main(void)
{
	Student stu1;
    char stu2[] = "aaa";
	memcpy(&stu1.name, stu2,sizeof(stu2));
	printf("##%s\n", stu1.name);
	return 0;
}
