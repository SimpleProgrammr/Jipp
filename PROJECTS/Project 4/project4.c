#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "DATA_TYPES.h"
#include "FIFO-list.c"
#include "FIFO-array.c"
#include "LIFO-list.c"
#include "LIFO-array.c"
#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>

    char getch() {
        char buf = 0;
        struct termios old = {0};
        fflush(stdout);

        if (tcgetattr(0, &old) < 0)
            perror("tcsetattr()");

        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;

        if (tcsetattr(0, TCSANOW, &old) < 0)
            perror("tcsetattr ICANON");

        if (read(0, &buf, 1) < 0)
            perror("read()");

        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;

        if (tcsetattr(0, TCSADRAIN, &old) < 0)
            perror("tcsetattr ~ICANON");

        return buf;
    }
#endif


enum DATA_TYPE_MODE {
    FIFO_LIST = 1,
    FIFO_ARRAY,
    LIFO_LIST,
    LIFO_ARRAY
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
void LIFO_list_run();
void FIFO_array_run();
void LIFO_array_run();

short searchModeSelection();

void convertTxtFileToBinFile() {
    printf("Converting txt.file\n");
    char buff[1024];
    long total_lines_in_file = 0;
    FILE * txt_file = fopen("dane.txt", "r");
    FILE * bin_file = fopen("Elements.bin", "wb");
    if (bin_file == NULL) {
        fprintf(stderr, "Unable to open \"Elements.bin\" file");
        exit(-404);
    }
    if (txt_file == NULL) {
        fprintf(stderr, "Unable to open \"dane.txt\" file");
        exit(-404);
    }
    while (fgets(buff, sizeof(buff), txt_file) != NULL) {
        total_lines_in_file++;
    }
    long number_of_elements = total_lines_in_file/3;
    fwrite(&number_of_elements, sizeof(long), 1, bin_file);
    fclose(txt_file);
    txt_file = fopen("dane.txt", "r");
    if (txt_file == NULL) {
        fprintf(stderr, "Unable to open \"dane.txt\" file");
        exit(-404);
    }

    STUDENT* st = &(STUDENT){NULL, NULL , 0};


    for (long i = 0; i < number_of_elements; i++) {
        fgets(buff, sizeof(buff), txt_file);
        int len = strlen(buff);
        if (buff[len - 1] == '\n')
            buff[len-1] = '\0';
        st->name = calloc(len, sizeof(char));
        if (st->name == NULL) {
            fprintf(stderr, "Unable to allocate memory for name(convertTxtFileToBinFile();)\n\nn");
            exit(-300);
        }
        strncpy(st->name, buff, len);

        fgets(buff, sizeof(buff), txt_file);
        len = strlen(buff);
        if (buff[len - 1] == '\n')
            buff[len-1] = '\0';
        st->surname = calloc(len, sizeof(char));
        if (st->surname == NULL) {
            fprintf(stderr, "Unable to allocate memory for surname(convertTxtFileToBinFile();)\n\nn");
            exit(-300);
        }
        strncpy(st->surname, buff, len);

        fgets(buff, sizeof(buff), txt_file);
        char* endptr;
        st->bYear = strtol(buff, &endptr, 10);

        savePackageToFile(bin_file, st);

        free(st->name);
        st->name = NULL;
        free(st->surname);
        st->surname = NULL;
    }
    fclose(txt_file);
    fclose(bin_file);
    printf("Conversion success...");
}

int main() {
    convertTxtFileToBinFile();
    printf("Which mode to use?\n"
        "1. FIFO List\n"
        "2. FIFO Array\n"
        "3. LIFO List\n"
        "4. LIFO Array\n");
    int choice = char_to_int((char)getch());;
    switch (choice) {
        case FIFO_LIST:
            FIFO_list_run();
            break;
        case FIFO_ARRAY:
            FIFO_array_run();
            break;
        case LIFO_LIST:
            LIFO_list_run();
            break;
        case LIFO_ARRAY:
            LIFO_array_run();
            break;
        default:
            fprintf(stderr, "Invalid choice\n");
            exit(10);
    }

    return 0;
}

void FIFO_list_run() {

    LIST *HEAD = NULL, *TAIL = NULL;
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
        int choice = char_to_int((char)getch());;
        postOperationName(choice);
        switch (choice) {
            case ADD_ELEMENT:
                STUDENT *st = create_student();
                fifo_list_add_student(&HEAD, &TAIL, st);
                break;
            case PULL_ELEMENT:
                fifo_list_pull_element(&HEAD, &TAIL, true);
                break;
            case SEARCH_ELEMENT:
                fifo_list_search_element(HEAD, TAIL, searchModeSelection());
                break;
            case PRINT_ELEMENTS:
                fifo_list_print_all_elements(&HEAD, &TAIL);
                break;
            case COUNT_ELEMENTS:
                printf("There are %ld elements\n\n", fifo_list_count_elements(&HEAD, &TAIL));
                break;
            case CLEAR_ALL_ELEMENTS:
                fifo_list_clear_all_elements(&HEAD, &TAIL);
                break;
            case SAVE_TO_BINARY:
                fifo_list_save_all_elements_to_file(&HEAD, &TAIL);
                break;
            case READ_FROM_BINARY:
                fifo_list_read_all_elements_from_file(&HEAD, &TAIL);
                break;
            case EXIT:
                fifo_list_clear_all_elements(&HEAD, &TAIL);
                return;
            default:
                fprintf(stderr, "Invalid choice\n");
                break;
        }
    }
}

void FIFO_array_run() {
    STUDENT **studentsArray = NULL;
    long studentsArraySize = 0;

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
        int choice = char_to_int((char)getch());
        postOperationName(choice);
        switch (choice) {
            case ADD_ELEMENT:
                STUDENT *st = create_student();
                studentsArray = fifo_array_add_student(studentsArray, &studentsArraySize, st, true);
                break;
            case PULL_ELEMENT:
                pullRet *pr = fifo_array_pull_student(studentsArray, &studentsArraySize, true);
                studentsArray = pr->arr;
                fifo_array_free_student(pr->st);
                break;
            case SEARCH_ELEMENT:
                studentsArray = fifo_array_search_element(studentsArray, &studentsArraySize, searchModeSelection());
                break;
            case PRINT_ELEMENTS:
                studentsArray = fifo_array_print_all_students(studentsArray, &studentsArraySize);
                break;
            case COUNT_ELEMENTS:
                printf("There are %ld elements\n\n", studentsArraySize);
                break;
            case CLEAR_ALL_ELEMENTS:
                studentsArray = fifo_array_clear_all_elements(studentsArray, &studentsArraySize);
                break;
            case SAVE_TO_BINARY:
                studentsArray = fifo_array_save_all_elements_to_file(studentsArray,&studentsArraySize);
                break;
            case READ_FROM_BINARY:
                studentsArray = fifo_array_read_all_elements_from_file(studentsArray,&studentsArraySize);
                break;
            case EXIT:
                fifo_array_clear_all_elements(studentsArray, &studentsArraySize);
                exit(0);
            default:
                fprintf(stderr, "Invalid choice\n");
                break;
        }
    }
}

void LIFO_list_run() {
    LIST *TOP = NULL, *BOTTOM = NULL;

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
        int choice = char_to_int((char)getch());
        postOperationName(choice);
        switch (choice) {
            case ADD_ELEMENT:
                STUDENT *st = create_student();
                lifo_list_add_student(&TOP, &BOTTOM, st);
                break;
            case PULL_ELEMENT:
                lifo_list_pull_element(&TOP, &BOTTOM, true);
                break;
            case SEARCH_ELEMENT:
                lifo_list_search_element(&TOP, &BOTTOM, searchModeSelection());
                break;
            case PRINT_ELEMENTS:
                lifo_list_print_all_elements(&TOP, &BOTTOM);
                break;
            case COUNT_ELEMENTS:
                printf("There are %ld elements\n\n", fifo_list_count_elements(&TOP, &BOTTOM));
                break;
            case CLEAR_ALL_ELEMENTS:
                lifo_list_clear_all_elements(&TOP, &BOTTOM);
                break;
            case SAVE_TO_BINARY:
                lifo_list_save_all_elements_to_file(&TOP, &BOTTOM);
                break;
            case READ_FROM_BINARY:
                lifo_list_read_all_elements_from_file(&TOP, &BOTTOM);
                break;
            case EXIT:
                lifo_list_clear_all_elements(&TOP, &BOTTOM);
                return;
            default:
                fprintf(stderr, "Invalid choice\n");
                break;
        }
    }
}

void LIFO_array_run() {
    STUDENT **studentsArray = NULL;
    long studentsArraySize = 0;

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
        int choice = char_to_int((char)getch());
        postOperationName(choice);
        switch (choice) {
            case ADD_ELEMENT:
                STUDENT *st = create_student();
                studentsArray = lifo_array_add_student(studentsArray, &studentsArraySize, st, true);
                break;
            case PULL_ELEMENT:
                pullRet *pr = lifo_array_pull_student(studentsArray, &studentsArraySize, true);
                studentsArray = pr->arr;
                lifo_array_free_student(pr->st);
                break;
            case SEARCH_ELEMENT:
                studentsArray = lifo_array_search_element(studentsArray, &studentsArraySize, searchModeSelection());
                break;
            case PRINT_ELEMENTS:
                studentsArray = lifo_array_print_all_students(studentsArray, &studentsArraySize);
                break;
            case COUNT_ELEMENTS:
                printf("There are %ld elements\n\n", studentsArraySize);
                break;
            case CLEAR_ALL_ELEMENTS:
                studentsArray = lifo_array_clear_all_elements(studentsArray, &studentsArraySize);
                break;
            case SAVE_TO_BINARY:
                studentsArray = lifo_array_save_all_elements_to_file(studentsArray,&studentsArraySize);
                break;
            case READ_FROM_BINARY:
                studentsArray = lifo_array_read_all_elements_from_file(studentsArray,&studentsArraySize);
                break;
            case EXIT:
                lifo_array_clear_all_elements(studentsArray, &studentsArraySize);
                exit(0);
            default:
                fprintf(stderr, "Invalid choice\n");
                break;
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
    int choice = char_to_int((char)getch());;
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
