#ifndef SOME_FUNCS_C
#define SOME_FUNCS_C

#include "some_funcs.h"

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

#endif
