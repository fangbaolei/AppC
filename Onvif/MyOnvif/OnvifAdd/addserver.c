#include "soapH.h"
#include "soapStub.h"
#include "ns.nsmap"

int main(void)
{
	struct soap add_soap;
	char Port[5] = "1234";
	int result;
	soap_init(&add_soap);
	soap_set_namespaces(&add_soap, namespaces);
    result = soap_bind(&add_soap, NULL, atoi(Port), 100);// 绑定端口
	if(result < 0)
	{
		fprintf(stderr, "Socket connection successful: master socket = %d\r\n", result);
		exit(1);
	}
	while(1)
	{
		result = soap_accept(&add_soap);//等待
		if(result < 0)
		{
			fprintf(stderr, "Socket connection successful: master socket = %d\r\n", result); 
            exit(1);
		}
		fprintf(stderr, "Socket connection successful: slave socket = %d\r\n", result);
		soap_serve(&add_soap);// 处理
		soap_end(&add_soap);// 结束
	}
	return 0;
}
int ns__add(struct soap *add_soap, int num1, int num2, int *sum)
{
	*sum = num1 + num2;
	return 0;
}
