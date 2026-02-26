#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <windows.h>

int main() {
    setlocale(LC_ALL, "pl_PL.UTF-8");
    setlocale(LC_NUMERIC, "C");
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int a = 0, b = 0, c = 0;
    int l = 0;
    char s;
    while (true) {
        s = getchar();
        if (s == '\n')
            continue;
        if (s == 'e') {
            printf("Koniec...");
            break;
        }
        if (s == 'a') {
            a++;
            goto skok;
        }
        if (s == 'b') {
            b++;
            goto skok;
        }
        if (s == 'c') {
            c++;
            goto skok;
        }
    skok:
        l++;
        system("cls");
        printf("a = %d\n", a);
        printf("b = %d\n", b);
        printf("c = %d\n", c);
        printf("l = %d\n\n", l);
        fflush(stdout);
    };
}