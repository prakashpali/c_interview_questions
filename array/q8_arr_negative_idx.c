/**
 * @file q8_arr_negative_idx.c
 * @author Prakash Pali (prakash14pali@gmail.com)
 * @brief Q8. WAP to reverse elements of an array.
 * @version 0.1
 * @date 2025-02-15
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <stdio.h>
#include <stdlib.h>


int main()
{
    int A[] = {0,1,2,3,4,5,6,7,8,9};

    int len_arr = (sizeof(A)/sizeof(A[0]));

    int *arr = &A[4];

    printf("=====================================================\n");
    printf("A[-1] = 0x%X\n", arr[-1]);
    printf("=====================================================\n");

    return 0;
}

