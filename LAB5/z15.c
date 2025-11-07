#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int replace(char *, char, char);

int main() {
    char tekst[256];
    char znak = ' ', nznak = ' ';
    printf("Please enter the text: ");
    gets(tekst);
    //fgets(tekst, 256, stdin);
    printf("Please enter old char: ");
    znak = getchar();
    while (getchar() != '\n');
    printf("Please enter new char: ");
    nznak = getchar();

    replace(tekst, znak, nznak);
    printf("%s\n", tekst);
}

int replace(char *txt, char old_c, char new_c) {
    for (int i = 0; txt[i] != '\0'; i++) {
        if (txt[i] == old_c) {
            printf("In text: %s, char '%c' was found on %d index\n", txt, old_c, i);
            txt[i] = new_c;
        }
    }
}
