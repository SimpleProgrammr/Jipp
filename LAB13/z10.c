
#include <math.h>
#include <stdio.h>

long double func(long double x) {
    return x;
}


long double it_sum(long double k, long double n, long double (*func)(long double)) {
    long double sum = 0;
    for (long double i = k; i <= n; i++) {
        sum += func(i);
    }
    return sum;
}

long double rek_sum(long double sum, long double k, long double n, long double (*func)(long double)) {
    if (k > n) {
        return 0;
    }
    long double tmp = sum + func(k);
    return tmp + rek_sum(sum, k + 1, n, func);
}

int main() {
    printf("%Lf\n", it_sum(0, 10, func));
    printf("%Lf\n", rek_sum(0, 0, 10, func));
}
