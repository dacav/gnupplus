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
        layout = new Layout(1, 1);
    }

    GnuPlot::~GnuPlot ()
    {
        delete layout;
    }

    void GnuPlot::trig ()
    {
        // TODO
    }

    void GnuPlot::clear ()
    {
        command("clear");
    }

    void GnuPlot::setLayout (Layout *l)
    {
        delete layout;
        layout = l;
    }

}

