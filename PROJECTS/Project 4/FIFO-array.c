#pragma once
#include "DATA_TYPES.h"
#include "FileIO.h"

void fifo_array_print_student(const STUDENT *st);

void fifo_array_print_all_students(STUDENT **arr, long studentsArraySize);

STUDENT **fifo_array_add_student(STUDENT **arr, long *studentsArraySize, STUDENT *newStudent) {
    STUDENT **newArray = NULL;
    (*studentsArraySize)++;

    if (arr == NULL) {
        newArray = (STUDENT **) calloc(*studentsArraySize, sizeof(STUDENT *));
    } else {
        newArray = resizeArray(arr, *studentsArraySize);
    }
    newArray[*studentsArraySize - 1] = newStudent;

    fifo_array_print_all_students(newArray, *studentsArraySize);

    return newArray;
}

STUDENT **fifo_array_add_student_debug(STUDENT **arr, long *studentsArraySize, const STUDENT *newStudent) {
    STUDENT **newArray = NULL;
    (*studentsArraySize)++;

    STUDENT *tmpStudent = calloc(*studentsArraySize, sizeof(STUDENT));
    tmpStudent->name = calloc(1, sizeof(strlen(newStudent->name)));
    memcpy(tmpStudent->name, newStudent->name, strlen(newStudent->name));
    tmpStudent->surname = calloc(1, sizeof(strlen(newStudent->surname)));
    memcpy(tmpStudent->surname, newStudent->surname, strlen(newStudent->surname));
    tmpStudent->bYear = newStudent->bYear;

    if (arr == NULL) {
        newArray = (STUDENT **) calloc(*studentsArraySize, sizeof(STUDENT *));
    } else {
        newArray = resizeArray(arr, *studentsArraySize);
    }
    newArray[*studentsArraySize - 1] = tmpStudent;

    fifo_array_print_all_students(newArray, *studentsArraySize);

    return newArray;
}

STUDENT *fifo_array_pull_student(STUDENT **arr, long *studentsArraySize) {
    if (arr[0] == NULL || *studentsArraySize <= 0) {
        perror("Unable to pull from empty array");
        return NULL;
    }
    STUDENT *pulledStudent = arr[0];
    arr[0] = NULL;

    shiftLeft(arr, *studentsArraySize);

    *studentsArraySize -= 1;


    arr = resizeArray(arr, *studentsArraySize);
    printf("Pulling...");
    fifo_array_print_student(pulledStudent);
    return pulledStudent;
}

void fifo_array_print_student(const STUDENT *st) {
    printf("------------Student--------------\n");
    printf("Name: %s\n", st->name);
    printf("Surname: %s\n", st->surname);
    printf("Birth year: %d\n", st->bYear);
}

void fifo_array_print_all_students(STUDENT **arr, long studentsArraySize) {
    for (long i = 0; i < studentsArraySize; i++) {
        fifo_array_print_student(arr[i]);
    }
}

