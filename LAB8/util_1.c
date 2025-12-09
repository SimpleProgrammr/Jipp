#include<stdio.h>
#include<stdlib.h>
#define MAX_ERR 5

static char *p[] = {
    "",
    " zle dane",
    " otwarcie pliku",
    " brak pamieci",
    " Usage : ",
    " nieznany ",
};

void Error(int nr, char *str) {
    int k;
    k = nr >= MAX_ERR ? MAX_ERR : nr;
    fprintf(stderr, "Blad(%d) - %s %s\n", nr, p[k], str);
    exit(nr);
}