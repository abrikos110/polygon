#ifndef QUICKSORT_C
#define QUICKSORT_C

#include "quicksort.h"

long long int rand_lli(unsigned only_nonnegative) {
    static unsigned long long int M = 1ll + RAND_MAX;
    static unsigned log2M = 0, calculated_consts = 0;

    if (!calculated_consts) {
        assert((M & (M-1)) == 0 /* check if M is power of 2*/ );
        assert(8 == sizeof(long long int));
        for (unsigned i = 0; i < 64; ++i)
            if (M == 1ull << i) {
                log2M = i;
                break;
            }
        calculated_consts = 1;
    }

    long long int ans = 0;
    unsigned i;
    for (i = 0; i + log2M < 63; i += log2M) // fill floor(63/log2M)*log2M bits
        ans = (ans << log2M) | rand();
    int r = rand();
    if (i < 63)
        ans = (ans << (63-i))
              | (r & ((1 << (63-i)) - 1)); // fill last 63-i bits
    if (!only_nonnegative && (r & (1 << (log2M-1)))) // use last bit for sign
        ans = -ans - 1; // last bit of r was not used because 63-i < log2M

    return ans;
}

long long int swaps = 0; // WORKAROUND
void swap_vp(void *a, void *b, int sz) {
    if (a == b)
        return;
    ++swaps;
    unsigned char *x = a, *y = b;
    for (int i = 0; i < sz; ++i) {
        x[i] ^= y[i];
        y[i] ^= x[i];
        x[i] ^= y[i];
    }
}

long long int median3(
    long long int a,
    long long int b,
    long long int c,
    int (*less)(long long int, long long int)) {
    // move max(a, b, c) to c
    if (less(b, a))
        swap_vp(&a, &b, sizeof(b));
    if (less(c, b))
        swap_vp(&b, &c, sizeof(b));
    // sort a, b
    if (less(b, a))
        swap_vp(&a, &b, sizeof(b));
    return b;
}

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
