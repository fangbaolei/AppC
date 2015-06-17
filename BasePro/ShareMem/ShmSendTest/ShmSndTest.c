#include <stdio.h>
#include <unistd.h>
#include "share_mem.h"
#include "msg_util.h"
#define SYS_MSG_KEY     0x1234
#define SYS_MEM_KEY     0x1111

int main()
{
    int i = 0;
    int MsgId = 0;
    int MemId = 0;
    char buf[3] = {1, 2, 3};
    MSG_BUF msg;
    memset(&msg, 0, sizeof(MSG_BUF));
    msg.Src = MSG_TYPE_MSG1;
    msg.Des = MSG_TYPE_MSG2;
    msg.cmd = sizeof(buf);
    
    MsgId = Msg_Init(SYS_MSG_KEY);
    MemId = ShareMemInit(SYS_MEM_KEY);
    while(1)
    {
        ShareMemWrite(0, buf, sizeof(buf));
        Msg_Send(MsgId, (void *)&msg, sizeof(MSG_BUF));
        buf[2] = i++;
        printf("buf[2]:%d\n",buf[2]);
        sleep(1);
    }

    return 0;
}
