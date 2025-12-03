#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fillTabWithRand(int *tab, int size) {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        tab[i] = rand() % 100;
        printf("tab[%d] = %d\n", i, tab[i]);
    }
}

int findMaxInTab(int *tab, int size, int *loc) {
    int max = 0;
    for (int i = 0; i < size; i++) {
        if (tab[i] > max) {
            max = tab[i];
            *loc = i;
        }
    }
    printf("max = %d [%d]\n", max, *loc);
    return max;
}

int main() {
    int size = 0;
    printf("Enter the size: ");
    scanf("%d", &size);
    int *tab = (int *) calloc((unsigned) size, sizeof(int));
    if (tab == NULL) {
        printf("Error allocating memory");
        return 1;
    }
    fillTabWithRand(tab, size);
    int locOfMax = 0;
    int max = findMaxInTab(tab, size, &locOfMax);


    free(tab);
    tab = NULL;
}