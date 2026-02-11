#include "strings.h"
#include <stdio.h>
#include <stdlib.h>

static int
callback(char** result, struct sockaddr_in* addr)
{
	printf("function returned: \"%s\"\n", *result);
	return 1;
}

int
main(int argc, char** argv)
{
	
	enum clnt_stat stat;
	stuff out;
	char* result = 0;

	if (argc < 2)
	{
		printf("usage: %s test_string\n", argv[0]);
		exit(1);
	}

	out.name = argv[1];
	out.val = 1234;

	if ((stat = clnt_broadcast(TEST_PROG, TEST_VERS, TEST_FUNC, (xdrproc_t)xdr_stuff, (caddr_t)&out, 
			(xdrproc_t)xdr_wrapstring, (caddr_t)&result, (resultproc_t)callback)) != RPC_SUCCESS)
	{
		clnt_perrno(stat);
		exit(1);
	}

	return 0;
}
