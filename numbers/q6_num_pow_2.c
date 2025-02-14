
/*
* Find if a number is power of two.
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int is_pow_2;
    int num = -4;

    // check the sign of the number
    is_pow_2 = num && !(num & (num -1));

    printf("=====================================================\n");
    printf("num = %d\n", num);
    if(is_pow_2)
    {
        printf("Entered number is a power of 2\n");
    }
    else
    {
        printf("Entered number is not a power of 2\n");
    }

    printf("=====================================================\n");

    return 0;
}