#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#include "msg_util.h"
int MsgInit(MSG_BUF *msg, int Val, int MsgKey, int MsgType)
{
    int MsgId = 0;
    memset(msg, 0, sizeof(MSG_BUF));
    msg->Src = MSG_TYPE_MSG1;
    msg->Des = MsgType;
    msg->cmd = Val;
    MsgId = Msg_Init(MsgKey);
    return MsgId;
}
int main(void)
{
    MSG_BUF msg,msg1;
    int MsgId,MsgId1;
    MsgId = MsgInit(&msg, 8, SYS_MSG_KEY, MSG_TYPE_MSG2);
    MsgId1 = MsgInit(&msg1, 55, SYS_MSG_KEY1, MSG_TYPE_MSG3);
    while(1)
    {
        Msg_Send(MsgId, (void *)&msg, sizeof(MSG_BUF));
        printf("send:%d\n",msg.cmd);
        Msg_Send(MsgId1, (void *)&msg1, sizeof(MSG_BUF));
        printf("send1:%d\n",msg1.cmd);
        sleep(1);
    }
    return 0;
}
