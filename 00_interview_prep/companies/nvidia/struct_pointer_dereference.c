/*
 * NVIDIA Interview Question:
 * 
 * Question:
 * What does this code do? Give an alternative way of writing it.
 *
 * Code Snippet:
 * x = (*state).x;
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * Explanation:
 * 1. What does this code do?
 *    - `state` is a pointer to a struct (or union) that contains a member named `x`.
 *    - `(*state)` dereferences the pointer to access the struct instance itself.
 *    - Parentheses around `(*state)` are required because the member access operator (`.`)
 *      has higher precedence than the dereference operator (`*`).
 *      Without parentheses, `*state.x` would be parsed as `*(state.x)`, which would be an error
 *      if `state` is a pointer rather than a struct.
 *    - `.x` selects the member `x` of that struct.
 *    - Finally, the evaluated value is assigned to the variable `x`.
 *
 * 2. Alternative way of writing it:
 *    - Using the arrow operator (`->`):
 *          x = state->x;
 *
 *    - In C, `pointer->member` is syntactic sugar and is semantically identical to `(*pointer).member`.
 *
 * 3. Machine / Assembly Level:
 *    - Both forms generate the exact same machine code: base register + offset load
 *      (e.g., in ARM: LDR R0, [R1, #offset_of_x]).
 *
 * 4. Safety Consideration:
 *    - If `state` is NULL, both `(*state).x` and `state->x` cause undefined behavior (typically a segmentation fault).
 */

typedef struct {
    int x;
    int y;
} State;

int main(void)
{
    State s = {.x = 42, .y = 100};
    State *state = &s;

    // Original snippet
    int x1 = (*state).x;

    // Alternative snippet (preferred & idiomatic C)
    int x2 = state->x;

    printf("Value accessed via (*state).x : %d\n", x1);
    printf("Value accessed via state->x    : %d\n", x2);

    return 0;
}
