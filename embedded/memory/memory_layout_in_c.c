/**
 * C program to explain memory segments in c
 * .text    --> Code section. Read only.
 * .data    --> Initialized data segment
 *                  - Global variables and static variables that are initialized to a non-zero value.
 *                  - Initialized read-only (const char string[] = “hello world”;)
 *                  - Initialized read-write (static int i = 10; global int i = 10;). Only non-zero initialization.
 *
 * .bss     --> Uninitialized data segment. bss stands for block started by symbol.
 *                  - Global variables and static variables that are initialized to zero (static int i = 0; int j = 0;)
 *                  - Global variables and static variables that do not have any initialization in source code (static int i; int j;)
 *
 * .heap    --> Dynamic memory pool
 *                  - Used when malloc(), realloc() and free() are used.
 * .stack   --> Local variable and stack trace
 *                  - All local variables are stored in stack.
 *                  - All registers, variables, function addresses during context switch are stored in stack.
 *
 * Get the size of segments using this command (modify the file accordingly):
 *      - size -m '/Users/prakashpali/git_workspace/c_interview_questions/embedded/memory/bin/memory_layout_in_c.o'
 *
 */

#include "../../utils.h"

// int global_no_init;                  // Goes to .bss section. Initialized to 0.
// int global = 1;                      // Goes to .data section.
// int global_zero = 0;                 // Goes to .bss section.
// static int global_static_no_init;    // Goes to .bss section. Initialized to 0.
// static int global_static = 1;        // Goes to .data section.
static int global_static_zero = 0;   // Goes to .bss section.

int main()
{
    // int local_no_init;               // Goes to .stack section. Holds random value.
    // int local = 1;                   // Goes to .stack section.
    // static int local_static_no_init; // Goes to .bss section. Initialized to 0.
    // static int local_static = 1;     // Goes to .data section.
    // static int local_static_zero = 0;     // Goes to .bss section.

    printf("=====================================================\n");

    printf("Variable value = %d\n", global_static_zero);
    *((volatile int*)&global_static_zero) = 127;
    printf("Variable value = %d\n", global_static_zero);

    printf("=====================================================\n");

    return 0;
}
