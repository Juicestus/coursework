#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int
main(int argc, char **argv)
{
    int pipe1[2];
    int pipe2[2];
    pipe(pipe1);
    pipe(pipe2);

    int pid = fork();

    if(pid == 0)
    {
        // child closes write end of pipe1, read end of pipe2
        close(pipe1[1]);
        close(pipe2[0]);

        // read from parent
        char buffer;
        read(pipe1[0], &buffer, 1);

        printf("%d: received ping\n", getpid());

        // write to parent
        char byte = 0x1;
        write(pipe2[1], &byte, 1);
        exit(0);
    }
    else
    {
        // parent closes read end of pipe1, write end of pipe2
        close(pipe1[0]);
        close(pipe2[1]);

        // write to child
        char byte = 0x1;
        write(pipe1[1], &byte, 1);

        // read from child
        char buffer;
        read(pipe2[0], &buffer, 1);
        printf("%d: received pong\n", getpid());
        exit(0);
    }

}