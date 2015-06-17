#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "soapStub.h"
#include "ns.nsmap"

int main(void)
{
	const char *ServerIp = "172.18.191.108:1234";
	int num1 = 1, num2 = 2, result = 0;
    int sum1;
    int *sum = &sum1;
	struct soap add_soap;
	soap_init(&add_soap);
	soap_set_namespaces(&add_soap, namespaces);
	soap_call_ns__add(&add_soap, ServerIp, NULL, num1, num2, sum);    
	printf("ServerIp is %s, num1 is %d, num2 is %d\r\n", ServerIp, num1, num2);
	if(add_soap.error)
	{
		printf("soap error: %d, %s, %s\r\n", add_soap.error, *soap_faultcode(&add_soap), *soap_faultstring(&add_soap));
		result = add_soap.error;
	}
	if(result != 0)
	{
		printf("soap error, errcode=%d \r\n", result);
	}
	else
	{
		printf("%d + %d = %d\r\n", num1, num2, *sum);
	}

	soap_end(&add_soap);
	soap_done(&add_soap);
	return 0;
}
