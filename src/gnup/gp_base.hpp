#ifndef __defined_gnup_gp_base_hpp
#define __defined_gnup_gp_base_hpp

#include <gnup/pipe.hpp>

namespace gnup {

    class GnuPlot : public Comm {

        public:
            GnuPlot () throw (CommError);

    };

}

#endif // __defined_gnup_gp_base_hpp

