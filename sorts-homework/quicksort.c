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
    assert(p > 0 && p != n);
    return p;
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

    int i = rand_lli(1) % n,
        j = rand_lli(1) % n,
        k = rand_lli(1) % n;
    j = (j + (j == i)) % n;
    if (k == i || k == j) {
        if ((k + 1) % n == i || (k + 1) % n == j)
            ++k;
        k = (k + 1) % n;
    }
    // i != j != k
    long long int pivot = median3(a[i], a[j], a[k], less);
    int p = partition(n, a, less, pivot);
    quicksort(p, a, less);
    quicksort(n-p, a+p, less);
}

#endif
