#ifndef __defined_test_environ_h
#define __defined_test_environ_h
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdbool.h>

/** Builds the test environment
 *
 * export PATH="$PATH:."
 *
 */
void build_environment ();

typedef struct {
    const char * params[3];     // params for the gnuplot emulator;
} inloop_t;

/** Initializer for a inloop.
 *
 * @param l The inloop to be initialized;
 * @param echo_name The name of the echoing application, used to build the
 *                  command line;
 * @param my_name The name of the calling program, which will be used as
 *                template for the output file name.
 */
int inloop_create (inloop_t *l, const char *echo_name,
                   const char *my_name);

/** Frees inloop memory
 *
 * @param l The inloop to be freed.
 */
void inloop_destroy (inloop_t *l);

/** Compare the inloop produced file.
 *
 * The inloop correspond to a certain file which contains the lines that
 * gnupplus should produce within a certain test.
 *
 * Empty lines and lines starting with '#' in the file will be ignored.
 * Therefore try to avoid putting that into lines!
 *
 * The lines vector elements are supposed to be terminated by '\0' and not
 * to contain '\n'.
 *
 * @param l The inloop;
 * @param lines A NULL-terminated array of strings to be compared.
 * @return True if the comparsion succeded, false otherwise.
 */
bool inloop_compare (inloop_t *l, const char * lines[]);

#ifdef __cplusplus
}
#endif
#endif // __defined_test_environ_h

