#include <stdio.h>
#include <stdlib.h>
#include "z2-io.h"
#include "z2-err.h"


STUDENT *HEAD;
STUDENT *TAIL;

char fpath[] = "./sts.txt";


int main() {
    TAIL = HEAD = addStudentOnHead(HEAD);
    clearSTDIN();

    while (1) {
        system("clear");
        printf("1. addStudentOnHead()\n");
        printf("2. addStudentOnTail()\n");
        printf("3. loadStudestsFromFilel()\n");
        printf("8. printAllStudents(HEAD -> TAIL)\n");
        printf("9. printAllStudents(TAIL -> HEAD)\n");
        printf("0. Exit\n");
        //clearSTDIN();
        char c = getc(stdin);
        switch (c) {
            case '1':
                HEAD = addStudentOnHead(HEAD);
                break;
            case '2':
                TAIL = addStudentOnTail(TAIL);
            case '3':
                if (fpath[0] == '\0')
                    loadStudentsFromFile(getText("File path"), TAIL);
                else
                    loadStudentsFromFile(fpath, TAIL);
                break;
            case'8':
                printAllStudents(TAIL);
                break;
            case'9':
                printAllStudents(HEAD);
                break;
            case '0':
                exit(0);
            default:
                break;
        }
        //clearSTDIN();
        printf("Click ENTER to continue...\n");
        getchar();
    }
}
