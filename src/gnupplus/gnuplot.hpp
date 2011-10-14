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
#include <gnupplus/layout.hpp>
#include <list>
#include <stdint.h>

namespace gnup {

    class GnuPlot : public Comm, Trigger {

        public:
            GnuPlot (const char * prog = "gnuplot",
                     const char * args[] = NULL,
                     Layout *layout = NULL);

            ~GnuPlot ();

            void trig ();
            void setTitle (const char *title);
            void clear ();
            void setLayout (Layout &l);
            Layout & getLayout ();

            void addPlot (Plot &p, unsigned row = 0, unsigned col = 0);

        private:
            Layout *layout;
            bool def_layout;
            const char *title;

    };

}

#endif // __defined_gnup_gp_base_hpp

