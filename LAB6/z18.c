#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS_INLINE 256

char **allocate2DcharTab(int lines, int chars) {
    char **tab = (char **) calloc(lines, sizeof(char *));
    if (tab == NULL) {
        printf("Memory allocation failed\n");
        exit(3);
    }

    for (int i = 0; i < lines; i++) {
        tab[i] = (char *) calloc(chars + 1, sizeof(char));
        if (tab[i] == NULL) {
            printf("Memory allocation failed\n");
            exit(3);
        }
    }

    return tab;
}

int *allocate1DIntTab(int lines) {
    int *tab = (int *) calloc(lines, sizeof(int));
    if (tab == NULL) {
        printf("Memory allocation failed\n");
        exit(3);
    }

    return tab;
}

int getWordsAmount(const char *str, char spacer) {
    int amount = 0;
    if (strlen(str) == 0)
        return 0;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == spacer) {
            if (i != 0 || i != strlen(str) - 1) {
                if (str[i - 1] != spacer) {
                    amount++;
                }
            }
        }
    }
    if (str[strlen(str) - 1] != spacer)
        amount++;
    return amount;
}

void printWordAtIndex(const char *str, char spacer, int index) {
    int amount = 1;
    if (strlen(str) == 0)
        return;
    for (int i = 0; i < strlen(str); i++) {
        if (amount == index) {
            if (str[i] != spacer) {
                printf("%c", str[i]);
            }
        }
        if (str[i] == spacer) {
            if (i != 0 || i != strlen(str) - 1) {
                if (str[i - 1] != spacer) {
                    amount++;
                }
            }
        }
    }

    printf("\n");
}

int main() {
    FILE *file = NULL;
    file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("File not found\n");
        return 1;
    }
    int loadedLines = 0, linesInTab = 10;

    char **text = allocate2DcharTab(linesInTab, MAX_CHARS_INLINE);
    int *wordsInLine = allocate1DIntTab(linesInTab);

    char bufor[MAX_CHARS_INLINE];
    while (fgets(bufor, MAX_CHARS_INLINE, file)) {
        if (loadedLines >= linesInTab) {
            linesInTab += 5;
            char **tmp1 = (char **) realloc(text, (linesInTab) * sizeof(char *));
            int *tmp2 = (int *) realloc(wordsInLine, (linesInTab) * sizeof(int *));
            if (tmp1 == NULL || tmp2 == NULL) {
                printf("Memory allocation failed\n");
                free(text);
                text = NULL;
                free(wordsInLine);
                wordsInLine = NULL;
                fclose(file);
                file = NULL;
                exit(1);
            }
            text = tmp1;
            wordsInLine = tmp2;
        }

        unsigned long len = strlen(bufor);
        bufor[len - 1] = '\0';
        if ((text[loadedLines] = (char *) calloc(len, sizeof(char *))) == (char *) NULL) {
            printf("Memory allocation error\n");
            exit(3);
        }
        strcpy(text[loadedLines], bufor);

        wordsInLine[loadedLines] = getWordsAmount(bufor, ':');

        printf("Line %d: %s\n", loadedLines, text[loadedLines]);
        loadedLines++;
    }

    int lineTarget = 0;
    printf("Enter line: ");
    scanf("%d", &lineTarget);
    if (lineTarget < 0 || lineTarget > linesInTab) {
        printf("Line %d is out of bounds\n", lineTarget);
        free(text);
        text = NULL;
        free(wordsInLine);
        wordsInLine = NULL;
        fclose(file);
        file = NULL;
        exit(3);
    }

    int wordNumber = 0;
    printf("Enter word number (1 < %d): ", wordsInLine[lineTarget]);
    scanf("%d", &wordNumber);
    if (wordNumber < 1 || wordNumber > linesInTab) {
        printf("Word %d is out of bounds\n", wordNumber);
        free(text);
        text = NULL;
        free(wordsInLine);
        wordsInLine = NULL;
        fclose(file);
        file = NULL;
        exit(3);
    }
    printWordAtIndex(text[lineTarget], ':', wordNumber);


    fclose(file);
    file = NULL;
    free(text);
    text = NULL;
    free(wordsInLine);
    wordsInLine = NULL;
    exit(0);
}
