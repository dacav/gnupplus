/*
 * Copyright 2010 Giovanni Simoni
 *
 * This file is part of libgnupplus.
 *
 * libgnupplus is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libgnupplus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libgnupplus.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <gnupplus/plots.hpp>
#include <gnupplus/gnuplot.hpp>
#include <cstring>

#include <cstdio>

namespace gnup {

    Plot::Plot (const char *tit)
    {
        title = tit;
        style = LINES;
        max_size = 0;
        setAutoUpdate(false);
        setTrigger(NULL);
    }

    Plot::~Plot ()
    {
        DataSet::iterator i, end;

        end = data.end();
        for (i = data.begin(); i != end; i ++) {
            delete[] *i;
        }
    }

    void Plot::addVector (double *vals)
    {
        size_t n = getDimension();
        double *v = new double[n];

        memcpy((void *)v, (void *)vals, n * sizeof(double));

        data.push_back(v);
        if (max_size && data.size() > max_size) {
            delete[] data.front();
            data.pop_front();
        }
        if (auto_update && trigger) {
            trigger->trig();
        }
    }

    void Plot::init (Comm *c)
    {
        const char *sn;

        switch (style) {
            case POINTS:
                sn = "points";
                break;
            case LINESPOINTS:
                sn = "linespoints";
                break;
            case IMPULSES:
                sn = "impulses";
                break;
            case DOTS:
                sn = "dots";
                break;
            case STEPS:
                sn = "steps";
                break;
            case ERRORBARS:
                sn = "errorbars";
                break;
            case BOXES:
                sn = "boxes";
                break;
            case BOXERRORBARS:
                sn = "boxerrorbars";
                break;
            case LINES:
            default:
                sn = "lines";
                break;
        }
        c->command("\"-\" with %s\n", sn);
    }

    void Plot::reset (Comm *c)
    {
        c->command("e\n");
    }

    void Plot::setTrigger (Trigger *t)
    {
        trigger = t;
    }

    void Plot::display (Comm *c)
    {
        display(c, data.begin(), data.end());
    }

    void Plot::setStyle (style_t s)
    {
        style = s;
    }

    void Plot::setAutoUpdate (bool au)
    {
        auto_update = au;
    }

    void Plot::setOverflow (size_t max)
    {
        max_size = max;
    }

    Plot2D::Plot2D (const char *title, axis_t x, axis_t y)
          : Plot(title)
    {
        coords.x = x;
        coords.y = y;

        realsize = 0;
        if (x == DATA) realsize ++;
        if (y == DATA) realsize ++;
    }

    void Plot2D::display (Comm *c, DataSet::iterator b,
                          DataSet::iterator e)
    {
        // Alternative (incremental) value for the y axis (if not
        // specified).
        unsigned alt_y = 0;

        while (b != e) {
            const double *vals = *b;

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

    void Plot2D::addVector (double x, double y)
    {
        double v[] = {x, y};
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

    void Plot3D::addVector (double x, double y, double z)
    {
        double v[] = {x, y, z};
        Plot::addVector(v);
    }

    void Plot3D::display (Comm *c, DataSet::iterator b,
                          DataSet::iterator e)
    {
        // Alternative (incremental) values for the x and y axis (if not
        // specified).
        unsigned alt_x = 0, alt_y = 0, alt_z = 0;

        while (b != e) {
            const double *vals = *b;

            c->command("%f %f %f\n",
                       coords.x == DATA ? vals[0] : alt_x ++,
                       coords.y == DATA ? vals[1] : alt_y ++,
                       coords.z == DATA ? vals[2] : alt_z ++);
            b ++;
        }
    }

}

