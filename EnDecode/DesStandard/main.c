#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LongseDes.h"

int main()
{

    char des_key[8] = "12345678";
    char inData[] = "hello123 i fuck you heheheheh";
    char enData[1024] = {0};
    char outData[1024] = {0};

    /*第一个参数大小必须大于len 并且是8的整数倍*/
    DES_Encode(enData,inData,des_key,strlen(inData));
    DES_Decode(outData,enData,des_key,strlen(inData));

    printf("%s\n",outData);

    return 0;
}
