#pragma once
#include "DATA_TYPES.h"

void savePackageToFile(FILE* FILE, const STUDENT * ST) {
    //<txt1 len>[int]<TXT1>[char[]] <- NAME
    int len = strlen(ST->name);
    fwrite(&len, sizeof(int), 1, FILE);
    fwrite(ST->name, sizeof(char), len, FILE);

    //<txt2 len>[int]<TXT2>[char[]] <- SURNAME
    len = strlen(ST->surname);
    fwrite(&len, sizeof(int), 1, FILE);
    fwrite(ST->surname, sizeof(char), len, FILE);

    //<bYear>[int]
    fwrite(&(ST->bYear), sizeof(int), 1, FILE);
}

STUDENT * readPackageFromFile(FILE* FILE) {
    STUDENT * ST = calloc(1, sizeof(STUDENT));
    //<txt1 len>[int]<TXT1>[char[]] <- NAME
    int len = 0;
    fread(&len, sizeof(int), 1, FILE);
    ST->name = calloc(len, sizeof(char));
    fread(ST->name, sizeof(char), len, FILE);

    //<txt2 len>[int]<TXT2>[char[]] <- SURNAME
    len = 0;
    fread(&len, sizeof(int), 1, FILE);
    ST->surname = calloc(len, sizeof(char));
    fread(ST->surname, sizeof(char), len, FILE);

    //<bYear>[int]
    fread(&(ST->bYear), sizeof(int), 1, FILE);
    return ST;
}
