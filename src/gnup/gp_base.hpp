#ifndef __defined_gnup_gp_base_hpp
#define __defined_gnup_gp_base_hpp

#include <gnup/pipe.hpp>
#include <list>
#include <stdint.h>

namespace gnup {

    class Trigger {
        public:
            /** Replot the graph.
             *
             * You may want to redraw, since new data are available.
             */
            virtual void trig (void) = 0;
    };

    class PlotError : public Error {
        public:
            PlotError (const char *msg) throw() : Error(msg) {}
    };

    typedef std::list<float *> DataSet;

    class Plot {

        public:

            /** Used by a GnuPlot instance in order to get the plotting
             * format for the 'plot' command.
             */
            virtual void getFormat (Comm *c) = 0;

            /** Used by a GnuPlot instance in order to get the plotting
             *  data sequence for the 'plot' command.
             */
            virtual void getPlotting (Comm *c, DataSet::iterator begin,
                                      DataSet::iterator end) = 0;

            const char * getTitle ();

            virtual ~Plot ();

            /*------------ Methods used by GnuPlot instance ------------*/

            /** Set the trigger.
             *
             * The trigger allows to signal new data. This method is used
             * by a GnuPlot instance in order to link the Plot.
             */
            void setTrigger (Trigger *t);

            void getPlotting (Comm *c);

            virtual size_t getDimension () = 0;

            void setWithLines (bool wl);
            bool getWithLines ();

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

        private:

            const char *title;
            Trigger *trigger;
            DataSet data;

            unsigned flags;
    };

    class GnuPlot : public Comm, Trigger {

        public:
            GnuPlot (size_t dimensions,
                     const char *prog = "gnuplot") throw (CommError);

            void trig ();
            void addSource (Plot &src) throw (PlotError);

        private:

            std::list<Plot *> sources;
            size_t dimensions;

            void initPlotting ();
    };

}

#endif // __defined_gnup_gp_base_hpp

