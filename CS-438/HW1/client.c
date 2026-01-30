#include "strings.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/rpc.h>
#include <rpc/pmap_clnt.h> 
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    CLIENT *clnt;
    stuff out;
    char *result = NULL;

    enum clnt_stat stat;
    struct timeval timeout;
    struct sockaddr_in bcast_addr;
    int sock, on = 1;
    uint16_t port;

    if (argc < 2) 
    {
        printf("usage: %s test_string\n", argv[0]);
        exit(1);
    }
    out.name = argv[1];
    out.val = 1234;

    
    struct sockaddr_in local_pmap;
    memset(&local_pmap, 0, sizeof(local_pmap));
    local_pmap.sin_family = AF_INET;
    local_pmap.sin_port = htons(PMAPPORT); 
    local_pmap.sin_addr.s_addr = htonl(INADDR_LOOPBACK); 

    if ((port = pmap_getport(&local_pmap, TEST_PROG, TEST_VERS, IPPROTO_UDP)) == 0)
    {
        printf("server not found\n");
        exit(1);
    }

    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)    /* manually create socket */
    {
        perror("socket");
        exit(1);
    }

    /* Configure broadcast + bcast addr */
    if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on)) < 0) 
    {
        perror("setsockopt");
        exit(1);
    }

    memset(&bcast_addr, 0, sizeof(bcast_addr));
    bcast_addr.sin_family = AF_INET;
    bcast_addr.sin_port = htons(port); 
    bcast_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST); 

    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    if ((clnt = clntudp_create(&bcast_addr, TEST_PROG, TEST_VERS, timeout, &sock)) == NULL)
    {
        clnt_pcreateerror("clntudp_create");
        exit(1);
    }

    if ((stat = clnt_call(clnt, TEST_FUNC, (xdrproc_t)xdr_stuff, (caddr_t)&out,
        (xdrproc_t)xdr_wrapstring, (caddr_t)&result, timeout)) != RPC_SUCCESS)
    {
        clnt_perror(clnt, "call");
        exit(1);
    }

    printf("function returned: \"%s\"\n", result);
    
    clnt_destroy(clnt);
    close(sock);
    return 0;
}