#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS_INLINE 256

unsigned char znaki[] = {
    'a', 0xB1, 'b', 'c', 0xE6, 'd', 'e', 0xEA, 'f', 'g', 'h', 'i', 'j', 'k', 'l', 0xB3, 'm', 'n', 0xF1, 'o', 0xF3, 'p',
    'q', 'r', 's', 0x9C, 't', 'u', 'v', 'w', 'x', 'y', 'z', 0x9F, 0xBC,
    'A', 0xA0, 'B', 'C', 0xC6, 'D', 'E', 0xCA, 'F', 'G', 'H', 'I', 'J', 'K', 'L', 0xA3, 'M', 'N', 0xD1, 'O', 0xD3, 'P',
    'Q', 'R', 'S', 0x8C, 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 0x8F, 0xAC,
    ' ', '.', ',', '?', ':', '-', '/', '(', ')', '&', '@', '!',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    '\0'
};

const char *morse[] = {
    ".-", ".-.-", "-...", "-.-.", "-.-.-", "--.--", ".", "..-.", "..-.", "--.", "....", "..", ".---", "-.-", ".-..",
    ".-..-", "--", "-.", "-..-.", "---", "---.", ".--.", "--.-", ".-.", "...", "-.-...", "-", "..-", "...-", ".--",
    "-..-", "-.--", "--..", "--..-", "--..-",
    ".-", ".-.-", "-...", "-.-.", "-.-.-", "--.--", ".", "..-.", "..-.", "--.", "....", "..", ".---", "-.-", ".-..",
    ".-..-", "--", "-.", "-..-.", "---", "---.", ".--.", "--.-", ".-.", "...", "-.-...", "-", "..-", "...-", ".--",
    "-..-", "-.--", "--..", "--..-", "--..-",
    "/", ".-.-.-", "--..--", "..--..", "---...", "-....-", "-..-.-", "-.--.-", "-.--.-", ".-...", ".--.-.", "-.-.--",
    "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.",
    NULL
};


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
    int amount = 1;
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

void translateToMorse(const char *str) {
    for (int i = 0; i < strlen(str); i++) {
        unsigned char c = str[i];
        for (int j = 0; j < 101; j++) {
            if (c == znaki[j])
                printf("%s ", morse[j]);
        }
    }
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

        printf("Line %d: %s     ->     ", loadedLines, text[loadedLines]);
        translateToMorse(text[loadedLines]);
        printf("\n");
        loadedLines++;
    }

    fclose(file);
    file = NULL;
    free(text);
    text = NULL;
    exit(0);
}