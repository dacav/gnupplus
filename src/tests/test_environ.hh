#ifndef __defined_test_environ_hh
#define __defined_test_environ_hh

#include <string>

/**
 * An InputLoop object correspond to a certain file which contains the
 * lines that gnupplus should produce within a certain test.
 */
class InputLoop
{
    public:
        /** Initializer for a inloop.
         *
         * @param echo_name The name of the echoing application, used to
         *                  build the command line;
         * @param my_name The name of the calling program, which will be
         *                used as template for the output file name.
         */

        InputLoop (const char * echo_name, const char * self_name);

        /** Compare the inloop produced file.
         *
         *
         * Empty lines and lines starting with '#' in the file will be
         * ignored. Therefore try to avoid putting that into the "lines"
         * array!
         *
         * The lines vector elements are supposed to be terminated by '\0'
         * and not to contain '\n'.
         *
         * @param lines A NULL-terminated array of strings to be compared.
         * @return true if the comparsion succeded, false otherwise.
         */
        bool operator== (const char *lines[]);

        const char * params[3];

    private:
        std::string fname;

        void build_env ();

};

#endif // __defined_test_environ_hh

