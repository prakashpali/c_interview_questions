/**
 * Program to cyclically rotate an array by one
 */

#include "../utils.h"

void rotate(int arr[], int n)
{
    // store the last element in a variable
    int last_el = arr[n - 1];
    for (int i = n - 1; i > 0; i--)
        arr[i] = arr[i - 1];

    // assign the last element to first element
    arr[0] = last_el;
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("=====================================================\n");
    printf("Given array is\n");
    arr_print(arr, n);

    rotate(arr, n);

    printf("\nRotated array is\n");
    arr_print(arr, n);
    printf("=====================================================\n");

    return 0;
}