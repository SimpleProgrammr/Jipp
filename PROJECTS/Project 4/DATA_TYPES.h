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

STUDENT *TABLE;

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

