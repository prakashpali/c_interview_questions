/**
Implement fibonacci series
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static void fibo(int n)
{
    int n_2 = 0;
    int n_1 = 1;
    int i, nth;

    printf("%d,", n_2);
    printf("%d,", n_1);

    for(i = 2; i <= n; i++)
    {
        nth = n_1 + n_2;
        printf("%d,", nth);
        n_2 = n_1;
        n_1 = nth;
    }
}

int main()
{
    int n = 5;

    fibo(n);

    return 0;
}
