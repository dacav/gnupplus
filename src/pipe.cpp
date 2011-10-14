/*
 * Copyright 2010 Giovanni Simoni
 *
 * This file is part of libgnupplus.
 *
 * libgnupplus is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libgnupplus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libgnupplus.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <cstdio>

#include <gnupplus/pipe.hpp>

namespace gnup {

    Comm::Comm (const char * prog, const char * args[], bool req_X)
    {
        int pipefd[2];

        if (req_X) {
            checkX();
        }

        if (pipe(pipefd) == -1) {
            throw CommError("Unable to pipe");
        }

        child = fork();
        if (child == -1) {
            throw CommError("Unable to fork");
        }
        if (child == 0) {
            char * const defargs[] = { (char * const)prog, NULL };

            close(pipefd[1]);
            if (dup2(pipefd[0], 0) == -1) {
                throw CommError("Unable to dup");
            }
            close(pipefd[0]);
            if (execvp(prog, args ? (char ** const)args : defargs) == -1) {
                throw CommError("Unable to exec");
            }
        }
        close(pipefd[0]);
        output = fdopen(pipefd[1], "a");
    }

    void Comm::checkX ()
    {
        if (getenv("DISPLAY") == NULL) {
            throw CommError("Cannot find DISPLAY variable");
        }
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

