/**
 * @file array_duplicates.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-03-14
 *
 * @copyright Copyright (c) 2026
 * ### Challenge G: "The Compact Byte Array" (Array/Logic)
 *
 * Scenario: You have a stream of 8-bit sensor readings. To save SRAM, you want to
 * "compress" them by removing any adjacent duplicates
 * (e.g., [1, 2, 2, 3, 3, 3, 1] becomes [1, 2, 3, 1]).
 *
 * Task: Implement int compress_array(uint8_t* arr, int size);.
 *
 * The Catch: You must do this in-place.
 *
 * Requirement: Return the new size of the array. The remaining "dead" space at the end of the array should be ignored.
 *
 * Embedded Twist: Minimize the number of "Store" instructions to the array to save power.
 *
 */

#include "../../utils.h"

int remove_duplicates(int *arr, int size)
{
    int i, j = 0;

    if (size <= 0)
    {
        return 0;
    }

    for (i = 0; i < size - 1; i++)
    {
        if (arr[i] == arr[i+1])
        {
            continue;
        }
        else
        {
            if (j != i)
            {
                arr[j++] = arr[i++];
            }
            else
            {
                j++;
            }
        }
    }

    arr[j++] = arr[i];

    return j;
}

int main(void)
{
    int arr[] = {1, 2, 2, 3, 3, 3, 1};
    int size = sizeof(arr)/sizeof(arr[0]);

    arr_print(arr, size);

    size = remove_duplicates(arr, size);

    arr_print(arr, size);

    return 0;
}