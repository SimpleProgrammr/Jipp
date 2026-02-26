#include <stdio.h>

int main() {
    int n = 0;

    printf("Podaj liczbe: ");
    if (scanf("%d", &n) != 1) return 10;

    while (n--) {
        printf("%d.\tHello world\n", n + 1);
    }
    return 0;
}