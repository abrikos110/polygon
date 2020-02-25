#ifndef SHELLSORT_C
#define SHELLSORT_C

#include "shellsort.h"

void insertionsort(
    int n,
    long long int *a,
    int step,
    int (*less)(long long int, long long int)) {

    if (n <= 1)
        return;
    for (int i = step; i < n; i += step)
        for (int j = i; j >= step && less(a[j], a[j-step]); j -= step)
            swap_vp(a+j, a+j-step, sizeof(*a));
}

int step(int n, int i) {
    int j, ans = 1;
    // from "A new upper bound for shellsort. Robert Sedgewick"
    // https://doi.org/10.1016/0196-6774(86)90001-5
    for (j = 1; ans < n; ++j)
        ans = 2 * (j == 1) + (1 << j - 3) * (1 << (j+1) - 3); // abs(2**j-3) * (2**(j+1)-3)
    j -= 1+i;
    if (j < 0)
        return 0;

    return 2 * (j == 1) + (1 << j - 3) * (1 << (j+1) - 3); // abs(2**j-3) * (2**(j+1)-3)
}

void shellsort(
    int n,
    long long int *a,
    int (*less)(long long int, long long int),
    int (*step)(int, int)) {

    if (n <= 1)
        return;
    for (int i = 0, s; (s = step(n, i)) > 0; ++i)
        for (int j = 0; j < s; ++j)
            insertionsort(n-j, a+j, s, less);
}

#endif
