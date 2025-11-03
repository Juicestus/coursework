#include <iostream>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <vector>
#include <string>

// on mac:
#include <fcntl.h>

#include "Tokenizer.h"

// all the basic colours for a shell prompt
#define RED     "\033[1;31m"
#define GREEN	"\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE	"\033[1;34m"
#define WHITE	"\033[1;37m"
#define NC      "\033[0m"

using namespace std;

std::string shellPrompt() 
{
    time_t now = time(nullptr);
    struct tm* local = localtime(&now);
    char timebuf[64];
    strftime(timebuf, sizeof(timebuf), "%b %d %H:%M:%S", local);

    char hostname[256];
    gethostname(hostname, sizeof(hostname));

    char cwd[512];
    getcwd(cwd, sizeof(cwd));

    return std::string() + timebuf + " " + hostname + ":" + cwd + "$ ";
}

int main () {
    for (;;) {
        // need date/time, username, and absolute path to current dir
        cout << YELLOW << shellPrompt() << NC << " ";

        while (waitpid(-1, nullptr, WNOHANG) > 0);
        
        // get user inputted command
        string input;
        getline(cin, input);
        if (input.size() <= 0) continue;

        if (input == "exit") {  // print exit message and break out of infinite loop
            cout << RED << "Now exiting shell..." << endl << "Goodbye" << NC << endl;
            break;
        }

        // get tokenized commands from user input
        Tokenizer tknr(input);
        if (tknr.hasError()) {  // continue to next prompt if input had an error
            continue;
        }


        if (tknr.commands[0]->args[0] == "cd")
        {
            char* path;
            if (tknr.commands[0]->args.size() == 0)
                path = getenv("HOME");
            else
                path = (char*)tknr.commands[0]->args[1].c_str();

            if (chdir(path) < 0)
                perror("cd");

            continue;
        }

        
        // // print out every command token-by-token on individual lines
        // // prints to cerr to avoid influencing autograder
        // for (auto cmd : tknr.commands) {
        //     for (auto str : cmd->args) {
        //         cerr << "|" << str << "| ";
        //     }
        //     if (cmd->hasInput()) {
        //         cerr << "in< " << cmd->in_file << " ";
        //     }
        //     if (cmd->hasOutput()) {
        //         cerr << "out> " << cmd->out_file << " ";
        //     }
        //     cerr << endl;
        // }

        size_t i_last = tknr.commands.size() - 1;
        int pipe_fd[2], prev_fd = -1;

        for (size_t i = 0; i <= i_last; i++)
        {
            Command* cmd = tknr.commands[i];
            bool is_last = i == i_last;
            if (!is_last)
                pipe(pipe_fd);

            pid_t pid = fork();
            if (pid < 0) perror("fork");

            else if (pid == 0)                      // parent
            {
                if (cmd->hasInput())                // handle input file
                {
                    int in_fd = open(cmd->in_file.c_str(), O_RDONLY);
                    dup2(in_fd, STDIN_FILENO);
                    close(in_fd);
                }
                else if (prev_fd >= 0)               // handle process input redirection
                {
                    dup2(prev_fd, STDIN_FILENO);
                }

                if (cmd->hasOutput())               // handle output file
                {
                    int out_fd = open(cmd->out_file.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    dup2(out_fd, STDOUT_FILENO);
                    close(out_fd);
                } 
                else if (!is_last)                  // handle process output redirection
                {
                    dup2(pipe_fd[1], STDOUT_FILENO);
                }

                if (!is_last)       close(pipe_fd[0]);
                if (prev_fd >= 0)   close(prev_fd);
                std::vector<char*> argv{};
                argv.reserve(cmd->args.size() + 1);
                for (std::string& arg : cmd->args)
                    argv.push_back((char*)arg.c_str());
                argv.push_back(nullptr);
                execvp(argv[0], argv.data());
                perror("execvp");
                exit(1);
            }
            else                                    // child
            {   
                if (prev_fd >= 0)   close(prev_fd); 
                if (!is_last)
                {
                    close(pipe_fd[1]);
                    prev_fd = pipe_fd[0];
                }

                if (!cmd->isBackground())           // wait for blocking non-background procs
                    waitpid(pid, nullptr, 0);
            }
        }

        
    }
}
