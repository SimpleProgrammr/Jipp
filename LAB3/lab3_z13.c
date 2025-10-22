#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <windows.h>

int count = 1;

void hanoi(int N, char A, char B, char C) {
    if (N > 0) {
        hanoi(N - 1, A, C, B);
        printf("Ruch %d: %c -> %c\n", count++, A, B);
        hanoi(N - 1, C, B, A);
    }
}

int main() {
    setlocale(LC_ALL, "pl_PL.UTF-8");
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int N = 0;
    int ret = 0;
    printf("Liczenie wieży hanoi dla N krążków\n");
    printf("Podaj N: ");
    ret = scanf("%d", &N);

    if (ret != 1) {
        printf("Złe argumenty");
        return -1;
    }
    if (N < 1) {
        printf("N musi być liczbą naturalną dodatnią\n");
        return -1;
    }
    hanoi(N, 'A', 'B', 'C');
    printf("Koniec\n");
}
