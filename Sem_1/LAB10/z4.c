#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "z4-data.h"

int main() {
    struct num8 n8;

    int num = 0;
    printf("Hello, enter 1st value from 0 to 255: ");
    scanf("%d", &num);
    if (num < 0 || num > 255) {
        perror("Error, wrong input. Number outside the range");
    }
    n8.a = num;

    printf("Enter 2nd value from 0 to 255: ");
    scanf("%d", &num);
    if (num < 0 || num > 255) {
        perror("Error, wrong input. Number outside the range");
    }
    n8.b = num;

    union num16 n16;
    n16.st8 = n8;

    printf(
        "\nUnion values\n"
        "Int val: %i\n"
        "Hex val: 0x%x\n"
        "Struct value\n",
        n16.st8, n16.i16
    );
}