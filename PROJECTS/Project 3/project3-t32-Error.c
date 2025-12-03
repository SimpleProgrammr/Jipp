#include <stdio.h>
#include <stdlib.h>

void PostError(char *msg, int level) {
    fprintf(stderr, "ERROR: %s\n", msg);
    if (level != 0)
        exit(level);
}
