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

#ifndef __defined_gnup_plots_hpp
#define __defined_gnup_plots_hpp

#include <gnup/gp_base.hpp>
#include <gnup/except.hpp>

namespace gnup {

    enum axis_t { DATA, AUTO };

    class Plot2D : public Plot {

        public:
            Plot2D (const char *title, axis_t x, axis_t y);

            void writePlotting (Comm *c, DataSet::iterator begin,
                               DataSet::iterator end);

            size_t getDimension ();

            void addVector (float x, float y);

            void writeFormat (Comm *c);

        private:
            struct { axis_t x, y; } coords;
            uint8_t realsize;

    };

    class Plot3D : public Plot {

        public:
            Plot3D (const char *title, axis_t x, axis_t y, axis_t z);

            void writePlotting (Comm *c, DataSet::iterator begin,
                               DataSet::iterator end);

            size_t getDimension ();

            void addVector (float x, float y, float z);

            void writeFormat (Comm *c);

        private:
            struct { axis_t x, y, z; } coords;
 
            uint8_t realsize;

    };

}

#endif // __defined_gnup_plots_hpp

