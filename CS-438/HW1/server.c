#include "strings.h"
#include <stdio.h>

char **
test_func_1_svc(stuff *argp, struct svc_req *rqstp)
{
	static char *result = "this goes back";
	
	printf("incoming string: \"%s\"\n", argp->name);
	printf("incoming value: %d\n", argp->val);
	printf("returning string: %s\n", result);
	
	return(&result);
}
