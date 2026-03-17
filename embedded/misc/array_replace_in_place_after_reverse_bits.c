
/**
 * @brief
 * ### Challenge J: "The Bit-Reversed Array" (Array/In-Place)
 * Scenario: You are implementing a Fast Fourier Transform (FFT) on a DSP. FFT
 * requires the input array to be in bit-reversed order. (e.g., index 1 (01b)
 * swaps with index 2 (10b)).
 *
 * Task: Given an array of N elements (where N is a power of 2), swap the
 * elements in-place based on their bit-reversed indices.
 * The Catch: You must not use a second array.
 *
 * Embedded Twist: How do you ensure you don't swap an element "back" to its
 * original position (the double-swap problem)?
 *
 */

#include "../../utils.h"

static void swap_values(uint32_t *ptr1, uint32_t *ptr2)
{
    if (*ptr1 == *ptr2)
    {
        return;
    }
    *ptr1 ^= *ptr2;
    *ptr2 ^= *ptr1;
    *ptr1 ^= *ptr2;

}

static uint32_t reverse_bits(uint32_t n, uint32_t N)
{
    uint32_t rev = 0;
    for (int i = 0; i < N; i++)
    {
        if (n & (1 << i))
        {
            rev |= (1 << (N - 1 - i));
        }
    }

    return rev;
}

int reverse_replace(uint32_t *arr, uint32_t size, uint32_t N)
{
    uint32_t half_size = size/2;
    for (uint32_t i = 0; i < half_size; i++)
    {
        uint32_t rev_i = reverse_bits(i, N);
        if (arr[i] != arr[rev_i])
        {
            swap_values(&arr[i], &arr[rev_i]);
        }
    }

}

int main(void)
{
    uint32_t N = 3;
    uint32_t size = 1 << N;
    uint32_t *arr = (uint32_t *)malloc(size*sizeof(uint32_t));

    /* Prepare the array */
    for (uint32_t i = 0; i < size; i++)
    {
        arr[i] = i;
    }

    arr_print(arr, size);

    reverse_replace(arr, size, N);

    arr_print(arr, size);

    return 0;
}