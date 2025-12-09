#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <tgmath.h>

bool isInRange(double value, double min, double max) {
    return value >= min && value <= max;
}

struct MATRIX {
    int rows;
    int cols;
    double **contents;
};

double **allocateMatrix(int rows, int cols) {
    double **temp = calloc(rows, sizeof(double *));
    for (int i = 0; i < cols; i++) {
        temp[i] = calloc(cols, sizeof(double));
    }
    return temp;
}

void freeMatrix(struct MATRIX matrix) {
    for (int r = 0; r < matrix.rows; r++) {
        free(matrix.contents[r]);
    }
    free(matrix.contents);
    matrix.rows = 0;
    matrix.cols = 0;
    matrix.contents = NULL;
}

struct MATRIX readMatrixFromFile(FILE *file) {
    int size = 0;
    fscanf(file, "%d", &size);
    if (size == 0) {
        printf("To small matrix\n");
        exit(1);
    }
    struct MATRIX M;
    M.rows = size;
    M.cols = size;
    M.contents = allocateMatrix(M.rows, M.cols);

    for (int i = 0; i < M.rows; i++) {
        for (int j = 0; j < M.cols; j++) {
            fscanf(file, "%lf", &M.contents[i][j]);
        }
    }
    return M;
}

void PiszMac(double **ma, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            printf("%lf ", ma[i][j]);
        printf("\n");
    }
}


int main() {
    char *fileName = "./dane.txt";
    FILE *inFile = fopen(fileName, "r");
    if (inFile == NULL) {
        printf("File could not be opened\n");
        return 1;
    }
    struct MATRIX M = readMatrixFromFile(inFile);

    PiszMac(M.contents, M.rows, M.cols);

    double sum = 0;
    for (int i = 0; i < M.rows; i++) {
        for (int j = 0; j < M.cols; j++) {
            if (i == j && sin(M.contents[i][j]) >= 0) {
                sum += M.contents[i][j];
            } else if (i == M.rows - j - 1 && sin(M.contents[i][j]) >= 0.5) {
                sum += M.contents[i][j];
            }
        }
    }

    printf("Sum of elements under diagonal:  %lf", sum);

    freeMatrix(M);
    fclose(inFile);
    inFile = NULL;;
}
