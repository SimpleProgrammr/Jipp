#pragma once
#include <stdbool.h>
#include "DATA_TYPES.h"
#include "FileIO.h"

void lifo_array_print_student(const STUDENT *st);

STUDENT** lifo_array_print_all_students(STUDENT **arr, long *studentsArraySize);

STUDENT **lifo_array_add_student(STUDENT **arr, long *studentsArraySize, STUDENT *newStudent, bool post) {
    STUDENT **newArray = NULL;
    (*studentsArraySize)++;

    if (arr == NULL) {
        newArray = (STUDENT **) calloc(*studentsArraySize, sizeof(STUDENT *));
    } else {
        newArray = resizeArray(arr, *studentsArraySize);
    }
    newArray[*studentsArraySize - 1] = newStudent;

    if (post)
        lifo_array_print_student(newArray[*studentsArraySize - 1]);

    return newArray;
}

STUDENT **lifo_array_add_student_debug(STUDENT **arr, long *studentsArraySize, const STUDENT *newStudent) {
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

    lifo_array_print_student(newArray[*studentsArraySize - 1]);
    return newArray;
}

pullRet *lifo_array_pull_student(STUDENT **arr, long *studentsArraySize, bool post) {

    if (arr == NULL || *studentsArraySize <= 0) {
        perror("Unable to pull from empty array");
        return (&(pullRet){NULL, NULL});
    }
    STUDENT *pulledStudent = arr[*studentsArraySize-1];
    arr[*studentsArraySize-1] = NULL;

    *studentsArraySize -= 1;


    arr = resizeArray(arr, *studentsArraySize);
    if (post) {
        printf("Pulling...\n");
        lifo_array_print_student(pulledStudent);
    }
    pullRet *r = &(pullRet){pulledStudent, arr};
    return r;
}

void lifo_array_print_student(const STUDENT *st) {
    printf("------------Student--------------\n");
    printf("Name: %s\n", st->name);
    printf("Surname: %s\n", st->surname);
    printf("Birth year: %d\n\n", st->bYear);
}

STUDENT ** lifo_array_print_all_students(STUDENT **arr, long *studentsArraySize) {
    if (*studentsArraySize == 1) {
        lifo_array_print_student(arr[0]);
        return arr;
    }
    long total_students = 0;
    STUDENT ** tempArr = NULL;
    for (long i = *studentsArraySize -1 ; i >= 0; i--) {
        pullRet *pr = lifo_array_pull_student(arr, studentsArraySize, false);
        STUDENT *st = pr->st;
        arr = pr->arr;
        tempArr = lifo_array_add_student(tempArr, &total_students, st, true);
    }
    for (long i = total_students - 1; i >= 0; i--) {
        pullRet *pr = lifo_array_pull_student(tempArr, &total_students, false);
        STUDENT *st = pr->st;
        arr = lifo_array_add_student(arr, studentsArraySize, st, false);
    }
    return arr;
}

void lifo_array_free_student(STUDENT *st) {
    if (st==NULL) {
        perror("Unable to free NULL");
        return;
    }
    if (st->name != NULL)
        free(st->name);
    if (st->surname != NULL)
        free(st->surname);
    free(st);
    st = NULL;
}

STUDENT ** lifo_array_clear_all_elements(STUDENT **arr, long *studentsArraySize) {
    long amount_to_free = *studentsArraySize;
    for (long i = amount_to_free -1; i >= 0; i--) {
        if (arr == NULL)
            continue;

        pullRet *pr = lifo_array_pull_student(arr, studentsArraySize, false);
        STUDENT* toFree = pr->st;
        arr = pr->arr;
        lifo_array_free_student(toFree);
        printf("Student freed...\n");
    }
    return arr;
}

STUDENT ** lifo_array_save_all_elements_to_file(STUDENT** arr, long *studentsArraySize) {
    FILE* file = fopen("Elements.bin", "wb");

    //<elements count>[int]
    fwrite(studentsArraySize, sizeof(long), 1, file);

    //Pulling to save
    for (long i = *studentsArraySize-1; i >= 0; i--) {
        pullRet *pr = lifo_array_pull_student(arr, studentsArraySize, false);
        STUDENT *tmpStudent = pr->st;
        arr = pr->arr;
        savePackageToFile(file,tmpStudent);

        //Putting back on place
        arr = lifo_array_add_student(arr, studentsArraySize, tmpStudent, true);
    }
    printf("Saved %ld elements to file\n\n", *studentsArraySize);
    fclose(file);
    return arr;
}

STUDENT ** lifo_array_read_all_elements_from_file(STUDENT ** arr, long *studentsArraySize) {
    FILE* file = fopen("Elements.bin", "rb");
    long count = 0;
    fread(&count, sizeof(long), 1, file);
    long c = 0;
    for (long i = count -1; i >= 0; i--) {
        STUDENT* tmpElement = readPackageFromFile(file);
        arr = lifo_array_add_student(arr, studentsArraySize, tmpElement, true);
        c++;
    }
    printf("Added %ld elements form file\n\n", c);

    fclose(file);
    return arr;
}

STUDENT ** lifo_array_search_element(STUDENT** arr, long* studentArraySize, short mode) {

    if (arr == NULL) {
        perror("Unable to look in NULL array");
        return NULL;
    }

    STUDENT *ST = calloc(1, sizeof(STUDENT));
    if (ST == NULL) {
        fprintf(stderr, "Unable to allocate memory");
        exit(-300);
    }
    switch (mode) {
        case 1:
            ST->name = set_text("Enter name: ");
            break;
        case 2:
            ST->surname = set_text("Enter surname: ");
            break;
        case 3:
            ST->bYear = get_int("Enter birth year: ");
            break;
        default:
            fprintf(stderr, "Wrong search mode selection!");
            free(ST);
            return arr;
    }
    long countedElements = *studentArraySize;
    pullRet *tmpElement;
    for (long i = countedElements-1; i >=0; i--) {
        if (*studentArraySize == 1)
            tmpElement = &(pullRet){*arr, arr};
        else {
            tmpElement = lifo_array_pull_student(arr, studentArraySize, false);
            arr = lifo_array_add_student(tmpElement->arr,studentArraySize, tmpElement->st, false);
        }
        switch (mode) {
            case 1: //by Name
                if (strcmp(ST->name, tmpElement->st->name) == 0)
                    lifo_array_print_student(tmpElement->st);
                break;
            case 2: //by Surname
                if (strcmp(ST->surname, tmpElement->st->surname) == 0)
                    lifo_array_print_student(tmpElement->st);
                break;
            case 3: //by bYear
                if (ST->bYear == tmpElement->st->bYear)
                    lifo_array_print_student(tmpElement->st);
                break;
            default: ;
        }
    }
    free(ST);
    ST = NULL;
    return arr;
}

