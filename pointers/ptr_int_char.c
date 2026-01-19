#include <stdio.h>


int main()
{
    int a = 0x200;
    char *x;
    x = (char *)&a;
    x[0] = 1;
    x[1] = 2;

    printf("0x%x\n", a);
    return 0;
}