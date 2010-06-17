#include <gnupplus/layout.hpp>

namespace gnup {

    Cell::Cell (const char *t)
        : std::list<Plot *>()
    {
        title = t;
        flags = 0;
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

    void Cell::setXRange (float min, float max)
    {
        ranges.x.min = min;
        ranges.x.max = max;
        flags |= RANGE_X;
    }

    void Cell::setYRange (float min, float max)
    {
        ranges.y.min = min;
        ranges.y.max = max;
        flags |= RANGE_Y;
    }

    void Cell::setZRange (float min, float max)
    {
        ranges.z.min = min;
        ranges.z.max = max;
        flags |= RANGE_Z;
    }

    void Cell::writeSettings (Comm *c)
    {
        const char * set = "set %crange [%f:%f]\n";

        if (flags & RANGE_X)
            c->command(set, 'x', ranges.x.min, ranges.x.max);
        if (flags & RANGE_Y)
            c->command(set, 'y', ranges.y.min, ranges.y.max);
        if (flags & RANGE_Z)
            c->command(set, 'z', ranges.z.min, ranges.z.max);

        if (title)
            c->command("set title \"%s\"\n", title);
    }

    void Cell::resetSettings (Comm *c)
    {
        const char * restore = "set %crange restore\n";

        if (flags & RANGE_X) c->command(restore, 'x');
        if (flags & RANGE_Y) c->command(restore, 'y');
        if (flags & RANGE_Z) c->command(restore, 'z');
    }

    Layout::Layout ()
    {
        ncols = nrows = 1;
    }

    Layout::~Layout ()
    {
    }

    void Layout::setColumns (size_t nc)
    {
        ncols = nc;
    }

    void Layout::setRows (size_t nr)
    {
        nrows = nr;
    }

    void Layout::draw (Comm *c)
    {
        unsigned row, col;
        bool multiplot = nrows + ncols > 2;

        if (multiplot) {
            c->command("set multiplot\n");
            c->command("set size %f,%f\n", 1.0 / ncols, 1.0 / nrows);
        }

        for (row = 0; row < nrows; row ++) {
            for (col = 0; col < ncols; col ++) {
                std::pair<unsigned, unsigned> coords;
                Cell *cell;

                coords.first = row;
                coords.second = col;

                if ((cell = cells[coords]) != NULL) {
                    drawCell(c, cell, row, col);
                }
            }
        }

        if (!multiplot) {
            c->command("unset multiplot\n");
            c->command("set size 1,1");
        }
    }

    void Layout::drawCell (Comm *c, Cell *cell, unsigned row,
                           unsigned col)
    {
        c->command("set origin %f,%f\n", (float)col / ncols,
                                         (float)row / nrows);
        cell->writeSettings(c);
        // TODO plot
        cell->resetSettings(c);
    }

}
