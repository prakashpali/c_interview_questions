/**
 * @file q1_arr_sorting.c
 * @author Prakash Pali (prakash14pali@gmail.com)
 * @brief Q1. WAP to sort an array.
 * @version 0.1
 * @date 2025-02-15
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "../utils.h"

static void sort_arr_ascending(int *arr, int n)
{
    int i, j, min_idx, tmp;

    for (i = 0; i < n; i++)
    {
        min_idx = i;
        for (j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }

            if (i != min_idx)
            {
                num_swap(&arr[min_idx], &arr[i]);
            }
        }
    }
}

static void sort_arr_descending(int *arr, int n)
{
    int i, j, max_idx, tmp;

    for (i = 0; i < n; i++)
    {
        max_idx = i;
        for (j = i + 1; j < n; j++)
        {
            if (arr[j] > arr[max_idx])
            {
                max_idx = j;
            }

            if (i != max_idx)
            {
                num_swap(&arr[max_idx], &arr[i]);
            }
        }
    }
}

int main()
{
    int n = 5;
    int a[] = {3, 6, 8, 1, 0};

    printf("=====================================================\n");
    printf("Unsorted array:\n");
    arr_print(a, n);

    printf("Sorted in descending order:\n");
    sort_arr_descending(a, n);
    arr_print(a, n);

    printf("Sorted in ascending order:\n");
    sort_arr_ascending(a, n);
    arr_print(a, n);
    printf("=====================================================\n");

    return 0;
}
