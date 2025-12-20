#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>

#include "z2-io.h"
#include "z2-err.h"


STUDENT *HEAD = NULL;
STUDENT *TAIL = NULL;
#ifdef _WIN32
    char fpath[] = ".\\sts.txt";
    #define CLEAR_CONSOLE system("cls");
#else
    char fpath[] = "./sts.txt";
    #define CLEAR_CONSOLE system("cls");
#endif

void deleteMenu();

int main() {
    //TAIL = HEAD = addStudentOnHead(HEAD);
    fflush(stdin);

    while (1) {
        CLEAR_CONSOLE;
        Sleep(25);
        fflush(stdout);

        printf("1. addStudentOnHead()\n");
        printf("2. addStudentOnTail()\n");
        printf("3. loadStudentsFromFile()\n");
        printf("4. findRichestStudent()\n");
        printf("5. getLength()\n");
        printf("6. deleteStudent()\n");
        printf("9. printAllStudents(TAIL -> HEAD)\n");
        printf("0. Exit\n");
        fflush(stdout);
        fflush(stdin);
        char c = getc(stdin);
        switch (c) {
            case '1':
                HEAD = addStudentOnHead(HEAD);
                break;
            case '2':
                TAIL = addStudentOnTail(TAIL);
                break;
            case '3':
                if (fpath[0] == '\0')
                    TAIL = loadStudentsFromFile(getText("File path"), TAIL);
                else
                    TAIL = loadStudentsFromFile(fpath, TAIL);
                break;

            case '4':
                printStudent(findRichestStudent(HEAD,0));
                break;

            case '5':
                printf("Currently registered students: %d\n",getLength(HEAD));
                break;

            case '6':
                deleteMenu();
                break;

            case'9':
                printAllStudents(TAIL);
                break;
            case '0':
                freeAllStudents(HEAD, HEAD, TAIL);
                exit(0);
            default:
                break;
        }
        controlDB(&HEAD, &TAIL);
        fflush(stdin);
        printf("Click ENTER to continue...\n");
        fflush(stdout);
        getc(stdin);
    }
}

void deleteMenu() {
STUDENT *student = NULL;
    fflush(stdout);
    bool researchModeMenu = true;;
    while (researchModeMenu) {
        system("cls");
        printf("Choose option of deletion:\n");
        printf("1. by Name\n");
        printf("2. by Surname\n");
        printf("3. by Address\n");
        printf("4. by Money\n");
        printf("5. by Age\n");
        printf("0. GO BACK\n");
        fflush(stdout);
        char c = getc(stdin);


        switch (c) {
            case '1':
                student = getStudentByName(HEAD,getText("Name"));
                researchModeMenu = false;
                break;
            case '2':
                student = getStudentBySurname(HEAD,getText("Surname"));
                researchModeMenu = false;
                break;
            case '3':
                student = getStudentByAddress(HEAD,getText("Address"));
                researchModeMenu = false;
                break;
            case '4':
                student = getStudentByMoney(HEAD,getDouble("Money"));
                researchModeMenu = false;
                break;
            case '5':
                student = getStudentByAge(HEAD,getInt("Age"));
                researchModeMenu = false;
                break;
            case '0':
                return;
        }

    }
    if (student == NULL) {
            ErrorPost("There is no student with this value assigned");
            return;
        }
        deleteStudent(student, &HEAD, &TAIL);

}
