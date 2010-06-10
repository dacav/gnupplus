#ifndef __defined_gnup_except_hpp
#define __defined_gnup_except_hpp

#include <exception>

namespace gnup {

    class Error : public std::exception {
        public:
            Error (const char *msg) throw ();
            Error (Error &copy) throw ();
            ~Error () throw ();
            const char *what () const throw ();
        private:
            const char *msg;
    };

}

#endif // __defined_gnup_except_hpp

