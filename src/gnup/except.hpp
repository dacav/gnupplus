#ifndef __defined_gnup_except_hpp
#define __defined_gnup_except_hpp

#include <exception>

namespace gnup {

    /** General exception for the gnup library */
    class Error : public std::exception {
        public:

            /** Constructor with message
             *
             * @param msg The error message.
             */
            Error (const char *msg) throw ();

            /** Copy constructor
             *
             * @param copy The copy.
             */
            Error (Error &copy) throw ();

            /** Destructor
             *
             * It's already virtual, since the class inherits from
             * std::exception.
             */
            ~Error () throw ();

            /** Cause of the exception
             *
             * @return A string describing the error.
             */
            const char *what () const throw ();

        private:

            /** The string returned by the gnup::Error::what method. */
            const char *msg;
    };

}

#endif // __defined_gnup_except_hpp

