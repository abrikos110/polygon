#include <stdio.h>
#include <time.h>
#include "quicksort.h"

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

    long long int *a = malloc(100*1000*1000 * sizeof(*a));
    int n = 100;

    for (int ftype = 1; ftype <= 4; ++ftype)
        for (n = 10; n <= 100*1000*1000; n *= 10) {
            fill_array(n, a, ftype, less);
            long long int was_cmps = cmps, was_swaps = swaps;
            quicksort(n, a, less);
            printf("quicksort swaps=%lld cmps=%lld ftype=%d n=%d\n",
                swaps - was_swaps, cmps - was_cmps, ftype, n);
            for (int i = 0; i < n-1; ++i)
                assert(!less(a[i+1], a[i]));
        }

    free(a);
    return 0;
}
