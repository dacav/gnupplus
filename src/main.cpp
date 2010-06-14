#include <gnup.hpp>

#include <unistd.h>
#include <cstdio>
#include <cstdlib>

using namespace gnup;

int main (int argc, char **argv)
{
    try {
        GnuPlot gp(2);

        Plot2D p("foo", AUTO, DATA);
        p.setStyle(Plot::LINESPOINTS);

        gp.addSource(p);
        //p.setAutoUpdate(true);
        p.setOverflow(200);

        for (int i = 0; i < 1000; i ++) {
            p.addVector(0, ((float )rand()) / RAND_MAX);
            usleep(5e3);
        }
        printf("Ok, finished!\n");

        gp.trig();

        sleep(100);

    } catch (gnup::CommError &err) {
        perror(err.what());
        throw;
    } 
}
