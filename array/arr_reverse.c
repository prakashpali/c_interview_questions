/**
 * Reverse elements of an array.
*/

#include <stdio.h>
#include <stdlib.h>

void reverse_arr(int A[], int size)
{
    for (int i = 0; i < size; i++)
    {
        int tmp = A[i];
        A[i] = A[size - 1];
        A[size - 1] = tmp;

        --size;
    }
}

void print_arr(int *arr, int n)
{
    for (size_t i = 0; i < n; i++)
    {
        printf("%d, ", arr[i]);
    }

    printf("\n");
}


int main()
{
    int A[] = {1, 2, 3, 4, 5, 6};

    int len_arr = (sizeof(A)/sizeof(A[0]));

    printf("=====================================================\n");
    print_arr(A, len_arr);
    reverse_arr(A, len_arr);
    print_arr(A, len_arr);

    printf("=====================================================\n");

    return 0;
}

