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
            DataSet::iterator b, e;

            getIters(b, e);
            while (b != e) {
                const float *vals = *b;

                c->command("%f %f %f\n", vals[0], vals[1], vals[2]);
                b ++;
            }
        }

        void addVector (float *vals)
        {
            Plot::addVector(vals, 3);
        }

};

int main ()
{
    try {
        GnuPlot plot;
        SrcTest src0;
        SrcTest src1;

        plot.addSource(src0);
        plot.addSource(src1);

        for (int i = 0; i < 100; i ++) {
            float vals[3];

            vals[1] = -0.5;
            vals[0] = (float) i;
            vals[2] = ((float) rand()) / RAND_MAX;
        
            printf("PUSHING: %f %f %f\n", vals[0], vals[1], vals[2]);

            usleep(50e3);
            src0.addVector(vals);

            vals[1] = 0.5;
            vals[0] = (float) i;
            vals[2] = ((float) rand()) / RAND_MAX;

            usleep(50e3);
            src1.addVector(vals);
        }

    } catch (gnup::CommError &err) {
        perror(err.what());
        throw;
    }
}
