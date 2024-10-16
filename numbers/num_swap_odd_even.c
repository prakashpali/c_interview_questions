/*
 *  Swap odd and even bits of a number.
 */

#include <stdio.h>

int main()
{
    int data = 2;
    printf("=====================================================\n");
    printf("Original num = 0x%X\n", data);
    data = ((data & 0xAAAAAAAA) >> 1 | (data & 0x55555555) << 1);
    printf("Final num = 0x%X\n", data);
    printf("=====================================================\n");
    return 0;
}