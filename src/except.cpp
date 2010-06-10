#include <gnup.hpp>

#include <cstring>
#include <cstdlib>

namespace gnup { 

    Error::Error (const char *m) throw ()
         : std::exception()
    {
        msg = strdup(m);
    }

    Error::~Error () throw ()
    {
        free((void *) msg);
    }

    Error::Error (Error &copy) throw ()
    {
        if (&copy != this) {
            msg = strdup(copy.msg);
        }
    }

    const char * Error::what () const throw ()
    {
        return msg;
    }
 
}
