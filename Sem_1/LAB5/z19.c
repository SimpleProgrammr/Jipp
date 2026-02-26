#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int moje_strcmp(const char *t1, const char *t2) {
    if (t1 == NULL || t2 == NULL) {
        return -1;
    }

    int i = 0;
    while (t1[i] != '\0' && t2[i] != '\0') {
        if (tolower(t1[i]) != tolower(t2[i])) {
            return 1;
        }
        i++;
    }

    if (t1[i] == '\0' && t2[i] == '\0') {
        return 0;
    } else {
        return 1;
    }
}

char *moje_strcat(char *tt, const char *t2) {
    if (tt == NULL || t2 == NULL) {
        fprintf(stderr, "Error: NULL pointer passed to moje_strcat\n");
        exit(-1);
    }

    int baselen = strlen(tt);

    int t2len = strlen(t2);

    int i = 0;
    while (i < t2len) {
        tt[baselen + i] = t2[i];
        i++;
    }
    tt[baselen + i] = '\0';

    return tt;
}

char *moje_strcpy(char *tt, const char *t2) {
    if (tt == NULL || t2 == NULL) {
        fprintf(stderr, "Error: NULL pointer passed to moje_strcpy\n");
        exit(-1);
    }

    int i = 0;
    while (t2[i] != '\0') {
        tt[i] = t2[i];
        i++;
    }
    tt[i] = '\0';

    return tt;
}

int main() {
    char t1[] = "Hello";
    char t2[] = "World";
    char t3[100] = "";

    printf("strcmp result: %d\n", moje_strcmp(t1, t2));
    printf("strcpy result: %s\n", moje_strcpy(t3, t1));
    printf("strcat result: %s\n", moje_strcat(t3, t2));

    return 0;
}