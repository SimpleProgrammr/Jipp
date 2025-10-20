
#include <locale.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>


void my_exit(int code) {
    printf("Kod zakończenia: %d\nNaciśnij Ctrl+Z żeby zakończyć\n", code);
    int c;
    while((c=getchar()) != EOF) {
        putchar(c);
    }
    exit(code);
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void w9Obliczenia(double x, double y, double z, int k, int m) {
    double w1 = pow(x/(y*z), 1.0/3.0) * log(pow(x,2.0)+pow(y,2.0));
    double w2 = sin((double)k*(x/2.0))*cos((double)m*y)
    + y * exp(2.0*x-1.0);
    double w3 = (double)fabs(x/((2*pow(y,2.0) +1)))
    + sqrt(y/(pow(z,2.0)+3))
    + 5*pow(y+z,3);
    double w4 = x/(y*z) * pow(z+1, 1.0/3.0)+ pow(pow(x,2.0)+pow(z,2.0) +1.0, 1.0/(double)k) - fabs(y);
    double w5 = 1/(sqrt(pow(x,2.0)+pow(y,2.0) + pow(k,2.0))) + (1/x)*sin((double)k*y) ;

    printf("w1 = %.8lf\n", w1);
    printf("w2 = %.8lf\n", w2);
    printf("w3 = %.8lf\n", w3);
    printf("w4 = %.8lf\n", w4);
    printf("w5 = %.8lf\n", w5);
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "pl_PL.UTF-8");
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    double x = 0.0, y = 0.0, z = 0.0, kd,md;
    int k = 0, m = 0;
    int ret = -1;

    printf("Program obliczeń dla zadania w9\n");
    printf("-------------------- Warunki zmiennych ------------------------------\n");
    printf("x należy do R \\{0, 1/2}\n"
           "y należy do R \\ {0}\n"
           "z należy do R \\ {0}\n"
           "k należy do Z \\ {0}\n"
           "m należy do Z\n");
           printf("Precyzja dla '0' to 1e-14\n");
           printf("Zmienne muszą być skończone\n");
           printf("Format dla liczb nie całkowitych: <cyfry>.<cyfry> (inaczej wyrzuci błąd)\n");
    printf("---------------------------------------------------------------------\n");
    printf("Podaj (rzeczywiste) x, y, z oraz (całkowite) k, m rozdzielone tylko SPACJAMI w podanej kolejności:\n");
    ret = scanf("%le%le%le%le%le", &x, &y, &z, &kd, &md);
    clearInputBuffer();
    if(ret != 5)
    {
        printf("Błedne dane wejściowe\n");
        printf("Wczytane: x = %e y = %e z = %e\n k = %d m = %d\n", x, y, z, k, m);
        my_exit(500);
    }

    if (kd - round(kd) != 0.0 || md - round(md) != 0.0) {
        printf("Dane k i m zostały powinny być całkowite\n");
        my_exit(500);
    }

    k = kd;
    m = md;
    if(fabs(x) < 1e-14 || fabs(y) < 1e-14 || fabs(z) < 1e-14 || k == 0 || x == 0.5)
    {

        printf("Któraś z danych jest spoza zakresu!!!\n");
        printf("Wczytane: x = %e y = %e z = %e\n k = %d m = %d\n", x, y, z, k, m);

        my_exit(400);
    }

    if (isnan(x) || isinf(x) || isnan(y) || isinf(y) || isnan(z) || isinf(z) ) {
        printf("Za duże lub brakujące dane\n");
        my_exit(400);
    }

    w9Obliczenia(x, y, z, k, m);
    my_exit(0);

}