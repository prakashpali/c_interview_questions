// Compute parity of a number `x` using the lookup table

#include <stdio.h>

int find_parity(int x)
{
    // recursively divide the (32–bit) integer into two equal
    // halves and take their XOR until only 1 bit is left

    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;

    // return 1 if the last bit is set; otherwise, return 0
    return x & 1;
}

int main()
{
    int x = 15;

    printf("=====================================================\n");
    if (find_parity(x))
    {
        printf("0x%X contains odd bits\n", x);
    }
    else
    {
        printf("0x%X contains even bits\n", x);
    }
    printf("=====================================================\n");

    return 0;
}