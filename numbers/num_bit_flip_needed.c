/*
 *  Count number of bits to be flipped to convert A to B.
 */

#include <stdio.h>

// Function to count the total number of set bits in `n`
static unsigned int count_ones_brian_kernighan(unsigned int num)
{
    // `count` stores the total bits set in `n`
    unsigned int count = 0;

    while (num)
    {
        num = num & (num - 1);    // clear the least significant bit set
        count++;
    }

    return count;
}

static unsigned int count_ones(unsigned int num)
{
    unsigned int count = 0;

    while(num)
    {
        if (num & 1)
            count++;
        num >>= 1;
    }

    return count;
}

int main()
{
    int a = 8;
    int b = 0xF;

    printf("=====================================================\n");
    printf("Bit flips needed to convert A = 0x%X to B = 0x%X is %d\n", a, b, count_ones_brian_kernighan(a^b));
    printf("=====================================================\n");
    return 0;
}