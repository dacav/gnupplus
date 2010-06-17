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

#ifndef __defined_gnup_gp_base_hpp
#define __defined_gnup_gp_base_hpp

#include <gnupplus/pipe.hpp>
#include <gnupplus/plots.hpp>
#include <list>
#include <stdint.h>

namespace gnup {

    class GnuPlot : public Comm, Trigger {

        public:
            GnuPlot (size_t dimensions,
                     const char *prog = "gnuplot") throw (CommError);

            void trig ();
            void addSource (Plot &src) throw (PlotError);

            void setXLabel (const char *label);
            void setYLabel (const char *label);
            void setZLabel (const char *label);

            void setXRange (float min, float max);
            void setYRange (float min, float max);
            void setZRange (float min, float max);

            void clear ();

        private:

            void setLabel (char which, const char *label);
            void setRange (char which, float min, float max);

            std::list<Plot *> sources;
            size_t dimensions;

            void initPlotting ();
    };

}

#endif // __defined_gnup_gp_base_hpp

