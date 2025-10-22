#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <windows.h>

int hanoi(int N) {
    if (N != 0) {
        printf("N = %d\n", N);
        return N + hanoi(N - 1);
    }
    return 0;
}


int main() {
    setlocale(LC_ALL, "pl_PL.UTF-8");
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int N = 0;
    int ret = 0;
    printf("Suma kolejnych N liczb naturalnych dodatnich za pomocą rekurencji\n");
    printf("Podaj N: ");
    ret = scanf("%d", &N);

    if (ret != 1 || N < 0) {
        printf("Błedne dane wejściowe");
        return -1;
    }


    printf("Suma N liczb: %d", hanoi(N));
}
