/****************
LE2: Introduction to Unnamed Pipes
****************/
#include <unistd.h> // pipe, fork, dup2, execvp, close
#include <iostream>
using namespace std;

int main () {
    // lists all the files in the root directory in the long format
    char* cmd1[] = {(char*) "ls", (char*) "-al", (char*) "/", nullptr};
    // translates all input from lowercase to uppercase
    char* cmd2[] = {(char*) "tr", (char*) "a-z", (char*) "A-Z", nullptr};

    // Create pipe
    int fds[2];
    if (pipe(fds) == -1) {
        cerr << "Pipe creation failed\n";
        return 1;
    }

    // Create child to run first command
    // In child, redirect output to write end of pipe
    // Close the read end of the pipe on the child side.
    // In child, execute the command
    pid_t pid1 = fork();
    if (pid1 == -1) {
        cerr << "Process creation for first child failed\n";
        return 1;
    }
    if (pid1 == 0) {
        // The body for child 1
        if (dup2(fds[1], STDOUT_FILENO) == -1) {
            cerr << "Failed to redirect the output of the first process into the write end of the pipe\n";
            _exit(1);
        }
        close(fds[0]);
        execvp(cmd1[0], cmd1);
        // If proc not replaced:
        cerr << "Failed to replace first child process with the required process\n";
        _exit(1);
    }

    // Create another child to run second command
    // In child, redirect input to the read end of the pipe
    // Close the write end of the pipe on the child side.
    // Execute the second command.
    pid_t pid2 = fork();
    if (pid2 == -1) {
        cerr << "Process creation for second child failed\n";
        return 1;
    }
    if (pid2 == 0) {
        if (dup2(fds[0], STDIN_FILENO) == -1) {
            cerr << "Failed to redirect the read end of the pipe into the input of the second process\n";
            _exit(1);
        }
        close(fds[1]);
        execvp(cmd2[0], cmd2);
        // if proc not replaced:
        cerr << "Failed to replace second child process with the required process\n";
        _exit(1);
    }

    // Reset the input and output file descriptors of the parent.
    wait(nullptr);
    close(fds[0]);
    close(fds[1]);
}
