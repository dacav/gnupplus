#include <gnupplus.hpp>
#include <cstdio>
#include <assert.h>
#include "test_environ.h"

static const char* tale[] = {
    "set multiplot",
    "set size 0.500000,0.500000",
    "set origin 0.000000,0.000000",
	"plot \"-\" with linespoints",
    "1.000000",
    "2.000000",
    "3.000000",
    "2.000000",
    "1.000000",
    "e",
    "set origin 0.500000,0.500000",
	"plot \"-\" with linespoints",
    "1.000000",
    "2.000000",
    "3.000000",
    "2.000000",
    "1.000000",
    "e",
    "set size 1,1",
    "unset multiplot",
    NULL
};

int main (int argc, char **argv)
{
    inloop_t io;

    build_environment();
    assert(inloop_create(&io, "testecho", argv[0]) == 0);

    gnup::Layout layout (2, 2);

    /* VERY IMPORTANT NOTE! In order to ensure determinism, the object
     * must be deallocated before the check, since you may accidentally
     * check the file before it gets written!
     *
     * This operation must be achieved explicitly in the library test, but
     * it's not necessary while using the library.
     */
    gnup::GnuPlot *gp = new gnup::GnuPlot("testecho", io.params);
    gnup::Plot2D plot ("Test plot", gnup::AUTO, gnup::DATA);

    gp->setLayout(layout);
    gp->addPlot(plot, 0, 0);
    gp->addPlot(plot, 1, 1);

    plot.setStyle(gnup::Plot::LINESPOINTS);
    plot.addVector(0, 1);
    plot.addVector(0, 2);
    plot.addVector(0, 3);
    plot.addVector(0, 2);
    plot.addVector(0, 1);
    gp->trig();

    delete gp;

    assert(inloop_compare(&io, tale));
    inloop_destroy(&io);

    return 0;
}
