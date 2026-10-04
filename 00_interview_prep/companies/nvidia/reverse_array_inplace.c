/*
 * NVIDIA Interview Question:
 *
 * Question:
 * Write some code to reverse the order of (not sort) the elements in an array
 * of integers, int m[100], in place.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

/*
 * ==============================================================================
 * ALGORITHM EXPLANATION
 * ==============================================================================
 *
 * Problem:
 * Reverse the elements of an array of 100 integers in-place without using extra
 * array allocation, and without sorting.
 *
 * Two-Pointer Technique (Optimal: O(N) time, O(1) space):
 * 1. Initialize two indices (or pointers):
 *    - `left` pointing to the first element (index 0).
 *    - `right` pointing to the last element (index 99 for size 100, or size - 1).
 * 2. Loop while `left < right`:
 *    - Swap `arr[left]` and `arr[right]`.
 *    - Increment `left` (`left++`).
 *    - Decrement `right` (`right--`).
 * 3. Termination:
 *    - When `left >= right`, exactly floor(size / 2) swaps have taken place
 *      (50 swaps for size 100).
 *    - If size is odd, the middle element naturally remains untouched.
 *
 * Swapping Methods:
 * - Temporary variable: Preferred and idiomatic. Compilers map this to registers,
 *   enabling optimal pipelining and SIMD/vectorization optimizations.
 * - XOR swap: Mentioned in interviews as a curiosity (`a ^= b; b ^= a; a ^= b;`),
 *   but in modern architectures, temp variable with registers is faster due to
 *   avoiding read-after-write dependencies and self-cancellation risks.
 */

#define ARRAY_SIZE 100

// Approach 1: Index-based Two-Pointer (Clear & Safe)
void reverse_array_indices(int m[], size_t size)
{
    if (m == NULL || size <= 1) {
        return;
    }

    size_t left = 0;
    size_t right = size - 1;

    while (left < right)
    {
        int temp = m[left];
        m[left] = m[right];
        m[right] = temp;

        left++;
        right--;
    }
}

// Approach 2: Pointer Arithmetic (Idiomatic C for Embedded Systems)
void reverse_array_pointers(int *start, size_t size)
{
    if (start == NULL || size <= 1) {
        return;
    }

    int *end = start + size - 1;

    while (start < end)
    {
        int temp = *start;
        *start = *end;
        *end = temp;

        start++;
        end--;
    }
}

// Helper to print a preview of the array
void print_array_preview(const char *label, const int m[], size_t size)
{
    printf("%s:\n  [", label);
    for (size_t i = 0; i < 5; i++) {
        printf("%d, ", m[i]);
    }
    printf("... ");
    for (size_t i = size - 5; i < size; i++) {
        printf("%d%s", m[i], (i == size - 1) ? "" : ", ");
    }
    printf("]\n");
}

int main(void)
{
    int m[ARRAY_SIZE];

    // Initialize array with 0, 1, 2, ..., 99
    for (int i = 0; i < ARRAY_SIZE; i++) {
        m[i] = i;
    }

    print_array_preview("Original array", m, ARRAY_SIZE);

    // Reverse in place using Approach 1
    reverse_array_indices(m, ARRAY_SIZE);
    print_array_preview("Reversed array (via indices)", m, ARRAY_SIZE);

    // Reverse back in place using Approach 2
    reverse_array_pointers(m, ARRAY_SIZE);
    print_array_preview("Re-reversed array (via pointers)", m, ARRAY_SIZE);

    return 0;
}
