/*
 * NVIDIA Interview Question (Question g):
 *
 * Question:
 * Explain the difference in types and storage lifetime between these 2 declarations.
 *
 * Declarations:
 * -------------
 * char *animal = "monkey";
 * char fruit[] = "apple";
 */

#include <stdio.h>

/*
 * ==============================================================================
 * DETAILED COMPARISON TABLE & EXPLANATION
 * ==============================================================================
 *
 * Feature                  | char *animal = "monkey";             | char fruit[] = "apple";
 * -------------------------|--------------------------------------|--------------------------------------
 * 1. Type                  | Pointer to char (`char *`)           | Array of 6 chars (`char[6]`)
 *                          | Stores memory address of string      | Represents contiguous memory holding
 *                          |                                      | 'a', 'p', 'p', 'l', 'e', '\0'
 * -------------------------|--------------------------------------|--------------------------------------
 * 2. Storage Location:     |                                      |
 *    - The variable itself | Stack (if local) or .data (if global)| Stack (if local) or .data/.rodata
 *    - The string data     | In .rodata (read-only text segment)  | In the array itself (copied to stack)
 * -------------------------|--------------------------------------|--------------------------------------
 * 3. Mutability:           |                                      |
 *    - Modifying characters| animal[0] = 'd'; -> UNDEFINED        | fruit[0] = 'A'; -> VALID & safe
 *    - Reassigning target  | animal = "bear"; -> VALID (re-points)| fruit = "orange"; -> COMPILE ERROR
 *                          |                                      | (arrays are not modifiable lvalues)
 * -------------------------|--------------------------------------|--------------------------------------
 * 4. Storage Lifetime      |                                      |
 *    (When declared inside | Pointer variable `animal`:           | Array `fruit`:
 *     a function / local): | Automatic duration (lives on stack,  | Automatic duration (entire array
 *                          | destroyed when function returns).    | destroyed when function returns).
 *                          | String literal `"monkey"`:           |
 *                          | Static duration (lives in .rodata    |
 *                          | for the entire program execution).   |
 * -------------------------|--------------------------------------|--------------------------------------
 * 5. sizeof operator       | sizeof(animal) = sizeof(char *)      | sizeof(fruit) = 6 * sizeof(char)
 *                          | 8 bytes (64-bit) / 4 bytes (32-bit)  | Exactly 6 bytes (including '\0')
 * ==============================================================================
 */

void demonstrate_differences(void)
{
    char *animal = "monkey";
    char fruit[] = "apple";

    printf("=== Type and Size Differences ===\n");
    printf("sizeof(animal) (pointer size) : %zu bytes\n", sizeof(animal));
    printf("sizeof(fruit)  (array size)   : %zu bytes (includes null terminator)\n\n", sizeof(fruit));

    printf("=== Memory Addresses ===\n");
    printf("Address of pointer animal     : %p (stack)\n", (void *)&animal);
    printf("Address pointed to by animal  : %p (.rodata - text segment)\n", (void *)animal);
    printf("Address of fruit array        : %p (stack)\n\n", (void *)fruit);

    printf("=== Mutation Capability ===\n");
    // fruit is modifiable
    fruit[0] = 'A';
    printf("fruit after modification      : %s\n", fruit);

    // animal can be redirected to another string literal
    animal = "zebra";
    printf("animal redirected             : %s\n", animal);

    /*
     * CAUTION:
     * animal[0] = 'd'; // Segmentation fault / Undefined Behavior!
     * fruit = "orange"; // Compilation error: assignment to expression with array type
     */
}

int main(void)
{
    demonstrate_differences();
    return 0;
}
