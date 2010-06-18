#include <gnupplus.hpp>
#include <cstdio>

#include "test_environ.h"

int main ()
{
    const char *args[] = { "eat", "flaming", NULL };

    build_environment();
    gnup::GnuPlot gp (2, "testecho", (char ** const)args);
    gp.command("Fuck!\n");
}
