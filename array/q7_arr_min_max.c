/**
 * @file q7_arr_min_max.c
 * @author Prakash Pali (prakash14pali@gmail.com)
 * @brief Q7. WAP to return minimum and maximum of an array.
 * @version 0.1
 * @date 2025-02-15
 *
 * @copyright Copyright (c) 2025
 *
 */

#include<stdio.h>

typedef struct pair
{
    int min;
    int max;
} min_max_t;

min_max_t getMinMax(int *arr, int arr_size)
{
    min_max_t min_max;

    if (arr_size < 1)
    {
        min_max.min = 0;
        min_max.max = 0;

        return min_max;
    }

    if (arr_size == 1)
    {
        min_max.min = arr[0];
        min_max.max = arr[0];

        return min_max;
    }

    if (arr[0] < arr[1])
    {
        min_max.min = arr[0];
        min_max.max = arr[1];
    }
    else
    {
        min_max.min = arr[1];
        min_max.max = arr[0];
    }

    for (int i = 2; i < arr_size; i++)
    {
        if (min_max.min > arr[i])
        {
            min_max.min = arr[i];
        }
        if (min_max.max < arr[i])
        {
            min_max.max = arr[i];
        }
    }

    return min_max;
}

/* Driver program to test above function */
int main()
{
    int arr[] = {1000, 11, 445, 1, 330, 3000};
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    min_max_t minmax = getMinMax(arr, arr_size);

    printf("Minimum element is %d\n", minmax.min);
    printf("Maximum element is %d\n", minmax.max);

    return 0;
}