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

