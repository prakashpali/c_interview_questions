// Find the absolute value of an integer without branching

#include <stdio.h>

int get_abs(int num)
{
    int const mask = num >> (sizeof(int) * 8 - 1);

    return ((num + mask) ^ mask);
}

int main()
{
    int num = -15;

    printf("=====================================================\n");
    printf("Absolute value of %d is %d\n", num, get_abs(num));
    printf("=====================================================\n");

    return 0;
}