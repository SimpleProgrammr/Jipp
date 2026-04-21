void DodWekt(double *w1, double *w2, double *w3, int n) {
    for (int k = 0; k < n; k++) {
        w1[k] = w2[k] + w3[k];
    }
}

double ilocz_skal(double *w1, double *w2, int n) {
    double s = 0.0;
    for (int k = 0; k < n; k++) {
        s += w1[k] * w2[k];
    }
    return s;
}

double MaxElem(double *w, int n) {
    double mx = w[0];

    for (int k = 0; k < n; k++) {
        mx = w[k] > mx ? w[k] : mx;
    }

    return mx;
}