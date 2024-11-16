#include <stdio.h>

int main()
{
    const int a = 5;
    int b = 4;
    const int *ptr;
    // int * const ptr1 = &b;
    ptr = &a;
    // *ptr1 = 2;

    printf("%d\n", a);
    return 0;
}