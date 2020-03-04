#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <assert.h>
#include "some_funcs.h"

int partition(
    int n,
    long long int *a,
    int (*less)(long long int, long long int),
    long long int pivot);

void quicksort(
    int n,
    long long int *a,
    int (*less)(long long int, long long int));

#endif
