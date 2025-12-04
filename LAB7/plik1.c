//*************************PLIK_1*****************************
#include <stdio.h>

double fun1(); //Deklaracja Funkcji, dostępna wszędzie
static int fun2(); //DF, Dostępna tylko w pliku 1
extern int fun3(); //DF, Definicja znajduje się w osobnym pliku
static int c = 5;
//Deklaracja zmiennej, dostępna i widoczna tylko w pliku 1, zapisana do pliku wykowywalnego, Żyje tak długo jak program
double a, b = 10; //DZ, DW, zyje tak długo jak plik 1 jest wykonywany
char *xx[] = {"mama", "tato", "stryjek", (char *) 0}; //DZ, DW, zyje tak długo jak plik 1 jest wykonywany
double aa[] = {1, 2, 3, 4, 5, 6}; //DZ, DW, zyje tak długo jak plik 1 jest wykonywany
int main() {
    double x, y = 5; //DZ, Lokalna, do końca bloku, x=garbage, y=5
    int i, j, k; //DZ, Lokalna, do końca bloku, i j k = garbage
    static double aa[] = {11, 12, 13, 14, 15, 16};
    printf("%lf %lf \n", aa[0], aa[1]);
    j = fun2();
    k = fun3();
    printf("j = %d, k = %d\n", j, k);
}

double fun1(int x, int y) {
    static char *xx[] = {"pies", "kot", "mysz", (char *) 0}; // DZ, lokalna, żyje do zakończenia programu
    int i = 0; //DZ, lokalna, do końca bloku
    i++;
}

char *xxxx[] = {"zima", "wiosna", "lato", (char *) 0};
//DZ, Dostępna tylko poniżej, zyje tak długo jak plik 1 jest wykonywany
static int fun2() {
    static int k = 0; //DZ, lokalna, zyje do końca programu
    puts("ppp fun2");
    k++;
    return (k);
}
