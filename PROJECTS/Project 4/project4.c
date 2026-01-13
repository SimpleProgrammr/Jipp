#include <stdio.h>
#include <stdlib.h>
#include "DATA_TYPES.h"
#include "FIFO-list.c"
#include "FIFO-table.c"
#include "LIFO-list.c"
#include "FIFO-table.c"

enum DATA_TYPE_MODE {
    FIFO_LIST = 1,
    FIFO_TABLE,
    LIFO_LIST,
    LIFO_TABLE
};

enum CHOSEN_OPERATION {
    EXIT,
    ADD_ELEMENT = 1,
    PULL_ELEMENT,
    SEARCH_ELEMENT,
    PRINT_ELEMENTS,
    COUNT_ELEMENTS,
    CLEAR_ALL_ELEMENTS,
    SAVE_TO_BINARY,
    READ_FROM_BINARY
};

STUDENT *create_student();

void FIFO_list_run();

short searchModeSelection();

int main() {
    printf("Which mode to use?\n"
        "1. FIFO List\n"
        "2. FIFO Table\n"
        "3. LIFO List\n"
        "4. LIFO Table\n");
    int *choice = calloc(sizeof(int), 1);
    if (choice == NULL) {
        fprintf(stderr, "Unable to allocate memory");
        exit(-300);
    }
    scanf("%d", choice);

    switch (*choice) {
        case FIFO_LIST:
            FIFO_list_run();
            break;
        case FIFO_TABLE:

            break;
        case LIFO_LIST:

            break;
        case LIFO_TABLE:

            break;
        default:
            fprintf(stderr, "Invalid choice\n");
            exit(10);
    }

    free(choice);
    return 0;
}

void FIFO_list_run() {
    int choice = -1;

    LIST *HEAD = NULL, *TAIL = NULL;

    addStudentDEBUG(&HEAD, &TAIL, &(STUDENT){"#1", "#11", 1});
    addStudentDEBUG(&HEAD, &TAIL, &(STUDENT){"#2", "#33", 2});
    addStudentDEBUG(&HEAD, &TAIL, &(STUDENT){"#3", "#33", 3});

    while (1) {
        printf("Choose operation: \n"
            "1. Add element\n"
            "2. Pull element\n"
            "3. Search element\n"
            "4. Print elements\n"
            "5. Count elements\n"
            "6. Clear all elements\n"
            "7. Write to .bin file\n"
            "8. Read from .bin file\n"
            "0. Exit\n");
        choice = -1;
        scanf("%d", &choice);
        switch (choice) {
            case ADD_ELEMENT:
                STUDENT *st = create_student();
                addStudent(&HEAD, &TAIL, st);
                break;
            case PULL_ELEMENT:
                pullElement(&HEAD, &TAIL, true);
                break;
            case SEARCH_ELEMENT:
                searchElement(HEAD, TAIL, searchModeSelection());
                break;
            case PRINT_ELEMENTS:
            printAllElements(&HEAD, &TAIL);
                break;
            case COUNT_ELEMENTS:
                printf("There are %ld elements\n\n", countElement(&HEAD, &TAIL));
                break;
            case CLEAR_ALL_ELEMENTS:
                clearAllElements(&HEAD, &TAIL);
                break;
            case SAVE_TO_BINARY:
                saveAllElementsToFile(&HEAD, &TAIL);
                break;
            case READ_FROM_BINARY:
                readAllElementsToFile(&HEAD, &TAIL);
                break;
            case EXIT:
                clearAllElements(&HEAD, &TAIL);
                return;
            default:
                fprintf(stderr, "Invalid choice\n");
                exit(10);
        }
    }
}

STUDENT *create_student() {
    STUDENT *st = calloc(1, sizeof(STUDENT));
    if (st == NULL) {
        fprintf(stderr, "Unable to allocate memory");
        exit(-300);
    }
    st->name = set_text("Enter name: ");
    st->surname = set_text("Enter surname: ");
    st->bYear = get_int("Enter birth year: ");
    return st;
}

short searchModeSelection() {
    printf("Choose search mode: \n"
        "1. By name\n"
        "2. By surname\n"
        "3. By year of birth\n");
    int choice;
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            return 1;
        case 2:
            return 2;
        case 3:
            return 3;
        default:
            return 0;
    }
}
