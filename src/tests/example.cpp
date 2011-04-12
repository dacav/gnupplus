#include <gnupplus.hpp>
#include <cstdio>
#include <assert.h>

#include "test_environ.hh"

static const char* tale[] = {
	"Command test!",
    NULL
};

int main (int argc, char **argv)
{
    InputLoop io ("testecho", argv[0]);

    /* VERY IMPORTANT NOTE! In order to ensure determinism, the object
     * must be deallocated before the check, since you may accidentally
     * check the file before it gets written!
     *
     * This operation must be achieved explicitly in the library test, but
     * it's not necessary while using the library.
     */
    gnup::GnuPlot *gp = new gnup::GnuPlot("testecho", io.params);
	gp->command("Command test!\n");
    delete gp;

	assert(io == tale);
    return 0;
}
