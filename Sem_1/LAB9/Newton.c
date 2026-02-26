#include <stdio.h>
#include <math.h>

double f(double);

double fdiff(double);

int newton(double *x, int n, double eps, double (*f)(double), double (*fdiff)(double)) {
    double x1;
    int i = 0;
    do {
        x1 = -(*f)(*x) / (*fdiff)(*x);
        *x += x1;
        if (fabs(x1) < eps) return 0;
    } while (i++ < n);
    return 1;
}

/* start 0.5 -> 0 0.8 -> -1.8954 1.0 -> 1.8954 */
int main() {
    double x0 = -10, eps = 0.001;
    int n = 100;
    // printf("podaj:\n przybl. dokl. maks.iter.\n");
    // scanf("%lf %lf %d", &x0,&eps,&n);
    if (!newton(&x0, n, eps, f, fdiff))
        printf("rozwiazanie= %lf wart.= %lf\n", x0, f(x0));
    else
        printf("Brak zbieznosci\n");
}


double f(double x) {
    return sin(x) - .5 * x;
}

double fdiff(double x) {
    return tan(x) - 2 * x;
}