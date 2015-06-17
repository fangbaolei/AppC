#include <stdio.h>
#include <string.h>
int main(void)
{
	char sql_cmd[512];
	sprintf(sql_cmd,"%s",
		"CREATE TABLE [devChannelInfo](\
		[enable]INT(1) NOT NULL,\
		[channelName] CHAR(32)  NOT NULL,\
		[channelNo] INT(1) NOT NULL,\
		[streamNo] INT(1) NOT NULL,\
		[addr] CHAR(32)  NOT NULL,\
		[port] INT(1) NOT NULL,\
		[userName] CHAR(32)  NOT NULL,\
		[userPwd] CHAR(32)  NOT NULL,\
		[protocol] INT(1) NOT NULL,\
		[manProtocolType] INT(1) NOT NULL);"
		);
	printf("sssslen:%d\n\n",strlen(sql_cmd));
	return 0;
}
