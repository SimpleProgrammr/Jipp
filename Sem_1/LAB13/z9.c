#include <math.h>
#include <stdio.h>
#include <stdbool.h>

bool it_isPrime(long n) {
    for (long i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

bool ret_isPrime(long n) {
    static long i = 0;
    if (i == 0)
        i = n - 1;
    if (i <= 2)
        return true;
    if (n % i == 0)
        return false;
    i--;
    return ret_isPrime(n);
}

int main(int argc, char *argv[]) {
    printf("%d\n", it_isPrime(69));
    printf("%d\n", ret_isPrime(69));
}