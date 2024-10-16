#include <stdio.h>

int main()
{
    const int a = 5;
    const int *ptr;
    ptr = &a;
    *ptr = 10;
    printf("%d\n", a);
    return 0;
}