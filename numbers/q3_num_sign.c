
/*
* Compute the sign of an integer.
* The MSB bit of a number defines their sign. If the MSB bit is set, the number will be negative.
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int sign;
    int data = 1;

    // check the sign of the number
    sign = data & 0x80000000;

    printf("=====================================================\n");
    printf("data = %d\n", data);
    if(sign)
    {
        printf("Entered number is a negative number\n");
    }
    else
    {
        printf("Entered number is a positve number\n");
    }

    printf("=====================================================\n");

    return 0;
}