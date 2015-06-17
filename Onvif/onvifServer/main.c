/*
 * main.c
 *
 *  Created on: Apr 13, 2014
 *      Author: root
 */
//#include "soapStub.h"

#include "wsdd.nsmap"
#include "soapH.h"
#include <pthread.h>
#include "pubFun.h"

#if 0
int bind_server_udp(int server_s)
{
	struct sockaddr_in local_addr;
	memset(&local_addr,0,sizeof(local_addr));
	local_addr.sin_family = AF_INET;
	local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	local_addr.sin_port = htons(3702);
	return bind(server_s, (struct sockaddr*)&local_addr,sizeof(local_addr));
}

static int create_server_socket_udp(void)
{
	int server_udp;
//	unsigned char one = 1;
	int sock_opt = 1;
	//server_udp = socket(PF_INET,SOCK_DGRAM,0);
	server_udp = socket(PF_INET,SOCK_DGRAM, IPPROTO_UDP);
	if ( server_udp == -1)
	{
		printf("unable to create socket\n");
	}
	if ( (setsockopt(server_udp,SOL_SOCKET,SO_REUSEADDR,(void*)&sock_opt,sizeof(sock_opt))) == -1)
	{
		printf("setsockopt\n");
	}
	struct ip_mreq mreq;
	mreq.imr_multiaddr.s_addr = inet_addr("239.255.255.250");
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);

	if(setsockopt(server_udp,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq)) == -1)
	{
		perror("memberchip error\n");
	}
	return server_udp;
}

#else

int bind_server_udp(int server_s)
{
	struct sockaddr_in local_addr;
	memset(&local_addr,0,sizeof(local_addr));
	local_addr.sin_family = AF_INET;
	//local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	local_addr.sin_addr.s_addr = inet_addr(IP_SEARCH);
	local_addr.sin_port = htons(PORT_PROBE);
	return bind(server_s,(struct sockaddr*)&local_addr,sizeof(local_addr));

}
static int create_server_socket_udp(void)
{
    int server_udp;
	unsigned char one = 1;
	int sock_opt = 1;

//	server_udp = socket(PF_INET, SOCK_DGRAM, 0);
    server_udp = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (server_udp == -1) {
        printf("unable to create socket\n");
    }

    /* reuse socket addr */
    if ((setsockopt(server_udp, SOL_SOCKET, SO_REUSEADDR, (void *) &sock_opt,sizeof (sock_opt))) == -1)
    {
        printf("setsockopt\n");
    }
    if ((setsockopt(server_udp, IPPROTO_IP, IP_MULTICAST_LOOP,&one, sizeof (unsigned char))) == -1)
    {
        printf("setsockopt\n");
    }

	struct ip_mreq mreq;
	mreq.imr_multiaddr.s_addr = inet_addr(IP_SEARCH);
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);

	if(setsockopt(server_udp,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq))==-1)
	{
		perror("memberchip error\n");
	}

    return server_udp;
}
#endif


#if 0

int main( int argc, char* argv[])
{
	int server_udp;
	int retval = 0;
	struct soap *soap_udp;
	int fault_flag =0;
	server_udp = create_server_socket_udp();
	bind_server_udp(server_udp);
	while(1)
	{
		soap_udp = soap_new();
		soap_init1(soap_udp, SOAP_IO_UDP);
		soap_udp->master = server_udp;
		soap_udp->socket = server_udp;
		soap_udp->errmode = 0;
		soap_udp->bind_flags = 1;

		if( !soap_valid_socket(soap_bind(soap_udp, NULL,3702,100)))
		{
			soap_print_fault(soap_udp,stderr);
		}
		printf("soap_server starting..\n");
//		fprintf(stderr,"soap_server starting..\n");
		retval = soap_serve(soap_udp);
		printf("retval = %d\n",retval);
//		fprintf(stderr,"retval = %d\n",retval);
		if ( retval && !(fault_flag))
		{
			fault_flag = 1;
		}
		else if(!retval)
		{
			fault_flag = 0;
		}
		soap_destroy(soap_udp);
		soap_end(soap_udp);
		soap_done(soap_udp);
		free(soap_udp);
	}

	return 0;
}

#else

void T_Probe(void* argv)
{
	printf("T_Probe2 start\n");
	struct soap soap_udp;
	soap_init1(&soap_udp, SOAP_IO_UDP);
	if( !soap_valid_socket(soap_bind(&soap_udp,NULL,3702,100)))
	{
		soap_print_fault(&soap_udp,stderr);
	}
	struct ip_mreq mcast;
	mcast.imr_multiaddr.s_addr = inet_addr(IP_SEARCH);
	mcast.imr_interface.s_addr = htonl(INADDR_ANY);
	if (setsockopt(soap_udp.master, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mcast, sizeof(mcast))<0)
	{
		TRACE("setsockopt,err\n");
	}
	while(1)
	{

		TRACE("soap_serve start\n");
		soap_serve(&soap_udp);
		TRACE("soap_serve end\n");

	}
	soap_destroy(&soap_udp);
	soap_end(&soap_udp);
	soap_done(&soap_udp);
	printf("T_Probe2 end\n");
}

int main(int argc, char *argv[])
{
	int m,s;
	struct soap add_soap;
	pthread_t thrProbe;
	
	pthread_create(&thrProbe,NULL,(void*)T_Probe,NULL);

	soap_init(&add_soap);
	soap_set_namespaces(&add_soap,namespaces);
	m = soap_bind(&add_soap,NULL,PORT_SERVER,100);
	if( m < 0)
	{
		soap_print_fault(&add_soap,stderr);
		exit(-1);
	}
	TRACE("Socket connection successful:master socket = %d\n",m);
	while(1)
	{
		s = soap_accept(&add_soap);
		if( s < 0)
		{
			soap_print_fault(&add_soap,stderr);
			exit(-1);
		}
		TRACE("Socket connection successful:slave socket = %d\n",s);
		soap_serve(&add_soap);
		//soap_end(&add_soap);
	}
	soap_destroy(&add_soap);
	soap_end(&add_soap);
	soap_done(&add_soap);
	return 0;
}
#endif
