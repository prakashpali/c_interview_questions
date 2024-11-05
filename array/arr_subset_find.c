/**
 * Find whether an array is subset of another array
 */

#include "../utils.h"

void sort_array(int *arr, int size)
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

static bool is_subset(int *arr1, int arr_size1, int *arr2, int arr_size2)
{
    bool ret = true;

    // assuming array1 is bigger array

    // sort array 1
    sort_array(arr1, arr_size1);
    printf("Sorted array1: ");
    arr_print(arr1, arr_size1);

    // sort array 2
    sort_array(arr2, arr_size2);
    printf("Sorted array2: ");
    arr_print(arr2, arr_size2);

    int i=0, j=0;

    // keep matching elements:
    // if array1[i] < array2[j], increment i. Assuming array1 is superset and it has more elements
    // if array1[i] == array2[j] increment i, j. Match found, move to next element
    // if array1[i] > array2[j] return failure. This means there are elements in array2 which are missing in array1

    while (i < arr_size1 && j < arr_size2)
    {
        if (arr1[i] < arr2[j])
        {
            i++;
        }
        else if (arr1[i] == arr2[j])
        {
            i++;
            j++;
        }
        else
        {
            ret = false;
            break;
        }
    }

    return ret;
}

// Driver Code
int main()
{
    int arr1[] = {1, 8, 6, 4, 5, 3, 7, 2};
    int arr2[] = {1, 3, 2};
    int arr_size1 = sizeof(arr1)/sizeof(arr1[0]);
    int arr_size2 = sizeof(arr2)/sizeof(arr2[0]);

    printf("=====================================================\n");

    printf("Original array1: ");
    arr_print(arr1, arr_size1);
    printf("Original array2: ");
    arr_print(arr2, arr_size2);

    if(is_subset(arr1, arr_size1, arr2, arr_size2))
    {
        printf("Array2 is subset of Array1\n");
    }
    else
    {
        printf("Array2 is NOT a subset of Array1\n");
    }

    printf("=====================================================\n");

    return 0;
}