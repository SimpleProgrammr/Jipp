#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "DATA_TYPES.h"
#include "FileIO.h"

LIST *lifo_list_pull_element(LIST **TOP, LIST **BOTTOM, bool post);

void lifo_list_add_student(LIST **TOP, LIST **BOTTOM, STUDENT *ST) {
    LIST *tmpNewElement = calloc(1, sizeof(LIST));
    if (tmpNewElement == NULL) {
        fprintf(stderr, "Unable to allocate memory");
        exit(-300);
    }

    tmpNewElement->data = ST;
    tmpNewElement->next = NULL;
    tmpNewElement->prev = *TOP;

    if (*TOP == NULL) {
        *TOP = tmpNewElement;
    }
    if (*BOTTOM == NULL) {
        *BOTTOM = tmpNewElement;
    } else {
        (*TOP)->next = tmpNewElement;
        *TOP = tmpNewElement;
    }
}

void lifo_list_add_student_debug(LIST **TOP, LIST **BOTTOM, const STUDENT *ST) {
    LIST *tmpNewElement = calloc(1, sizeof(LIST));
    if (tmpNewElement == NULL) {
        fprintf(stderr, "Unable to allocate memory");
        exit(-300);
    }

    tmpNewElement->data = calloc(1, sizeof(STUDENT));
    tmpNewElement->data->name = calloc(1, sizeof(strlen(ST->name)));
    memcpy(tmpNewElement->data->name, ST->name, strlen(ST->name));
    tmpNewElement->data->surname = calloc(1, sizeof(strlen(ST->surname)));
    memcpy(tmpNewElement->data->surname, ST->surname, strlen(ST->surname));
    tmpNewElement->data->bYear = ST->bYear;


    tmpNewElement->next = NULL;
    tmpNewElement->prev = *TOP;

    if (*TOP == NULL) {
        *TOP = tmpNewElement;
    }
    if (*BOTTOM == NULL) {
        *BOTTOM = tmpNewElement;
    } else {
        (*TOP)->next = tmpNewElement;
        *TOP = tmpNewElement;
    }
}

void lifo_list_free_element(LIST **el) {
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
    if ((*el)->data->surname != NULL) {
        free((*el)->data->surname);
        (*el)->data->surname = NULL;
    }
    free((*el)->data);
    (*el)->data = NULL;

    free(*el);
    *el = NULL;
}

void lifo_list_add_element(LIST **TOP, LIST **BOTTOM, LIST *EL) {
    EL->next = NULL;
    EL->prev = *TOP;

    if (*TOP == NULL) {
        *TOP = EL;
    }
    if (*BOTTOM == NULL) {
        *BOTTOM = EL;
    } else {
        (*TOP)->next = EL;
        *TOP = EL;
    }
}

void lifo_list_print_element(const STUDENT *st) {
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

long lifo_list_count_elements(LIST **TOP, LIST **BOTTOM) {
    LIST *tmpTOP = NULL, *tmpBOTTOM = NULL;
    long count = 0;
    //Pulling to count
    while (*TOP != NULL && *BOTTOM != NULL) {
        LIST *tmpEl = lifo_list_pull_element(TOP, BOTTOM, false);
        lifo_list_add_element(&tmpTOP, &tmpBOTTOM, tmpEl);
        count++;
    }
    //Putting back on place
    while (tmpTOP != NULL && tmpBOTTOM != NULL) {
        LIST *tmpEl = lifo_list_pull_element(&tmpTOP, &tmpBOTTOM, false);
        lifo_list_add_element(TOP, BOTTOM, tmpEl);
    }
    return count;
}

void lifo_list_search_element(LIST *TOP, LIST *BOTTOM, short mode) {
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
    long countedElements = lifo_list_count_elements(&TOP, &BOTTOM);
    for (long i = 0; i < countedElements; i++) {
        LIST *tmpElement = lifo_list_pull_element(&TOP, &BOTTOM, false);
        lifo_list_add_element(&TOP, &BOTTOM, tmpElement);
        switch (mode) {
            case 1: //by Name
                if (strcmp(ST->name, tmpElement->data->name) == 0)
                    lifo_list_print_element(tmpElement->data);
                break;
            case 2: //by Surname
                if (strcmp(ST->surname, tmpElement->data->surname) == 0)
                    lifo_list_print_element(tmpElement->data);
                break;
            case 3: //by bYear
                if (ST->bYear == tmpElement->data->bYear)
                    lifo_list_print_element(tmpElement->data);
                break;
            default: ;
        }
    }
    free(ST);
    ST = NULL;
}


LIST *lifo_list_pull_element(LIST **TOP, LIST **BOTTOM, bool post) {
    if (*TOP == NULL && *BOTTOM == NULL) {
        fprintf(stderr, "Nothing to pull\n");
        return NULL;
    }

    if (post)
        lifo_list_print_element((*TOP)->data);

    LIST *tmpElement = *TOP;
    if (*TOP == *BOTTOM) {
        *BOTTOM = NULL;
        *TOP = *BOTTOM;
    } else if ((*TOP)->prev != NULL) {
        *TOP = (*TOP)->prev;
    }

    return tmpElement;
}

void lifo_list_print_all_elements(LIST **TOP, LIST **BOTTOM) {
    LIST *tmpTOP = NULL, *tmpBOTTOM = NULL;
    //Pulling to print
    while (*TOP != NULL && *BOTTOM != NULL) {
        LIST *tmpEl = lifo_list_pull_element(TOP, BOTTOM, true);
        lifo_list_add_element(&tmpTOP, &tmpBOTTOM, tmpEl);
    }
    //Putting back on place
    while (tmpTOP != NULL && tmpBOTTOM != NULL) {
        LIST *tmpEl = lifo_list_pull_element(&tmpTOP, &tmpBOTTOM, false);
        lifo_list_add_element(TOP, BOTTOM, tmpEl);
    }
}

void lifo_list_clear_all_elements(LIST **TOP, LIST **BOTTOM) {
    while (*TOP != NULL && *BOTTOM != NULL) {
        LIST *tmpEl = lifo_list_pull_element(TOP, BOTTOM, true);
        printf("Freeing...\n");
        lifo_list_free_element(&tmpEl);
    }
    printf("All elements are gone!\n");
}

void lifo_list_save_all_elements_to_file(LIST **TOP, LIST **BOTTOM) {
    FILE *file = fopen("Elements.bin", "wb");

    //<elements count>[int]
    long count = lifo_list_count_elements(TOP, BOTTOM);
    fwrite(&count, sizeof(long), 1, file);


    LIST *tmpTOP = NULL, *tmpBOTTOM = NULL;
    //Pulling to save
    while (*TOP != NULL && *BOTTOM != NULL) {
        LIST *tmpEl = lifo_list_pull_element(TOP, BOTTOM, true);
        lifo_list_add_element(&tmpTOP, &tmpBOTTOM, tmpEl);
        savePackageToFile(file, tmpEl->data);
    }
    //Putting back on place
    while (tmpTOP != NULL && tmpBOTTOM != NULL) {
        LIST *tmpEl = lifo_list_pull_element(&tmpTOP, &tmpBOTTOM, false);
        lifo_list_add_element(TOP, BOTTOM, tmpEl);
    }
    fclose(file);
}

void lifo_list_read_all_elements_from_file(LIST **TOP, LIST **BOTTOM) {
    FILE *file = fopen("Elements.bin", "rb");
    long count = 0;
    fread(&count, sizeof(long), 1, file);

    for (long i = 0; i < count; i++) {
        STUDENT *tmpElement = readPackageFromFile(file);
        lifo_list_add_student(TOP, BOTTOM, tmpElement);
    }

    fclose(file);
}
