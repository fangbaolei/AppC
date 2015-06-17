#include "soapH.h"
#include "soapStub.h"
#include "ns.nsmap"

int main(int argc, char **argv)
{
	int m, s;
	struct soap add_soap;//gSOAP运行环境实例
	soap_init(&add_soap);//当客户端程序访问远程方法前或当服务端程序能够接收一个请求前，必须先将这个环境变量初始化
	soap_set_namespaces(&add_soap, namespaces);

	if (argc < 2)
	{
		printf("usage: %s <server_port> /n", argv[0]);
		exit(1);
	}
	else
	{
		m = soap_bind(&add_soap, NULL, atoi(argv[1]), 100);// 绑定端口
		if (m < 0)
		{
			soap_print_fault(&add_soap, stderr);
			exit(-1);
		}
		fprintf(stderr, "Socket connection successful: master socket = %d\r\n", m);
		for (;;)
		{
			s = soap_accept(&add_soap);//等待
			if (s < 0)
			{
				soap_print_fault(&add_soap, stderr);
				exit(-1);
			}
			fprintf(stderr, "Socket connection successful: slave socket = %d\r\n", s);
			soap_serve(&add_soap);// 处理
			soap_end(&add_soap);// 结束
		}
	}
	return 0;
}

int ns__add(struct soap *add_soap, int num1, int num2, int *sum)
{
	*sum = num1 + num2;
	return 0;
}

