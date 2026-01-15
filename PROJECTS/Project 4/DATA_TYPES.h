#pragma once
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student {
    char *name;
    char *surname;
    int bYear;
} STUDENT;

typedef struct list {
    STUDENT *data;
    struct list *next;
    struct list *prev;
} LIST;

typedef struct {
    STUDENT* st;
    STUDENT** arr;
} pullRet;

STUDENT **resizeArray(STUDENT **arr, size_t newSize) {
    if (newSize == 0 && arr != NULL) {
        STUDENT *st = *arr;
        if (st!=NULL) {
            if (st->name != NULL)
                free(st->name);
            if (st->surname != NULL)
                free(st->surname);
            free(st);
            st = NULL;
        }
        free(arr);
        return NULL;
    }
    STUDENT **newArr = NULL;
    if (arr == NULL && newSize > 0) {
        newArr = (STUDENT **)calloc(newSize, sizeof(STUDENT *));
    }else
        newArr = (STUDENT **) realloc(arr, newSize * sizeof(STUDENT *));

    if (newArr == NULL) {
        fprintf(stderr, "Unable to resize array!");
        exit(-300);
    }
    return newArr;
}

void shiftLeft(STUDENT **arr, size_t arrSize) {
    if (arr[0] != NULL) {
        fprintf(stderr, "Memory leak on shiftLeft()\nCheck if it getting freed before shift\n\n");
    }
    if (arrSize < 1) {
        fprintf(stderr, "Empty Array\n");
        return;
    }
    for (int i = 1; i < arrSize; i++) {
        arr[i - 1] = arr[i];
    }
    arr[arrSize - 1] = NULL;
}

void shiftRight(STUDENT **arr, size_t arrSize) {
    if (arr[0] != NULL) {
        fprintf(stderr, "Memory leak on shiftRight()\nCheck if it getting freed before shift\n\n");
    }
    if (arrSize < 1) {
        fprintf(stderr, "Empty Array\n");
        return;
    }
    for (int i = 1; i < arrSize; i++) {
        arr[i] = arr[i-1];
    }
    arr[0] = NULL;
}

char *set_text(char *msg) {
    char buff[1024];

    printf("%s", msg);
    if (scanf("%s", buff) == 0) {
        printf("Error reading input");
        return NULL;
    }
    size_t len = strlen(buff);
    char *str = calloc(strlen(buff) + 1, sizeof(char));
    if (str == NULL) {
        fprintf(stderr, "Unable to allocate memory");
        exit(-300);
    }
    memcpy(str, buff, len);

    return str;
}

long get_long(char *msg) {
    long val = 0;
wrongInput:
    printf("%s", msg);
    fflush(stdin);
    if (scanf("%ld", &val) == 0) {
        fprintf(stderr, "Wrong input\n");
        fflush(stderr);
        goto wrongInput;
    }

    return val;
}

int get_int(char *msg) {
    int val = 0;

    wrongInput:
    printf("%s", msg);
    fflush(stdin);
    if (scanf("%d", &val) == 0) {
        fprintf(stderr, "Wrong input\n");
        fflush(stderr);
        goto wrongInput;
    }

    return val;
}

int char_to_int(char ch) {
    if (ch >= '0' && ch <= '9') {
        return ch - '1' + 1;
    }
    return -1;
}

void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void postOperationName(int choice) {
    clearConsole();
    switch (choice) {
        case 0:
            printf("Exiting program...\n");
            break;
        case 1:
            printf("Adding element\n");
            break;
        case 2:
            printf("Pulling element\n");
            break;
        case 3:
            printf("Searching element\n");
            break;
        case 4:
            printf("Printing all elements\n");
            break;
        case 5:
            printf("Counting elements\n");
            break;
        case 6:
            printf("Clearing all elements\n");
            break;
        case 7:
            printf("Coping to .bin file\n");
            break;
        case 8:
            printf("Reading from .bin file\n");
            break;
        default:
            break;
    }
}


