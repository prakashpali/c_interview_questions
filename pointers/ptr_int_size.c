#include <stdio.h>

int main()
{
    int a = 5, b = 10, c;
    int *p = &a, *q = &b;
    c = p - q;
    printf("0x%lX, 0x%lX, %d\n", (unsigned long)p, (unsigned long)q, c);
    return 0;
}