#include <locale.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <windows.h>

double ff(double);

void clearSTDIN();

int main() {
    setlocale(LC_ALL, "pl_PL.UTF-8");
    setlocale(LC_NUMERIC, "C");
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    printf("Podaj zakres [a b]: ");
    double a = 0.0, b = 0.0, d = 0.0;
    if (scanf("%lf%lf", &a, &b) != 2) {
        fprintf(stderr, "Błędne dane wejściowe\n");
        return 404;
    }
    clearSTDIN();
    printf("Podaj wielkość kroku: ");
    if (scanf("%lf", &d) != 1) {
        fprintf(stderr, "Błędne dane wejściowe\n");
        return 404;
    };

    FILE *file = NULL;
    file = fopen("z15.txt", "w+");
    if (file == NULL) {
        printf("Błąd otwarcia pliku...\n");
        return 404;
    }

    fprintf(file, "X\t\t\t|\tf(x)\n");
    printf("X\t\t\t|\tf(x)\n");
    for (double i = a; i <= b; i += d) {
        fprintf(file, "\t%10.2lf\t\t%15.4lf\n", i, ff(i));
        printf("\t%10.2lf\t\t%15.4lf\n", i, ff(i));
    }
    fclose(file);
    return 0;
}

double ff(double x) {
    return 1 / (x * x + sqrt(1 + 2 * x + 3 * x * x));
}

void clearSTDIN() {
    while (getchar() != '\n');
}