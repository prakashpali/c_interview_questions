/*
 * Round up a number to the next highest power of 2
 */

#include <stdio.h>

// Compute power of two greater than or equal to `n`
unsigned int find_next_pow_of_2(unsigned int n)
{
    // decrement `n` (to handle the case when `n` itself
    // is a power of 2)
    // n = n - 1;
    printf("n is %d \n", n);
    if (n == 0)
    {
        return 2;
    }
    if (!(n & (n-1)))
    {
        return n;
    }

    // do till only one bit is left
    while (n & (n - 1)) {
        n = n & (n - 1);        // unset rightmost bit
    }

    // `n` is now a power of two (less than `n`)

    // return next power of 2
    return n << 1;
}

int main()
{
    unsigned n = 4;

    printf("=====================================================\n");
    printf("The next power of %d is %d \n", n, find_next_pow_of_2(n));
    printf("=====================================================\n");

    return 0;
}