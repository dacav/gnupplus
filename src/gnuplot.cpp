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
           : Comm(prog, args, true)
    {
        if (l != NULL) {
            layout = l;
            def_layout = false;
        } else {
            layout = new Layout(1, 1);
            def_layout = true;
        }
        layout->setTrigger(this);
        title = NULL;
    }

    GnuPlot::~GnuPlot ()
    {
        if (def_layout) {
            delete layout;
        }
    }

    void GnuPlot::setTitle (const char *t)
    {
        if (def_layout) {
            title = t;
        } else {
            throw LayoutError("You provided a layout, use it for titles");
        }
    }

    void GnuPlot::trig ()
    {
        if (title) command("set title \"%s\"\n", title);
        layout->run(this);
    }

    void GnuPlot::clear ()
    {
        command("clear\n");
    }

    void GnuPlot::addPlot (Plot &p, unsigned row, unsigned col)
    {
        layout->addPlot(p, row, col);
        p.setTrigger(this);
    }

    void GnuPlot::setLayout (Layout &l)
    {
        if (def_layout)
            delete layout;
        layout = &l;
        l.setTrigger(this);
        def_layout = false;
    }

    Layout & GnuPlot::getLayout ()
    {
        return *layout;
    }

}

