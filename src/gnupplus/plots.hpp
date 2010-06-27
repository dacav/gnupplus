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

#include <gnupplus/except.hpp>
#include <gnupplus/pipe.hpp>
#include <gnupplus/drawable.hpp>

#include <list>
#include <stdint.h>

namespace gnup {

    /** Exception for plotting */
    class PlotError : public Error {
        public:
            /** Constructor.
             *
             * @param msg The error message.
             */
            PlotError (const char *msg) throw() : Error(msg) {}
    };

    /** Every plot basically boils down to a list of double. */
    typedef std::list<double *> DataSet;

    /** The plotting class
     *
     * This class builds the main structure of a plot, but it's just an
     * abstract class.
     *
     * Many of the internal methods are supposed to be called by the
     * GnuPlot class. The ones which are meant for external access will be
     * marked in the comment.
     */
    class Plot : public Drawable {

        public:

            /** Style to be used in this plot.
             *
             * @warning The error bars are not correctly implemented, for
             *          the moment.
             */
            enum style_t {
                LINES,          /**< Plot lines */
                POINTS,         /**< Plot points */
                LINESPOINTS,    /**< Plot both lines and points */
                IMPULSES,       /**< Plot dirac deltas */
                DOTS,           /**< Plot dots */
                STEPS,          /**< Plot steps from the previous value */
                ERRORBARS,      /**< Plot error bars */
                BOXES,          /**< Plot boxes */
                BOXERRORBARS    /**< Plot boxes and error bars */
            };

            /** Destructor */
            virtual ~Plot ();

            /** Set the trigger.
             *
             * The trigger allows to signal new data. This method is used
             * by a GnuPlot instance in order to link the Plot.
             */
            void setTrigger (Trigger *t);

            /** Dimension of the plot.
             *
             * Obviously the dimension depends on the extending class and
             * must be implemented.
             *
             * @return The size of the plot.
             */
            virtual size_t getDimension () = 0;

            void setStyle (style_t s);

            void writeStyle (Comm *c);

            /** Enables or disables the auto-update function
             *
             * The function allows to enable or disable the real-time
             * plotting behaviour by enabling or disabling the trigger
             * when the addVector() method is called.
             *
             * By default the class has a real-time behaviour.
             *
             * @param au Auto-update flag, true for real-time behaviour,
             *           false for offline behaviour.
             */
            void setAutoUpdate (bool au);

            /** Set the maximum length of the internal data list.
             *
             * @param max The max length. Set it to 0 in order to keep all
             *            data.
             */
            void setOverflow (size_t max);

            void init (Comm *c);
            void display (Comm *c);
            void reset (Comm *c);
 
        protected:
            Plot (const char *title);

            /** Concatenate a new data vector.
             *
             * This procedure makes a copy of the vector before inserting
             * it into the data list, then it triggers the plotting class
             * specified by gnup::Plot::setTrigger, if any.
             *
             * @param vals The values to be added;
             * @param n The size of the vector;
             */
            void addVector (double *vals);

            DataSet data;

            /** Writer for the plotting sequence.
             *
             * Used by a gnup::GnuPlot instance in order to get the
             * plotting data sequence for the 'plot' command.
             *
             * This method must be implemented by the extending class
             * depending on the specific plotting semantics.
             *
             * @see gnup::2DPlot and gnup::3DPlot.
             *
             * @param c The communication channel;
             * @param begin The stdlib iterator for start of the list;
             * @param end The stdlib iterator for end of the list.
             */
            virtual void display (Comm *c, DataSet::iterator begin,
                                  DataSet::iterator end) = 0;

        private:

            const char *title;

            /** A double-pointer to the gnup::Trigger
             *
             * This allows the gnup::Layout class to change its trigger
             * without caring about all internal plots, which will be
             * automatically updated.
             */
            Trigger *trigger;
            style_t style;
            bool auto_update;
            size_t max_size;

    };

    enum axis_t { DATA, AUTO };

    class Plot2D : public Plot {

        public:
            Plot2D (const char *title, axis_t x, axis_t y);

            void display (Comm *c, DataSet::iterator begin,
                          DataSet::iterator end);

            size_t getDimension ();

            void addVector (double x, double y);

            void writeFormat (Comm *c);

        private:
            struct { axis_t x, y; } coords;
            uint8_t realsize;

    };

    class Plot3D : public Plot {

        public:
            Plot3D (const char *title, axis_t x, axis_t y, axis_t z);

            void display (Comm *c, DataSet::iterator begin,
                          DataSet::iterator end);

            size_t getDimension ();

            void addVector (double x, double y, double z);

            void writeFormat (Comm *c);

        private:
            struct { axis_t x, y, z; } coords;
 
            uint8_t realsize;

    };

}

#endif // __defined_gnup_plots_hpp

