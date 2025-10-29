#include <math.h>
#include <stdbool.h>
#include <stdio.h>

double f(double);

void clearSTDIN();

int main() {
    FILE *file = NULL;
    file = fopen("z15.txt", "w+");
    if (file == NULL) {
        printf("File could not be opened\n");
        return 404;
    }
    printf("Podaj zakres [a b]: ");
    double a = 0.0, b = 0.0, d = 0.0;
    scanf("%lf%lf", &a, &b);
    clearSTDIN();
    printf("Podaj dokładność: ");
    scanf("%lf", &d);

    fprintf(file, "X\t\t\t|\tf(x)\n");
    printf("X\t\t\t|\tf(x)\n");
    for (double i = a; i <= b; i += d) {
        fprintf(file, "%lf\t|\t%lf\n", i, f(i));
        printf("%lf\t|\t%lf\n", i, f(i));
    }


    fclose(file);
    return 0;
}

double f(double x) {
    return 1 / (x * x + sqrt(1 + 2 * x + 3 * x * x));
}

void clearSTDIN() {
    while (getchar() != '\n');
}