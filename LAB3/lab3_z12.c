#include <math.h>
#include <stdio.h>

int sumOfN(int N) {
}


int main() {
    int N = 0;
    int ret = 0;
    printf("Suma kolejnych N liczb naturalnych za pomocą rekurencji\n");
    printf("Podaj N:\n");
    ret = scanf("%d ", &N);

    if (ret != 1) {
        printf("error");
        return 0;
    }
}