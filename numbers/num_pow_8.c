
/*
* Find if a number is power of two.
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int is_pow_8;
    int num = 1;

    // return true if `n` is a power of 2, and its only
    // set bit is present at (0, 3, 6, … ) position
    is_pow_8 = num && !(num & (num - 1)) && !(num & 0xB6DB6DB6);

    printf("=====================================================\n");
    printf("num = %d\n", num);
    if(is_pow_8)
    {
        printf("Entered number is a power of 8\n");
    }
    else
    {
        printf("Entered number is not a power of 8\n");
    }

    printf("=====================================================\n");

    return 0;
}