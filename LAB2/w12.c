// 12. Napisać program, który będzie obliczał pole powierzchni oraz obwód takich figur jak:
// trójkąt, kwadrat, prostokąt, koło. Dla trójkąta sprawdzić warunek trójkąta, dla wszystkich figur
// wprowadzić zabezpieczenia uniemożliwiające podanie przez użytkownika wartości
// niepoprawnych (np. ujemnych).
// Obliczenie pola kwadratu, obwodu kwadratu itd. dla wszystkich figur zapisać w osobnych
// funkcjach, które kolejno będą wywoływane w main().

#include <locale.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>

void my_exit(int code);

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void trojkat(double a, double b, double c) {
    if(a < 1e-14 || b < 1e-14 || c < 1e-14)
    {
        printf("To nie będzie trójkąt.\n"
               "A lub B lub C jest <= 0\n");

        return;
    }
    if (a + b < c || a + c < b || b + c < a) {
        printf("To nie jest trójkąt. Spróbuj ponownie\n");
        return;
    }
    if (a + b == c || a + c == b || b + c == a) {
        printf("To jakiś degenerat!\n"
               "To trójkąt zdegenerowany :)\n");
    }

    double p = (a + b + c) / 2;
    double S=sqrt(p*(p-a)*(p-b)*(p-c));
    double obw = a+b+c;

    printf("Pole trójkąta: %le\n", S);
    printf("Obwód trójkąta: %le\n", obw);
}

void prostokat(double a, double b) {
    if(a < 1e-14 || b < 1e-14)
    {
        printf("To nie będzie prostokąt.\n"
               "A lub B <= 0\n");
        return;
    }

    printf("Pole prostokąta: %le\n", a*b);
    printf("Obwód prostokąta: %le\n", 2*a+2*b);
}

void kolo (double r) {
    if(r < 1e-14 )
    {
        printf("To nie będzie koło.\n"
               "A Powinno być większe od 0\n");
        return;
    }
    double pi = acos(-1);
    printf("Pole koła: %le\n", pi*pow(r,2));
    printf("Obwód koła: %le\n", 2*pi*r);
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
    printf("--------------------------------------------------------------\n");
    printf("Przykładowy trójkąt\n"
           "        /\\            _____________            ______      \n"
           "       /  \\          |             |          / a    \\      \n"
           "    a /    \\ b       |             | b       |<---    |     \n"
           "     /      \\        |             |          \\______/      \n"
           "    /________\\       |_____________|                       \n"
           "        c                    a                              \n"
           "\t  a > 0 \n"
           "\t  b > 0 \n"
           "\t  c > 0 \n");
    printf("Precyzja dla '0' to 1e-14\n");
    printf("Zmienne muszą być skończone\n");
    printf("Format dla liczb nie całkowitych: <cyfry>.<cyfry> (inaczej wyrzuci błąd)\n");
    printf("--------------------------------------------------------------\n");
    printf("Podaj a, b, c rozdzielone tylko SPACJAMI w podanej kolejności:\n");
    ret = scanf("%le%le%le", &a, &b, &c);

    if(ret != 3)
    {
        printf("Błedy w podanych danych.\n");
        printf("Wczytane: a = %e b = %e c = %e\n", a, b, c);

        my_exit(3);
    }
    clearInputBuffer();
    if (isnan(a) || isinf(a) || isnan(b) || isinf(b) || isnan(c) || isinf(c)) {
        printf("Za duże lub brakujące dane\n");
        my_exit(400);
    }

    printf("Trójkąt:\n");
    trojkat(a,b,c);

    if (a == b)
        printf("Kwadrat:\n");
    else
        printf("Prostokąt:\n");
    prostokat(a,b);
    printf("Koło:\n");
    kolo(a);


    my_exit(0);
};
