/**
 * Remove duplicate elements in an unordered array
 */

#include "../utils.h"

void shift_elements(int *arr, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        arr[i] = arr[i+1];
    }
}

int remove_duplicates(int *arr, int size)
{
    int dup_arr_len = size;

    for (int i = 0; i < dup_arr_len;i++)
    {
        for(int j = i+1; j < dup_arr_len;)
        {
            if(arr[i] == arr[j])
            {
                shift_elements(&arr[j], (dup_arr_len-j));
                dup_arr_len--;
            }
            else
            {
                j++;
            }
        }
        arr_print(arr, size);
    }

    return dup_arr_len;
}

int main()
{
    int A[] = {0, 5, 1, 5, 1, 2, 3, 3, 2, 4, 4, 4, 5, 7, 1, 0};

    int len_arr = (sizeof(A)/sizeof(A[0]));

    printf("=====================================================\n");
    printf("Original array:\n");
    arr_print(A, len_arr);
    len_arr = remove_duplicates(A, len_arr);

    printf("Final array:\n");
    arr_print(A, len_arr);

    printf("=====================================================\n");

    return 0;
}

