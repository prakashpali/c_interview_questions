/**
 * C program to check bit fields in c
 */

#include "../utils.h"

typedef struct __attribute__((packed))
{
    unsigned char a : 8;
    unsigned char b : 8;
    unsigned char c : 4;
    unsigned char d : 4;
    unsigned char e : 1;
    unsigned char f : 1;
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

    t.d = 0x78;
    printf("a = 0x%X, b = 0x%X, c = 0x%X, d = 0x%X, e = 0x%X, f = 0x%X\n", t.a, t.b, t.c, t.d, t.e, t.f);

    t.e = 0;
    printf("a = 0x%X, b = 0x%X, c = 0x%X, d = 0x%X, e = 0x%X, f = 0x%X\n", t.a, t.b, t.c, t.d, t.e, t.f);

    t.f = 1;
    printf("a = 0x%X, b = 0x%X, c = 0x%X, d = 0x%X, e = 0x%X, f = 0x%X\n", t.a, t.b, t.c, t.d, t.e, t.f);

    printf("Address of t = 0x%lX\n", (unsigned long)&t);

    /* Address of bit field is not allowed in c. */
    // printf("Address of t.a = 0x%lX", (unsigned long)&(t.a));

    printf("32 bit value at address t = 0x%08X\n", *((unsigned int *)&t));
    printf("=====================================================\n");

    return 0;
}
