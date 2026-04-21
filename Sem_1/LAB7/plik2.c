//*************************PLIK_2*****************************
#include <stdio.h>

extern double fun1(); //DF, Def w innym pliku
static double fun2(); //DF, Widoczna tylko w tym pliku
int fun3(); //DF, widoczna wszędzie
static char *c[] = {"slon", "lew", "pantera", (char *) 0}; //DZ, widoczna tylko w pliku, inicjowana podczas kompilacji
extern char *xx[]; //DZ, Deklarowana w innym pliku

static double fun2() {
    static char *zz[] = {"krzeslo", "szafa", "tapczan", (char *) 0}; // DZ, IPK, Widoczna tylko w bloku
    puts("qqq fun2");
    return ((double) 2.0);
}

int fun3() {
    double ff; //DZ, Lokalna, nie zainicjiowana, śmieci
    puts("qqq fun3");
    ff = fun2();
    return (5);
}