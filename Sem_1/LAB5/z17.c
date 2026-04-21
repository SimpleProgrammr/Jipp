#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void strJoin(char t1[], char t2[], int startIndex, char *r) {
    for (int i = 0; i < strlen(t1); i++) {
        r[i] = t1[i];
    }
    for (int i = 0; i < strlen(r); i++) {
        r[i + strlen(t1)] = t2[i + startIndex];
    }
}


int main() {
    char tekst1[256], tekst2[256];
    int sInd = 0;
    printf("Please enter the text 1: ");
    gets(tekst1);
    printf("Please enter the text 2: ");
    gets(tekst2);
    printf("Please enter the start index(0 <= index < %d): ", strlen(tekst2));
    if (scanf("%d", &sInd) != 1 || sInd >= strlen(tekst2) || sInd < 0) {
        printf("Error!");
        return 0;
    }

    char *tekst3 = calloc(strlen(tekst1) + strlen(tekst2) - sInd, sizeof(char));
    strJoin(tekst1, tekst2, sInd, tekst3);
    printf("Joined texts: %s", tekst3);

    if (tekst3)
        free(tekst3);
    tekst3 = NULL;
}