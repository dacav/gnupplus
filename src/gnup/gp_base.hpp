#ifndef __defined_gnup_gp_base_hpp
#define __defined_gnup_gp_base_hpp

#include <gnup/pipe.hpp>
#include <list>
#include <stdint.h>

namespace gnup {

    /** Trigger abstract class
     *
     * Any extending class must implement the trig() method, which will be
     * called by a plotting class (namely an extender of the Plot
     * abstract). This will require a replotting.
     */
    class Trigger {
        public:
            /** Replot the graph.
             *
             * You may want to redraw, since new data are available.
             */
            virtual void trig () = 0;
    };

    /** Exception for plotting */
    class PlotError : public Error {
        public:
            /** Constructor.
             *
             * @param msg The error message.
             */
            PlotError (const char *msg) throw() : Error(msg) {}
    };

    /** Every plot basically boils down to a list of float. */
    typedef std::list<float *> DataSet;

    /** The plotting class
     *
     * This class builds the main structure of a plot, but it's just an
     * abstract class.
     *
     * Many of the internal methods are supposed to be called by the
     * GnuPlot class. The ones which are meant for external access will be
     * marked in the comment.
     */
    class Plot {

        public:

            /** Style to be used in this plot */
            enum style_t {
                LINES,
                POINTS,
                LINESPOINTS,
                IMPULSES,
                DOTS,
                STEPS,
                ERRORBARS,
                BOXES,
                BOXERRORBARS
            };

            /** Used by a GnuPlot instance in order to get the plotting
             *  data sequence for the 'plot' command.
             */
            virtual void writePlotting (Comm *c, DataSet::iterator begin,
                                        DataSet::iterator end) = 0;

            const char * getTitle ();

            virtual ~Plot ();

            /** Set the trigger.
             *
             * The trigger allows to signal new data. This method is used
             * by a GnuPlot instance in order to link the Plot.
             */
            void setTrigger (Trigger *t);

            void writePlotting (Comm *c);

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

            /** Used by a GnuPlot instance in order to get the plotting
             * format for the 'plot' command.
             */
            virtual void writeFormat (Comm *c) = 0;

            /** Set the maximum length of the internal data list.
             *
             * @param max The max length. Set it to 0 in order to keep all
             *            data.
             */
            void setOverflow (size_t max);

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
            void addVector (float *vals);

            DataSet data;

        private:

            const char *title;
            Trigger *trigger;
            style_t style;
            bool auto_update;
            size_t max_size;

    };

    class GnuPlot : public Comm, Trigger {

        public:
            GnuPlot (size_t dimensions,
                     const char *prog = "gnuplot") throw (CommError);

            void trig ();
            void addSource (Plot &src) throw (PlotError);

            void setXLabel (const char *label);
            void setYLabel (const char *label);
            void setZLabel (const char *label);

        private:

            void setLabel (char which, const char *label);

            std::list<Plot *> sources;
            size_t dimensions;

            void initPlotting ();
    };

}

#endif // __defined_gnup_gp_base_hpp

