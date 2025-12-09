#include <stdio.h>

typedef struct {
    char imie[100];
    char nazwisko[100];
    int rok;
    char adres[100];
    double stypendium;
} STUDENT;

void swap(STUDENT *a, STUDENT *b) {
    STUDENT temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void sort(STUDENT st[], int size) {
    int swapped;
    do {
        swapped = 0;
        for (int j = 0; j < size - 1; j++) {
            if (st[j].stypendium < st[j + 1].stypendium) {
                swap(&st[j], &st[j + 1]);
                swapped++;
            }
        }
    } while (swapped != 0);

    for (int i = 0; i < size; i++) {
        printf("%s %s %d %s %lf\n", st[i].imie, st[i].nazwisko, st[i].rok, st[i].adres, st[i].stypendium);
    }
}

int main() {
    FILE *f = fopen("student.txt", "r");
    STUDENT st[100];
    int st_loaded = 0;
    while (st_loaded < 100) {
        fscanf(f, "%s %s %d %s %lf", st[st_loaded].imie, st[st_loaded].nazwisko, &st[st_loaded].rok,
               st[st_loaded].adres, &st[st_loaded].stypendium);
        printf("%s %s %d %s %lf\n", st[st_loaded].imie, st[st_loaded].nazwisko, st[st_loaded].rok, st[st_loaded].adres,
               st[st_loaded].stypendium);
        if (feof(f)) {
            break;
        }
        st_loaded++;
    }
    fclose(f);

    printf("\n\n");
    sort(st, st_loaded);
}
