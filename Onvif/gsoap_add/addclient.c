#include "soapStub.h"
#include "ns.nsmap"

int add(const char *server, int num1, int num2, int *sum)
{
	struct soap add_soap;
	int result = 0;
	soap_init(&add_soap);
	soap_set_namespaces(&add_soap, namespaces);
	soap_call_ns__add(&add_soap, server, NULL, num1, num2, sum);
	printf("server is %s, num1 is %d, num2 is %d\r\n", server, num1, num2);

	if(add_soap.error)
	{
		printf("soap error: %d, %s, %s\r\n", add_soap.error, *soap_faultcode(&add_soap), *soap_faultstring(&add_soap));
		result = add_soap.error;
	}

	soap_end(&add_soap);
	soap_done(&add_soap);

	return result;
}

