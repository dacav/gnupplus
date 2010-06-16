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

