/**
 * @file q12_arr_subsets_print.c
 * @author Prakash Pali (prakash14pali@gmail.com)
 * @brief Q12. WAP to print all subsets of an array.
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
    int A[] = {0,1,2};

    int len_arr = (sizeof(A)/sizeof(A[0]));
    int N = 1 << len_arr;

    printf("=====================================================\n");
    printf("len_arr=%d\n", len_arr);
    printf("N=%d\n", N);

    for (int i = 1; i < N; i++)
    {
        printf("[");
        for (int j = 0; j < len_arr; j++)
        {
            if (i & (1 << j))
            {
                printf("%d,", A[j]);
            }
        }
        printf("]\n");
    }
    printf("=====================================================\n");

    return 0;
}

