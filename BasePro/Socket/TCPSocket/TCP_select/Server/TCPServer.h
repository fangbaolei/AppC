#ifndef _TCP_SERVER_H
#define _TCP_SERVER_H
#ifdef __cplusplus
extern "C" {
#endif
/*
�궨�庯��:
1. ���������ͷ���ֵ����Ҫ����
2. ����������ָ�봫�����ƣ�������ֵ���ݡ�



*/
#define MAC_CLOSE_SOCK(sock) if(-1!=sock){shutdown(sock,2); close(sock); sock = -1;}


#ifdef __cplusplus
}
#endif
#endif
