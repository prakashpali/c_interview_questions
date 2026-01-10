/**
 * Swap value of two variables without using third variable
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int swap_1(int *a, int *b)
{
    if (NULL == a || NULL == b)
    {
        return -1;
    }

    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;

    return 0;
}

static int swap_2(int *a, int *b)
{
    if (NULL == a || NULL == b)
    {
        return -1;
    }

    *a = (*a) ^ (*b);
    *b = (*a) ^ (*b);
    *a = (*a) ^ (*b);

    return 0;
}

int main()
{
    int a = 3;
    int b = 5;

    printf("Before swapping: a = %d, b = %d\n", a, b);

    swap_1(&a, &b);
    printf("After swapping : a = %d, b = %d\n", a, b);

    swap_2(&a, &b);
    printf("After swapping : a = %d, b = %d\n", a, b);

    return 0;
}