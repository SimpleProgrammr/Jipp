
#include <locale.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void my_exit(int code) {
    printf("Kod zakończenia: %d\nNaciśnij Ctrl+Z żeby zakończyć\n", code);
    int c;
    while((c=getchar()) != EOF) {
        putchar(c);
    }
    exit(code);
}

double pr_round(double x, unsigned int digits) {
    double fac = pow(10, digits);
    return round(x*fac)/fac;
}

void wynikiZespolone(double a, double b, double c) {

    double r1 = - ( b / (2*a));
    double u1 = sqrt(fabs( pow(r1,2) - c/a ));
    double r2 = r1;
    double u2 = -u1;

    printf("Rownanie kwadratowe: %le *X^2 + %le *X + %le = 0\n\n", a, b, c);
    printf("Pierwiastek C1: %e + %e i\n", r1, u1);
    printf("Pierwiastek C2: %e + %e i\n", r2, u2);
    printf("---------------------------------------------------------");

}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "pl_PL.UTF-8");

    double a = 0.0, b = 0.0, c = 0.0;
    int ret = -1;

    printf("Program obliczenia rzeczywistych pierwiastkow rownania kwadratowego\n");
    printf("-------------------- a*x^2+b*x+c = 0 ------------------------------\n\n");
    printf("Precyzja dla '0' to 1e-6\n");
    printf("Zmienne muszą być skończone\n");
    printf("Format dla liczb nie całkowitych: <cyfry>,<cyfry> (inaczej wyrzuci błąd)\n");
    printf("Podaj a,b,c\n");
    ret = scanf("%le%le%le", &a, &b, &c);

    if(ret != 3)
    {
        printf("Blad przy wczytaniu\n");
        printf("Wczytane: a = %e b = %e c = %e\n", a, b, c);

        exit(3);
    }

    if (isnan(a) || isinf(a) || isnan(b) || isinf(b) || isnan(c) || isinf(c)) {
        printf("Za duże lub brakujące dane\n");
        my_exit(400);
    }

    if(fabs(a) < 1e-6)
    {
        printf("To nie jest rownanie kwadratowe: a = 0.\n");

        my_exit(500);
    }

    double D = -1.0;
    D = b*b-4.0*a*c;
    if(D < 0.0)
    {
        wynikiZespolone(a,b,c);
        return 0;
    }
    if (D == 0.0) {
        double x = (-b)/(2.0*a);
        printf("Rownanie kwadratowe: %le *X^2 + %le *X + %le = 0\n\n", a, b, c);
        printf("Pierwiastek: x1 = %e\n", x);
        printf("---------------------------------------------------------");
        exit(1);
    }

    double p1, p2, x1, x2;
    p1 = -b/(2.0*a);
    p2 = sqrt(D)/(2.0*a);
    x1 = p1+p2;
    x2 = p1-p2;
    printf("Rownanie kwadratowe: %le *X^2 + %le *X + %le = 0\n\n", a, b, c);
    printf("Pierwiastki: x1 = %e x2 = %e\n", x1, x2);
    printf("---------------------------------------------------------");


    my_exit(0);

}

