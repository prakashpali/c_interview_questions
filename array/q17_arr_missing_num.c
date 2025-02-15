/**
 * Find missing number from the array
 */

#include "../utils.h"

#define GET_MIN(a, b) ((a) < (b) ? (a) : (b))

static int find_missing(int *arr1, int arr_size1)
{
    // XOR operation can be used in this situation
    // XOR1 = XOR of all numbers of array
    // XOR2 = XOR of all natural numbers till n
    // XOR1 ^ XOR2 gives the missing number

    int i = 0, xor1 = 0, xor2 = 0;
    for (i = 0; i < arr_size1; i++)
    {
        xor1 ^= arr1[i];
    }

    for (i = 0; i < arr_size1; i++)
    {
        xor2 ^= i;
    }

    return (xor1 ^ xor2);
}

// Driver Code
int main()
{
    int arr1[] = {1, 8, 6, 4, 5, 1, 1, 3, 7, 9};
    int arr_size1 = sizeof(arr1)/sizeof(arr1[0]);

    printf("=====================================================\n");

    printf("Original array1: ");
    arr_print(arr1, arr_size1);

    int missing = find_missing(arr1, arr_size1);

    printf("missing number from array = %d \n", missing);

    printf("=====================================================\n");

    return 0;
}