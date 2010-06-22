#ifndef __defined_gnupplus_drawable_hpp
#define __defined_gnupplus_drawable_hpp

#include <gnupplus/pipe.hpp>

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

    class Drawable {
        public:
            void run (Comm *c);
            void setTrigger (Trigger *t);

        protected:
            virtual void init (Comm *c) = 0;
            virtual void display (Comm *c) = 0;
            virtual void reset (Comm *c) = 0;
    };

}

#endif // __defined_gnupplus_drawable_hpp

