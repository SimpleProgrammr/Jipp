#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double Re;
    double Im;
} COMPLEX;

typedef struct {
    double a;
    double b;
    double c;
} SQUARE_EQU;

void wynikiZespolone(SQUARE_EQU eq, COMPLEX *x1, COMPLEX *x2) {

    x1->Re = - ( eq.b / (2*eq.a));
    x1->Im = sqrt(fabs( pow(x1->Re,2) - eq.c/eq.a ));
    x2->Re = x1->Re;
    x2->Im = -x1->Im;
}

void wynikD0(SQUARE_EQU eq) {
    double x = (-eq.b)/(2.0*eq.a);
    printf("Rownanie kwadratowe: %le *X^2 + %le *X + %le = 0\n\n", eq.a, eq.b, eq.c);
    printf("Pierwiastek: x1 = %e\n", x);
    printf("---------------------------------------------------------");
    exit(1);
}

void wynikiRE(SQUARE_EQU eq) {
    double p1, p2, x1, x2;
    double D = eq.b*eq.b-4*eq.a*eq.c;
    p1 = -eq.b/(2.0*eq.a);
    p2 = sqrt(D)/(2.0*eq.a);
    x1 = p1+p2;
    x2 = p1-p2;
    printf("Rownanie kwadratowe: %le *X^2 + %le *X + %le = 0\n\n", eq.a, eq.b, eq.c);
    printf("Pierwiastki: x1 = %e x2 = %e\n", x1, x2);
    printf("---------------------------------------------------------");
}

int main() {
    SQUARE_EQU quadratic_equation;
    quadratic_equation.a = 1;
    quadratic_equation.b = 6;
    quadratic_equation.c = 3;

     COMPLEX x1, x2;

    double Delta = quadratic_equation.b*quadratic_equation.b-4*quadratic_equation.a*quadratic_equation.c;
    if (Delta < 0) {
        wynikiZespolone(quadratic_equation, &x1, &x2 );

        printf("Rownanie kwadratowe: %le *X^2 + %le *X + %le = 0\n\n", quadratic_equation.a, quadratic_equation.b, quadratic_equation.c);
        printf("Pierwiastek C1: %e + %e i\n", x1.Re, x1.Im);
        printf("Pierwiastek C2: %e + %e i\n", x2.Re, x2.Im);
        printf("---------------------------------------------------------");
    }else if (Delta == 0) {
        wynikD0(quadratic_equation);
    }else {
        wynikiRE(quadratic_equation);
    }
}
