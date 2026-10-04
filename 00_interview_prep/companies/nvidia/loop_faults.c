/*
 * NVIDIA Interview Question:
 *
 * Question:
 * The following code fragment should print 0 to 100 inclusive in steps of 2.
 * Could you find the two major faults with it? How would you alter the code to do this?
 *
 * Original Code Fragment:
 * -----------------------
 * int n, s;
 * n = 0;
 * s = 1;
 * while (s > 0)
 * {
 *     printf("%d\n", n);
 *     n += 2;
 *     if (n == 100)
 *     {
 *         s = 0;
 *     }
 * }
 */

#include <stdio.h>

/*
 * ==============================================================================
 * ANALYSIS OF THE TWO MAJOR FAULTS
 * ==============================================================================
 *
 * Fault 1: Off-by-one Error (100 is never printed - Requirement Violated)
 * ----------------------------------------------------------------------
 * - When `n` is 98, `printf("%d\n", n);` prints 98.
 * - Next, `n += 2;` updates `n` to 100.
 * - The condition `if (n == 100)` evaluates to TRUE, setting `s = 0;`.
 * - The loop then checks `while (s > 0)`: since `s == 0`, the loop terminates
 *   IMMEDIATELY without executing the next iteration.
 * - Result: 100 is never printed! The fragment only prints 0 through 98.
 *
 * Fault 2: Redundant State Flag `s` & Fragile Termination Logic
 * ----------------------------------------------------------------------
 * - The variable `s` is an unnecessary sentinel/flag that obscures loop control.
 * - Using an exact equality check `n == 100` inside the loop body is brittle:
 *   if initial value or step size changes (e.g., starting at 1 or step of 3),
 *   `n` will bypass 100, resulting in an INFINITE LOOP (until integer overflow).
 * - Idiomatic C uses the loop condition itself (`n <= 100`) to govern iteration,
 *   making the code cleaner, safer, and eliminating the extra variable `s`.
 *
 * Note on Written Exam Variations:
 * - If written as `if (n = 100)` (single '=' assignment operator), `n` is assigned
 *   100 and evaluates to true on the very first iteration, stopping after printing 0.
 *
 * ==============================================================================
 * ALTERNATIVE / CORRECTED IMPLEMENTATIONS
 * ==============================================================================
 */

// Approach 1: Idiomatic C 'for' loop (Best Practice)
void print_even_for_loop(void)
{
    printf("--- Solution 1: Idiomatic 'for' loop ---\n");
    for (int n = 0; n <= 100; n += 2)
    {
        printf("%d ", n);
    }
    printf("\n\n");
}

// Approach 2: Corrected 'while' loop without flag variable
void print_even_while_loop(void)
{
    printf("--- Solution 2: Clean 'while' loop ---\n");
    int n = 0;
    while (n <= 100)
    {
        printf("%d ", n);
        n += 2;
    }
    printf("\n\n");
}

// Approach 3: Minimal correction preserving original structure (if required by interviewer)
void print_even_minimal_fix(void)
{
    printf("--- Solution 3: Minimal fix to original structure ---\n");
    int n = 0;
    int s = 1;
    while (s > 0)
    {
        printf("%d ", n);
        if (n >= 100) // Check boundary BEFORE increment or use >= 100
        {
            s = 0;
        }
        n += 2;
    }
    printf("\n\n");
}

int main(void)
{
    print_even_for_loop();
    print_even_while_loop();
    print_even_minimal_fix();

    return 0;
}
