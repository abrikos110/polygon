#ifndef QUICKSORT_C
#define QUICKSORT_C

#include "quicksort.h"

int partition(
    int n,
    long long int *a,
    int (*less)(long long int, long long int),
    long long int pivot) {

    int p = 0, q = n-1;
    while (p <= q) {
        while (less(a[p], pivot)) // a[p] < pivot
            ++p;
        while (less(pivot, a[q])) // a[q] > pivot
            --q;
        if (p >= q)
            break;
        swap_vp(a + p++, a + q--, sizeof(*a));
    }
    return q+1;
}

void quicksort(
    int n,
    long long int *a,
    int (*less)(long long int, long long int)) {

    if (n <= 1)
        return;
    else if (n == 2) {
        if (less(a[1], a[0]))
            swap_vp(a, a+1, sizeof(*a));
        return;
    }
    else if (n == 3) {
        // move max(a[0], a[1]) to end
        if (less(a[1], a[0]))
            swap_vp(a, a+1, sizeof(*a));
        if (less(a[2], a[1]))
            swap_vp(a+2, a+1, sizeof(*a));
        // sort a[0] and a[1]
        if (less(a[1], a[0]))
            swap_vp(a, a+1, sizeof(*a));
        return;
    }

    long long int pivot = a[n/2];
    int p = partition(n, a, less, pivot);
    quicksort(p, a, less);
    quicksort(n-p, a+p, less);
}

#endif
