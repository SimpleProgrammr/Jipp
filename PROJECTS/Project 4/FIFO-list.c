#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "DATA_TYPES.h"

LIST *pullElement(LIST **HEAD, LIST **TAIL);

void addStudent(LIST **HEAD, LIST **TAIL, STUDENT *ST) {
    LIST *tmpNewElement = calloc(1, sizeof(LIST));
    tmpNewElement->data = ST;
    tmpNewElement->next = *TAIL;
    tmpNewElement->prev = NULL;

    if (*HEAD == NULL) {
        *HEAD = tmpNewElement;
    }
    if (*TAIL == NULL) {
        *TAIL = tmpNewElement;
    } else {
        (*TAIL)->prev = tmpNewElement;
        *TAIL = tmpNewElement;
    }
}

void addElement(LIST **HEAD, LIST **TAIL, LIST *EL) {
    if (*HEAD == NULL) {
        *HEAD = EL;
    }
    if (*TAIL == NULL) {
        *TAIL = EL;
    } else {
        (*TAIL)->prev = EL;
        *TAIL = EL;
    }
}

void printElement(STUDENT *st) {
    if (st == NULL) {
        fprintf(stderr, "Empty element\n");
        return;
    }
    if (st->name == NULL && st->surname == NULL) {
        fprintf(stderr, "NULL Data error\n");
        return;
    }
    printf("----------STUDENT----------\n"
           "Name: %s\n"
           "Surname: %s\n"
           "Birth year: %d\n\n\n",
           st->name, st->surname, st->bYear);
}

long countElement(LIST **HEAD, LIST **TAIL) {
    LIST *tmpHEAD = NULL, *tmpTAIL = NULL;
    long count = 0;
    //Pulling to count
    while (HEAD != NULL && TAIL != NULL) {
        LIST *tmpEl = pullElement(HEAD, TAIL);
        addElement(&tmpHEAD, &tmpTAIL, tmpEl);
        count++;
    }
    //Putting back on place
    while (tmpHEAD != NULL && tmpTAIL != NULL) {
        LIST *tmpEl = pullElement(&tmpHEAD, &tmpTAIL);
        addElement(HEAD, TAIL, tmpEl);
    }
    return count;
}

void searchElement(LIST *HEAD, LIST *TAIL, short mode) {
    STUDENT *ST = calloc(1, sizeof(STUDENT));
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
            return;
    }
    long countedElements = countElement(&HEAD, &TAIL);
    for (long i = 0; i < countedElements; i++) {
        LIST *tmpElement = pullElement(&HEAD, &TAIL);
        addElement(&HEAD, &TAIL, tmpElement);
        switch (mode) {
            case 1: //by Name
                if (strcmp(ST->name, tmpElement->data->name) == 0)
                    printElement(tmpElement->data);
                break;
            case 2: //by Surname
                if (strcmp(ST->surname, tmpElement->data->surname) == 0)
                    printElement(tmpElement->data);
                break;
            case 3: //by bYear
                if (ST->bYear == tmpElement->data->bYear)
                    printElement(tmpElement->data);
                break;
        }
    }
    free(ST);
    ST = NULL;
}

void freeElement(LIST *el) {
    if (el == NULL) {
        fprintf(stderr, "List element is NULL\n");
        return;
    }
    if (el->data == NULL) {
        fprintf(stderr, "Elements data is NULL\n");
        free(el);
        return;
    }

    if (el->data->name != NULL)
        free(el->data->name);
    if (el->data->surname != NULL)
        free(el->data->surname);
    free(el->data);

    free(el);
}

LIST *pullElement(LIST **HEAD, LIST **TAIL) {
    if (*HEAD == NULL && *TAIL == NULL) {
        fprintf(stderr, "Nothing to pull\n");
        return NULL;
    }

    printElement((*HEAD)->data);

    LIST *tmpElement = *HEAD;
    if (*HEAD == *TAIL) {
        *TAIL = NULL;
        *HEAD = *TAIL;
    } else if ((*HEAD)->prev != NULL) {
        *HEAD = (*HEAD)->prev;
    }

    return tmpElement;
}

void printAllElements(LIST **HEAD, LIST **TAIL) {
    LIST *tmpElement = NULL;
    long count = countElement(HEAD, TAIL);
    for (long i = 0; i < count; i++) {
    }
}
