#include <stdio.h>

long fibonachi(long last1, long last2, int max_iteration) {
    if (max_iteration <= 0) return 1;
    long sum = last1 + last2;
    printf("%ld, ", sum);
    return fibonachi(last2, sum, max_iteration - 1);
}

int main() {
    fibonachi(0, 1, 50);
    printf("\n");
}