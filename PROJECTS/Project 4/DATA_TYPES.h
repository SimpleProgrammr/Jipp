#pragma once
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
    char buff[100];

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
    if (scanf("%ld", &val) == 0) {
        fprintf(stderr, "Wrong input\n");
        goto wrongInput;
    }

    return val;
}

int get_int(char *msg) {
    int val = 0;
wrongInput:
    printf("%s", msg);
    if (scanf("%d", &val) == 0) {
        fprintf(stderr, "Wrong input\n");
        goto wrongInput;
    }

    return val;
}

