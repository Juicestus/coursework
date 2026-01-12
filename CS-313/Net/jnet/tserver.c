#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>

int strtol2(long *num, char *str)
{
    char *end;
    *num = strtol(str, &end, 10);
    if (end == str) return 1;
    if (*end != '\0') return 2;
    if (errno == ERANGE) return 3;
    return 0;
}

int main(int argc, char** argv)
{
    if (argc != 2) 
    {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        return -1;
    }

    // IPv4 TCP Stream
    int host_fd = socket(AF_INET, SOCK_STREAM, 0);

    // Convert port str to int
    unsigned short port;
    if (strtol2((long *)&port, argv[1]))
    {
        fprintf(stderr, "invalid port number %s\n", argv[1]);
        return -2;
    }
    port &= 0xFFFF;

    // Setup socket addr
    struct sockaddr_in addr = {0};
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket to port and listen
    bind(host_fd, (struct sockaddr *)&addr, sizeof(addr));
    listen(host_fd, 16);

    printf("Listening on port %d...\n", port);

    int remote_fd = accept(host_fd, NULL, NULL);

    close(remote_fd);
    close(host_fd);
    return 0;
}