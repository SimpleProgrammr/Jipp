#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void strJoin(char t1[], char t2[], char *r) {
    for (int i = 0; i < strlen(t1); i++) {
        r[i] = t1[i];
    }
    for (int i = 0; i < strlen(t2); i++) {
        r[i + strlen(t1)] = t2[i];
    }
}


int main() {
    char tekst1[256], tekst2[256];
    printf("Please enter the text 1: ");
    gets(tekst1);
    printf("Please enter the text 2: ");
    gets(tekst2);

    char *tekst3 = calloc(sizeof(char), strlen(tekst1) + strlen(tekst2));
    strJoin(tekst1, tekst2, tekst3);
    printf("Joined texts: %s", tekst3);

    if (tekst3)
        free(tekst3);
    tekst3 = NULL;
}