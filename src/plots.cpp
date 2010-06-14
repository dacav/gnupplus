#include <gnup.hpp>

namespace gnup {

    Plot2D::Plot2D (const char *title, axis_t x, axis_t y)
          : Plot(title)
    {
        coords.x = x;
        coords.y = y;

        realsize = 0;
        if (x == DATA) realsize ++;
        if (y == DATA) realsize ++;
    }

    void Plot2D::writePlotting (Comm *c, DataSet::iterator b,
                              DataSet::iterator e)
    {
        // Alternative (incremental) value for the y axis (if not
        // specified).
        unsigned alt_y = 0;

        while (b != e) {
            const float *vals = *b;

            if (coords.x == AUTO) {
                c->command("%f\n", coords.y == DATA ? vals[1] : alt_y ++);
            } else {
                c->command("%f %f\n",
                           vals[0], coords.y == DATA ? vals[1] : alt_y ++);
            }

            b ++;
        }
    }

    size_t Plot2D::getDimension ()
    {
        return 2;
    }

    void Plot2D::addVector (float x, float y)
    {
        float v[] = {x, y};
        Plot::addVector(v);
    }

    void Plot2D::writeFormat (Comm *c)
    {
    }

    Plot3D::Plot3D (const char *title, axis_t x, axis_t y, axis_t z)
          : Plot(title)
    {
        coords.x = x;
        coords.y = y;
        coords.z = z;

        realsize = 0;
        if (x == DATA) realsize ++;
        if (y == DATA) realsize ++;
        if (z == DATA) realsize ++;
    }

    size_t Plot3D::getDimension ()
    {
        return 3;
    }

    void Plot3D::addVector (float x, float y, float z)
    {
        float v[] = {x, y, z};
        Plot::addVector(v);
    }

    void Plot3D::writePlotting (Comm *c, DataSet::iterator b,
                              DataSet::iterator e)
    {
        // Alternative (incremental) values for the x and y axis (if not
        // specified).
        unsigned alt_x = 0, alt_y = 0, alt_z = 0;

        while (b != e) {
            const float *vals = *b;

            c->command("%f %f %f\n",
                       coords.x == DATA ? vals[0] : alt_x ++,
                       coords.y == DATA ? vals[1] : alt_y ++,
                       coords.z == DATA ? vals[2] : alt_z ++);
            b ++;
        }
    }

    void Plot3D::writeFormat (Comm *c)
    {
    }

}

