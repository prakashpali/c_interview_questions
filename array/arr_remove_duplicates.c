/**
 * Reverse elements of an array.
*/

#include <stdio.h>
#include <stdlib.h>

int remove_duplicates(int A[], int size)
{
    int j = 0;
    for (int i = 0; i < size-1; i++)
    {
        if(A[i] != A[i+1])
        {
            A[j++] = A[i];
        }
    }

    A[j++] = A[size-1];

    return j;
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
    int A[] = {0,0,1,1,1,2,2,3,3,4};

    int len_arr = (sizeof(A)/sizeof(A[0]));

    printf("=====================================================\n");
    print_arr(A, len_arr);
    len_arr = remove_duplicates(A, len_arr);
    print_arr(A, len_arr);

    printf("=====================================================\n");

    return 0;
}

