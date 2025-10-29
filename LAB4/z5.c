#include <stdio.h>

int main() {
    int n = 0;
    int silnia = 1;
    printf("Podaj liczbe: ");
    if (scanf("%d", &n) != 1) return 10;

    for (int i = 1; i <= n; i++) {
        silnia = silnia * i;
    }
    printf("Silnia %d\n", silnia);
}