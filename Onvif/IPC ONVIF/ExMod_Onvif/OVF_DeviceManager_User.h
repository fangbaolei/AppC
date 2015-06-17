//OVF_DeviceManager_User.h
/*################################################################################
#Project Description:
#      OVIF Э��SDK
#
# The File Description:
#      OVIF Э�� �豸����.�û�����
# Note:
#      1.OVIF ���ʻ������Ȩ�޽�������5��������һ��Զ���ʻ���
#
#
# Authors:
#       Fifo2005@gmail.com                                       2011.12.30 First
#       
#Copyright:
#       Copyright(c) 2008~2001x 
#  	    Fifo2005@gmail.com All rights reserved.
###############################################################################*/
#ifndef OVF_DEVICEMAGER_USER_H
#define OVF_DEVICEMAGER_USER_H
typedef enum 
{USER_LEVEL_ADMIN       = 0,
 USER_LEVEL_OPERATOR    = 1, 
 USER_LEVEL_USER        = 2,
 USER_LEVEL_ANONYMOUS   = 3,
 USER_LEVEL_EXTENDED    = 4,
}ENU_USERLEVEL;
typedef struct tagUSER
{
	CHAR          UserName[OVFCHARLENTH];	
	CHAR          UserPwd[OVFCHARLENTH];	
	ENU_USERLEVEL UserLevel;                //Ȩ�޼���
}USER,LPUSER;
typedef struct tagUSERS
{
    INT           UserSize;
    USER          Users[OVFMAXCHANNEL];
}USERS,*LPUSERS;
typedef struct tagREMOTUSER
{
	CHAR          UserName[OVFCHARLENTH];	
	CHAR          UserPwd[OVFCHARLENTH];	
	BOOL          UserUseDerivedPwd;
}REMOTEUSER,*LPREMOTEUSER;                  //Զ�̷����ʻ�
#endif//OVF_DEVICEMAGER_USER_H

