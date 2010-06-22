#include "test_environ.h"

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <assert.h>

void build_environment ()
{
    const char *path;
    char *new_path;
    size_t n;

    path = getenv("PATH");
    n = strlen(path);
    new_path = malloc(sizeof(char) * (3 + n));  // room for ":.\0"

    memcpy((void *)new_path, (void *)path, n * sizeof(char));
    new_path[n++] = ':';
    new_path[n++] = '.';
    new_path[n++] = '\0';
    setenv("PATH", new_path, 1);
    free(new_path);
}

int inloop_create (inloop_t *l, const char *echo_name,
                   const char *my_name)
{
    register char * fname;
    size_t n;
    
    // Build the name for the pipe basing on my program name.
    n = strlen(my_name);
    fname = malloc(sizeof(char) * (n + 3));  // room for __ and \0
    assert(fname != NULL);
    strcpy(fname, my_name);
    fname[n ++] = '_';
    fname[n ++] = '_';
    fname[n] = '\0';

    // Build the calling frame for the forked program.
    l->params[0] = echo_name;
    l->params[1] = fname;
    l->params[2] = NULL;

    return 0;
}

static inline
const char * inloop_filename (inloop_t *l)
{
    return l->params[1];
}

void inloop_destroy (inloop_t *l)
{
    register const char *fname = inloop_filename(l);
    free((void *)fname);
}

bool inloop_compare (inloop_t *l, const char * lines[])
{
    FILE *f;
    char *lineptr = NULL;
    size_t n;
    ssize_t read = -1;
    bool passed;

    f = fopen(inloop_filename(l), "rt");
    while ((read = getline(&lineptr, &n, f)) >= 0 && *lines != NULL) {
        register char last;

        if (read <= 0) {
            continue;   // skip empty row.
        }

        if ((last = lineptr[read - 1]) == '\n') {
            lineptr[read - 1] = '\0';
        }

        if (strcmp(*lines, lineptr) != 0) {
            return false;
        }
        lines ++;
    }
    passed = (read < 0) && (*lines == NULL);
    free(lineptr);
    fclose(f);

    return passed;
}

