
#include <stdio.h>
#include <stdlib.h>

int arr[] = {11, 22, 33, 44, 55};

int main(void)
{
    int *ptr = &arr[1];

    printf("%d\n", *ptr++); // 22
    printf("%d\n", *++ptr); // 44
    printf("%d\n", *--ptr); // 33
}