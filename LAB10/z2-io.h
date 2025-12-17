#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "z2-err.h"

typedef struct student {
    char *name;
    char *surname;
    int age;
    char *address;
    double money;
    struct student *prev;
    struct student *next;
} STUDENT;

void clearSTDIN() {
    fseek(stdin, 0,SEEK_END);
}

double getDouble(char *purpose) {
    double number;
    printf("Enter a %s: ", purpose);
    while (scanf("%lf", &number) != 1) {
        printf("Please enter a number only!\n");
        printf("Enter a %s: ", purpose);
    }
    return number;
}

int getInt(char *purpose) {
    int number;
    printf("Enter a %s:", purpose);
    while (scanf("%d", &number) != 1) {
        printf("Please enter a number only!\n");
        printf("Enter a %s: ", purpose);
    }
    return number;
}

char *getText(char *purpose) {
    char *text = (char *) calloc(100, sizeof(char));
    printf("Enter a %s: ", purpose);
    clearSTDIN();
    while (fgets(text, 99,stdin), strlen(text) == 0) {
        ErrorPost("Enter text please\n");
        printf("Enter a %s: ", purpose);
        clearSTDIN();
    }
    return text;
}


void deleteStudent(STUDENT *student) {
    if (student->prev != NULL) {
        student->prev->next = student->next;
    }
    if (student->next != NULL)
        student->next->prev = student->prev;
    free(student->name);
    free(student->surname);
    free(student->address);
    free(student);
}

STUDENT *addStudentOnTail(STUDENT *LAST) {
    STUDENT *temp = (STUDENT *) calloc(1, sizeof(STUDENT));
    if (temp == NULL) {
        ErrorExit("addStudentOnTail(): memory allocation error", 1);
    }

    temp->prev = LAST;
    temp->next = NULL;
    temp->name = getText("Students Name");
    temp->surname = getText("Students Surname");
    temp->address = getText("Students Address");
    temp->money = getDouble("Students Money");
    temp->age = getInt("Students Age");

    if (LAST != NULL)
        LAST->next = temp;

    return temp;
}

STUDENT *addStudentOnTailWithReadyMemory(STUDENT *LAST, STUDENT *New) {
    STUDENT *temp = (STUDENT *) calloc(1, sizeof(STUDENT));
    if (temp == NULL) {
        ErrorExit("addStudentOnTail(): memory allocation error", 1);
    }

    temp->prev = LAST;
    temp->next = NULL;
    temp->name = New->name;
    temp->surname = New->surname;
    temp->address = New->address;
    temp->money = New->money;
    temp->age = New->age;

    if (LAST != NULL)
        LAST->next = temp;

    return temp;
}


STUDENT *addStudentOnHead(STUDENT *HEAD) {
    STUDENT *temp = (STUDENT *) calloc(1, sizeof(STUDENT));
    if (temp == NULL) {
        ErrorExit("addStudentOnTail(): memory allocation error", 1);
    }
    temp->prev = NULL;
    temp->next = HEAD;
    temp->name = getText("Students Name");
    temp->surname = getText("Students Surname");
    temp->address = getText("Students Address");
    temp->money = getDouble("Students Money");
    temp->age = getInt("Students Age");

    if (HEAD != NULL)
        HEAD->prev = temp;

    return temp;
}


void printAllStudents(STUDENT *st) {
    if (st->next != NULL) {
        printAllStudents(st->next);
    }
    printf("Students Name: %s\n", st->name);
    printf("Students Surname: %s\n", st->surname);
    printf("Students Address: %s\n", st->address);
    printf("Students Money: %lf\n", st->money);
    printf("Students Age: %d\n", st->age);
    printf("------------------------------\n");
}

void printStudent(STUDENT *st) {
    if (st == NULL) {
        ErrorPost("printStudent(): NULL student");
        return;
    }
    printf("Students Name: %s\n", st->name);
    printf("Students Surname: %s\n", st->surname);
    printf("Students Address: %s\n", st->address);
    printf("Students Money: %lf\n", st->money);
    printf("Students Age: %d\n", st->age);
    printf("------------------------------\n");
}

void goBackBy1(FILE* f) {
    int p = ftell(f);
    if (p != 0) {
        fseek(f, p - 1, SEEK_SET);
    }
}

void loadStudentsFromFile(char *filePath, STUDENT *TAIL) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        ErrorExit("File does not exist", 404);
    }

    STUDENT *tmp = calloc(1, sizeof(STUDENT));
    if (tmp == NULL) {
        ErrorExit("loadStudentsFromFile(): Memory allocation failed\n", 400);
    }

    char buffer[100] = {0};
    int result;


    while (1) {
        // Odczytaj imię
        if (!fgets(buffer, sizeof(buffer), file)) {
            break; // Koniec pliku
        }
        buffer[strcspn(buffer, "\n")] = '\0';
        tmp->name = calloc(strlen(buffer) + 1, sizeof(char));
        if (tmp->name == NULL) {
            ErrorExit("Memory allocation failed for name\n", 400);
        }
        strcpy(tmp->name, buffer);

        // Odczytaj nazwisko
        if (!fgets(buffer, sizeof(buffer), file)) {
            break; // Koniec pliku
        }
        buffer[strcspn(buffer, "\n")] = '\0';
        tmp->surname = calloc(strlen(buffer) + 1, sizeof(char));
        if (tmp->surname == NULL) {
            ErrorExit("Memory allocation failed for surname\n", 400);
        }
        strcpy(tmp->surname, buffer);

        // Odczytaj adres
        if (!fgets(buffer, sizeof(buffer), file)) {
            break; // Koniec pliku
        }
        buffer[strcspn(buffer, "\n")] = '\0';
        tmp->address = calloc(strlen(buffer) + 1, sizeof(char));
        if (tmp->address == NULL) {
            ErrorExit("Memory allocation failed for address\n", 400);
        }
        strcpy(tmp->address, buffer);
        goBackBy1(file);

        // Odczytaj wiek
        result = fscanf(file, "%d", &tmp->age);
        if (result != 1) {
            break; // Koniec pliku lub błąd
        }
        // Pomiń znak nowej linii po liczbie
        while (fgetc(file) == '\n');

        // Odczytaj ilość pieniędzy
        result = fscanf(file, "%lf", &tmp->money);
        if (result != 1) {
            break; // Koniec pliku lub błąd
        }
        // Pomiń znak nowej linii po liczbie
        while (fgetc(file) == '\n');

        // Dodaj studenta do listy
        TAIL = addStudentOnTailWithReadyMemory(TAIL, tmp);
        printStudent(tmp);


        // Zaalokuj nową strukturę
        tmp = calloc(1, sizeof(STUDENT));
        if (tmp == NULL) {
            ErrorExit("loadStudentsFromFile(): Memory allocation failed\n", 400);
        }
    }

    // Zwolnij ostatnią alokację, jeśli była
    if (tmp != NULL) {
        if (tmp->name) free(tmp->name);
        if (tmp->surname) free(tmp->surname);
        if (tmp->address) free(tmp->address);
        free(tmp);
    }

    // Zamknij plik po przetworzeniu całej zawartości
    fclose(file);
}
