/**
 * C program to check bit fields in c
 */

#include "../utils.h"

// Declaration of union is same as structures
typedef union
{
    int x;
    char y;
    bool z;
} test;

int main()
{
    // A union variable t
    test t;

    printf("=====================================================\n");
    t.x = 256;
    printf("x = 0x%X, y = 0x%X, z = %d\n", t.x, t.y, t.z);

    t.y = 127;
    printf("x = 0x%X, y = 0x%X, z = %d\n", t.x, t.y, t.z);

    t.z = 0;
    printf("x = 0x%X, y = 0x%X, z = %d\n", t.x, t.y, t.z);
    printf("=====================================================\n");

    return 0;
}
