#include <stdio.h>
#include <stdlib.h>

int replace(char *, char);

int main() {
    char tekst[256];
    char znak = ' ';
    printf("Please enter the text: ");
    gets(tekst);
    //fgets(tekst, 256, stdin);
    printf("Please enter char: ");
    znak = getchar();

    replace(tekst, znak);
}

int replace(char *txt, char c) {
    for (int i = 0; txt[i] != '\n'; i++) {
        if (txt[i] == c)
            printf("In text: %s, char '%c' was found on %d index\n", txt, c, i);
    }
}
