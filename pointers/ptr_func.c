#include <stdio.h>
#include <stdlib.h>

void fun(int *p)
{
    static int q = 10;

    p = &q;
}

int main()
{
    int r = 20;
    int *p = &r;

    fun(p);

    printf("%d", *p);

    return 0;
}
