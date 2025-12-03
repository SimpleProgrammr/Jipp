#include <stdbool.h>
#include <stdio.h>

extern void PostError(char *, int);

FILE *OpenFile(const char *fileName, const char *mode) {
    FILE *f = fopen(fileName, mode);
    if (f == NULL)
        PostError("Unable to open file", 404);
    return f;
}

void CloseFile(FILE *f) {
    if (f != NULL)
        fclose(f);
}
