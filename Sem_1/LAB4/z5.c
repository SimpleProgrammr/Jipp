#include <locale.h>
#include <stdio.h>
#include <windows.h>

int main() {
    setlocale(LC_ALL, "pl_PL.UTF-8");
    setlocale(LC_NUMERIC, "C");
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int n = 0;
    int silnia = 1;
    printf("Podaj liczbe całkowitą (części dziesiętnę oraz znaki po ',' lub '.' będą ignorowane): ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Błędne dane wejściowe.\n");
        return 10;
    };

    for (int i = 1; i <= n; i++) {
        silnia = silnia * i;
    }
    printf("Silnia %d\n", silnia);
}