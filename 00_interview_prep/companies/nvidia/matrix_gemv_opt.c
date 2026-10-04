/*
 * NVIDIA Interview Question:
 * Section 3.2: Matrix-Vector Optimization (GEMV)
 *
 * Question:
 * How can the following code be optimised?
 *
 * a) Consider how a compiler may attempt to optimise or auto-vectorise the loop
 *    in the function.
 * b) Suggest improvements to the code that might allow the compiler to better
 *    optimise the code.
 *
 * Original Code:
 * --------------
 * #define SIZE ... // a large number
 *
 * void f(float x[SIZE],
 *        const float A[SIZE][SIZE],
 *        const float b[SIZE], const float c[SIZE]) {
 *     float y[SIZE];
 *     int i, j;
 *
 *     for (i = 0; i < SIZE; ++i)
 *         y[i] = 0.0;
 *
 *     for (j = 0; j < SIZE; ++j)
 *         for (i = 0; i < SIZE; ++i)
 *             y[i] += A[i][j] * b[j];
 *
 *     for (j = 0; j < SIZE; ++j)
 *         x[j] = y[j] + c[j];
 * }
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 512

/*
 * ==============================================================================
 * PART (a): COMPILER ANALYSIS & CRITICAL BOTTLENECKS IN ORIGINAL CODE
 * ==============================================================================
 *
 * Mathematical Operation:
 * Computes: x = (A * b) + c   (Matrix-Vector multiplication followed by vector addition)
 *
 * Major Performance Bottlenecks:
 *
 * 1. Column-Major Stride on Row-Major Matrix (Disastrous Cache Misses):
 *    - In C, 2D arrays are stored in ROW-MAJOR order (contiguous row by row).
 *    - The original code loops `for (j = 0; ...) for (i = 0; ...)` and reads `A[i][j]`.
 *    - In the inner loop, `i` increments, so consecutive accesses jump by `SIZE * sizeof(float)`
 *      bytes in memory (A[0][j], A[1][j], A[2][j], ...).
 *    - For large SIZE, every single inner-loop read is a CACHE MISS. A full 64-byte cache line
 *      is loaded from DRAM, but only 4 bytes (one float) are used before being evicted!
 *
 * 2. Excessive Memory Traffic to `y[i]`:
 *    - `y[i] += A[i][j] * b[j]` repeatedly reads and writes to the memory buffer `y`
 *      in the inner loop rather than keeping the accumulator in a CPU register.
 *
 * 3. Stack Overflow Risk from `float y[SIZE]`:
 *    - `y[SIZE]` is allocated on the stack. If SIZE is large (e.g. SIZE = 100,000),
 *      `y` requires 400KB to multiple Megabytes, triggering a stack overflow (SIGSEGV).
 *
 * 4. Redundant Separate Loops:
 *    - Loop 1 zeroes `y`, Loop 2 calculates `A * b`, Loop 3 adds `c`.
 *    - Multiple passes over memory add loop overhead and pollute cache lines.
 *
 * 5. Pointer Aliasing:
 *    - Without `restrict`, the compiler must assume writing to `x` might overwrite `A`, `b`, or `c`.
 *
 * ==============================================================================
 * PART (b): STEP-BY-STEP OPTIMISATIONS
 * ==============================================================================
 *
 * 1. Loop Interchange (Row-Major Access):
 *    - Swap `i` and `j` in the matrix loop: outer loop `i`, inner loop `j`.
 *    - Memory access to `A[i][j]` becomes perfectly sequential (stride-1):
 *      `A[i][0], A[i][1], A[i][2], ...`
 *    - Enables 100% cache line utilization and hardware stream prefetching.
 *
 * 2. Loop Fusion & Eliminating Array `y[SIZE]`:
 *    - Initialize the accumulator directly with `c[i]`!
 *    - Completely eliminates the temporary buffer `y[SIZE]` (reducing stack memory
 *      from O(SIZE) to O(1) and removing stack overflow risk).
 *    - Fuses all 3 loops into a SINGLE clean loop!
 *
 * 3. Register Accumulation & Fused Multiply-Add (FMA):
 *    - Inner loop accumulates into a scalar register `sum`.
 *    - Directly maps to hardware SIMD FMA instructions (e.g. `vfmadd231ps` on x86,
 *      `fmla` on ARM NEON).
 *
 * 4. `restrict` Keyword:
 *    - Informs the compiler that `x`, `A`, `b`, and `c` do not overlap, enabling
 *      aggressive auto-vectorization.
 */

// Original unoptimised version
void gemv_original(float x[SIZE],
                   const float A[SIZE][SIZE],
                   const float b[SIZE], const float c[SIZE])
{
    float y[SIZE];
    int i, j;

    for (i = 0; i < SIZE; ++i)
        y[i] = 0.0f;

    for (j = 0; j < SIZE; ++j)
        for (i = 0; i < SIZE; ++i)
            y[i] += A[i][j] * b[j];

    for (j = 0; j < SIZE; ++j)
        x[j] = y[j] + c[j];
}

// Fully optimised version
void gemv_optimised(float * restrict x,
                    const float (* restrict A)[SIZE],
                    const float * restrict b,
                    const float * restrict c)
{
    // Fused loop: Eliminates temporary array y entirely!
    for (int i = 0; i < SIZE; ++i) {
        float sum = c[i]; // Initialize with c[i] directly

        // Sequential memory access: A[i][j] and b[j] are contiguous
        // Compilers (GCC/Clang -O3) easily auto-vectorize this dot-product with FMA
        #pragma GCC ivdep
        for (int j = 0; j < SIZE; ++j) {
            sum += A[i][j] * b[j];
        }

        x[i] = sum;
    }
}

int main(void)
{
    printf("=== Section 3.2: Matrix-Vector Optimization (GEMV) ===\n\n");

    // Dynamic heap allocation to safely support large SIZE in test
    float *x_orig = malloc(SIZE * sizeof(float));
    float *x_opt  = malloc(SIZE * sizeof(float));
    float (*A)[SIZE] = malloc(SIZE * sizeof(*A));
    float *b = malloc(SIZE * sizeof(float));
    float *c = malloc(SIZE * sizeof(float));

    if (!x_orig || !x_opt || !A || !b || !c) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize inputs
    for (int i = 0; i < SIZE; ++i) {
        b[i] = 1.0f;
        c[i] = 2.0f;
        for (int j = 0; j < SIZE; ++j) {
            A[i][j] = 0.5f;
        }
    }

    // Run both
    gemv_original(x_orig, A, b, c);
    gemv_optimised(x_opt, A, b, c);

    // Verify numerical equivalence
    float max_diff = 0.0f;
    for (int i = 0; i < SIZE; ++i) {
        float diff = (x_orig[i] > x_opt[i]) ? (x_orig[i] - x_opt[i]) : (x_opt[i] - x_orig[i]);
        if (diff > max_diff) max_diff = diff;
    }

    printf("Verification: Max difference between original and optimised = %.6f\n", max_diff);
    printf("Sample output x[0] = %.2f (Expected: %.2f * 0.5 + 2.0 = %.2f)\n",
           x_opt[0], (float)SIZE, (float)SIZE * 0.5f + 2.0f);

    free(x_orig);
    free(x_opt);
    free(A);
    free(b);
    free(c);

    return 0;
}
