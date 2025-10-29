#include <stdbool.h>
#include <stdio.h>

int main() {
    FILE *f = NULL;
    f = fopen("z10.txt", "w+");
    if (f == NULL) {
        printf("File could not be opened\n");
        return 404;
    }

    fprintf(f, "I <3 programming\n");
    fclose(f);

    f = fopen("z10.txt", "r");
    char c;
    while (fscanf(f, "%c", &c) != EOF) {
        printf("%c\n", c);
    }
    fclose(f);
    f = NULL;
    return 0;
}