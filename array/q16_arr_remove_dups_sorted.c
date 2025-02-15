/**
 * Remove duplicate elements from an sorted array.
*/

#include "../utils.h"

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

int main()
{
    int A[] = {0,0,1,1,1,2,2,3,3,4};

    int len_arr = (sizeof(A)/sizeof(A[0]));

    printf("=====================================================\n");
    arr_print(A, len_arr);
    len_arr = remove_duplicates(A, len_arr);
    arr_print(A, len_arr);

    printf("=====================================================\n");

    return 0;
}

