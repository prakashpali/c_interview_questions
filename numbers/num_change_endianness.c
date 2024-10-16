/*
    Change endianness of the number.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHANGE_ENDIANNESS(num)  ((((num) & 0x000000FF) << 24) | \
                                 (((num) & 0x0000FF00) << 8)  | \
                                 (((num) & 0x00FF0000) >> 8)  | \
                                 (((num) & 0xFF000000) >> 24))

int main(void)
{
    unsigned int num = 0x11223344;

    printf("=====================================================\n");

    printf("Original endianness = 0x%X\n", num);
    num = CHANGE_ENDIANNESS(num);
    printf("Original endianness = 0x%X\n", num);

    printf("=====================================================\n");

    return 0;
}