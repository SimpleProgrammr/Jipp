#include <stdio.h>
#include <string.h>

#include "util_1.c"
#include "util_2.c"
#include "util_3.c"
#include "util_4.c"
#include "util_5.c"

FILE *fw, *fd;

void argumenty(int argc, char *argv[]);

int main(int argc, char *argv[]) {
    double *x, *y;
    double **a, **b, **c;
    int n, m;
    argumenty(argc, argv);
    if (!(fd = fopen(argv[1], "r"))) Error(2, "dane");
    if (!(fw = fopen(argv[2], "w"))) Error(2, "wyniki");
    fscanf(fd, "%d %d", &n, &m);
    x = DajWekt(m);
    y = DajWekt(m);
    a = DajMac_1(n, m);
    b = DajMac_1(n, m);
    c = DajMac_1(n, m);
    CzytMac(fd, a, n, m);
    CzytMac(fd, b, n, m);
    CzytWekt(fd, x, m);
    DodMac(a, b, c, n, m);
    Mac_x_Wekt(a, x, y, n, m);
    printf("Macierz\n");
    PiszMac(stdout, c, n, m);
    fprintf(fw, "Macierz\n");
    PiszMac(fw, c, n, m);
    printf("Wektor\n");
    PiszWekt(stdout, y, n);
    fprintf(fw, "Wektor\n");
    PiszWekt(fw, y, n);
}

void argumenty(int argc, char *argv[]) {
    int len;
    char *usage;
    if (argc != 3) {
        len = strlen(argv[0]) + 19;
        if (!(usage = (char *) malloc((unsigned) len * sizeof(char))))
            Error(3, "tablica usage");
        strcpy(usage, argv[0]);
        strcat(usage, " file_in file_out");
        Error(4, usage);
    }
}