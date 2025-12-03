#include <stdlib.h>
#include <stdio.h>

double *DajWekt(int n) {
    double *Wekt = (double *) calloc(n, sizeof(double));
    return Wekt;
}

void CzytWekt(FILE *File, double *Wekt, int n) {
    for (int k = 0; k < n; k++)
        fscanf(File, "%lf", &Wekt[k]);
}

void PiszWekt(FILE *File, double *Wekt, int n) {
    for (int k = 0; k < n; k++) {
        fprintf(File, "%lf ", Wekt[k]);
        if (!((k + 1) % 5)) fprintf(File, "\n");
    }
}