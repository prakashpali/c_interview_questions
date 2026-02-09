#include "../utils.h"

void swap(int *a, int *b)
{
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

static void sort_arr_descending(int *arr, int n)
{
    for(int i = 0; i < n-1; i++)
    {
        int max_idx = i;
        for(int j = i+1; j < n; j++)
        {
            if(arr[j] > arr[i])
            {
                max_idx = j;
            }
            if(i != max_idx)
            {
                swap(&arr[i], &arr[max_idx]);
            }
        }
    }
}

static void sort_arr_ascending(int *arr, int n)
{
    for(int i = 0; i < n-1; i++)
    {
        int min_idx = i;
        for(int j = i+1; j < n; j++)
        {
            if(arr[j] < arr[i])
            {
                min_idx = j;
            }
            if(i != min_idx)
            {
                swap(&arr[i], &arr[min_idx]);
            }
        }
    }
}

int main()
{
    int n = 5;
    int a[] = {3, 6, 8, 1, 0};

    printf("=====================================================\n");
    printf("Unsorted array:\n");
    arr_print(a, n);

    printf("Sorted in descending order:\n");
    sort_arr_descending(a, n);
    arr_print(a, n);

    printf("Sorted in ascending order:\n");
    sort_arr_ascending(a, n);
    arr_print(a, n);
    printf("=====================================================\n");

    return 0;
}
