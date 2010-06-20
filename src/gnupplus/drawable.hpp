#ifndef __defined_gnupplus_drawable_hpp
#define __defined_gnupplus_drawable_hpp

#include <gnupplus/pipe.hpp>

namespace gnup {

    class Drawable {
        public:
            void run (Comm *c);

        protected:
            virtual void init (Comm *c) = 0;
            virtual void display (Comm *c) = 0;
            virtual void reset (Comm *c) = 0;
    };

}

#endif // __defined_gnupplus_drawable_hpp

