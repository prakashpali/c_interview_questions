/*
 * NVIDIA Interview Question:
 *
 * Question:
 * Write some code to test whether either of bits 5 or 8 in a 32-bit unsigned integer
 * are set. Bits are numbered from 0 (LSB) to 31 (MSB).
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/*
 * ==============================================================================
 * CONCEPT & BIT MASK EXPLANATION
 * ==============================================================================
 *
 * Bit Numbering (0 = LSB, 31 = MSB):
 *  31                                8       5         0
 * +---+---+ ... +---+---+---+---+---+---+---+---+---+---+
 * |   |   |     |   |   |   |   |   | 1 |...| 1 |...|   |
 * +---+---+ ... +---+---+---+---+---+---+---+---+---+---+
 *                                     ^       ^
 *                                   Bit 8   Bit 5
 *
 * Mask Calculation:
 * - Bit 5: (1U << 5) = 0x00000020 (32)
 * - Bit 8: (1U << 8) = 0x00000100 (256)
 * - Combined Mask = (1U << 5) | (1U << 8) = 0x00000120 (288)
 *
 * Important Embedded / Firmware Considerations:
 * 1. Always use unsigned suffix `1U`:
 *    In C, `1` is a signed int. While shifting by 5 or 8 does not overflow a signed
 *    32-bit int, using `1U` is best practice in firmware to prevent accidental UB
 *    when shifting higher bit positions (e.g., `1 << 31` causes signed overflow UB).
 * 2. Return boolean:
 *    `(val & MASK) != 0` evaluates cleanly to a boolean (0 or 1).
 * 3. Assembly efficiency:
 *    On ARM architectures (Cortex-M, Cortex-A), this compiles to a single `TST`
 *    instruction (Test bits: bitwise AND and set condition flags):
 *        TST R0, #0x120
 *        BNE bit_is_set
 */

#define BIT(n)              (1U << (n))
#define MASK_BIT_5_OR_8     (BIT(5) | BIT(8))  // 0x120

/*
 * Interpretation 1: Inclusive OR (Standard)
 * Tests if AT LEAST ONE of bit 5 or bit 8 is set (Bit 5, Bit 8, or both).
 */
bool is_bit_5_or_8_set(uint32_t val)
{
    return (val & MASK_BIT_5_OR_8) != 0;
}

/*
 * Interpretation 2: Exclusive OR (Strict "Either ... Or")
 * Tests if EXACTLY ONE of bit 5 or bit 8 is set, but NOT both.
 * (Helpful bonus to mention during an interview to show thoroughness).
 */
bool is_strictly_one_of_bit_5_or_8_set(uint32_t val)
{
    uint32_t masked = val & MASK_BIT_5_OR_8;
    // Exactly one bit is set if masked is non-zero and not equal to both bits set
    return (masked != 0) && (masked != MASK_BIT_5_OR_8);
}

/*
 * Test Harness
 */
void run_test(const char *label, uint32_t val)
{
    printf("%-30s | Value: 0x%08X | Inclusive (At least one): %s | Strict XOR: %s\n",
           label,
           val,
           is_bit_5_or_8_set(val) ? "SET" : "NOT SET",
           is_strictly_one_of_bit_5_or_8_set(val) ? "YES" : "NO");
}

int main(void)
{
    printf("=========================================================================\n");
    printf("Testing Bits 5 and 8 (Mask: 0x%08X)\n", MASK_BIT_5_OR_8);
    printf("=========================================================================\n");

    run_test("Neither set", 0x00000000);
    run_test("Only bit 5 set", BIT(5));
    run_test("Only bit 8 set", BIT(8));
    run_test("Both bits 5 and 8 set", BIT(5) | BIT(8));
    run_test("Arbitrary value (0x00000021)", 0x00000021); // bit 0 and 5 set
    run_test("Arbitrary value (0x0000000F)", 0x0000000F); // bits 0-3 set
    run_test("All 32 bits set", 0xFFFFFFFF);

    return 0;
}
