#include <gnup.hpp>

#include <unistd.h>
#include <cstdio>
#include <cstdlib>

using namespace gnup;

class SrcTest : public Plot {

    public:
        SrcTest () : Plot( AXIS_X | AXIS_Y | AXIS_Z ) { }

        void giveFormat (Comm *c)
        {
            c->command("\"-\" title \"%s\" w l", "ciupa");
        }

        void givePlotting (Comm *c)
        {
            const float *vals;
            while ((vals = nextVector()) != NULL) {
                c->command("%f %f %f\n", vals[0], vals[1], vals[2]);
            }
        }

        void addVector (float *vals)
        {
            Plot::addVector(vals, 2);
        }

};

int main ()
{
    try {
        GnuPlot plot;
        SrcTest src;

        plot.addSource(src);

        for (int i = 0; i < 100; i ++) {
            float vals[3];

            vals[0] = ((float) rand()) / RAND_MAX;
            vals[1] = ((float) rand()) / RAND_MAX;
            vals[2] = ((float) rand()) / RAND_MAX;

            usleep(50e3);
            src.addVector(vals);
        }

    } catch (gnup::CommError &err) {
        perror(err.what());
        throw;
    }
}
