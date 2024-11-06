/**
 * Find union of two arrays
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

static void find_union(int *arr1, int arr_size1, int *arr2, int arr_size2, int **final_arr, int *final_arr_size)
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
    *final_arr_size = (arr_size1 + arr_size2);
    *final_arr = (int *)malloc(*final_arr_size * sizeof(int));

    // Keep looking for both elements:
    // if array1[i] == array2[j], increment i & j. Add element to union array
    // if array1[i] != array2[j], get minimum of array1[i] & array2[j]. Increment i if array1[i] is minimum, else j.

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

        if (arr1[i] == arr2[j])
        {
            (*final_arr)[k++] = arr1[i];
            i++;
            j++;
        }
        else
        {
            int temp = GET_MIN(arr1[i], arr2[j]);
            (*final_arr)[k++] = temp;
            if (temp == arr1[i])
            {
                i++;
            }
            else
            {
                j++;
            }
        }
    }

    while(i < arr_size1)
    {
        (*final_arr)[k++] = arr1[i++];
    }

    while(j < arr_size2)
    {
        (*final_arr)[k++] = arr2[j++];
    }
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

    find_union(arr1, arr_size1, arr2, arr_size2, &final_arr, &final_arr_size);

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
        printf("Failed to get union of both arrays\n");
    }

    printf("=====================================================\n");

    return 0;
}