#include <math.h>
#include <stdio.h>


void obliczKolo(double r, double *w1, double *w2);

int main() {
    double r = 0.0;
    double pole = 0.0, obw = 0.0;
    int ret = 0;

    printf("Program obliczenia trójkątów dla zadania w11\n");
    printf("--------------------------------------------------------------\n");
    printf("Przykładowy trójkąt\n"
        "      _______\n"
        "     / r    \\      \n"
        "     |<---    |     \n"
        "     \\______/      \n"
        "\t  a > 0 \n");
    printf("Precyzja dla '0' to 1e-14\n");
    printf("Zmienne muszą być skończone\n");
    printf("Format dla liczb nie całkowitych: <cyfry>.<cyfry> (inaczej wyrzuci błąd)\n");
    printf("--------------------------------------------------------------\n");
    printf("Podaj r:\n");
    ret = scanf("%le", &r);

    if (ret != 1) {
        printf("error");
        return 0;
    }

    obliczKolo(r, &pole, &obw);

    printf("Promien: %.3lf\n", r);
    printf("Obwod: %.3lf\n", obw);
    printf("Pole: %.3lf\n", pole);
}

void obliczKolo(double r, double *w1, double *w2) {
    *w1 = r * r * M_PI;
    *w2 = 2 * r * M_PI;
}