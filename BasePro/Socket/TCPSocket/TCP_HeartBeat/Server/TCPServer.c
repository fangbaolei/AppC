#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>
#include <unistd.h>

#define BUFSIZE 1000
#define SERVER_PORT 1234

int main (int argc, char *argv[])
{
    int s = 0;
    int fd = 0;
    int len = 0;
    struct sockaddr_in my_addr;
    struct sockaddr_in remote_addr;
    socklen_t sin_size = 0;
    char buf[BUFSIZE] = {0};

    sin_size = sizeof (struct sockaddr_in);
    bzero(&my_addr, sizeof (my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = INADDR_ANY;
    my_addr.sin_port = htons (SERVER_PORT);

    if ((s = socket (PF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror ("socket");
        close (s);
        return -1;
    }

    if (bind (s, (struct sockaddr *) &my_addr, sizeof (struct sockaddr)) < 0)
    {
        perror ("bind");
        close (s);
        return -1;
    }

    listen (s, 5);

    while (1)
    {

        if ((fd = accept (s, (struct sockaddr *) &remote_addr, &sin_size)) < 0)
        {
            perror ("accept");
            close (fd);
            continue;
            //close (s);
        }
        printf ("accept client %s\n", inet_ntoa (remote_addr.sin_addr));
        len = send (fd, "Welcome to my server!", 21, 0);
        if(len < 0)
        {
            close (fd);
            continue;
        }
        len = recv (fd, buf, BUFSIZE, 0);
        if(len > 0)
        {
            buf[len] = '\0';
            printf ("Server recieve:%s\n", buf);
            if (send (fd, buf, len, 0) < 0)
            {
                perror ("write");
                close (fd);
                continue;
            }

        }
        close(fd);
    }
    close (fd);
    close (s);
    return 0;
}
