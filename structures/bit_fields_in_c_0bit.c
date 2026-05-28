/**
 * C program to check bit fields in c
 */

#include "../utils.h"

typedef struct __attribute__((packed))
{
    unsigned char a : 1;    // This is same as unsigned char a : 8;
    unsigned char b : 3;    // Bit field size take precedence over data type
    unsigned char : 0;      // This will ensure that next field is stored in next byte. This is called forced padding.
    unsigned char d : 3;    // Bit fields are always packed. i.e. 1st 8, 8 bits and last 3,3,1,1 bits are combined to take up 3 bytes (24 bits).
    unsigned char e : 1;
} test;

int main()
{
    test t;

    memset(&t, 0, sizeof(t));

    printf("=====================================================\n");
    printf("Size of t = %lu bytes\n", sizeof(t));

    t.a = 0x1;
    printf("a = 0x%X, b = 0x%X, d = 0x%X, e = 0x%X\n", t.a, t.b, t.d, t.e);

    t.b = 0x4;
    printf("a = 0x%X, b = 0x%X, d = 0x%X, e = 0x%X\n", t.a, t.b, t.d, t.e);

    t.d = 0x2;
    printf("a = 0x%X, b = 0x%X, d = 0x%X, e = 0x%X\n", t.a, t.b, t.d, t.e);

    t.e = 1;
    printf("a = 0x%X, b = 0x%X, d = 0x%X, e = 0x%X\n", t.a, t.b, t.d, t.e);

    printf("Address of t = 0x%lX\n", (unsigned long)&t);

    /* Address of bit field is not allowed in c. */
    // printf("Address of t.a = 0x%lX", (unsigned long)&(t.a));

    printf("Value at address t = 0x%lX\n", *((unsigned long *)&t));
    printf("=====================================================\n");

    return 0;
}
