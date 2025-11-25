#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Environment needed
//MacOs Terminal with set 1 byte coding (ISO Latin 2)

#define MAX_CHARS_INLINE 256

char **allocate2DcharTab(int lines, int chars) {
    char **tab = calloc(lines, sizeof(char *));
    if (tab == NULL) {
        printf("Memory allocation failed\n");
        exit(10);
    }

    for (int i = 0; i < lines; i++) {
        tab[i] = (char *) calloc(chars + 1, sizeof(char));
        if (tab[i] == NULL) {
            printf("Memory allocation failed\n");
            exit(10);
        }
    }

    return tab;
}

void free2DcharTab(char **tab, int lines) {
    if (tab == NULL)
        return;

    for (int i = 0; i < lines; i++) {
        free(tab[i]);
    }
    free(tab);
}

char **getTextFromFile(const char *name, const char *mode, int *size) {
    FILE *file = NULL;
    file = fopen(name, mode);
    if (file == NULL) {
        printf("File not found\n");
        exit(1);
    }
    int i = 0, linesInTab = 10;

    char **text = allocate2DcharTab(linesInTab, MAX_CHARS_INLINE);

    char bufor[MAX_CHARS_INLINE] = {0};
    while (fgets(bufor, MAX_CHARS_INLINE, file)) {
        if (i >= linesInTab) {
            linesInTab += 5;
            char **tmp = realloc(text, (linesInTab) * sizeof(char *));

            if (tmp == NULL) {
                printf("Memory reallocation failed\n");
                free(tmp);
                tmp = NULL;
                exit(0);
            }
            text = tmp;
        }
        unsigned long len = strlen(bufor);
        if (bufor[len - 1] == '\n')
            bufor[len - 1] = '\0';
        if ((text[i] = (char *) calloc(len, sizeof(char *))) == (char *) NULL) {
            printf("Memory allocation error\n");
            exit(3);
        }
        strcpy(text[i], bufor);
        printf("Line %d: %s\n", i + 1, text[i]);
        i++;
    }
    *size = i;
    fclose(file);
    file = NULL;
    return text;
}

int main() {
    int t1h = 0;
    char **t1 = getTextFromFile("t1.txt", "r", &t1h);


    printf("\n");

    int t2h = 0;
    char **t2 = getTextFromFile("t2.txt", "r", &t2h);


    printf("Litera | wiersz | Kolumna\n");

    bool run = true;
    for (int i = t1h - 1; i >= 0 && run; i--) {
        for (int j = strlen(t1[i]); j >= 0 && run; j--) {
            char c = t1[i][j];
            if (c == '\0')
                continue;

            for (int k = t2h - 1; k >= 0 && run; k--) {
                for (int l = strlen(t2[k]); l >= 0 && run; l--) {
                    char c2 = t2[k][l];
                    if (c == c2 && c2 != '\0') {
                        printf("   %c   |\t%d\t|\t%d\n", t2[k][l], i + 1, j + 1);

                        run = false;
                    }
                }
            }
        }
    }


    free2DcharTab(t1, t1h);
    t1 = NULL;
    free2DcharTab(t2, t2h);
    t2 = NULL;
    return 0;
}
