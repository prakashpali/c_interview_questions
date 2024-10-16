/**
 * Swap value of two variables without using third variable
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int a = 3;
    int b = 5;

    printf("Before swapping: a = %d, b = %d\n", a, b);

    a = a ^ b;
    b = a ^ b;
    a = a ^ b;

    printf("After swapping: a = %d, b = %d\n", a, b);

    return 0;
}