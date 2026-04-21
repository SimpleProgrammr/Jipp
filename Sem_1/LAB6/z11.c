#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS_INLINE 256

char **allocate2DcharTab(int lines, int chars) {
    char **tab = (char **) calloc(lines, sizeof(char *));
    if (tab == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    for (int i = 0; i < lines; i++) {
        tab[i] = (char *) calloc(chars + 1, sizeof(char));
        if (tab[i] == NULL) {
            printf("Memory allocation failed\n");
            return NULL;
        }
    }

    return tab;
}

int main(int argc, char *argv[]) {
    FILE *file = NULL;
    file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("File not found\n");
        return 1;
    }
    int nl = 0, ld = 0, lm = 0, wl = 0;

    char **text = allocate2DcharTab(10, MAX_CHARS_INLINE);

    int i = 0;
    char bufor[MAX_CHARS_INLINE];
    while (i < MAX_CHARS_INLINE && fgets(bufor, MAX_CHARS_INLINE, file)) {
        int len = strlen(bufor);
        bufor[len - 1] = '\0';
        if ((text[i] = (char *) malloc((unsigned) len)) == (char *) NULL) {
            printf("Brak pamieci\n");
            exit(3);
        }
        strcpy(text[i], bufor);
        i++;
    }
    fclose(file);
}