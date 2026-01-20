#pragma once
#include "DATA_TYPES.h"

void postOperationName(int choice) {
    clearConsole();
    switch (choice) {
        case 0:
            printf("Exiting program...\n");
            break;
        case 1:
            printf("Adding element\n");
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

void post_student(STUDENT *st) {
    if (st == NULL) {
        printf("Student is NULL\n");
        return;
    }
    if (st->name == NULL) {
        printf("Name is NULL\n");
    }
    if (st->surname == NULL) {
        printf("Surname is NULL\n");
    }
    printf("----------STUDENT----------\n"
           "Name: %s\n"
           "Surname: %s\n"
           "Birth year: %d\n\n",
           st->name, st->surname, st->bYear);
}

void post_addition_header() {
    printf("----------ADDITION----------\n");
}

void post_pull_header() {
    printf("----------PULL-----------\n");
}

void post_file_read_header() {
    printf("----------FROM FILE----------\n");
}

void post_file_save_header() {
    printf("----------TO FILE----------\n");
}

void post_search_header() {
    printf("----------SEARCH----------\n");
}

void post_clear_header() {
    printf("----------CLEAR----------\n");
}