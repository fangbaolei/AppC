#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#include "msg_util.h"

int main()
{
    MSG_BUF msg,msg1;
    int MsgId, MsgId1;
    int MsgType = MSG_TYPE_MSG2;
    int MsgType1 = MSG_TYPE_MSG3;
    MsgId = Msg_Init(SYS_MSG_KEY);
    MsgId1 = Msg_Init(SYS_MSG_KEY1);
    while(1)
    {
        memset(&msg, 0, sizeof(MSG_BUF));
        Msg_Rsv(MsgId, MsgType, (void *)&msg, sizeof(MSG_BUF));
        printf("RecBuf:%d\n",msg.cmd); 
        memset(&msg1, 0, sizeof(MSG_BUF));
        Msg_Rsv(MsgId1, MsgType1, (void *)&msg1, sizeof(MSG_BUF));
        printf("RecBuf1:%d\n",msg1.cmd); 
    }
    return 0;
}
