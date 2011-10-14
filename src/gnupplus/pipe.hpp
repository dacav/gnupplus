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

#ifndef __defined_gnup_pipe_hpp
#define __defined_gnup_pipe_hpp

#include <unistd.h>
#include <cstdio>
#include <stdexcept>
#include <string>

namespace gnup {

    class CommError : public std::runtime_error {
        public:
            CommError (const std::string &m) :
                std::runtime_error(m) {}
    };

    class Comm {
        public:
            virtual ~Comm ();
            void command (const char *fmt, ...);

        protected:
            Comm (const char * prog, const char * args[], bool req_X);

        private:
            pid_t child;
            FILE *output;

            void checkX();
    };

}

#endif // __defined_gnup_pipe_hpp

