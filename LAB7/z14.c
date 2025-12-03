#include<stdio.h>
#include<string.h>
#include"z14-util1.c"
#include"z14-util2.c"
#include"z14-util3.c"
#define LL 200

void argumenty(int, char **);

int main(int argc, char *argv[]) {
    double *x = DajWekt(LL), *y = DajWekt(LL), *z = DajWekt(LL);

    FILE *fw, *fd;
    int n;
    argumenty(argc, argv);
    if (!((fd = fopen(argv[1], "r")))) error(2, "dane");
    if (!((fw = fopen(argv[2], "w")))) error(2, "wyniki");
    printf("Files loaded\n");

    fscanf(fd, "%d", &n);
    CzytWekt(fd, x, n);
    CzytWekt(fd, y, n);

    double s = 0;

    DodWekt(z, x, y, n);
    const double mx = MaxElem(x, n);
    const double my = MaxElem(y, n);
    s = ilocz_skal(x, y, n);

    PiszWekt(fw, z, n);
    fprintf(fw, "\nilocz.skal=%lf mx=%lf my=%lf\n", s, mx, my);
    printf("\nilocz.skal=%lf mx=%lf my=%lf\n", s, mx, my);
}

void argumenty(int argc, char *argv[]) {
    if (argc != 3) {
        char *usage;
        int len = strlen(argv[0]) + 19;
        if (!((usage = (char *) malloc((unsigned) len * sizeof(char)))))
            error(3, "tablica usage");
        strcpy(usage, argv[0]);
        strcat(usage, " file_in file_out");
        error(4, usage);
    }
}