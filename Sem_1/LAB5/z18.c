#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int rotare(char *txt) {
    char *tmp = (char *) calloc(strlen(txt), sizeof(char));
    for (int i = 0; i < strlen(txt); i++) {
        for (int j = 0; j < strlen(txt); j++) {
            tmp[j] = txt[(j + i) % strlen(txt)];
        }
        printf("%d.\t%s\n", i, tmp);
    }
    if (tmp)
        free(tmp);
    tmp = NULL;
}

int main() {
    char tekst[256];
    printf("Please enter the text: ");
    gets(tekst);


    rotare(tekst);
}