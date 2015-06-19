#include  <unistd.h>
#include  <sys/types.h>       /* basic system data types */
#include  <sys/socket.h>      /* basic socket definitions */
#include  <netinet/in.h>      /* sockaddr_in{} and other Internet defns */
#include  <arpa/inet.h>       /* inet(3) functions */
#include <sys/epoll.h> /* epoll function */
#include <fcntl.h>     /* nonblocking */
#include <sys/resource.h> /*setrlimit */

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#define MAX_EPOLL_NUM 10000 // ��Ҫ�����ĸ���
#define MAX_LISTEM_NUM 1024 // �������еĸ���
#define MAX_LINE 10240
#define SERVER_PORT 1234 

#define TURE 1
#define FALSE 0

/************************
 * ������
 **************************/
int handle(int ConnectFd)
{
    int nread;
    char buf[MAX_LINE];
    nread = read(ConnectFd, buf, MAX_LINE);//��ȡ�ͻ���socket��
    if (nread == 0) 
    {
        printf("client close the connection\n");
        close(ConnectFd);
        return -1;
    } 
    if (nread < 0) 
    {
        perror("read error");
        close(ConnectFd);
        return -1;
    }    
    write(ConnectFd, buf, nread);//��Ӧ�ͻ���  
    return 0;
}

/********************
 *�������ܣ�����ÿ����������򿪵�����ļ���
 **********************/
 int SetLimitFile(void)
 {
    struct rlimit rt;
    rt.rlim_max = rt.rlim_cur = MAX_EPOLL_NUM;
    if (setrlimit(RLIMIT_NOFILE, &rt) == -1) 
    {
        perror("setrlimit error");
        return -1;
    }
    return 0;
 }

/****************************
 *�������ܣ�ע���µ�fd��EpollFd
 *******************************/
int Epoll_Ctrl(int EpollFd, int ListenFd)
{
    struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLET;// ���ļ����������óɿɶ�(EPOLLIN)�ͱ�Ե����(EPOLLET)��ģʽ
    ev.data.fd = ListenFd;
    if (epoll_ctl(EpollFd, EPOLL_CTL_ADD, ListenFd, &ev) < 0)// ע���µ�fd��EpollFd�� 
    {
        fprintf(stderr, "epoll set insertion error: ListenFd=%d\n", ListenFd);
        return -1;
    }
    return 0;
}

/*******************************
 *����socket
 ****************************/ 
int Socket_Create(struct sockaddr_in *servaddr)
{
    int fd;
    memset(servaddr, 0, sizeof(struct sockaddr_in));
    servaddr->sin_family = AF_INET; 
    servaddr->sin_addr.s_addr = htonl (INADDR_ANY);
    servaddr->sin_port = htons (SERVER_PORT);
    fd = socket(AF_INET, SOCK_STREAM, 0); 
    return fd;
}

/*********************************
 * �������ܣ�����TCP���������������
********************************/
int TCP_Create(int *ListenFd)
{
   int fd = -1; 
   int opt = TURE;
   struct sockaddr_in servaddr;

   fd = Socket_Create(&servaddr);
   if (fd == -1) 
   {
       perror("can't create socket file");
       return -1;
   }

   // SO_REUSEADDR:���óɶ˿ڸ��ã��������Ӷ���ͻ���
   setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

   // O_NONBLOCK:���óɷ�����ģʽ
   if(fcntl(fd, F_SETFL, fcntl(fd, F_GETFD, 0)|O_NONBLOCK) == -1) 
   {
       perror("setnonblock error");
       return -1;
   }

   //�׽�����ָ���˿�����
   if(bind(fd, (struct sockaddr *) &servaddr, sizeof(struct sockaddr)) == -1) 
   {
       perror("bind error");
       return -1;
   } 

   // ��������
   if(listen(fd, MAX_LISTEM_NUM) == -1) 
   {
       perror("listen error");
       return -1;
   }
   *ListenFd = fd;
   return 0;
}

/******************************
 * �������ܣ�����epoll
 *********************************/
int Epoll_Cteate(int *EpollFd, int ListenFd)
{
    int fd;
    fd = epoll_create(MAX_EPOLL_NUM);
    if(fd < 0)
    {
        printf("epoll_create fail!\n");    
        return -1;
    }
    if(Epoll_Ctrl(fd, ListenFd) < 0)
    {
        printf("Epoll_Ctrl fail!\n");    
        return -1;
    }
    *EpollFd = fd;
    return 0;
}

/********************************
 *�������ܣ��ȴ����մ���������Ϣ
 ********************************/
int Epoll_Wait(int EpollFd, int ListenFd)
{
    int nfds, n;
    int ConnectFd = -1;
    int curfds = 1;
    int acceptCount = 0;
    struct sockaddr_in cliaddr;
    socklen_t socklen = sizeof(struct sockaddr_in);
    struct epoll_event events[MAX_EPOLL_NUM];
    char buf[MAX_LINE];
    struct epoll_event ev;

    while(1)
    {
        nfds = epoll_wait(EpollFd, events, curfds, -1);
        if (nfds == -1)
        {
            perror("epoll_wait");
            continue;
        }

        /* ���������¼� */
        for (n = 0; n < nfds; ++n)
        {
            if (events[n].data.fd == ListenFd) 
            {
                ConnectFd = accept(ListenFd, (struct sockaddr *)&cliaddr,&socklen);
                if (ConnectFd < 0) 
                {
                    perror("accept error");
                    continue;
                }

                sprintf(buf, "accept form %s:%d\n", inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port);
                printf("AcceptCount:%d:%s", ++acceptCount, buf);

                if (curfds >= MAX_EPOLL_NUM) 
                {
                    fprintf(stderr, "too many connection, more than %d\n", MAX_EPOLL_NUM);
                    close(ConnectFd);
                    continue;
                } 

                if (fcntl(ConnectFd, F_SETFL, fcntl(ConnectFd, F_GETFD, 0)|O_NONBLOCK) == -1) 
                {
                    perror("setnonblock error");
                }

                if(Epoll_Ctrl(EpollFd, ConnectFd) < 0)
                {
                    printf("Epoll_Ctrl fail!\n");    
                    return -1;
                }
                curfds++;
                continue;
            } 

            /*
             ����ͻ�������
             ����ʧ��ʱ����ʾ�ͻ��������Ѿ��Ͽ�����ɾ��fd
             * */
            if (handle(events[n].data.fd) < 0)
            {
                epoll_ctl(EpollFd, EPOLL_CTL_DEL, events[n].data.fd,&ev);
                curfds--;
            }
        }
    }
    return 0;
}

int main(int argc, char **argv)
{
    int ListenFd, EpollFd;
    int res;

    res = SetLimitFile();
    if(res < 0)
    {
        printf("SetLimitFile fail!\n");    
        return -1;
    }

    res = TCP_Create(&ListenFd);
    if(res < 0)
    {
        printf("TCP_Create Error!\n");    
        close(ListenFd);
        return -1;
    }

    res = Epoll_Cteate(&EpollFd, ListenFd);
    if(res < 0)
    {
       printf("Epoll_Cteate Error!\n"); 
       close(EpollFd);
       close(ListenFd);
       return -1;
    }
    printf("epollserver startup,port %d, max connection is %d\n", SERVER_PORT, MAX_EPOLL_NUM);
    Epoll_Wait(EpollFd, ListenFd);
    close(EpollFd);
    close(ListenFd);
    return 0;
}
