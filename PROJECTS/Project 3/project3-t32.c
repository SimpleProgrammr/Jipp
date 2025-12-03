#include <stdio.h>
#include <stdlib.h>
#include "project3-t32-Arrays.c"
#include "project3-t32-Calculations.c"
#include "project3-t32-FilesIO.c"
#include "project3-t32-Error.c"

int col = 0;
int row = 0;

void privateExit(int code) {
}

int main() {
    int choice = -1;
    FILE *dane = OpenFile("Data.txt", "r");
    FILE *vector = OpenFile("vector.txt", "r");
    //FILE* wyniki = OpenFile("Wyniki.txt", "w");

    while (1) {
        system("clear");
        printf("Choose an option: \n"
            "1. Calculate vector\n"
            "2. Calculate row in matrix\n"
            "3. Calculate column in matrix\n"
            "4. Calculate diagonal in matrix\n"
            "5. Calculate under diagonal in matrix\n"
            "6. Calculate above diagonal in matrix\n"
            "00. Exit\n");
        scanf("%d", &choice);

        if (choice == 0)
            exit(0);
        if (choice == 1)
            printf("Result: %d\n", HowManyElementsIn1DInRange(vector, choice));
        else if (choice >= 2 && choice <= 6)
            printf("Result: %d\n", HowManyElementsIn1DInRange(dane, choice));
        rewind(vector);
        rewind(dane);
        choice = 128;
    }
    CloseFile(dane);
    //CloseFile(wyniki);
}

void SetRow(int maxVal) {
    while (1) {
        printf("\n\nEnter row number (1 - %d): ", maxVal);
        scanf("%d", &row);
        row--;
        if (row > maxVal || row < 0) {
            printf("Invalid row number\n");
            continue;
        }
        break;
    }
}

void SetColumn(int maxVal) {
    while (1) {
        printf("\n\nEnter row number (1 - %d): ", maxVal);
        scanf("%d", &col);
        col--;
        if (row > maxVal || row < 0) {
            printf("Invalid row number\n");
            continue;
        }
        break;
    }
}



