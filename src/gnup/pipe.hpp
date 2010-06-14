#ifndef __defined_gnup_pipe_hpp
#define __defined_gnup_pipe_hpp

#include <gnup/except.hpp>

#include <unistd.h>
#include <cstdio>
#include <exception>

namespace gnup {

    class CommError : public Error {
        public:
            CommError (const char *msg) throw() : Error(msg) {}
    };

    class Comm {

        public:
            virtual ~Comm ();
            void command (const char *fmt, ...);

        protected:
            Comm (const char *prog) throw (CommError);

        private:
            pid_t child;
            FILE *output;

    };

}

#endif // __defined_gnup_pipe_hpp

