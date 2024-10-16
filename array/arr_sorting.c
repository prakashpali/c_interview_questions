/**
Implement sorting algo.
This one is Selection Sort.
*/

#include "../utils.h"

static void swap(int *a, int *b)
{
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

void sort_arr_ascending(int *arr, int n)
{
    int i, j, min_idx, tmp;

    for (i = 0; i < n; i++)
    {
        min_idx = i;
        for (j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }

            if (i != min_idx)
            {
                swap(&arr[min_idx], &arr[i]);
            }
        }
    }
}

void sort_arr_descending(int *arr, int n)
{
    int i, j, max_idx, tmp;

    for (i = 0; i < n; i++)
    {
        max_idx = i;
        for (j = i + 1; j < n; j++)
        {
            if (arr[j] > arr[max_idx])
            {
                max_idx = j;
            }

            if (i != max_idx)
            {
                swap(&arr[max_idx], &arr[i]);
            }
        }
    }
}

int main()
{
    int n = 5;
    int a[] = {3, 6, 8, 1, 0};

    arr_print(a, n);
    sort_arr_descending(a, n);
    arr_print(a, n);
    sort_arr_ascending(a, n);
    arr_print(a, n);

    return 0;
}
