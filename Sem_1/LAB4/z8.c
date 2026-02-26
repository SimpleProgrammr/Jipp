#include <conio.h>
#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <windows.h>

void prinf_abc(int a, int b, int c) {
    system("cls");
    printf("a = %d\n", a);
    printf("b = %d\n", b);
    printf("c = %d\n", c);
    printf("Podaj znak: ");
    fflush(stdout);
}

int main() {
    setlocale(LC_ALL, "pl_PL.UTF-8");
    setlocale(LC_NUMERIC, "C");
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int a = 0, b = 0, c = 0;
    char s;
    printf("Podaj znak: ");
    while (true) {
        s = getchar();
        if (s == 'e') {
            printf("Koniec...");
            break;
        }
        if (s == 'a') {
            a++;
            prinf_abc(a, b, c);
            continue;
        }
        if (s == 'b') {
            b++;
            prinf_abc(a, b, c);
            continue;
        }
        if (s == 'c') {
            c++;
            prinf_abc(a, b, c);
        }
    };
}