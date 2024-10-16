
/*
* Find if a number is power of two.
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int is_pow_4;
    int num = 16;

    // return true if `n` is a power of 2, and its only
    // set bit is present at even position
    is_pow_4 = num && !(num & (num - 1)) && !(num & 0xAAAAAAAA);

    printf("=====================================================\n");
    printf("num = %d\n", num);
    if(is_pow_4)
    {
        printf("Entered number is a power of 4\n");
    }
    else
    {
        printf("Entered number is not a power of 4\n");
    }

    printf("=====================================================\n");

    return 0;
}