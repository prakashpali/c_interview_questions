/*
 * NVIDIA Interview Question (Question h):
 *
 * Question:
 * What will be the value of sum?
 *
 * Code Fragment:
 * --------------
 * unsigned int i, sum = 0;
 * int myarray[] = { 1, 2, 3, 4, 5, 6 };
 * for( i = 0;
 *      i < sizeof(myarray);
 *      i++ ) {
 *     sum += myarray[i];
 * }
 */

#include <stdio.h>

/*
 * ==============================================================================
 * EXPLANATION: SIZEOF IN BYTES VS. NUMBER OF ELEMENTS
 * ==============================================================================
 *
 * Answer:
 * The value of `sum` is UNPREDICTABLE / UNDEFINED BEHAVIOR (Garbage Value).
 *
 * Why?
 * 1. `sizeof(myarray)` returns the total size of the array in BYTES, NOT the count
 *    of elements.
 * 2. On standard 32-bit and 64-bit architectures, `sizeof(int)` is 4 bytes.
 *    Therefore, `sizeof(myarray)` evaluates to:
 *        6 elements * 4 bytes/element = 24 bytes.
 * 3. The loop runs with condition:
 *        `i < 24`
 *    This causes the loop to iterate 24 times (indices 0 through 23).
 * 4. The array only has 6 elements (valid indices 0 to 5).
 *    Indices 6 through 23 access OUT-OF-BOUNDS memory on the stack (Buffer Over-read).
 * 5. As a result, `sum` adds the 6 valid elements (1 + 2 + 3 + 4 + 5 + 6 = 21) PLUS
 *    18 integers worth of random stack garbage (or may cause a segmentation fault).
 *
 * How to Fix it:
 * Divide `sizeof(myarray)` by `sizeof(myarray[0])` to get the element count:
 *     #define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
 */

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

void demonstrate_correct_sum(void)
{
    unsigned int i, sum = 0;
    int myarray[] = { 1, 2, 3, 4, 5, 6 };

    printf("sizeof(myarray)              = %zu bytes\n", sizeof(myarray));
    printf("sizeof(myarray[0])           = %zu bytes\n", sizeof(myarray[0]));
    printf("Number of elements (length)  = %zu\n\n", ARRAY_SIZE(myarray));

    // Correct loop
    for (i = 0; i < ARRAY_SIZE(myarray); i++) {
        sum += myarray[i];
    }

    printf("Correct sum (1+2+3+4+5+6)    = %u\n", sum);
}

int main(void)
{
    printf("=== Question h Analysis ===\n\n");
    demonstrate_correct_sum();
    return 0;
}
