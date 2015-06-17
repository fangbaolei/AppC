#include "threadpool.h"
#include "fwserver.h"
#include "linklist.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include "time.h"


void processSignal(int signal)
{
    signal++;
    printf("###############################################################\n");
    printf("###################     signal SIGPIPE     ####################\n");
    printf("###############################################################\n");
}


int main(void)
{
    int port;
    int sn;

    FWServer *fwServer = FW_CreateNew();
    TP_PushTaskEx(fwServer->pool,(TP_FUN)FW_StartListen,(void*)fwServer,0);
    TP_PushTaskEx(fwServer->pool,(TP_FUN)FW_Start,(void*)fwServer,0);
    signal(SIGPIPE, processSignal);
#if 0
    port = 10000;
    sn = 123456;

    while(1){
        char c = getchar();

        if('s'==c){
            FW_AddSessionToListen(fwServer,port,sn);
            port ++;
            sn ++;
        }else if('w'==c){
            FW_AddSession(fwServer,1);
        }
        if('q'==c) break;

        sleep(10);
    }
#endif
    return 0;
}

