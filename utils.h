/**
 * Utility file to be used across this project.
 *
 */

#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>

void arr_print(int *arr, int n)
{
    for (size_t i = 0; i < n - 1; i++)
    {
        printf("%d, ", arr[i]);
    }

    printf("%d", arr[n - 1]);

    printf("\n");
}

#endif /* __UTILS_H__ */