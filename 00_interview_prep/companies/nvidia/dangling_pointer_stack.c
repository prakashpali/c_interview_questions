/*
 * NVIDIA Interview Question (Question i):
 *
 * Question:
 * What will be displayed by following program?
 *
 * Code Fragment:
 * --------------
 * #include <stdio.h>
 *
 * char* foo(int i) {
 *     char digits[] = "01234567890123456789";
 *     return &digits[i];
 * }
 *
 * void main() {
 *     printf("%s\n", foo(10));
 * }
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * ==============================================================================
 * EXPLANATION: RETURNING POINTER TO LOCAL STACK VARIABLE (DANGLING POINTER)
 * ==============================================================================
 *
 * Answer:
 * The output is UNDEFINED BEHAVIOR.
 *
 * Why?
 * 1. `digits[]` is declared as a local array with AUTOMATIC storage duration.
 *    It is allocated on the activation frame (stack frame) of function `foo()`.
 * 2. When `foo()` returns, its stack frame is popped / invalidated. The memory
 *    occupied by `digits` is no longer reserved and is subject to immediate reuse
 *    or corruption by subsequent function calls (such as `printf`).
 * 3. `return &digits[i];` returns a DANGLING POINTER (address of expired stack memory).
 * 4. In `main()`, `printf("%s\n", foo(10))` dereferences this dangling pointer:
 *    - Best-case scenario (coincidence): If `printf`'s stack frame has not yet
 *      clobbered that memory, it might appear to print "0123456789".
 *    - Likely scenario: `printf` sets up its own stack frame, partially or fully
 *      overwriting the memory, printing corrupted garbage.
 *    - Worst-case scenario: Segmentation fault / crash.
 *
 * Additional Note:
 * - `void main()` is non-standard in ISO C. The standard return type is `int main(void)`.
 *
 * ==============================================================================
 * PROPER SOLUTIONS
 * ==============================================================================
 */

// Fix 1: Pointer to string literal (lives in .rodata with static lifetime)
const char* foo_fixed_literal(int i) {
    const char *digits = "01234567890123456789";
    return &digits[i];
}

// Fix 2: Static array (persists for program lifetime in .data/.rodata)
const char* foo_fixed_static(int i) {
    static const char digits[] = "01234567890123456789";
    return &digits[i];
}

int main(void)
{
    printf("=== Question i Analysis ===\n\n");
    printf("Result using string literal pointer (safe): %s\n", foo_fixed_literal(10));
    printf("Result using static array storage (safe) : %s\n", foo_fixed_static(10));

    return 0;
}
