#include <gnupplus/drawable.hpp>

namespace gnup {

    void Drawable::run (Comm *c)
    {
        init(c);
        display(c);
        reset(c);
    }

}

