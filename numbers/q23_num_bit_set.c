/**
 * Q: Given a number N, start bit position, end bit position, and another number n1.
 * Set all bits from start to end position of N with n1.
 * 
 * Example:
 * N = 0x12100000
 * start = 4
 * end = 7
 * n1 = 0xf
 * 
 * Result: 0x12110f0
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint32_t my_solution(uint32_t N, int start, int end, uint32_t n1)
{
    uint32_t mask = (uint32_t)((0xffffffffULL << start) &  ~(0xffffffffULL << (end+1)));
    
    // 1. Clear the target bits in N
    N &= ~mask;
    
    // 2. Shift n1 into position, mask it to prevent overflow beyond 'end', and OR it with N
    N |= ((n1 << start) & mask);
    
    return N;
}

uint32_t set_nth_bit(uint32_t N, int start, int end, uint32_t n1)
{
    // Calculate the number of bits to set
    int num_bits = end - start + 1;
    
    // Create a mask with 'num_bits' 1s, then shift it to the 'start' position
    // (We use 1ULL to safely handle the case where num_bits == 32)
    uint32_t mask = ((1ULL << num_bits) - 1) << start;
    
    // 1. Clear the target bits in N
    N &= ~mask;
    
    // 2. Shift n1 into position, mask it to prevent overflow beyond 'end', and OR it with N
    N |= (n1 << start) & mask;
    
    return N;
}

int main(void)
{
    uint32_t N = 0x12100000;
    int start = 0;
    int end = 31;
    uint32_t n1 = 0x3;
    
    printf("Original N : 0x%08X\n", N);
    
    uint32_t result = set_nth_bit(N, start, end, n1);
    
    // Note: The comment example '0x12110f0' seems to have a missing zero.
    // The correct result of setting bits 4-7 of 0x12100000 to 0xF is 0x121000F0.
    printf("Result     : 0x%08X\n", result);

    result = my_solution(N, start, end, n1);
    printf("Result     : 0x%08X\n", result);
    
    return 0;
}
