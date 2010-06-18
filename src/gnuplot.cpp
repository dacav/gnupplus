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

#include <gnupplus/gnuplot.hpp>
#include <cstdio>

namespace gnup {

    GnuPlot::GnuPlot (size_t dims, const char *prog, const char * args[])
                     throw (CommError)
           : Comm(prog, args, true)
    {
        dimensions = dims;
    }

    void GnuPlot::addSource (Plot &src) throw (PlotError)
    {
        if (src.getDimension() > dimensions) {
            PlotError err("Too many dimensions");
            throw err;
        } else {
            sources.push_back(&src);
            src.setTrigger(this);
        }
    }

    void GnuPlot::initPlotting ()
    {
        size_t size;
        std::list<Plot *>::iterator i, end;

        // Format initialization phase: gnuplot must know in advance which
        // plots must be achieved.
        switch (dimensions) {
            case 0:
                // Nothing to plot (it should never be the case)
                return;
            case 1:
            case 2:
                command("plot ");
                break;
            default:
                command("splot ");
        }

        i = sources.begin();
        end = sources.end();
        size = sources.size();
        // We know that this operation will be achieved at least once,
        // since size > 0
        do {
            Plot *src = *i;
            const char *title = src->getTitle();

            command("\"-\" ");
            if (title != NULL) command("title \"%s\" ", title);
            else command("notitle");

            // Plot specific data settings:
            src->writeFormat(this);
            src->writeStyle(this);

            if (--size) {
                // This puts the comma between two plotting indications.
                command(", ");
            }
        } while ((++ i) != end);
        command("\n");
    }

    void GnuPlot::trig ()
    {
        std::list<Plot *>::iterator i, end;

        if (sources.size() == 0) {
            // Nothing to plot...
            return;
        }

        initPlotting();
        
        // Actual plotting phase
        for (i = sources.begin(); i != sources.end(); i ++) {
            Plot *src = *i;
            src->writePlotting(this);
            // Terminate data set
            command("e\n");
        }
    }

    void GnuPlot::setXLabel (const char *label)
    {
        setLabel('x', label);
    }

    void GnuPlot::setYLabel (const char *label)
    {
        setLabel('y', label);
    }

    void GnuPlot::setZLabel (const char *label)
    {
        setLabel('z', label);
    }

    void GnuPlot::setLabel (char which, const char *label)
    {
        command("set %clabel \"%s\"\n", which, label);
    }

    void GnuPlot::clear ()
    {
        command("clear");
    }

    void GnuPlot::setXRange (float min, float max)
    {
        setRange('x', min, max);
    }

    void GnuPlot::setYRange (float min, float max)
    {
        setRange('y', min, max);
    }

    void GnuPlot::setZRange (float min, float max)
    {
        setRange('z', min, max);
    }

    void GnuPlot::setRange (char which, float min, float max)
    {
        command("set %crange [%f:%f]\n", which, min, max);
    }

}

