/**
 * Print index of subarray with given sum
 */

#include "../utils.h"

void subarraySum(int *arr, int arr_size, int sum, int* ret)
{
    int curr_sum = 0;
    int s = 0, e;

    for (int i = 0; i < arr_size; i++)
    {
        curr_sum += arr[i];
        e = i;

        while (curr_sum > sum && s < e)
        {
            printf("curr_sum from %d to %d : %d\n", s, e, curr_sum);
            curr_sum -= arr[s++];
        }

        if (curr_sum == sum)
        {
            printf("curr_sum from %d to %d : %d\n", s, e, curr_sum);
            ret[0] = s;
            ret[1] = e;
            break;
        }

    }

}

// Driver Code
int main()
{
    int arr[] = {15, 2, 4, 8, 9, 5, 10, 23};
    int arr_size = sizeof(arr)/sizeof(arr[0]);
    int sum = 23;
    int result[2] = {-1};

    printf("=====================================================\n");

    printf("Original array: ");
    arr_print(arr, arr_size);

    subarraySum(arr, arr_size, sum, result);

    printf("Subset indeces are: ");
    if (-1 != result[0])
    {
        arr_print(result, 2);
    }
    printf("=====================================================\n");

    return 0;
}