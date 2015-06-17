#include <stdio.h>
#include <unistd.h>
#include "share_mem.h"
#include "msg_util.h"

#define SYS_MSG_KEY     0x1234
#define SYS_MEM_KEY     0x1111

int main()
{
    int len = 0;
    int MsgId = 0;
    int MemId = 0;
    int MsgType= MSG_TYPE_MSG2;
    char buf[10] = {0};
    MSG_BUF msg;
    memset(&msg, 0, sizeof(MSG_BUF));
    MsgId = Msg_Init(SYS_MSG_KEY);
    MemId = ShareMemInit(SYS_MEM_KEY);
    while(1)
    {
        Msg_Rsv(MsgId, MsgType, (void *)&msg, sizeof(MSG_BUF));
        len = msg.cmd;
        ShareMemRead(0, buf, len);
        printf("buf[0]:%d,buf[1]:%d,buf[2]:%d\n", buf[0], buf[1], buf[2]);
    }

    return 0;
}
