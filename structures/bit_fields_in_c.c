/**
 * C program to check bit fields in c
 */

#include "../utils.h"

typedef struct
{
    unsigned char a : 8;    // This is same as unsigned char a : 8;
    unsigned char b : 8;    // Bit field size take precedence over data type
    unsigned char c : 3;    // This nibble is combined with next nibble in actual memory
    unsigned char d : 3;    // Bit fields are always packed. i.e. 1st 8, 8 bits and last 3,3,1,1 bits are combined to take up 3 bytes (24 bits).
    unsigned char e : 1;
    unsigned char f : 1;
    unsigned int x;         // This is another structure field. Above bit fields take up 3 bytes, this int takes up 4 bytes. But both are aligned to take up 8 bytes.
} test;

int main()
{
    test t;

    memset(&t, 0, sizeof(t));

    printf("=====================================================\n");
    printf("Size of t = %lu bytes\n", sizeof(t));

    t.a = 0x12;
    printf("a = 0x%X, b = 0x%X, c = 0x%X, d = 0x%X, e = 0x%X, f = 0x%X\n", t.a, t.b, t.c, t.d, t.e, t.f);

    t.b = 0x34;
    printf("a = 0x%X, b = 0x%X, c = 0x%X, d = 0x%X, e = 0x%X, f = 0x%X\n", t.a, t.b, t.c, t.d, t.e, t.f);

    t.c = 0x56;
    printf("a = 0x%X, b = 0x%X, c = 0x%X, d = 0x%X, e = 0x%X, f = 0x%X\n", t.a, t.b, t.c, t.d, t.e, t.f);

    t.d = 0x79;
    printf("a = 0x%X, b = 0x%X, c = 0x%X, d = 0x%X, e = 0x%X, f = 0x%X\n", t.a, t.b, t.c, t.d, t.e, t.f);

    t.e = 2;
    printf("a = 0x%X, b = 0x%X, c = 0x%X, d = 0x%X, e = 0x%X, f = 0x%X\n", t.a, t.b, t.c, t.d, t.e, t.f);

    t.f = 1;
    printf("a = 0x%X, b = 0x%X, c = 0x%X, d = 0x%X, e = 0x%X, f = 0x%X\n", t.a, t.b, t.c, t.d, t.e, t.f);

    t.x = 0x12345678;

    printf("Address of t = 0x%lX\n", (unsigned long)&t);

    /* Address of bit field is not allowed in c. */
    // printf("Address of t.a = 0x%lX", (unsigned long)&(t.a));

    printf("32 bit value at address t = 0x%lX\n", *((unsigned long *)&t));
    printf("=====================================================\n");

    return 0;
}
