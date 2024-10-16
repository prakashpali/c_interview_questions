#include <stdio.h>

int main()
{
    int a = 5, b = 10, c;
    int *p = &a, *q = &b;
    c = p - q;
    printf("0x%X, 0x%X, %d\n", (unsigned int)p, (unsigned int)q, c);
    return 0;
}