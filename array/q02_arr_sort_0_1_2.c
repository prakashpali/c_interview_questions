/**
 * @file q2_arr_sort_0_1_2.c
 * @author Prakash Pali (prakash14pali@gmail.com)
 * @brief Q2. WAP to sort an array with 0, 1 and 2.
 * @version 0.1
 * @date 2025-02-15
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "../utils.h"

/* Sort the input array, the array is assumed to have values in {0, 1, 2} */
void sort012(int a[], int arr_size)
{
    int lo = 0;
    int hi = arr_size - 1;
    int mid = 0;
    // Iterate till all the elements are sorted
    while (mid <= hi)
    {
        switch (a[mid])
        {
        // If the element is 0
        case 0:
            num_swap(&a[lo++], &a[mid++]);
            // printf("0 \n");
            break;
        // If the element is 1
        case 1:
            mid++;
            // printf("1 \n");
            break;
        // If the element is 2
        case 2:
            num_swap(&a[mid], &a[hi--]);
            // printf("2 \n");
            break;
        }
    }
}

/* Driver program to test */
int main()
{
    int arr[] = {0, 1, 1, 0, 1, 2, 1, 2, 0, 0, 0, 1};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    int i;

    printf("=====================================================\n");
    printf("Unsorted array:\n");
    arr_print(arr, arr_size);

    sort012(arr, arr_size);

    printf("Sorted array:\n");
    arr_print(arr, arr_size);
    printf("=====================================================\n");

    return 0;
}
