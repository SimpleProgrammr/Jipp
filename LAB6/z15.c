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
    int loadedLines = 0, linesInTab = 10;

    char **text = allocate2DcharTab(linesInTab, MAX_CHARS_INLINE);

    char bufor[MAX_CHARS_INLINE];
    while (fgets(bufor, MAX_CHARS_INLINE, file)) {
        if (loadedLines >= linesInTab) {
            linesInTab += 5;
            char **tmp1 = (char **) realloc(text, (linesInTab) * sizeof(char *));
            if (tmp1 == NULL) {
                printf("Memory allocation failed\n");
                free(text);
                text = NULL;
                fclose(file);
                file = NULL;
                exit(1);
            }
            text = tmp1;
        }
        unsigned long len = strlen(bufor);
        bufor[len - 1] = '\0';
        if ((text[loadedLines] = (char *) calloc(len, sizeof(char *))) == (char *) NULL) {
            printf("Memory allocation error\n");
            exit(3);
        }
        strcpy(text[loadedLines], bufor);
        printf("Line %d: %s\n", loadedLines, text[loadedLines]);
        loadedLines++;
    }

    int line1 = 0, line2 = 0;
    printf("File loaded.\n");
    printf("Enter 1st line: ");
    scanf("%d", &line1);
    printf("Enter 2nd line: ");
    scanf("%d", &line2);

    if (line1 > linesInTab || line2 > linesInTab || line1 < 0 || line2 < 0) {
        printf("Wrong input\n");
        fclose(file);
        file = NULL;
        free(text);
        text = NULL;
        return 10;
    }

    char *tmp = text[line1];
    text[line1] = text[line2];
    text[line2] = tmp;

    for (int n = 0; n < loadedLines; n++) {
        printf("%d\t|\t%s", n, text[n]);
        printf("\n");
    }

    fclose(file);
    file = NULL;
    free(text);
    text = NULL;
    return 0;
}
