#include <stdio.h>

long fibonachi(long last1, long last2, int max_iteration) {
    if (max_iteration <= 0) return last2;
    return fibonachi(last2, last1 + last2, max_iteration - 1);
}

int main() {
    printf("%ld\n", fibonachi(0, 1, 5));
}