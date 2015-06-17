#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define P_FIFO "/tmp/PipeDdns"

int PipeWrite(int *WriteBuf, int BufLen)
{
	int fd;
    int num = 0;
    fd= open(P_FIFO,O_WRONLY|O_NONBLOCK);  //非阻塞方式
    if( fd < 0)
    {
		printf("Open Pipe file fail!\n");
        close(fd);
		return -1;
	}
    num = write(fd, WriteBuf, BufLen);
	if(num < 0)
    {
		printf("Write Pipe file fail!\n");
        close(fd);
		return -1;
	}
    close(fd);
	return 0;
}
int main(int argc, char argv[])
{
  //   int WriteBuf[5] = {8, 2, 3, 4, 5};
       int data = 22;
//     PipeWrite(WriteBuf,sizeof(WriteBuf));
       PipeWrite(&data,sizeof(data));
}

