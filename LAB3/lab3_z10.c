#include <locale.h>
#include <math.h>
#include <windows.h>
#include <stdio.h>

void zamien(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

int main() {
    setlocale(LC_ALL, "pl_PL.UTF-8");
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int x = 0, y = 0;
    int ret = 0;
    printf("Zamienianie miejscami za pomocą POINTER-ów\n");
    printf("Podaj x, y rozdzielone tylko SPACJAMI w podanej kolejności:\n");
    ret = scanf("%d%d1", &x, &y);

    if (ret != 2) {
        printf("Błędne dane wejściowe");
        return -1;
    }

    printf("x: %d\ny: %d\n", x, y);
    zamien(&x, &y);
    printf("Zamiana!!!\n");
    printf("x: %d\ny: %d\n", x, y);
}