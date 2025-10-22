#include <float.h>
#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <windows.h>

void funkcja(const double *x, const double *y, double *z) {
    if (*x * *x + *y * *y <= 1) {
        *z = *x * *x + *y;
        printf("Segment: 1\n");
    } else if (y > x + 5) {
        *z = 2 * *x + *y * *y;
        printf("Segment: 2\n");
    } else {
        *z = 1 / 2.0 * *x * *x + *y;
        printf("Segment: 3\n");
    }
}

int main() {
    setlocale(LC_ALL, "pl_PL.UTF-8");
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    double x = 0, y = 0, z = 0;
    int ret = 0;
    printf("Podaj x, y (liczby rzeczywiste) rozdzielone tylko SPACJAMI w podanej kolejności:\n");
    ret = scanf("%le%le", &x, &y);

    if (ret != 2) {
        printf("Błedne dane wejściowe.\n");
        return -1;
    }

    if (isnan(x) || isinf(x) || isnan(y) || isinf(y) || isnan(z) || isinf(z)) {
        printf("Liczba z poza zakresu.\n");
        return -1;
    }

    funkcja(&x, &y, &z);

    printf("X: %le\nY: %le\nZ: %le\n", x, y, z);
}
