
/**
 * ### The Challenge: Count Trailing Zeros (CTZ)
 *
 * Goal: Write a function in C that returns the index (0 to 31) of the first bit set to 1, starting from the Least Significant Bit (LSB).
 *
 * Constraints:
 *
 * No Intrinsics: Do not use __builtin_ctz or _BitScanForward.
 *
 * Efficiency: Avoid a simple 32-iteration loop. Aim for O(logn) or a constant time approach.
 *
 * Input: A uint32_t. If the input is 0, return a sentinel value (e.g., −1 or 32).
 *
 * ### Embedded Context: Why This Matters
 *
 * In a Real-Time OS (RTOS), the scheduler often maintains a "Ready List" as a bitmask. When the CPU finishes a task, it needs to find the next highest priority task.
 *
 * Bit 0: Highest Priority (e.g., Emergency Stop)
 *
 * Bit 31: Lowest Priority (e.g., Log Upload)
 *
 * Finding the first set bit is the "Find Next Task" operation.
 *
 * ### Technical Strategy Hints
 *
 * There are three common ways to solve this. I want to see which one you choose:
 *
 * Binary Search Approach: Check if the lower 16 bits are zero. If yes, the bit is in the upper 16. Repeat by halving.
 *
 * De Bruijn Sequence (Constant Time): A clever trick using a magic constant and a small lookup table. This is how many high-performance libraries do it.
 *
 * The "Isolation" Trick: You can isolate the lowest set bit using x & -x. How does that help you find its index?
 *
 * ### Your Task
 *
 * Write the C implementation for:
 * int32_t find_first_set_bit(uint32_t n);
 *
 * Bonus: Explain the Time Complexity of your solution and why your specific approach is suitable for a low-power microcontroller (like an ARM Cortex-M0) that might lack a hardware CLZ instruction.
 *
 */

#include "../utils.h"

static int32_t find_first_set_bit_optimized(uint32_t n) {
    if (n == 0) return -1;

    uint32_t x = n & -n; // Isolate LSB
    int32_t pos = 0;

    // Binary search the position of the isolated bit
    if (x & 0xFFFF0000) pos += 16;
    if (x & 0xFF00FF00) pos += 8;
    if (x & 0xF0F0F0F0) pos += 4;
    if (x & 0xCCCCCCCC) pos += 2;
    if (x & 0xAAAAAAAA) pos += 1;

    return pos;
}

static int32_t find_first_set_bit(uint32_t n)
{
    /* This approach takes 2 cycles for calculating 2's complement and 1 cycle for bit wise AND.
     * It takes maximum 32 cycles to find the position. Overall computation is very minimal. For
     * low power MCUs, it means minimal CPU usage and hence minimum power requirement.
     * CPU can execute this logic and stay in low power mode for longer.
     */
    uint32_t tmp = n & (-n);
    int32_t i = 0;

    /* This loop runs for maximum 32 times. Time complexity should be close to O(1). */
    while (tmp)
    {
        i++;
        tmp >>= 1;
    }

    /* Bit position starts from 0. If this function returns 2 it means, bit position 0 & 1 is not set, but bit position 2 is set.
     * For example 0x9 has 0th bit set.
     */
    return (i-1);
}

int main(void)
{
    uint32_t n = 0x9;

    printf("First set bit is %d\n", find_first_set_bit(n));

    return 0;
}