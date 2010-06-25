#include <gnupplus.hpp>
#include <cstdio>
#include <assert.h>
#include "test_environ.h"

static const char* tale[] = {
    "splot \"-\" with linespoints",
    "0.000000 1.000000 1.000000",
    "e",
    "splot \"-\" with linespoints",
    "0.000000 1.000000 1.000000",
    "1.000000 2.000000 1.000000",
    "e",
    "splot \"-\" with linespoints",
    "0.000000 1.000000 1.000000",
    "1.000000 2.000000 1.000000",
    "2.000000 3.000000 1.000000",
    "e",
    "splot \"-\" with linespoints",
    "0.000000 1.000000 1.000000",
    "1.000000 2.000000 1.000000",
    "2.000000 3.000000 1.000000",
    "3.000000 2.000000 2.000000",
    "e",
    "splot \"-\" with linespoints",
    "0.000000 1.000000 1.000000",
    "1.000000 2.000000 1.000000",
    "2.000000 3.000000 1.000000",
    "3.000000 2.000000 2.000000",
    "4.000000 1.000000 2.000000",
    "e",
    "splot \"-\" with linespoints",
    "0.000000 1.000000 1.000000",
    "1.000000 2.000000 1.000000",
    "2.000000 3.000000 1.000000",
    "3.000000 2.000000 2.000000",
    "4.000000 1.000000 2.000000",
    "5.000000 3.000000 2.000000",
    "e",
    NULL
};

#include <unistd.h>

int main (int argc, char **argv)
{
    inloop_t io;

    build_environment();

    assert(inloop_create(&io, "testecho", argv[0]) == 0);

    /* VERY IMPORTANT NOTE! In order to ensure determinism, the object
     * must be deallocated before the check, since you may accidentally
     * check the file before it gets written!
     *
     * This operation must be achieved explicitly in the library test, but
     * it's not necessary while using the library.
     */
    gnup::GnuPlot *gp = new gnup::GnuPlot("testecho", io.params);
    gnup::Plot3D plot ("Test plot", gnup::AUTO, gnup::DATA, gnup::DATA);

    gp->addPlot(plot);
    plot.setStyle(gnup::Plot::LINESPOINTS);
    plot.setAutoUpdate(true);

    plot.addVector(0, 1, 1);
    plot.addVector(0, 2, 1);
    plot.addVector(0, 3, 1);
    plot.addVector(0, 2, 2);
    plot.addVector(0, 1, 2);
    plot.addVector(0, 3, 2);

    delete gp;

    assert(inloop_compare(&io, tale));
    inloop_destroy(&io);

    return 0;
}
