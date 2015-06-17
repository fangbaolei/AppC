#include <stdio.h>
#include <memory.h>
typedef struct Stu{
	char *name;
	int age;
}Student;
int main(void)
{
	Student stu1,*stu2;
	stu1.name = "abc";
	stu1.age = 3;
	stu2 = &stu1;
	printf("name1:%s,age1:%d\n", stu1.name, stu1.age);
	memset(&stu1,0,sizeof(stu1));
	stu2->name = "kkkk";
	stu2->age = 22;
	printf("name2:%s,age2:%d\n", stu2->name, stu2->age);
    return 0;
}
