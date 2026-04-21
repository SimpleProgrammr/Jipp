#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>

int main() {
    setlocale(LC_ALL, "pl_PL.UTF-8");
    setlocale(LC_NUMERIC, "C");
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int a = 0, b = 0, c = 0;
    while (true) {
        c = getchar();
        if (c == 'e') {
            printf("No to koniec...");
            break;
        }
    }
}