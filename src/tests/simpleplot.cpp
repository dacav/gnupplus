#include <gnupplus.hpp>
#include <cstdio>
#include <assert.h>

#include "test_environ.hh"

static const char* tale[] = {
    "set xlabel \"x axis label\"",
    "set ylabel \"y axis label\"",
    "plot \"-\" title \"A plot\" with linespoints",
    "1.000000",
    "2.000000",
    "3.000000",
    "2.000000",
    "1.000000",
    "e",
    "set xlabel \"x axis label\"",
    "set ylabel \"y axis label\"",
    "plot \"-\" title \"A plot\" with linespoints",
    "1.000000",
    "2.000000",
    "3.000000",
    "2.000000",
    "1.000000",
    "40.000000",
    "41.000000",
    "50.000000",
    "e",
    NULL
};

int main (int argc, char **argv)
{
    InputLoop io("testecho", argv[0]);

    /* VERY IMPORTANT NOTE! In order to ensure determinism, the object
     * must be deallocated before the check, since you may accidentally
     * check the file before it gets written!
     *
     * This operation must be achieved explicitly in the library test, but
     * it's not necessary while using the library.
     */
    gnup::GnuPlot *gp = new gnup::GnuPlot("testecho", io.params);
    gnup::Plot2D plot ("A plot", gnup::AUTO, gnup::DATA);

    gp->getLayout().getCell(0,0).setXLabel("x axis label");
    gp->getLayout().getCell(0,0).setYLabel("y axis label");
    gp->addPlot(plot);
    plot.setStyle(gnup::Plot::LINESPOINTS);
    plot.addVector(0, 1);
    plot.addVector(0, 2);
    plot.addVector(0, 3);
    plot.addVector(0, 2);
    plot.addVector(0, 1);
    gp->trig();

    plot.addVector(0, 40);
    plot.addVector(0, 41);
    plot.addVector(0, 50);
    gp->trig();

    delete gp;

	assert(io == tale);

    return 0;
}
