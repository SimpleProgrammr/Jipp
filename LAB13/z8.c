#include <stdio.h>
#include <stdlib.h>

long it_pow(long n, long power) {
    if (power <= 0) return 1;
    long ret = n;
    for (long i = 2; i <= power; i++) {
        ret *= n;
    }
    return ret;
}

long rek_pow(long n, long power) {
    if (power <= 0) return 1;
    if (power == 1) return n;
    return n * rek_pow(n, power - 1);
}

int main() {
    printf("%ld\n", rek_pow(2, 5));
    printf("%ld\n", it_pow(2, 5));
}