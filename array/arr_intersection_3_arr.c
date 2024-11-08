/**
 * Find intersection of three arrays
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

static void find_intersection(int *arr1, int arr_size1, int *arr2, int arr_size2, int *arr3, int arr_size3, int **final_arr, int *final_arr_size)
{
    // sort array 1
    sort_array(arr1, arr_size1);
    printf("Sorted array1: ");
    arr_print(arr1, arr_size1);

    // sort array 2
    sort_array(arr2, arr_size2);
    printf("Sorted array2: ");
    arr_print(arr2, arr_size2);

    // sort array 2
    sort_array(arr3, arr_size3);
    printf("Sorted array3: ");
    arr_print(arr3, arr_size3);

    int i = 0, j = 0, k = 0, l = 0;
    *final_arr_size = GET_MIN(arr_size1, GET_MIN(arr_size2, arr_size3));
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
        if ((k < arr_size3 - 1) && (arr3[k] == arr3[k + 1]))
        {
            k++;
            continue;
        }


        if (arr1[i] == arr2[j] && arr2[j] == arr3[k])
        {
            (*final_arr)[l++] = arr1[i];
            i++;
            j++;
            k++;
        }

        if (arr1[i] < arr2[j] || arr1[i] < arr3[k])
        {
            i++;
        }

        if (arr2[j] < arr1[i] || arr2[j] < arr3[k])
        {
            j++;
        }

        if (arr3[k] < arr1[i] || arr3[k] < arr2[j])
        {
            k++;
        }

    }

    *final_arr_size = l;
}

// Driver Code
int main()
{
    int arr1[] = {1, 8, 6, 4, 5, 1, 1, 3, 7, 9, 2};
    int arr2[] = {1, 3, 2, 1};
    int arr3[] = {1, 3, 4, 2};
    int arr_size1 = sizeof(arr1)/sizeof(arr1[0]);
    int arr_size2 = sizeof(arr2)/sizeof(arr2[0]);
    int arr_size3 = sizeof(arr3)/sizeof(arr3[0]);
    int *final_arr = NULL;
    int final_arr_size = 0;

    printf("=====================================================\n");

    printf("Original array1: ");
    arr_print(arr1, arr_size1);
    printf("Original array2: ");
    arr_print(arr2, arr_size2);

    find_intersection(arr1, arr_size1, arr2, arr_size2, arr3, arr_size3, &final_arr, &final_arr_size);

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