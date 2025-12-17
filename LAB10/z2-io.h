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

STUDENT *getLastStudentFromTAIL(STUDENT* TAIL) {
    if (TAIL == NULL || TAIL->next == (STUDENT *)0xfeeefeeefeeefeee) {
        return NULL;
    }
    if (TAIL->prev == NULL) {
        return TAIL;
    }
    return getLastStudentFromTAIL(TAIL->prev) == NULL ? TAIL : getLastStudentFromTAIL(TAIL->prev);
}

STUDENT * getLastStudentFromHEAD(STUDENT * HEAD) {
    if (HEAD == NULL || HEAD->next == (STUDENT *)0xfeeefeeefeeefeee) {
        return NULL;
    }
    if (HEAD->next == NULL) {
        return HEAD;
    }
    return getLastStudentFromHEAD(HEAD->next) == NULL ? HEAD : getLastStudentFromHEAD(HEAD->next);
}

void controlDB(STUDENT **HEAD, STUDENT** TAIL) {

            STUDENT *temp = getLastStudentFromTAIL(*TAIL);
        *HEAD = temp == NULL ? *HEAD : temp ;

            temp = getLastStudentFromHEAD(*HEAD);
        *TAIL = temp == NULL ? *TAIL : temp;

}

char *replaceNewLine(char *str, char nchar) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '\n')
            str[i] = nchar;
        i++;
    }
    return str;
}

char *clearNewLine(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '\n')
            str[i] = '\0';
        i++;
    }
    return str;
}

char *replaceChar(char *str,char oldChar, char nchar) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == oldChar)
            str[i] = nchar;
        i++;
    }
    return str;
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
    fflush(stdin);
    while (fgets(text, 99,stdin), strlen(text) <= 1) {
        ErrorPost("Enter text please\n");
        printf("Enter a %s: ", purpose);
        fflush(stdin);
    }
    return replaceNewLine(text,'\0');
}

void deleteStudent(STUDENT *student, STUDENT **HEAD, STUDENT **TAIL) {
    if (student == NULL) {
        ErrorPost("deleteStudent(): student is null");
    }
    printf("Deleting student: %s\n", student->name);

    if (student->prev != NULL) {
        student->prev->next = student->next;

    }
    if (student->next != NULL) {
        student->next->prev = student->prev;

    }
    if (*HEAD == student && *HEAD != NULL ) {
            *HEAD = student->next;
        }
    if (*TAIL == student && *TAIL != NULL ) {
            *TAIL = student->prev;
        }

    free(student->name);student->next = NULL;
    free(student->surname);student->surname=NULL;
    free(student->address);student->address=NULL;
    student->next = NULL;
    student->prev = NULL;
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
    if (New == NULL) {
        ErrorExit("addStudentOnTail(): New object is null", 1);
    }

    if (LAST != NULL) {
        LAST->next = New;
        LAST->next->prev = LAST;
    }
    return New;
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

void printAllStudents(const STUDENT *st) {
    if (st == NULL) {
        ErrorPost("printStudent(): NULL student");
        return;
    }
    if (st->prev != NULL) {
        printAllStudents(st->prev);
    }

    printf("Students Name: %s\n", st->name);
    printf("Students Surname: %s\n", st->surname);
    printf("Students Address: %s\n", st->address);
    printf("Students Money: %lf\n", st->money);
    printf("Students Age: %d\n", st->age);
    printf("------------------------------\n");
}

void printStudent(const STUDENT *st) {
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

void goBackBy1(FILE *f) {
    int p = ftell(f);
    if (p != 0) {
        fseek(f, p - 1, SEEK_SET);
    }
}

void skipEmptyLines(FILE *f) {
    char c= 0;
    while (c = fgetc(f),c == '\n' || c == ' ');
    goBackBy1(f);
}

STUDENT * loadStudentsFromFile(const char *filePath, STUDENT *TAIL) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        ErrorExit("File does not exist", 404);
    }

    STUDENT *tmp = calloc(1, sizeof(STUDENT));
    if (tmp == NULL) {
        ErrorExit("loadStudentsFromFile(): Memory allocation failed\n", 400);
    }

    char *buffer = calloc(100, sizeof(char));
    if (buffer == NULL) {
        ErrorExit("loadStudentsFromFile(): Memory allocation failed\n", 400);
    }
    int bufferSize = 100*sizeof(char);


    while (1) {
        // Odczytaj imię
        if (!fgets(buffer, bufferSize, file)) break;

        buffer = clearNewLine(buffer);
        tmp->name = calloc(strlen(buffer) + 1, sizeof(char));
        if (tmp->name == NULL) {
            ErrorExit("Memory allocation failed for name\n", 400);
        }
        strcpy(tmp->name, buffer);

        // Odczytaj nazwisko
        if (!fgets(buffer, bufferSize, file)) break;

        buffer = clearNewLine(buffer);
        tmp->surname = calloc(strlen(buffer) + 1, sizeof(char));
        if (tmp->surname == NULL) {
            ErrorExit("Memory allocation failed for surname\n", 400);
        }
        strcpy(tmp->surname, buffer);

        // Odczytaj adres
        if (!fgets(buffer, bufferSize, file)) break;

        buffer = clearNewLine(buffer);
        tmp->address = calloc(strlen(buffer) + 1, sizeof(char));
        if (tmp->address == NULL) {
            ErrorExit("Memory allocation failed for address\n", 400);
        }
        strcpy(tmp->address, buffer);

        // Odczytaj wiek
        if (fscanf(file, "%d", &tmp->age) != 1) {
            break; // Koniec pliku lub błąd
        }
        // Pomiń znak nowej linii po liczbie
        while (fgetc(file) == '\n');
        goBackBy1(file);

        // Odczytaj ilość pieniędzy
        if (fscanf(file, "%lf", &tmp->money) != 1) {
            break; // Koniec pliku lub błąd
        }
        // Pomiń znak nowej linii po liczbie
        skipEmptyLines(file);

        printStudent(tmp);
        // Dodaj studenta do listy
        TAIL = addStudentOnTailWithReadyMemory(TAIL, tmp);

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
        tmp = NULL;
    }

    // Zamknij plik po przetworzeniu całej zawartości
    if (buffer!= NULL) free(buffer);
    fclose(file);
    return TAIL;
}

STUDENT *getStudentByName(STUDENT *st, char *name) {
    STUDENT *sss;
    if (st == NULL) {
        return NULL;
    }
    if (st->next != NULL) {
        sss = getStudentByName(st->next, name);
        if (sss != NULL) {
            return sss;
        }
    }
    if (strcmp(name, st->name) == 0) {
        return st;
    }
    return NULL;
}

STUDENT *getStudentBySurname(STUDENT *st, char *surname) {
    STUDENT *sss;
    if (st == NULL) {
        return NULL;
    }
    if (st->next != NULL) {
        sss = getStudentBySurname(st->next, surname);
        if (sss != NULL) {
            return sss;
        }
    }
    if (strcmp(surname, st->surname) == 0) {
        return st;
    }
    return NULL;
}

STUDENT *getStudentByAddress(STUDENT *st, char *address) {
    STUDENT *sss;
    if (st == NULL) {
        return NULL;
    }
    if (st->next != NULL) {
        sss = getStudentByAddress(st->next, address);
        if (sss != NULL) {
            return sss;
        }
    }
    if (strcmp(address, st->address) == 0) {
        return st;
    }
    return NULL;
}

STUDENT *getStudentByMoney(STUDENT *st, double money) {
    STUDENT *sss;
    if (st == NULL) {
        return NULL;
    }
    if (st->next != NULL) {
        sss = getStudentByMoney(st->next, money);
        if (sss != NULL) {
            return sss;
        }
    }
    if (money == st->money) {
        return st;
    }
    return NULL;
}

STUDENT *getStudentByAge(STUDENT *st, int age) {
    STUDENT *sss;
    if (st == NULL) {
        return NULL;
    }
    if (st->next != NULL) {
        sss = getStudentByAge(st->next, age);
        if (sss != NULL) {
            return sss;
        }
    }
    if (age == st->age) {
        return st;
    }
    return NULL;
}

STUDENT *findRichestStudent(STUDENT *st, int min) {
    if (st == NULL) {
        ErrorPost("Null Students");
        return NULL;
    }
    STUDENT *tmp = NULL;
    if (st->next != NULL) {
        tmp = findRichestStudent(st->next, min);
        if (tmp->money > st->money) {
            return tmp;
        }
        return st;
    }
    return st;
}

int getLength(const STUDENT *st) {

    static int len = 0;
    len = 0;
    if (st == NULL) {
        return len;
    }
    if (st->next != NULL) {
        getLength(st->next);
    }
    len++;
    return len;
}

void freeAllStudents(const STUDENT *st, STUDENT **HEAD, STUDENT **TAIL) {
    if (st == NULL) {
        ErrorPost("freeAllStudents(): No student to free\n");
        return;
    }
    if (st->next != NULL) {
        freeAllStudents(st->next, HEAD, TAIL);
    }
    deleteStudent(st, HEAD, TAIL);
}
