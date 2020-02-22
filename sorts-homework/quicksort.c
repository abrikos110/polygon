#ifndef QUICKSORT_C
#define QUICKSORT_C

#include "quicksort.h"

int partition(
    int n,
    long long int *a,
    int (*less)(long long int, long long int),
     long long int pivot) {

    // need min(a) <= pivot <= max(a)
    assert(n > 1);
    int p = -1, q = n;
    while (1) {
        do {
            ++p;
        } while (less(a[p], pivot)); // a[p] < pivot
        do {
            --q;
        } while (less(pivot, a[q])); // a[q] > pivot
        if (p >= q)
            break;
        swap_vp(a+p, a+q, sizeof(*a));
    }
    /* always 0 <= i < p ==> a[i] <= pivot
       and    q < i < n ==> a[i] >= pivot

       p > q ==> 0 <= i < p ==> a[i] <= pivot
                 and q < p <= i < n ==> a[i] >= pivot
       p == q ==> p and q stopped on same value ==> a[p] >= pivot >= a[q]
    */

    assert(!less(a[p], pivot));
    assert(p != n); // TODO: prove it
    // WORKAROUND to guarantee decreasing of size of array in quicksort
    if (p == 0) {
        int mini = 0;
        for (int i = 0; i < n; ++i)
            if (less(a[i], a[mini]))
                mini = i;
        if (mini != 0)
            swap_vp(a+mini, a, sizeof(*a));
        p = 1;
    }
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

    long long int pivot = median3(
        a[rand_lli(1) % n],
        a[rand_lli(1) % n],
        a[rand_lli(1) % n], less);
    int p = partition(n, a, less, pivot);
    quicksort(p, a, less);
    quicksort(n-p, a+p, less);
}

#endif
