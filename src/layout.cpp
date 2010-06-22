#include <gnupplus/layout.hpp>

using std::make_pair;

namespace gnup {

    Cell::Cell ()
        : std::list<Plot *>()
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
        const char * set = "set %crange [%f:%f]\n";

        if (flags & RANGE_X) {
            c->command(set, 'x', ranges.x.min, ranges.x.max);
        }
        if (flags & RANGE_Y) {
            c->command(set, 'y', ranges.y.min, ranges.y.max);
        }
        if (flags & RANGE_Z) {
            c->command(set, 'z', ranges.z.min, ranges.z.max);
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
        std::list<Plot *>::iterator i,
                                    end = plots.end();

        if (plots.size() == 0) {
            return;
        }

        c->command(dimensions > 2 ? "splot " : "plot ");
        for (i = plots.begin(); i != end; i ++) {
            (*i)->init(c);
        }
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

        if (title != NULL) {
            c->command("set title\n");
        }
    }

    void Cell::addPlot (Plot &p)
    {
        size_t dim = p.getDimension();
        if (dimensions == 0) {
            dimensions = dim;
        } else if (dim != dimensions) {
            PlotError err ("Inconsistent dimension for cell");
            throw err;
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

    Cell * Layout::getCell (unsigned row, unsigned col)
                           throw (LayoutError)
    {
        if (row < nrows && col < ncols) {
            Coords coords = make_pair(row, col);
            Cell *ret;

            ret = cells[coords];
            if (ret == NULL) {
                ret = new Cell();
                cells[coords] = ret;
            }
            return ret;

        } else {
            LayoutError err ("Trying to plot outside the boundary");
            throw err;
        }
    }

    void Layout::addPlot (Plot &p, unsigned row, unsigned col)
                         throw (LayoutError)
    {
        Cell *c = getCell(row, col);
        c->addPlot(p);
    }

}
