#include "test_environ.hh"

#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>

void InputLoop::build_env ()
{
    std::string path = getenv("PATH");
    path += ":.";
    setenv("PATH", path.c_str(), 1);
}

InputLoop::InputLoop (const char * echo_name,
                      const char * self_name)
    :   fname(self_name)
{
    /* Including current directory in the search path */
    build_env();

    fname += "__";
    params[0] = echo_name;
    params[1] = fname.c_str();
    params[2] = NULL;
}

bool InputLoop::operator== (const char * lines[])
{
    std::fstream f(fname.c_str(), std::fstream::in);
    std::string row;

    while (!f.eof() && *lines != NULL) {

        std::getline(f, row);

        if (row.length() == 0) {
            std::cout << "Skipping empty row";
            continue;   // skip empty row.
        }

        if (row != *lines) {
            return false;
        }
        lines ++;
    }

    bool emptylines = true;

    while (!f.eof()) {
        std::getline(f, row);
        emptylines = row.length() == 0;
    }
    return emptylines && *lines == NULL;
}

