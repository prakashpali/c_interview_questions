/*
 * NVIDIA Interview Question:
 * Section 2.2: A Storage Problem
 *
 * Question:
 * You have an array of 64 variables to store, x[i], where 0 <= i <= 63.
 * These variables can only take values 0 to 15 (4 bits each).
 *
 * byte a[64]; // Very wasteful of memory
 *
 * A more efficient method stores two values in each 8-bit byte as follows:
 *   [Byte 0   ] [Byte 1   ] [Byte 2   ] [Byte 3   ] ...
 *   [x[1] x[0]] [x[3] x[2]] [x[5] x[4]] [x[7] x[6]] ...
 *
 * Design two functions, with declarations given below, which store and
 * retrieve the values:
 *
 *   void Store(byte Value, int Index);
 *   byte Recall(int Index);
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

typedef uint8_t byte;

#define TOTAL_ELEMENTS 64
#define STORAGE_BYTES  (TOTAL_ELEMENTS / 2)  // 32 bytes

// Static storage pool of 32 bytes to hold 64 4-bit nibbles
static byte storage[STORAGE_BYTES] = {0};

/*
 * Store:
 * Stores a 4-bit Value (0-15) into element at Index (0-63).
 *
 * Mapping:
 * - Byte index = Index / 2 (or Index >> 1)
 * - If Index is even (Index & 1 == 0): stored in lower nibble (bits 0..3)
 * - If Index is odd  (Index & 1 == 1): stored in upper nibble (bits 4..7)
 */
void Store(byte Value, int Index)
{
    if (Index < 0 || Index >= TOTAL_ELEMENTS) {
        fprintf(stderr, "Error: Index %d out of bounds [0..63]\n", Index);
        return;
    }

    int byte_idx = Index >> 1; // Index / 2
    byte val_nibble = Value & 0x0F; // Clamp to 4 bits

    if ((Index & 1) == 0) {
        // Even index: modify lower nibble (bits 0-3), preserve upper nibble (bits 4-7)
        storage[byte_idx] = (storage[byte_idx] & 0xF0) | val_nibble;
    } else {
        // Odd index: modify upper nibble (bits 4-7), preserve lower nibble (bits 0-3)
        storage[byte_idx] = (storage[byte_idx] & 0x0F) | (val_nibble << 4);
    }
}

/*
 * Recall:
 * Retrieves the 4-bit value at Index (0-63).
 */
byte Recall(int Index)
{
    if (Index < 0 || Index >= TOTAL_ELEMENTS) {
        fprintf(stderr, "Error: Index %d out of bounds [0..63]\n", Index);
        return 0xFF; // Error indicator
    }

    int byte_idx = Index >> 1; // Index / 2

    if ((Index & 1) == 0) {
        // Even index: extract lower nibble
        return storage[byte_idx] & 0x0F;
    } else {
        // Odd index: extract upper nibble
        return (storage[byte_idx] >> 4) & 0x0F;
    }
}

int main(void)
{
    printf("=== Testing 4-bit Nibble Packing (64 variables in 32 bytes) ===\n\n");

    // Test 1: Store pattern where x[i] = i % 16
    for (int i = 0; i < TOTAL_ELEMENTS; i++) {
        Store((byte)(i % 16), i);
    }

    // Verify all stored values
    bool all_passed = true;
    for (int i = 0; i < TOTAL_ELEMENTS; i++) {
        byte expected = (byte)(i % 16);
        byte actual = Recall(i);
        if (actual != expected) {
            printf("Mismatch at index %d: Expected %u, got %u\n", i, expected, actual);
            all_passed = false;
        }
    }

    if (all_passed) {
        printf("All 64 elements successfully verified!\n\n");
    }

    // Inspect the first 4 packed bytes
    printf("Memory dump of first 4 bytes:\n");
    for (int b = 0; b < 4; b++) {
        printf("Byte %d: 0x%02X (x[%d]=0x%X, x[%d]=0x%X)\n",
               b, storage[b],
               2 * b + 1, Recall(2 * b + 1),
               2 * b, Recall(2 * b));
    }

    return 0;
}
