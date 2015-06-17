#include <sys/stat.h>
#include <stdio.h>

int main(void) 
{
    struct stat buf;
    stat("/etc/hosts", &buf);
    printf("/etc/hosts file size 是= %ld\n", buf.st_size);
    return 0;
}
