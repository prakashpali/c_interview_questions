/*
 * NVIDIA Interview Question:
 * Section 3.1: Loop Optimisation and Auto-Vectorisation
 *
 * Question:
 * How can the following code be optimised?
 *
 * a) Consider how a compiler may attempt to optimise or auto-vectorise the loop
 *    in the function.
 * b) If you believe it is not possible for the code to be auto-vectorised by the
 *    compiler, explain why.
 * c) Suggest improvements to the code that might allow the compiler to
 *    auto-vectorise or better optimise the code.
 *
 * Original Code:
 * --------------
 * extern void g(int* py);
 *
 * void f (int* p, int* q, int* r, int n) {
 *     int x = ...;
 *     int y = ...;
 *     for (int i = 5; i < n; i++) {
 *         p[i] += 1000/x;
 *         q[i] += 1000/y;
 *         g(&x);
 *         r[i] += 1000/y + p[4];
 *     }
 * }
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * ==============================================================================
 * PART (a): HOW A COMPILER ATTEMPTS TO OPTIMISE
 * ==============================================================================
 *
 * 1. Loop-Invariant Code Motion (LICM):
 *    - `y` is a local variable whose address is never taken. The compiler knows `y`
 *      cannot be modified by `g(&x)` or pointer stores. Therefore, `1000 / y` is
 *      loop-invariant and can theoretically be hoisted out of the loop.
 *    - `p[4]`: Can it be hoisted? The loop modifies `p[i]` for `i >= 5`. It never
 *      writes to `p[4]` through `p`. HOWEVER, because C allows pointer aliasing,
 *      stores to `q[i]` or `r[i]` might overwrite `p[4]`. Without `restrict`,
 *      the compiler CANNOT safely hoist `p[4]`!
 *
 * 2. Common Subexpression Elimination (CSE):
 *    - `1000 / y` appears twice in the same iteration (in `q[i]` and `r[i]`).
 *      The compiler can eliminate the second division and reuse the first result.
 *
 * 3. Dead Code / Strength Reduction:
 *    - If division can be converted to multiplication (for constants), compiler does so;
 *      here divisors are variables, so costly integer DIV instructions are used.
 *
 * ==============================================================================
 * PART (b): WHY AUTO-VECTORISATION IS IMPOSSIBLE IN ORIGINAL CODE
 * ==============================================================================
 *
 * 1. Opaque External Function Call (`g(&x)`):
 *    - `g(&x)` is an external function call with unknown side effects. SIMD vector
 *      instructions require executing the same operation across 4, 8, or 16 elements
 *      simultaneously. A function call inside the loop forces sequential scalar execution.
 *
 * 2. Loop-Carried Dependency:
 *    - `g(&x)` takes `&x` as a non-const pointer, meaning `x` is modified on each
 *      iteration. The value of `1000 / x` in iteration (i+1) depends on `g(&x)`
 *      from iteration i. This serialized dependency chain prevents parallel vector lanes.
 *
 * 3. Pointer Aliasing Hazards:
 *    - Pointers `p`, `q`, and `r` may point to overlapping memory regions (e.g., `q == p + 1`).
 *      Without proof of non-aliasing, the compiler must preserve strict scalar order.
 *
 * 4. Variable Integer Division:
 *    - Integer division (`idiv`) is not vectorizable on most architectures (or incurs
 *      immense latency compared to vector addition/multiplication).
 *
 * ==============================================================================
 * PART (c): SUGGESTED IMPROVEMENTS
 * ==============================================================================
 *
 * 1. Hoist Loop Invariants:
 *    - Precompute `const int inv_y = 1000 / y;` outside the loop.
 *    - Cache `const int p4_val = p[4];` into a local variable outside the loop.
 *
 * 2. Use `restrict` Pointers:
 *    - Declare `int* restrict p, int* restrict q, int* restrict r`.
 *    - Informs the compiler that memory blocks do not overlap.
 *
 * 3. Loop Fission / Distribution:
 *    - Split the independent operations into separate loops!
 *    - Updates to `q` and `r` only depend on `inv_y` and `p4_val`. They have ZERO
 *      dependency on `x` or `g(&x)`.
 *    - By extracting them into their own loop, that loop becomes 100% AUTO-VECTORISABLE
 *      with SIMD instructions (AVX2 / ARM NEON)!
 */

// Dummy implementation of external g() for testing
void g(int* py) {
    if (py) {
        *py += 1;
    }
}

// Optimised implementation
void f_optimised(int* restrict p, int* restrict q, int* restrict r, int n)
{
    int x = 10;
    int y = 20;

    if (n <= 5) return;

    // 1. Hoist loop invariants
    const int inv_y = 1000 / y;
    const int p4_val = p[4];
    const int r_add = inv_y + p4_val;

    // 2. Loop Fission: Loop A (Vectorizable loop for q and r)
    // This loop has no function calls and contiguous non-aliased memory access.
    // Compilers (GCC/Clang -O3) will fully auto-vectorize this loop using SIMD!
    #pragma GCC ivdep // Hint: no loop-carried vector dependencies
    for (int i = 5; i < n; i++) {
        q[i] += inv_y;
        r[i] += r_add;
    }

    // 3. Loop B: Scalar loop for operations dependent on g(&x)
    for (int i = 5; i < n; i++) {
        p[i] += 1000 / x;
        g(&x);
    }
}

int main(void)
{
    printf("=== Section 3.1: Loop Optimisation and Vectorisation ===\n");
    printf("Successfully analyzed compiler barriers and implemented loop fission with restrict.\n");

    const int n = 16;
    int p[16] = {0}, q[16] = {0}, r[16] = {0};
    p[4] = 42;

    f_optimised(p, q, r, n);

    printf("p[5] = %d, q[5] = %d, r[5] = %d\n", p[5], q[5], r[5]);
    printf("p[6] = %d, q[6] = %d, r[6] = %d\n", p[6], q[6], r[6]);

    return 0;
}
