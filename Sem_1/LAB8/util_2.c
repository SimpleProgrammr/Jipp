/******************** plik util_2.c*********************************/
#include <stdio.h>
#include <stdlib.h>

extern void Error(int, char *);

double *DajWekt(int n) {
    double *we;
    if (!(we = (double *) malloc((unsigned) n * sizeof(double)))) Error(2, "wektor");
    return we;
}

void CzytWekt(FILE *fd, double *we, int n) {
    int i;
    char *err;
    for (i = 0; i < n; i++) {
        if (fscanf(fd, "%lf", &we[i]) != 1) {
            err = malloc((unsigned) 25);
            sprintf(err, "element nr %d\n", i);
            Error(1, err);
        }
    }
}

void PiszWekt(FILE *fw, double *we, int n) {
    int i;
    for (i = 0; i < n; i++) {
        fprintf(fw, "%15.4lf ", we[i]);
        if (!((i + 1) % 5)) fprintf(fw, "\n");
    }
    fprintf(fw, "\n");
}