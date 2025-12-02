/*
* server.c -- a stream socket server demo
*/

#include "shared.h"


#define BACKLOG 10

void sigchld_hdlr(int s)
{
    (void)s;

    int _errno = errno;
    while (waitpid(-1, NULL, WNOHANG) > 0);
    errno = _errno;
}


int main(void)
{
    int sockfd, new_fd;
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr;
    socklen_t sin_size;
    struct sigaction sa;
    int yes = 1;
    char s[INET6_ADDRSTRLEN];
    int rv;
    pid_t pid;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    for (p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            perror("socket");
            continue;
        }
        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
            perror("setsocketopt");
            exit(1);
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("bind");
            continue;
        }   

        break;
    }
    
    freeaddrinfo(servinfo);
    
    if (p == NULL) {
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }        

    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    sa.sa_handler = sigchld_hdlr;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("server: waiting for connections...\n");

    while (1) {
        sin_size = sizeof(their_addr);

        if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1) {
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof (s));

        printf("server: rx'd connection from %s\n", s);

        if ((pid = fork()) > 0) {
            close(sockfd);
            if (send(new_fd, "Hello, world!", 13, 0) == -1) {
                perror("send");
            }
            close(new_fd);
            exit(0);
        } else if (pid == 0) {
            close(new_fd);
        } else {
            perror("fork");
        }
    }

    return 0;
}


