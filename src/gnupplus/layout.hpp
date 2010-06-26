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

#ifndef __defined_gnupplus_layout_hpp
#define __defined_gnupplus_layout_hpp

#include <map>
#include <list>
#include <utility>

#include <stdint.h>

#include <gnupplus/drawable.hpp>
#include <gnupplus/plots.hpp>
#include <gnupplus/pipe.hpp>
#include <gnupplus/except.hpp>

namespace gnup {

    typedef std::pair<unsigned, unsigned> Coords;

    /** Layout cell
     *
     * The graph will be subdivided into cells basing on the layout
     * definition.
     *
     * Each cell of the layout can be used to plot multiple graphs, which
     * will be overlapped and managed with the appropriate scale.
     *
     * Basically this is a list of plots of a single cell, but it's
     * characterized by some graph-related characteistics.
     */
    class Cell : public std::list<Plot *>, public Drawable {

        public:

            Cell ();
            Cell (Cell &c);

            void setXLabel (const char *label);
            void setYLabel (const char *label);
            void setZLabel (const char *label);

            void setXRange (double min, double max);
            void setYRange (double min, double max);
            void setZRange (double min, double max);

            void writeSettings (Comm *c);
            void resetSettings (Comm *c);
            void draw (Comm *c);

            void addPlot (Plot &p);
            void setTitle (const char *title);
            void setTrigger (Trigger *t);

        private:

            size_t dimensions;

            const char *title;
            struct {
                const char *x, *y, *z;
            } labels;
            struct {
                struct {
                    double min, max;
                } x, y, z;
            } ranges;

            uint8_t flags;
            static const uint8_t RANGE_X = 1 << 0;
            static const uint8_t RANGE_Y = 1 << 1;
            static const uint8_t RANGE_Z = 1 << 2;
            static const uint8_t LABEL_X = 1 << 3;
            static const uint8_t LABEL_Y = 1 << 4;
            static const uint8_t LABEL_Z = 1 << 5;

            std::list<Plot *> plots;

            void init (Comm *c);
            void display (Comm *c);
            void reset (Comm *c);

    };

    /** From cell coordinate to plot.
     *
     * Like an umbounded matrix.
     */
    typedef std::map<Coords, Cell *> CellMap;

    /** Exception for layout */
    class LayoutError : public Error {
        public:
            /** Constructor.
             *
             * @param msg The error message.
             */
            LayoutError (const char *msg) throw() : Error(msg) {}
    };

    class Layout : public Drawable {

        public:
            Layout (size_t nrows, size_t ncols);
            Layout (Layout &l);

            virtual ~Layout ();
            void draw (Comm *c);

            void setTrigger (Trigger *trig);

            void addPlot (Plot &p, unsigned row, unsigned col)
                         throw (LayoutError);

            Cell * getCell (unsigned row, unsigned col)
                           throw (LayoutError);

        private:

            void init (Comm *c);
            void display (Comm *c);
            void reset (Comm *c);

            size_t ncols;
            size_t nrows;

            CellMap cells;

            void drawCell (Comm *c, Cell *cell, unsigned row,
                           unsigned col);

    };

}

#endif // __defined_gnupplus_layout_hpp

