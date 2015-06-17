/* 
 * File:   main.c
 * Author: tianshuai
 *
 * Created on 2011年11月29日, 下午10:34
 */
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int port=1900;

int main(int argc, char** argv) 
{

    int sin_len;
    char message[256];
    char AckBuf[] = "Recv OK!\n";
    int socket_descriptor;
    struct sockaddr_in sin, DstAddr;
    printf("Waiting for data form sender \n");

    bzero(&sin,sizeof(sin));
    sin.sin_family=AF_INET;
    sin.sin_addr.s_addr=htonl(INADDR_ANY);
    sin.sin_port=htons(port);
    sin_len=sizeof(sin);
    // add by he
    bzero(&DstAddr, sizeof(DstAddr));
    DstAddr.sin_family = AF_INET;
    DstAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    DstAddr.sin_port = htons(9988);

    socket_descriptor=socket(AF_INET,SOCK_DGRAM,0);
    bind(socket_descriptor,(struct sockaddr *)&sin,sizeof(sin));

    while(1)
    {
        recvfrom(socket_descriptor,message,sizeof(message),0,(struct sockaddr *)&sin, (socklen_t*)&sin_len);
        printf("Response from server:%s\n",message);
        // add by he
        sendto(socket_descriptor, AckBuf, sizeof(AckBuf), 0, (struct sockaddr *)&DstAddr, sizeof(DstAddr));
        if(strncmp(message,"stop",4) == 0)//接受到的消息为 “stop”
        {

            printf("Sender has told me to end the connection\n");
            break;
        }
    }

    shutdown(socket_descriptor, 0);
    exit(0);

    return (EXIT_SUCCESS);
}
