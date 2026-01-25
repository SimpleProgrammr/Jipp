//To tylko funkcje, które mogą być dodane do projektu

#include <stdio.h>
#include <string.h>
#include <sys/_types/_null.h>

typedef struct student {
    char *name;
    char *surname;
    int b_year;
    char *address;
    int money;
    struct student *next;
    struct student *prev;
} STUDENT;

typedef enum sort_mode {
    BY_NAME,
    BY_SURNAME,
    BY_B_YEAR
} SORT_MODE;

void swapStudents(STUDENT **h, STUDENT **t, STUDENT *temp) {
    if (temp->prev == *h) {
        *h = temp;
    } else if (temp == *t) {
        *t = temp->prev;
    }
    if (temp->prev->prev != NULL) {
        temp->prev->prev->next = temp;
    }
    temp->prev->next = temp->next;
    temp->prev->prev = temp;

    temp->prev = temp->prev->prev;
    temp->next = temp->prev;

    temp->next->prev = temp->prev;
}

void bubbleSort(STUDENT **h, STUDENT **t, SORT_MODE mode) {
    if (*h == NULL || *t == NULL) {
        printf("Empty set\n");
        return;
    }
    long long count = 0;
    STUDENT *temp = *h;
    do {
        do {
            if (temp->prev != NULL) {
                switch (mode) {
                    case BY_NAME:
                        if (strcmp(temp->prev->name, temp->name) > 0) {
                            count++;
                            swapStudents(h, t, temp);
                        }
                        break;
                    case BY_SURNAME:
                        if (strcmp(temp->prev->surname, temp->surname) > 0) {
                            count++;
                            swapStudents(h, t, temp);
                        }
                        break;
                    case BY_B_YEAR:
                        if (temp->prev->b_year > temp->b_year) {
                            count++;
                            swapStudents(h, t, temp);
                        }
                        break;
                }
            }
            temp = temp->next;
        } while (temp->next != NULL);
    } while (count != 0);
};

STUDENT *findPlaceForNew(STUDENT *newStudent, STUDENT **h) {
    if (*h == NULL) {
        printf("Empty set\n");
        return NULL;
    }
    STUDENT *toReturn = *h;
    while (toReturn->next != NULL) {
        if (strcmp(toReturn->surname, newStudent->surname) < 0 && strcmp(toReturn->next->surname, newStudent->surname) >
            0) {
            return toReturn;
        }
        toReturn = toReturn->next;
    }
    return toReturn;
}

void addSortedBySurname(STUDENT * *h, STUDENT * *t, STUDENT * new) {
    if (*h == NULL && *t == NULL) {
        *t = new;
        *h = new;
        return;
    }
    STUDENT *newPlace = findPlaceForNew(new, h);
    if (newPlace->next != NULL && newPlace == *t) {
        newPlace->next = new;
        new
        ->
        prev = newPlace;
        return;
    }
    STUDENT *temp = newPlace;
    new
    ->
    prev = newPlace;
    new
    ->
    next = newPlace->next;
    newPlace->next = new;
    newPlace->next->prev = newPlace;
}