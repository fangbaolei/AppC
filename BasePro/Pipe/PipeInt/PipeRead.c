#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define P_FIFO         "/tmp/PipeDdns"
typedef struct Data{
	int num;
}Data;
int PipeRead(int *ReadBuf, int BufLen)
{
	int fd;
	if(access(P_FIFO,F_OK)==0)
	{                                        //管道文件存在
	     execlp("rm","-f", P_FIFO, NULL);   //删掉
	     printf("access.\n");
	}
	if(mkfifo(P_FIFO, 0777) < 0)
	{
	      printf("createnamed pipe failed.\n");
	}
	fd= open(P_FIFO,O_RDONLY|O_NONBLOCK);     // 非阻塞方式打开，只读
	if(fd < 0)
	{
	      printf("Open pipe file fail!\n");
	      close(fd);
	      return -1;
	}
	while(1)
    {
    memset(ReadBuf,0, BufLen);
    if((read(fd, ReadBuf, BufLen)) < 0 )
    {                                  //     没有读到数据
        printf("Read pipe file fail!\n");
    }
    else 
    {
    	printf("data:%d\n", *ReadBuf);
    }
     sleep(1);
    }
	close(fd);
	return 0;

}
int main(int argc, char** argv)
{
     int DdnsReflashTime = 0;
     int fd;
  memset(&DdnsReflashTime, 0, sizeof(DdnsReflashTime));
#if 1
		if((read(fd, &DdnsReflashTime, sizeof(DdnsReflashTime))) < 0 )
		{                                  //     没有读到数据
			Printf("Read pipe file fail!\n");
		}
		else
		{
			Printf("#######DdnsReflashTime:%d\n",DdnsReflashTime);
		}   
//     PipeRead(&ReadBuf,sizeof(ReadBuf));
#endif
     return 0;
}

