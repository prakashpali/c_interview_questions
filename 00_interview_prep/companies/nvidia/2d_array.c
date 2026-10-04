/*
 * Technical Interview Question:
 *
 * Question:
 * Can you write code to allocate a 2D array dynamically in C?
 *
 * Core CPU & Systems Architecture Topics:
 * 1. Subscript resolution: How `arr[i][j]` expands to `*(*(arr + i) + j)`.
 * 2. CPU Cache Performance: Spatial locality, 64-byte cache line utilization,
 *    and CPU hardware prefetcher behavior across sequential vs scattered memory.
 * 3. Memory & Allocation Overhead: Heap metadata per malloc chunk vs contiguous blocks.
 * 4. Error handling & Unwinding: Preventing memory leaks if an allocation fails midway.
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * ==============================================================================
 * CPU MEMORY LAYOUT & PERFORMANCE COMPARISON
 * ==============================================================================
 *
 * ------------------------------------------------------------------------------
 * Approach 1: Discontiguous (Array of Pointers via N+1 mallocs)
 * ------------------------------------------------------------------------------
 *  - Structure:
 *      arr ---> [ int* ] (row 0) ----> [ int | int | int ... ] (Heap chunk A)
 *               [ int* ] (row 1) ----> [ int | int | int ... ] (Heap chunk B)
 *               [ int* ] (row 2) ----> [ int | int | int ... ] (Heap chunk C)
 *
 *  - Syntax: `arr[i][j]` (Evaluates to: `*(*(arr + i) + j)`)
 *  - Allocations: (rows + 1) malloc calls.
 *  - CPU / Architecture Trade-offs:
 *      1. Cache Inefficiency: Rows may be scattered across non-contiguous heap
 *         addresses. Crossing from one row to the next defeats the CPU hardware
 *         prefetcher and causes L1/L2 cache misses.
 *      2. Pointer Chasing: Every access requires two memory dereferences:
 *         First fetch pointer `arr[i]`, then fetch value `arr[i][j]`.
 *      3. Allocator Overhead: Each malloc call adds 8-16 bytes of glibc chunk metadata.
 *      4. Complex Deallocation: Requires an O(N) loop to free every row.
 *  - Valid Use Cases:
 *      - "Ragged" / "jagged" arrays (where rows have differing lengths).
 *      - O(1) row swapping by simply swapping pointers (`tmp = arr[0]; arr[0] = arr[1]; arr[1] = tmp;`).
 *
 * ------------------------------------------------------------------------------
 * Approach 2: Contiguous Data Buffer with Row Pointers (2 Mallocs)
 * ------------------------------------------------------------------------------
 *  - Structure:
 *      arr ---> [ int* ] (row 0) ---\
 *               [ int* ] (row 1) ----+--> [ Row 0 elements | Row 1 elements | Row 2 elements ]
 *               [ int* ] (row 2) ---/    (Single contiguous block of rows * cols * sizeof(int))
 *
 *  - Syntax: Retains native `arr[i][j]` double-subscript syntax.
 *  - Allocations: Exactly 2 malloc calls (1 for pointer table, 1 for payload).
 *  - CPU / Architecture Trade-offs:
 *      1. Cache Friendly: Elements are strictly sequential in memory. Iterating
 *         through elements maximizes CPU cache line hits (64 bytes / line).
 *      2. Fast Deallocation: O(1) cleanup (`free(arr[0]); free(arr);`).
 *      3. Simple Error Handling: If the second malloc fails, only one pointer needs freeing.
 *
 * ==============================================================================
 */

/* ============================================================================
 * APPROACH 1: Array of Pointers (Discontiguous / Multi-malloc)
 * ============================================================================ */

int **get_2d_array_discontiguous(int rows, int cols)
{
    if (rows <= 0 || cols <= 0) {
        return NULL;
    }

    // 1. Allocate array of row pointers
    int **arr = (int **)malloc(rows * sizeof(int *));
    if (!arr) {
        perror("Failed to allocate row pointer array");
        return NULL;
    }

    // 2. Allocate each row individually
    for (int r = 0; r < rows; r++) {
        arr[r] = (int *)malloc(cols * sizeof(int));
        if (!arr[r]) {
            perror("Failed to allocate row block");
            // Unwind previously allocated rows to prevent memory leak
            for (int k = 0; k < r; k++) {
                free(arr[k]);
            }
            free(arr);
            return NULL;
        }
    }

    return arr;
}

void free_2d_array_discontiguous(int **arr, int rows)
{
    if (!arr) return;

    for (int r = 0; r < rows; r++) {
        free(arr[r]);
    }
    free(arr);
}

/* ============================================================================
 * APPROACH 2: Contiguous Data Buffer with Row Pointers (2 Mallocs)
 * ============================================================================ */

int **get_2d_array_contiguous(int rows, int cols)
{
    if (rows <= 0 || cols <= 0) {
        return NULL;
    }

    // 1. Allocate array of row pointers
    int **arr = (int **)malloc(rows * sizeof(int *));
    if (!arr) {
        perror("Failed to allocate row pointer array");
        return NULL;
    }

    // 2. Allocate all elements in a single contiguous memory block
    int *data = (int *)malloc(rows * cols * sizeof(int));
    if (!data) {
        perror("Failed to allocate contiguous data block");
        free(arr);
        return NULL;
    }

    // 3. Map each row pointer to its offset in the contiguous block
    for (int r = 0; r < rows; r++) {
        arr[r] = data + (r * cols);
    }

    return arr;
}

void free_2d_array_contiguous(int **arr)
{
    if (!arr) return;

    // arr[0] points to the head of the contiguous data block
    free(arr[0]);
    // free the pointer array
    free(arr);
}

/* ============================================================================
 * CPU CACHE LOCALITY & MEMORY VERIFICATION
 * ============================================================================ */

int main(void)
{
    const int rows = 3;
    const int cols = 4;

    printf("====================================================================\n");
    printf("1. TESTING DISCONTIGUOUS 2D ARRAY (Approach 1: N+1 Mallocs)\n");
    printf("====================================================================\n");
    int **arr1 = get_2d_array_discontiguous(rows, cols);
    if (arr1) {
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                arr1[r][c] = (r * 10) + c;
            }
        }

        for (int r = 0; r < rows; r++) {
            printf("Row %d (base %p): ", r, (void *)arr1[r]);
            for (int c = 0; c < cols; c++) {
                printf("%2d (&: %p) ", arr1[r][c], (void *)&arr1[r][c]);
            }
            printf("\n");
        }

        long diff1 = (char *)&arr1[1][0] - (char *)&arr1[0][cols - 1];
        printf("End of Row 0 to Start of Row 1 gap: %ld bytes (independent heap chunks)\n\n", diff1);
        free_2d_array_discontiguous(arr1, rows);
    }

    printf("====================================================================\n");
    printf("2. TESTING CONTIGUOUS 2D ARRAY (Approach 2: 2 Mallocs)\n");
    printf("====================================================================\n");
    int **arr2 = get_2d_array_contiguous(rows, cols);
    if (arr2) {
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                arr2[r][c] = 100 + (r * 10) + c;
            }
        }

        for (int r = 0; r < rows; r++) {
            printf("Row %d (base %p): ", r, (void *)arr2[r]);
            for (int c = 0; c < cols; c++) {
                printf("%3d (&: %p) ", arr2[r][c], (void *)&arr2[r][c]);
            }
            printf("\n");
        }

        long diff2 = (char *)&arr2[1][0] - (char *)&arr2[0][cols - 1];
        printf("End of Row 0 to Start of Row 1 gap: %ld bytes (exactly sizeof(int) = %zu bytes!)\n\n",
               diff2, sizeof(int));
        free_2d_array_contiguous(arr2);
    }

    return 0;
}