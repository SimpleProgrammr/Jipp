#pragma once
#include <stdbool.h>
#include "CONSOLE_IO.h"
#include "DATA_TYPES.h"
#include "FileIO.h"


STUDENT **fifo_array_print_all_students(STUDENT **arr, long *studentsArraySize);

STUDENT **fifo_array_add_student(STUDENT **arr, long *studentsArraySize, STUDENT *newStudent, bool post) {
    STUDENT **newArray = NULL;
    (*studentsArraySize)++;

    if (arr == NULL) {
        newArray = (STUDENT **) calloc(*studentsArraySize, sizeof(STUDENT *));
    } else {
        newArray = resizeArray(arr, *studentsArraySize);
    }
    newArray[*studentsArraySize - 1] = newStudent;

    if (post) {
        post_addition_header();
        post_student(newArray[*studentsArraySize - 1]);
    }

    return newArray;
}

pullRet *fifo_array_pull_student(STUDENT **arr, long *studentsArraySize, bool post) {
    if (arr == NULL || *studentsArraySize <= 0) {
        perror("Unable to pull from empty array");
        return (&(pullRet)
        {
            NULL, NULL
        }
        )
        ;
    }
    STUDENT *pulledStudent = arr[0];
    arr[0] = NULL;

    shiftLeft(arr, *studentsArraySize);

    *studentsArraySize -= 1;


    arr = resizeArray(arr, *studentsArraySize);
    if (post) {
        post_pull_header();
        post_student(pulledStudent);
    }
    pullRet *r = &(pullRet)
    {
        pulledStudent, arr
    };
    return r;
}

STUDENT **fifo_array_print_all_students(STUDENT **arr, long *studentsArraySize) {
    if (*studentsArraySize == 1) {
        post_student(arr[0]);
        return arr;
    }

    for (long i = 0; i < *studentsArraySize; i++) {
        post_pull_header();
        pullRet *pr = fifo_array_pull_student(arr, studentsArraySize, true);
        STUDENT *st = pr->st;
        arr = pr->arr;
        arr = fifo_array_add_student(arr, studentsArraySize, st, false);
    }
    return arr;
}

void fifo_array_free_student(STUDENT *st) {
    if (st == NULL) {
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

STUDENT **fifo_array_clear_all_elements(STUDENT **arr, long *studentsArraySize) {
    long amount_to_free = *studentsArraySize;
    for (long i = 0; i < amount_to_free; i++) {
        if (arr == NULL)
            continue;

        pullRet *pr = fifo_array_pull_student(arr, studentsArraySize, false);
        STUDENT *toFree = pr->st;
        arr = pr->arr;
        post_clear_header();
        post_student(toFree);
        fifo_array_free_student(toFree);
    }
    return arr;
}

STUDENT **fifo_array_save_all_elements_to_file(STUDENT **arr, long *studentsArraySize) {
    FILE *file = fopen("Elements.bin", "wb");

    //<elements count>[int]
    fwrite(studentsArraySize, sizeof(long), 1, file);

    //Pulling to save
    for (long i = 0; i < *studentsArraySize; i++) {
        pullRet *pr = fifo_array_pull_student(arr, studentsArraySize, false);
        STUDENT *tmpStudent = pr->st;
        arr = pr->arr;
        savePackageToFile(file, tmpStudent);

        //Putting back on place
        post_student(tmpStudent);
        arr = fifo_array_add_student(arr, studentsArraySize, tmpStudent, true);
    }
    printf("Saved %ld elements to file\n\n", *studentsArraySize);
    fclose(file);
    return arr;
}

STUDENT **fifo_array_read_all_elements_from_file(STUDENT **arr, long *studentsArraySize) {
    FILE *file = fopen("Elements.bin", "rb");
    long count = 0;
    fread(&count, sizeof(long), 1, file);
    long c = 0;
    for (long i = 0; i < count; i++) {
        STUDENT *tmpElement = readPackageFromFile(file);
        post_file_read_header();
        arr = fifo_array_add_student(arr, studentsArraySize, tmpElement, true);
        c++;
    }
    printf("Added %ld elements form file\n\n", c);

    fclose(file);
    return arr;
}

STUDENT **fifo_array_search_element(STUDENT **arr, long *studentArraySize, short mode) {
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
    pullRet *tmpElement = calloc(1, sizeof(pullRet));
    if (tmpElement == NULL) {
        fprintf(stderr, "Unable to allocate memory");
        exit(-300);
    }
    STUDENT *toCheck = NULL;
    for (long i = 0; i < countedElements; i++) {
        if (*studentArraySize == 1)
            tmpElement = &(pullRet)
        {
            *arr, arr
        };
        else
        {
            tmpElement = fifo_array_pull_student(arr, studentArraySize, false);
            toCheck = tmpElement->st;
            arr = fifo_array_add_student(tmpElement->arr, studentArraySize, tmpElement->st, false);
        }
        switch (mode) {
            case 1: //by Name
                if (strcmp(ST->name, toCheck->name) == 0) {
                    post_search_header();
                    post_student(toCheck);
                }
                break;
            case 2: //by Surname
                if (strcmp(ST->surname, toCheck->surname) == 0) {
                    post_search_header();
                    post_student(toCheck);
                }
                break;
            case 3: //by bYear
                if (ST->bYear == toCheck->bYear) {
                    post_search_header();
                    post_student(toCheck);
                }
                break;
            default: ;
        }
    }
    free(tmpElement);
    free(ST);
    ST = NULL;
    return arr;
}