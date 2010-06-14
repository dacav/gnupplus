#include <gnup.hpp>

#include <unistd.h>
#include <cstdio>
#include <cstdlib>

using namespace gnup;

int main (int argc, char **argv)
{
    try {
        GnuPlot gplot(2, argc > 1 ? argv[1] : "gnuplot");
        Plot2D p("foo", DATA, DATA);
        p.setStyle(Plot::LINESPOINTS);

        gplot.addSource(p);

        for (int i = 0; i < 100; i ++) {
            p.addVector(100 * i, ((float )rand()) / RAND_MAX);
            usleep(250e3);
        }
        printf("Ok, finished!\n");

    } catch (gnup::CommError &err) {
        perror(err.what());
        throw;
    }
}
