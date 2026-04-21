#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int minVal = 0, maxVal = 10;

bool isInRange(int value) {
    return value >= minVal && value <= maxVal;
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


int main() {
    char *fileName = "./dane.txt";
    FILE *inFile = fopen(fileName, "r");
    if (inFile == NULL) {
        printf("File could not be opened\n");
        return 1;
    }
    struct MATRIX M = readMatrixFromFile(inFile);

    double sum = 0;
    for (int i = 0; i < M.rows; i++) {
        for (int j = 0; j < M.cols; j++) {
            if (i > j && isInRange(M.contents[i][j])) {
                sum += M.contents[i][j];
            }
        }
    }

    printf("Sum of elements under diagonal:  %lf", sum);

    freeMatrix(M);
    fclose(inFile);
    inFile = NULL;;
}