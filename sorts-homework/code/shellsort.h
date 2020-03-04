#ifndef SHELLSORT_H
#define SHELLSORT_H

#include <assert.h>
#include "some_funcs.h"

void insertionsort(
    int n,
    long long int *a,
    int step,
    int (*less)(long long int, long long int));

int step(int n, int i);

void shellsort(
    int n,
    long long int *a,
    int (*less)(long long int, long long int),
    int (*step)(int, int));

#endif
