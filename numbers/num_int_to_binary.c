/**
 * Convert integer number directly into a binary number
*/

#include "../utils.h"

static int int_to_b_recursive(int num)
{
    int b = 0;
    if(!num)
    {
        return 0;
    }

    b = (num % 2) + 10 * int_to_b_recursive(num / 2);

    return b;
}


static int int_to_binary(int num)
{
    int b = 0;
    int base = 1;

    while (num)
    {
        // b += ((num & 1)*base);
        // base = base*10;
        // num >>= 1;

        b += (num % 2) * base;
        num = num / 2;
        base *= 10;
    }

    return b;
}

int main()
{
    int num = 32;

    printf("Binary of %d = 0x%d\n", num, int_to_binary(num));
    printf("Binary of %d = 0x%d\n", num, int_to_b_recursive(num));

    return 0;
}