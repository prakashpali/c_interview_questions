/**
 * Bit Rotation: A rotation (or circular shift) is an operation similar to shift
 * except that the bits that fall off at one end are put back to the other end.
 * In left rotation, the bits that fall off at left end are put back at right end.
 * In right rotation, the bits that fall off at right end are put back at left end.
*/

#include <stdio.h>
#include <stdlib.h>

#define INT_BITS 32U
#define ROTATE_LEFT(data, pos)  ((data << pos)|(data >> (INT_BITS - pos)))
#define ROTATE_RIGHT(data, pos) ((data >> pos)|(data << (INT_BITS - pos)))

int rotate_left(int num, int r)
{
    r = r % 32;
    if(r == 0)
    {
        return num;
    }

    int temp = 0;

    for(int i = 0; i < r; i++)
    {
        temp <<= 1;
        temp |= ((num & 0x80000000)>>31);
        // printf("%d\n", temp);
        num <<= 1;
    }

    num |= temp;

    return num;
}


int main()
{
    unsigned int n = 0xC0001101;
    unsigned int rotate = 2;

    // int m = rotate_left(n, rotate);
    int m = ROTATE_LEFT(n, rotate);

    printf("=====================================================\n");
    printf("n=0x%X, m=0x%X\n", n, m);
    printf("=====================================================\n");

    return 0;
}

