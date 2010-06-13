#ifndef __defined_gnup_gp_base_hpp
#define __defined_gnup_gp_base_hpp

#include <gnup/pipe.hpp>
#include <list>

namespace gnup {

    class Trigger {
        public:
            /** Replot the graph.
             *
             * You may want to redraw, since new data are available.
             */
            virtual void trig (void) = 0;
    };

    typedef std::list<float *> DataSet;

    class Plot {

        public:

            static const unsigned AXIS_NONE = 0;
            static const unsigned AXIS_X = 1 << 0;
            static const unsigned AXIS_Y = 1 << 1;
            static const unsigned AXIS_Z = 1 << 2;

            /** Axis definition
             *
             * Returns a bitwise or of the values in
             * gnup::Plot::axis_t enumerative. Basing on this the
             * gnup::GnuPlot class can infer how to build the plot.
             *
             * @return The plotting setting for this data source.
             */
            unsigned getAxis ();

            /** Set the trigger.
             *
             * The trigger allows to signal new data.
             */
            void setTrigger (Trigger *t);

            /** Used by the GnuPlot class, put commands to the channel */
            virtual void giveFormat (Comm *c) = 0;
            virtual void givePlotting (Comm *c) = 0;

            /** Used when vector size is already known */
            virtual void addVector (float *vals) = 0;

            virtual ~Plot ();

        protected:
            Plot (unsigned axis);

            /** Concatenate a new vector */
            void addVector (float *vals, size_t n);
            void getIters (DataSet::iterator &b, DataSet::iterator &e);

        private:
            /** Used axis */
            unsigned axis;

            Trigger *trigger;
            DataSet data;
    };

    class GnuPlot : public Comm, Trigger {

        public:
            GnuPlot (const char *prog = "gnuplot") throw (CommError);

            void trig ();
            void addSource (Plot &src);

        private:
            std::list<Plot *> sources;

            /** Enabled plotting axis */
            unsigned enab_axis;
            unsigned countEnabAxis ();

    };

}

#endif // __defined_gnup_gp_base_hpp

