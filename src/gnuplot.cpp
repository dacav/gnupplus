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

    GnuPlot::GnuPlot (const char *prog, const char * args[],
                      Layout *l)
                     throw (CommError)
           : Comm(prog, args, true)
    {
        if (l != NULL) {
            layout = new Layout(*l);
        } else {
            layout = new Layout(1, 1);
        }
        layout->setTrigger(this);
    }

    GnuPlot::~GnuPlot ()
    {
        delete layout;
    }

    void GnuPlot::trig ()
    {
        layout->run(this);
    }

    void GnuPlot::clear ()
    {
        command("clear\n");
    }

    void GnuPlot::addPlot (Plot &p, unsigned row, unsigned col)
                           throw (LayoutError)
    {
        layout->addPlot(p, row, col);
        p.setTrigger(this);
    }

    void GnuPlot::setLayout (Layout &l)
    {
        delete layout;
        layout = new Layout(l);
        layout->setTrigger(this);
    }

}

