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

#include <gnupplus/layout.hpp>

using std::make_pair;

namespace gnup {

    Cell::Cell ()
    {
        flags = 0;
        dimensions = 0;
    }

    Cell::Cell (Cell &c)
    {
        flags = c.flags;
        dimensions = c.dimensions;
        title = c.title;
        labels = c.labels;
        ranges = c.ranges;
        plots = c.plots;
    }

    void Cell::setTitle (const char *t)
    {
        title = t;
    }

    void Cell::setXLabel (const char *label)
    {
        labels.x = label;
        flags |= LABEL_X;
    }

    void Cell::setYLabel (const char *label)
    {
        labels.y = label;
        flags |= LABEL_Y;
    }

    void Cell::setZLabel (const char *label)
    {
        labels.z = label;
        flags |= LABEL_Z;
    }

    void Cell::setXRange (double min, double max)
    {
        ranges.x.min = min;
        ranges.x.max = max;
        flags |= RANGE_X;
    }

    void Cell::setYRange (double min, double max)
    {
        ranges.y.min = min;
        ranges.y.max = max;
        flags |= RANGE_Y;
    }

    void Cell::setZRange (double min, double max)
    {
        ranges.z.min = min;
        ranges.z.max = max;
        flags |= RANGE_Z;
    }

    void Cell::init (Comm *c)
    {
        const char * set_range = "set %crange [%f:%f]\n";
        const char * set_label = "set %clabel \"%s\"\n";

        if (flags & RANGE_X) {
            c->command(set_range, 'x', ranges.x.min, ranges.x.max);
        }
        if (flags & RANGE_Y) {
            c->command(set_range, 'y', ranges.y.min, ranges.y.max);
        }
        if (flags & RANGE_Z) {
            c->command(set_range, 'z', ranges.z.min, ranges.z.max);
        }

        if (flags & LABEL_X) {
            c->command(set_label, 'x', labels.x);
        }
        if (flags & LABEL_Y) {
            c->command(set_label, 'y', labels.y);
        }
        if (flags & LABEL_Z) {
            c->command(set_label, 'z', labels.z);
        }

        if (title != NULL) {
            c->command("set title \"%s\"\n", title);
        }


    }

    void Cell::setTrigger (Trigger *t)
    {
        std::list<Plot *>::iterator i, end;

        end = plots.end();
        for (i = plots.begin(); i != end; i ++) {
            (*i)->setTrigger(t);
        }
    }

    void Cell::display (Comm *c)
    {
        size_t size;
        std::list<Plot *>::iterator i = plots.begin(),
                                    end = plots.end();

        if ((size = plots.size()) == 0) {
            return;
        }

        c->command(dimensions > 2 ? "splot " : "plot ");
        do {
            (*i)->init(c);
            if (-- size) c->command(", ");
            i ++;
        } while (i != end);
        c->command("\n");
        for (i = plots.begin(); i != end; i ++) {
            (*i)->display(c);
            (*i)->reset(c);
        }
    }

    void Cell::reset (Comm *c)
    {
        const char * restore = "set %crange restore\n";

        if (flags & RANGE_X) c->command(restore, 'x');
        if (flags & RANGE_Y) c->command(restore, 'y');
        if (flags & RANGE_Z) c->command(restore, 'z');
    }

    void Cell::addPlot (Plot &p)
    {
        size_t dim = p.getDimension();
        if (dimensions == 0) {
            dimensions = dim;
        } else if (dim != dimensions) {
            throw PlotError("Inconsistent dimension for cell");
        }
        plots.push_back(&p);
    }

    Layout::Layout (size_t nr, size_t nc)
    {
        nrows = nr;
        ncols = nc;
    }

    Layout::Layout (Layout &l)
    {
        if (&l != this) {
            CellMap::iterator i, end;

            nrows = l.nrows;
            ncols = l.ncols;

            end = l.cells.end();
            for (i = l.cells.begin(); i != end; i ++) {
                cells[i->first] = new Cell(*(i->second));
            }
        }
    }

    Layout::~Layout ()
    {
        CellMap::iterator i, end;

        end = cells.end();
        for (i = cells.begin(); i != end; i ++) {
            delete i->second;
        }
    }

    void Layout::init (Comm *c)
    {
        if (nrows + ncols > 2) {
            c->command("set multiplot\n");
            c->command("set size %f,%f\n", 1.0 / ncols, 1.0 / nrows);
        }
    }

    void Layout::display (Comm *c)
    {
        unsigned row, col;
        const char *fmt = (nrows + ncols == 2) ? NULL
                             : "set origin %f,%f\n";

        for (row = 0; row < nrows; row ++) {
            for (col = 0; col < ncols; col ++) {
                Cell *cell;
                if ((cell = cells[make_pair(row, col)]) != NULL) {
                    if (fmt) {
                        c->command(fmt, (double)col / ncols,
                                        (double)row / nrows);
                    }
                    cell->run(c);
                }
            }
        }

    }

    void Layout::reset (Comm *c)
    {
        if (nrows + ncols > 2) {
            c->command("set size 1,1\n");
            c->command("unset multiplot\n");
        }
    }

    void Layout::setTrigger (Trigger *t)
    {
        CellMap::iterator i, end;

        end = cells.end();
        for (i = cells.begin(); i != end; i ++) {
            i->second->setTrigger(t);
        }
    }

    Cell & Layout::getCell (unsigned row, unsigned col)
    {
        if (row < nrows && col < ncols) {
            Coords coords = make_pair(row, col);
            Cell *ret;

            if (cells.find(coords) == cells.end()) {
                cells.insert(make_pair(coords, ret = new Cell()));
            } else {
                ret = cells[coords];
            }
            return *ret;
        } else {
            throw LayoutError("Trying to plot outside the boundary");
        }
    }

    void Layout::addPlot (Plot &p, unsigned row, unsigned col)
    {
        getCell(row, col).addPlot(p);
    }

}
