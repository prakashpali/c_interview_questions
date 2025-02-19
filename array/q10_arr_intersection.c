/**
 * @file q10_arr_intersection.c
 * @author Prakash Pali (prakash14pali@gmail.com)
 * @brief Q10. WAP to find intersection of two arrays.
 * @version 0.1
 * @date 2025-02-15
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "../utils.h"

#define GET_MIN(a, b) ((a) < (b) ? (a) : (b))

static void sort_array(int *arr, int size)
{
    int min;
    for(int i = 0; i < size-1; i++)
    {
        min = i;
        for(int j = i+1; j < size; j++)
        {
            if(arr[j] < arr[min])
            {
                min = j;
            }
        }

        if(min != i)
        {
            int temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
        }
    }
}

static void find_intersection(int *arr1, int arr_size1, int *arr2, int arr_size2, int **final_arr, int *final_arr_size)
{
    // sort array 1
    sort_array(arr1, arr_size1);
    printf("Sorted array1: ");
    arr_print(arr1, arr_size1);

    // sort array 2
    sort_array(arr2, arr_size2);
    printf("Sorted array2: ");
    arr_print(arr2, arr_size2);

    int i = 0, j = 0, k=0, prev1, prev2;
    *final_arr_size = GET_MIN(arr_size1, arr_size2);
    *final_arr = (int *)malloc(*final_arr_size * sizeof(int));

    // Keep looking for both elements:
    // if array1[i] < array2[j], increment i.
    // if array1[i] > array2[j], increment j.
    // if both are same, add element to intersection array

    while (i < arr_size1 && j < arr_size2)
    {
        if ((i < arr_size1 - 1) && (arr1[i] == arr1[i + 1]))
        {
            i++;
            continue;
        }
        if ((j < arr_size2 - 1) && (arr2[j] == arr2[j + 1]))
        {
            j++;
            continue;
        }

        if (arr1[i] < arr2[j])
        {
            i++;
        }
        else if (arr1[i] > arr2[j])
        {
            j++;
        }
        else
        {
            (*final_arr)[k++] = arr1[i];
            i++;
            j++;
        }
    }

    *final_arr_size = k;
}

// Driver Code
int main()
{
    int arr1[] = {1, 8, 6, 4, 5, 1, 1, 3, 7, 9};
    int arr2[] = {1, 3, 2, 1};
    int arr_size1 = sizeof(arr1)/sizeof(arr1[0]);
    int arr_size2 = sizeof(arr2)/sizeof(arr2[0]);
    int *final_arr = NULL;
    int final_arr_size = 0;

    printf("=====================================================\n");

    printf("Original array1: ");
    arr_print(arr1, arr_size1);
    printf("Original array2: ");
    arr_print(arr2, arr_size2);

    find_intersection(arr1, arr_size1, arr2, arr_size2, &final_arr, &final_arr_size);

    printf("final_arr = 0x%X, final_arr_size = %d \n", final_arr, final_arr_size);

    if((NULL != final_arr) && (0 != final_arr_size))
    {
        printf("Final array: ");
        arr_print(final_arr, final_arr_size);
        free(final_arr);
        final_arr = NULL;
        final_arr_size = 0;
    }
    else
    {
        printf("Failed to get intersection of both arrays\n");
    }

    printf("=====================================================\n");

    return 0;
}