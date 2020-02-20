#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <stdlib.h>
#include <assert.h>

long long int rand_lli(unsigned only_nonnegative);

extern long long int swaps; // WORKAROUND
void swap_vp(void *a, void *b, int sz);

long long int median3(
    long long int a,
    long long int b,
    long long int c,
    int (*less)(long long int, long long int));

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
