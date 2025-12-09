void DodMac(double **ma_dest, double **ma1, double **ma2, const int n, const int m) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            ma_dest[i][j] = ma1[i][j] + ma2[i][j];
}

void Mac_x_Wekt(double **ma, double *we, double *wy, int n, int m) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int k = 0; k < n; k++)
                wy[i] += ma[i][k] * we[k];
}

void Mac_x_Mac(double **x, double **y, double **z, int n, int m, int p) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int k = 0; k < p; k++)
                z[i][j] += x[i][k] * y[k][p];
}