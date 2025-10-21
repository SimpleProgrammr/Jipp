#include <math.h>
#include <stdio.h>

void zamien(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

int main() {
    int x = 0, y = 0;
    int ret = 0;
    printf("Podaj x, y rozdzielone tylko SPACJAMI w podanej kolejności:\n");
    ret = scanf("%d%d1 ", &x, &y);

    if (ret != 2) {
        printf("error");
        return 0;
    }
    printf("x: %d\ny: %d\n", x, y);
    zamien(&x, &y);
    printf("x: %d\ny: %d\n", x, y);
}