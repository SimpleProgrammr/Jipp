
#include <locale.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>
// 11. Dane są cztery liczby całkowite a,b,c,d. Znaleźć wśród nich liczbę największą i wydrukować
// jej wartość i pozycję przyjmując, że dla a(pozycja=1), b(pozycja=2) itd. (nie wprowadzać
// zmiennej indeksowanej).

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

    double a = 0.0, b = 0.0, c = 0.0, d = 0.0;
    double arr[4];
    int ret = -1;



    printf("Program obliczenia największej wartości\n");
    printf("Precyzja dla '0' to 1e-14\n");
    printf("Zmienne muszą być skończone\n");
    printf("Format dla liczb nie całkowitych: <cyfry>.<cyfry> (inaczej wyrzuci błąd)\n");
    printf("-----------------------------------------\n");
    printf("Podaj cztery wartości rzeczywiste (a, b, c, d)");
    printf("--------------------------------\n");
    printf("Podaj a, b, c, d rozdzielone tylko SPACJAMI w podanej kolejności:\n");
    ret = scanf("%le%le%le%le", &a, &b, &c, &d);

    if(ret != 4)
    {
        printf("Błedy w podanych danych.\n");
        printf("Wczytane: a = %e b = %e c = %e\n", a, b, c);

        exit(3);
    }
    arr[0] = a;
    arr[1] = b;
    arr[2] = c;
    arr[3] = d;

    clearInputBuffer();

    int index = 0;
    double max = 0;
    for(int i = 0; i < 4; i++) {
        if (arr[i] > max) {
            max = arr[i];
            index = i;
        }
    }

    printf("Największa liczba to %le na pozycji %d[index: %d] (litera: %c)\n", max, index+1, index, (97+index));


    my_exit(0);
};
