#pragma once
#include <stdio.h>
#include <stdlib.h>

void ErrorExit(char *s, int code) {
    perror(s);
    exit(code);
}

void ErrorPost(char *s) {
    perror(s);
}