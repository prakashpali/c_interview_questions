/**
 * Convert binary number directly into an integer
*/

#include "../utils.h"

static int binary_to_int_recursive(int b)
{
    int num;

    if(!b)
    {
        return 0;
    }

    num = (b % 10) + 2 * binary_to_int_recursive(b / 10);

    return num;
}

static int binary_to_int(int b)
{
    int num = 0;
    int base = 1;

    while (b)
    {
        // b += ((num & 1)*base);
        // base = base*10;
        // num >>= 1;

        num += (b%10) * base;
        b = b/10;
        base <<= 1;
    }

    return num;
}

int main()
{
    int b = 1101;

    printf("Decimal of 0x%d = %d\n", b, binary_to_int(b));
    printf("Decimal of 0x%d = %d\n", b, binary_to_int_recursive(b));

    return 0;
}