/**
 * Program to cyclically rotate an array by one
 */

#include <stdio.h>

void rotate(int arr[], int n)
{
    // store the last element in a variable
    int last_el = arr[n - 1];
    for (int i = n - 1; i > 0; i--)
        arr[i] = arr[i - 1];

    // assign the last element to first element
    arr[0] = last_el;
}

void print_arr(int *arr, int n)
{
    for (size_t i = 0; i < n - 1; i++)
    {
        printf("%d, ", arr[i]);
    }

    printf("%d", arr[n - 1]);

    printf("\n");
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("=====================================================\n");
    printf("Given array is\n");
    print_arr(arr, n);

    rotate(arr, n);

    printf("\nRotated array is\n");
    print_arr(arr, n);
    printf("=====================================================\n");

    return 0;
}