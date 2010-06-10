#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <cstdio>

#include <gnup.hpp>

namespace gnup {

    CommError::CommError (const char *m) throw()
          : Error(m) { } 

    Comm::Comm (const char *prog) throw (CommError)
    {
        int pipefd[2];

        if (pipe(pipefd) == -1) {
            CommError err("Unable to pipe");
            throw err;
        }

        child = fork();
        if (child == -1) {
            CommError err("Unable to fork");
            throw err;
        }
        if (child == 0) {
            char * const args[] = {NULL};

            close(pipefd[1]);
            if (dup2(pipefd[0], 0) == -1) {
                CommError err("Unable to dup");
                throw err;
            }
            close(pipefd[0]);
            if (execvp(prog, args) == -1) {
                CommError err("Unable to exec");
                throw err;
            }
        }
        close(pipefd[0]);
        output = fdopen(pipefd[1], "a");
    }

    Comm::~Comm ()
    {
        fclose(output);
        wait(NULL);
    }

    void Comm::command (const char *fmt, ...)
    {
        va_list args;

        va_start(args, fmt);
        vfprintf(output, fmt, args);
        fflush(output);
        va_end(args);
    }

}

