/**
 * @file q4_arr_reverse.c
 * @author Prakash Pali (prakash14pali@gmail.com)
 * @brief Q4. WAP to reverse elements of an array.
 * @version 0.1
 * @date 2025-02-15
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "../utils.h"

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

int main()
{
    int A[] = {1, 2, 3, 4, 5, 6};

    int len_arr = (sizeof(A)/sizeof(A[0]));

    printf("=====================================================\n");
    arr_print(A, len_arr);
    reverse_arr(A, len_arr);
    arr_print(A, len_arr);

    printf("=====================================================\n");

    return 0;
}

