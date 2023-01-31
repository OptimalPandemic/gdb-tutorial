#include <stdio.h>
#include <stdlib.h>
#include "testRunner.h"

void runTest(int (*test)(), char* name, int *p, int *f) {
    char* result;
    if (test()) {
        result = "PASS";
        (*p)++;
    }
    else {
        result = "FAIL";
        (*f)++;
    }
    printf("%-50s%-8s\n", name, result);
}