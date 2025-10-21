#include <math.h>
#include <stdio.h>

void funkcja(const double *x, const double *y, double *z) {
    if (*x * *x + *y * *y <= 1) {
        *z = *x * *x + *y;
        printf("Segment: 1\n");
    } else if (y > x + 5) {
        *z = 2 * *x + *y * *y;
        printf("Segment: 2\n");
    } else {
        *z = 1 / 2.0 * *x * *x + *y;
        printf("Segment: 3\n");
    }
}

int main() {
    double x = 0, y = 0, z = 0;
    int ret = 0;
    printf("Podaj x, y rozdzielone tylko SPACJAMI w podanej kolejności:\n");
    ret = scanf("%le%le", &x, &y);

    if (ret != 2) {
        printf("error");
        return 0;
    }

    funkcja(&x, &y, &z);

    printf("X: %le\nY: %le\nZ: %le\n", x, y, z);
}
