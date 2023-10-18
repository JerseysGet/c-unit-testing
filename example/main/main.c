#include "main.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int factorial(int n) {
    sleep(1);
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

char* string() {
    sleep(2);
    char* ret = (char*) malloc(sizeof(char) * 128);
    strcpy(ret, "test");
    return ret;
}