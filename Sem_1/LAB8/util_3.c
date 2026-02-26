/******************** plik util_3.c*********************************/

void DodWekt(double *w1, double *w2, double *w3, int n) {
    int i;
    for (i = 0; i < n; i++)
        w3[i] = w1[i] + w2[i];
}

double IloczynSkal(double *w1, double *w2, int n) {
    int i;
    double sk = 0;
    for (i = 0; i < n; i++)
        sk += w1[i] * w2[i];
    return sk;
}

double MaxElem(double *w, int n) {
    int i;
    double max;
    max = w[0];
    for (i = 1; i < n; i++)
        max = w[i] > max ? w[i] : max;
    return max;
}