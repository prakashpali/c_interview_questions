/**
 * Utility file to be used across this project.
 *
 */

#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <malloc/malloc.h>

void arr_print(int *arr, int n)
{
    if (NULL == arr || 0 == n)
    {
        return;
    }

    printf("[");
    for (size_t i = 0; i < n - 1; i++)
    {
        printf("%d, ", arr[i]);
    }

    printf("%d", arr[n - 1]);
    printf("]");

    printf("\n\n");
}

void num_swap(int *a, int *b)
{
    if (NULL == a || NULL == b)
    {
        return;
    }
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

#endif /* __UTILS_H__ */