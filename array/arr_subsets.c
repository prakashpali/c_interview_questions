/**
 * Print all subsets of an array.
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

