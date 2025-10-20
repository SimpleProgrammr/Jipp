
#include <locale.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>

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

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "pl_PL.UTF-8");
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    double a = 0.0, b = 0.0, c = 0.0;
    int ret = -1;

    printf("Program obliczenia trójkątów dla zadania w11\n");
    printf("--------------------------------\n");
    printf("Przykładowy trójkąt\n"
           "        /\\ \n"
           "       /  \\ \n"
           "    a /    \\ b\n"
           "     /      \\ \n"
           "    /________\\ \n"
           "        c\n"
           "\t  a > 0 \n"
           "\t  b > 0 \n"
           "\t  c > 0 \n");
    printf("Precyzja dla '0' to 1e-14\n");
    printf("Zmienne muszą być skończone\n");
    printf("Format dla liczb nie całkowitych: <cyfry>.<cyfry> (inaczej wyrzuci błąd)\n");
    printf("--------------------------------\n");
    printf("Podaj a, b, c rozdzielone tylko SPACJAMI w podanej kolejności:\n");
    ret = scanf("%le%le%le", &a, &b, &c);

    if(ret != 3)
    {
        printf("Błedy w podanych danych.\n");
        printf("Wczytane: a = %e b = %e c = %e\n", a, b, c);

        exit(3);
    }
    clearInputBuffer();
    if (isnan(a) || isinf(a) || isnan(b) || isinf(b) || isnan(c) || isinf(c)) {
        printf("Za duże lub brakujące dane\n");
        my_exit(400);
    }
    if(a < 1e-14 || b < 1e-14 || c < 1e-14)
    {
        printf("To nie będzie trójkąt.\n"
               "A lub B lub C jest < 0\n");
        my_exit(500);
    }
    if (a + b < c || a + c < b || b + c < a) {
        printf("To nie jest trójkąt. Spróbuj ponownie\n");
        my_exit(300);
    }
    if (a + b == c || a + c == b || b + c == a) {
        printf("To jakiś degenerat!\n"
               "To trójkąt zdegenerowany :)\n");

    }

    double p = (a + b + c) / 2;
    double S=sqrt(p*(p-a)*(p-b)*(p-c));
    double R = S / p;

    printf("Pole trójkąta: %le\n", S);
    printf("Promień koła wpisanego w trójkąt: %le\n", R);


    my_exit(0);
};
