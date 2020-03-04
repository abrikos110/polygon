#include <stdio.h>
#include <string.h>
#include <time.h>
#include "quicksort.h"
#include "shellsort.h"

long long int lliabs(long long int x) {
    if (x < 0)
        return -x;
    return x;
}

long long int cmps = 0; // WORKAROUND
int less(long long int a, long long int b) {
    ++cmps;
    return lliabs(a) > lliabs(b);
}

void fill_array(int n, long long int *a, int filltype,
    int (*less)(long long int, long long int)) {

    for (int i = 0; i < n; ++i)
        a[i] = rand_lli(0);
    if (filltype == 1 || filltype == 2)
        quicksort(n, a, less);

    if (filltype == 2)
        for (int i = 0; i < n/2; ++i)
            swap_vp(a+i, a+n-i-1, sizeof(*a));
}



int main(void) {
    srand(time(NULL));

    int n, maxn = 100*1000*1000;
    long long int *a = malloc(maxn * sizeof(*a)),
                  *b = malloc(maxn * sizeof(*b));
    long long int was_cmps, was_swaps;

    for (int ftype = 1; ftype <= 4; ++ftype) {
        for (n = 10; n <= maxn; n *= 10) {
            fill_array(n, a, ftype, less);
            memcpy(b, a, n * sizeof(*a));

            was_swaps = swaps;
            was_cmps = cmps;
            quicksort(n, a, less);
            printf("quicksort swaps=%lld cmps=%lld ftype=%d n=%d\n",
                swaps - was_swaps, cmps - was_cmps, ftype, n);
            for (int i = 0; i < n-1; ++i)
                assert(!less(a[i+1], a[i]));

            was_swaps = swaps;
            was_cmps = cmps;
            shellsort(n, b, less, step);
            printf("shellsort swaps=%lld cmps=%lld ftype=%d n=%d\n",
                swaps - was_swaps, cmps - was_cmps, ftype, n);
            for (int i = 0; i < n-1; ++i)
                assert(!less(b[i+1], b[i]));
        }
    }

    free(a);
    free(b);
    return 0;
}
