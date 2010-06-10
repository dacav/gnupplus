#include <gnup.hpp>

#include <unistd.h>
#include <cstdio>

int main ()
{
    try {
        gnup::GnuPlot gp;
        gp.command("a = %d\n", 4);
        gp.command("b = %d\n", 3);
        gp.command("print a + b\n");
    } catch (gnup::CommError &err) {
        perror(err.what());
        throw;
    }
}
