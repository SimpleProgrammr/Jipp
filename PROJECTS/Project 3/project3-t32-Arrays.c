#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct MATRIX_1D {
    int height;
    int width;
    double *content;
};

double DownRange = -1.5;
double UpRange = 3.5;
extern int col;
extern int row;

extern void SetRow(int);

extern void SetColumn(int);

extern void PostError(char *, int);

double *Allocate2DArrayIn1D(int height, int width) {
    double *tmp = calloc(height * width, sizeof(double));
    if (tmp == NULL) {
        PostError("Unable to allocate array", 10);
    }
    return tmp;
}

double getValue(struct MATRIX_1D M, int row, int column) {
    return M.content[row * M.width + column];
}

void setValue(struct MATRIX_1D M, int row, int column, double value) {
    M.content[row * M.width + column] = value;
}

void Free1DArray(double *arr) {
    free(arr);
}

struct MATRIX_1D LoadFileIn2Din1DArray(FILE *file) {
    struct MATRIX_1D M = {};
    fscanf(file, "%d", &M.height);
    if (M.height <= 0) {
        PostError("Size must be greater than 0", 200);
    }
    M.width = M.height;
    M.content = Allocate2DArrayIn1D(M.height, M.width);
    for (int i = 0; i < M.height; i++) {
        for (int j = 0; j < M.width; j++) {
            double val = 0;
            fscanf(file, "%lf", &val);
            setValue(M, i, j, val);
        }
    }
    return M;
}

struct MATRIX_1D LoadVector(FILE *file) {
    struct MATRIX_1D M = {};
    fscanf(file, "%d", &M.width);
    if (M.width <= 0)
        PostError("Size must be greater than 0", 200);
    M.height = 1;
    M.content = Allocate2DArrayIn1D(M.height, M.width);
    for (int i = 0; i < M.width; i++) {
        fscanf(file, "%lf", &M.content[i]);
    }
    return M;
}


bool IsInRange(double val) {
    return val >= DownRange && val <= UpRange;
}

int HowManyElementsIn1DInRange(FILE *f, int mode) {
    struct MATRIX_1D M = {};

    int amount = 0;

    if (mode == 1) {
        M = LoadVector(f);
    } else {
        M = LoadFileIn2Din1DArray(f);
    }

    if (mode == 2) {
        SetColumn(M.height);
    } else if (mode == 3) {
        SetRow(M.width);
    }

    for (int i = 0; i < M.height; i++) {
        for (int j = 0; j < M.width; j++) {
            double val = getValue(M, i, j);
            switch (mode) {
                case 1:
                    if (IsInRange(val))
                        amount++;
                    break;
                case 2:

                    if (i == col) {
                        if (IsInRange(val))
                            amount++;
                    }
                    break;
                case 3:

                    if (j == row)
                        if (IsInRange(val))
                            amount++;
                    break;
                case 4:
                    if (i == j && IsInRange(val))
                        amount++;
                    break;
                case 5:
                    if (i > j && IsInRange(val))
                        amount++;
                    break;
                case 6:
                    if (i < j && IsInRange(val))
                        amount++;
                    break;
                default:
                    break;
            }
        }
    }
    Free1DArray(M.content);
    return amount;
}