#include <stdio.h>
#include <stdlib.h>

extern void Error(int, char *);

double **DajMac_1(int n, int m) {
    double **tab = calloc(n, sizeof(double *));
    if (tab == NULL) {
        printf("Memory allocation failed\n");
        exit(10);
    }

    for (int i = 0; i < n; i++) {
        tab[i] = (double *) calloc(m, sizeof(double));
        if (tab[i] == NULL) {
            printf("Memory allocation failed\n");
            exit(10);
        }
    }

    return tab;
}

double **DajMac_2(int n, int m) {
    double **tab_a, *tab_b;
    tab_b = (double *) malloc(sizeof(double) * n * m);
    if (!tab_b) {
        Error(2, "Memory allocation failed");
    }
    tab_a = (double **) malloc(sizeof(double *) * n);
    if (!tab_a) {
        Error(2, "Memory allocation failed");
    }
    for (int i = 0; i < n; i++) {
        tab_a[i] = &tab_b[m * i];
    }
    return tab_a;
}

void ZwrocMac_1(double **ma, int n, int m) {
    if (ma == NULL)
        return;

    for (int i = 0; i < n; i++) {
        free(ma[i]);
    }
    free(ma);
}

void ZwrocMac_2(double **ma, int n, int m) {
    if (ma[0]) {
        free(ma[0]); // free(tab_a[0]);
        ma[0] = NULL;
    }
    if (ma) {
        free(ma);
        ma = NULL;
    }
}

void CzytMac(FILE *fd, double **ma, int n, int m) {
    int i, j;
    char *err;
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++) {
            if (fscanf(fd, "%lf", &ma[i][j]) != 1) {
                printf("blad - element nr %d %d\n", i, j);
            }
        }
}

void PiszMac(FILE *fw, double **ma, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            fprintf(fw, "%lf ", ma[i][j]);
        fprintf(fw, "\n");
    }
}
