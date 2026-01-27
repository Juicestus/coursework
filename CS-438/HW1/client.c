#include "strings.h"
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char** argv)
{
	CLIENT *clnt;
	char *host;
	stuff  out;  /* outgoing parameters */
	char **result; /* return value */

	if(argc < 3) {
		printf("usage: %s server_host test_string\n", argv[0]);
		exit(1);
	}
	host = argv[1];

	clnt = clnt_create(host, TEST_PROG, TEST_VERS, "tcp");
	if (clnt == NULL) {
		clnt_pcreateerror(host);
		exit(1);
	}

	out.name = argv[2];
	out.val = 1234;

	result = test_func_1(&out, clnt);	/* call the remote function */

	/* test if the RPC succeeded */
	if (result == NULL) {
		clnt_perror(clnt, "call failed:");
		exit(1);
	}

	printf("function returned: \"%s\"\n", *result);
	clnt_destroy( clnt );
}
