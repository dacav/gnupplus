#ifndef __defined_gnupplus_layout_hpp
#define __defined_gnupplus_layout_hpp

#include <map>
#include <list>
#include <utility>

#include <stdint.h>

#include <gnupplus/plots.hpp>
#include <gnupplus/pipe.hpp>

namespace gnup {

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
    class Cell : public std::list<Plot *> {

        public:
            Cell (const char *title = NULL);

            void setXLabel (const char *label);
            void setYLabel (const char *label);
            void setZLabel (const char *label);

            void setXRange (float min, float max);
            void setYRange (float min, float max);
            void setZRange (float min, float max);

            void writeSettings (Comm *c);
            void resetSettings (Comm *c);

        private:
            const char *title;
            struct {
                const char *x, *y, *z;
            } labels;
            struct {
                struct {
                    float min, max;
                } x, y, z;
            } ranges;

            uint8_t flags;
            static const uint8_t RANGE_X = 1 << 0;
            static const uint8_t RANGE_Y = 1 << 1;
            static const uint8_t RANGE_Z = 1 << 2;
            static const uint8_t LABEL_X = 1 << 3;
            static const uint8_t LABEL_Y = 1 << 4;
            static const uint8_t LABEL_Z = 1 << 5;

    };

    /** From cell coordinate to plot.
     *
     * Like an umbounded matrix.
     */
    typedef std::map<std::pair<unsigned, unsigned>, Cell *> CellMap;

    class Layout {

        public:
            Layout ();
            virtual ~Layout ();

            void setColumns (size_t nc);
            void setRows (size_t nr);

            void draw (Comm *c);

        private:
            size_t ncols;
            size_t nrows;

            CellMap cells;

            void drawCell (Comm *c, Cell *cell, unsigned row,
                           unsigned col);
    };

    //        void setLabel (char which, const char *label);
    //        void setRange (char which, float min, float max);



}

#endif // __defined_gnupplus_layout_hpp

