#include "test_environ.h"
#include <stdlib.h>
#include <string.h>

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
