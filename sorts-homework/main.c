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

void fill_array(int n, long long int *a, int filltype) {
    for (int i = 0; i < n; ++i)
        a[i] = rand_lli(0);
    if (filltype == 1 || filltype == 2)
        quicksort(n, a, less);

printf("...\n");
    if (filltype == 2)
        for (int i = 0; i < n/2; ++i)
            swap_vp(a+i, a+n-i-1, sizeof(*a));
}
// not works
int main(void) {
    srand(time(NULL));

    int n = 10, maxn = 100*1000*1000;
    long long int *a = malloc(maxn * sizeof(*a));

    for (n = 10; n <= maxn; n *= 10) {
        for (int filltype = 1; filltype <= 4; ++filltype) {
            fill_array(n, a, filltype);
            long long int was_cmps = cmps, was_swaps = swaps;
            quicksort(n, a, less);
            for (int j = 0; j < n-1; ++j)
                assert(less(a[j], a[j+1]));
            printf("quicksort: compares=%lld swaps=%lld filltype=%d n=%d\n",
                cmps - was_cmps, swaps - was_swaps, filltype, n);
        }
    }

    free(a);
    return 0;
}
