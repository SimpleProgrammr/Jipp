#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "DATA_TYPES.h"
#include "FileIO.h"

LIST *fifo_list_pull_element(LIST **HEAD, LIST **TAIL, bool post);

void fifo_list_add_student(LIST **HEAD, LIST **TAIL, STUDENT *ST) {
    LIST *tmpNewElement = calloc(1, sizeof(LIST));
    if (tmpNewElement == NULL) {
        fprintf(stderr, "Unable to allocate memory");
        exit(-300);
    }

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

void fifo_list_add_student_debug(LIST **HEAD, LIST **TAIL, const STUDENT *ST) {
    LIST *tmpNewElement = calloc(1, sizeof(LIST));
    if (tmpNewElement == NULL) {
        fprintf(stderr, "Unable to allocate memory");
        exit(-300);
    }

    tmpNewElement->data = calloc(1,sizeof(STUDENT));
        tmpNewElement->data->name = calloc(1, sizeof(strlen(ST->name)));
            memcpy(tmpNewElement->data->name, ST->name, strlen(ST->name));
        tmpNewElement->data->surname= calloc(1, sizeof(strlen(ST->surname)));
            memcpy(tmpNewElement->data->surname, ST->surname, strlen(ST->surname));
        tmpNewElement->data->bYear = ST->bYear;


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

void fifo_list_free_element(LIST **el) {
    if (*el == NULL) {
        fprintf(stderr, "List element is NULL\n");
        return;
    }
    if ((*el)->data == NULL) {
        fprintf(stderr, "Elements data is NULL\n");
        free(el);
        return;
    }

    if ((*el)->data->name != NULL) {
        free((*el)->data->name);
        (*el)->data->name = NULL;
    }
    if ((*el)->data->surname != NULL){
        free((*el)->data->surname);
        (*el)->data->surname = NULL;
    }
    free((*el)->data);
    (*el)->data = NULL;

    free(*el);
    *el = NULL;
}

void fifo_list_add_element(LIST **HEAD, LIST **TAIL, LIST *EL) {
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

void fifo_list_print_element(const STUDENT *st) {
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
           "Birth year: %d\n\n",
           st->name, st->surname, st->bYear);
}

long fifo_list_count_elements(LIST **HEAD, LIST **TAIL) {
    LIST *tmpHEAD = NULL, *tmpTAIL = NULL;
    long count = 0;
    //Pulling to count
    while (*HEAD != NULL && *TAIL != NULL) {
        LIST *tmpEl = fifo_list_pull_element(HEAD, TAIL, false);
        fifo_list_add_element(&tmpHEAD, &tmpTAIL, tmpEl);
        count++;
    }
    //Putting back on place
    while (tmpHEAD != NULL && tmpTAIL != NULL) {
        LIST *tmpEl = fifo_list_pull_element(&tmpHEAD, &tmpTAIL, false);
        fifo_list_add_element(HEAD, TAIL, tmpEl);
    }
    return count;
}

void fifo_list_search_element(LIST *HEAD, LIST *TAIL, short mode) {
    STUDENT *ST = calloc(1, sizeof(STUDENT));
    if (ST == NULL) {
        fprintf(stderr, "Unable to allocate memory");
        exit(-300);
    }
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
            free(ST);
            return;
    }
    long countedElements = fifo_list_count_elements(&HEAD, &TAIL);
    for (long i = 0; i < countedElements; i++) {
        LIST *tmpElement = fifo_list_pull_element(&HEAD, &TAIL, false);
        fifo_list_add_element(&HEAD, &TAIL, tmpElement);
        switch (mode) {
            case 1: //by Name
                if (strcmp(ST->name, tmpElement->data->name) == 0)
                    fifo_list_print_element(tmpElement->data);
                break;
            case 2: //by Surname
                if (strcmp(ST->surname, tmpElement->data->surname) == 0)
                    fifo_list_print_element(tmpElement->data);
                break;
            case 3: //by bYear
                if (ST->bYear == tmpElement->data->bYear)
                    fifo_list_print_element(tmpElement->data);
                break;
            default: ;
        }
    }
    free(ST);
    ST = NULL;
}



LIST *fifo_list_pull_element(LIST **HEAD, LIST **TAIL, bool post) {
    if (*HEAD == NULL && *TAIL == NULL) {
        fprintf(stderr, "Nothing to pull\n");
        return NULL;
    }

    if (post)
        fifo_list_print_element((*HEAD)->data);

    LIST *tmpElement = *HEAD;
    if (*HEAD == *TAIL) {
        *TAIL = NULL;
        *HEAD = *TAIL;
    } else if ((*HEAD)->prev != NULL) {
        *HEAD = (*HEAD)->prev;
    }

    return tmpElement;
}

void fifo_list_print_all_elements(LIST **HEAD, LIST **TAIL) {
    LIST *tmpHEAD = NULL, *tmpTAIL = NULL;
    //Pulling to print
    while (*HEAD != NULL && *TAIL != NULL) {
        LIST *tmpEl = fifo_list_pull_element(HEAD, TAIL, true);
        fifo_list_add_element(&tmpHEAD, &tmpTAIL, tmpEl);
    }
    //Putting back on place
    while (tmpHEAD != NULL && tmpTAIL != NULL) {
        LIST *tmpEl = fifo_list_pull_element(&tmpHEAD, &tmpTAIL, false);
        fifo_list_add_element(HEAD, TAIL, tmpEl);
    }
}

void fifo_list_clear_all_elements(LIST **HEAD, LIST **TAIL) {
    while (*HEAD != NULL && *TAIL != NULL) {
        LIST *tmpEl = fifo_list_pull_element(HEAD, TAIL, true);
        printf("Freeing...\n");
        fifo_list_free_element(&tmpEl);
    }
    printf("All elements are gone!\n");
}

void fifo_list_save_all_elements_to_file(LIST **HEAD, LIST **TAIL) {
    FILE* file = fopen("Elements.bin", "wb");

    //<elements count>[int]
    long count = fifo_list_count_elements(HEAD, TAIL);
    fwrite(&count, sizeof(long), 1, file);


    LIST *tmpHEAD = NULL, *tmpTAIL = NULL;
    //Pulling to save
    while (*HEAD != NULL && *TAIL != NULL) {
        LIST *tmpEl = fifo_list_pull_element(HEAD, TAIL, true);
        fifo_list_add_element(&tmpHEAD, &tmpTAIL, tmpEl);
        savePackageToFile(file,tmpEl->data);
    }
    //Putting back on place
    while (tmpHEAD != NULL && tmpTAIL != NULL) {
        LIST *tmpEl = fifo_list_pull_element(&tmpHEAD, &tmpTAIL, false);
        fifo_list_add_element(HEAD, TAIL, tmpEl);
    }
    fclose(file);
}

void fifo_list_read_all_elements_from_file(LIST **HEAD, LIST **TAIL) {
    FILE* file = fopen("Elements.bin", "rb");
    long count = 0;
    fread(&count, sizeof(long), 1, file);

    for (long i = 0; i < count; i++) {
        STUDENT* tmpElement = readPackageFromFile(file);
        fifo_list_add_student(HEAD, TAIL, tmpElement);
    }

    fclose(file);
}
