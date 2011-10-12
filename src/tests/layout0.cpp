#include <gnupplus.hpp>
#include <cstdio>
#include <assert.h>
#include "test_environ.hh"

static const char* tale[] = {
    "set multiplot",
    "set size 0.500000,0.500000",
    "set origin 0.000000,0.000000",
    "set xlabel \"First x axis\"",
    "set ylabel \"First y axis\"",
    "set title \"First plot\"",
    "plot \"-\" title \"A plot\" with linespoints,"
        " \"-\" title \"Another plot\" with lines",
    "1.000000",
    "2.000000",
    "3.000000",
    "2.000000",
    "1.000000",
    "e",
    "1.000000 0.000000",
    "2.000000 1.000000",
    "3.000000 2.000000",
    "2.000000 3.000000",
    "1.000000 4.000000",
    "e",
    "set origin 0.500000,0.500000",
    "set xlabel \"Second x axis\"",
    "set ylabel \"Second y axis\"",
    "set title \"Second plot\"",
    "plot \"-\" title \"A plot\" with linespoints",
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
    InputLoop io("testecho", argv[0]);

    gnup::Layout layout (2, 2);

    /* VERY IMPORTANT NOTE! In order to ensure determinism, the object
     * must be deallocated before the check, since you may accidentally
     * check the file before it gets written!
     *
     * This operation must be achieved explicitly in the library test, but
     * it's not necessary while using the library.
     */
    gnup::GnuPlot *gp = new gnup::GnuPlot("testecho", io.params);
    gnup::Plot2D plot0 ("A plot", gnup::AUTO, gnup::DATA),
                 plot1 ("Another plot", gnup::DATA, gnup::AUTO);

    gp->setLayout(layout);

    gp->addPlot(plot0, 0, 0);
    gp->addPlot(plot1, 0, 0);
    layout.getCell(0, 0).setTitle("First plot");
    layout.getCell(0, 0).setXLabel("First x axis");
    layout.getCell(0, 0).setYLabel("First y axis");

    gp->addPlot(plot0, 1, 1);
    layout.getCell(1, 1).setTitle("Second plot");
    layout.getCell(1, 1).setXLabel("Second x axis");
    layout.getCell(1, 1).setYLabel("Second y axis");

    plot0.setStyle(gnup::Plot::LINESPOINTS);
    plot0.addVector(0, 1);
    plot0.addVector(0, 2);
    plot0.addVector(0, 3);
    plot0.addVector(0, 2);
    plot0.addVector(0, 1);
    plot1.addVector(1, 0);
    plot1.addVector(2, 0);
    plot1.addVector(3, 0);
    plot1.addVector(2, 0);
    plot1.addVector(1, 0);
    gp->trig();

    delete gp;

    assert(io == tale);

    return 0;
}
