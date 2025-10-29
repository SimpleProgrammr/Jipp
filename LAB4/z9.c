#include <stdbool.h>
#include <stdio.h>

int main() {
    int a = 0, b = 0, c = 0;
    int l = 0;
    char s;
    while (true) {
        s = getchar();
        if (s == 'e')
            break;
        if (s == 'a') {
            a++;
            continue;
        }
        if (s == 'b') {
            b++;
            continue;
        }
        if (s == 'c') {
            c++;
            goto skok;
        }
    skok:
        l++;
    };
    printf("a = %d\n", a);
    printf("b = %d\n", b);
    printf("c = %d\n", c);
    printf("l = %d\n", l);
}