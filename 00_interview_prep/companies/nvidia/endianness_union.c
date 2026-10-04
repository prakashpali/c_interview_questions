/*
 * NVIDIA Interview Question (Question f):
 *
 * Question:
 * The following program fragment displays one result on machine A and a different
 * result on machine B. Explain why.
 *
 * Code Fragment:
 * --------------
 * union u_tag {
 *     u16 a;
 *     u8 b[2];
 * } u;
 * u.a = 0x1234;
 * printf("%x %x\n", u.b[0], u.b[1]);
 */

#include <stdio.h>
#include <stdint.h>

typedef uint16_t u16;
typedef uint8_t  u8;

/*
 * ==============================================================================
 * EXPLANATION: ENDIANNESS (BYTE ORDERING)
 * ==============================================================================
 *
 * Why do machine A and machine B display different results?
 *
 * The discrepancy is caused by CPU ENDIANNESS (byte order in memory).
 * In a union, all members share the exact same starting memory address.
 * `u.a` is a 16-bit integer (2 bytes: 0x12 (MSB) and 0x34 (LSB)).
 * `u.b` is an array of two 8-bit bytes occupying the same 2 bytes of memory.
 *
 * 1. On a Little-Endian Machine (e.g., x86, x86-64, ARM Cortex-A/M default):
 *    - The Least Significant Byte (LSB) is stored at the lowest memory address.
 *    - Memory layout:
 *        Address:   [Base + 0]   [Base + 1]
 *        Content:      0x34         0x12
 *                     u.b[0]       u.b[1]
 *    - Output: "34 12"
 *
 * 2. On a Big-Endian Machine (e.g., IBM PowerPC, SPARC, network byte order):
 *    - The Most Significant Byte (MSB) is stored at the lowest memory address.
 *    - Memory layout:
 *        Address:   [Base + 0]   [Base + 1]
 *        Content:      0x12         0x34
 *                     u.b[0]       u.b[1]
 *    - Output: "12 34"
 *
 * Systems / Embedded Significance:
 * - Network protocols are Big-Endian ("network byte order").
 * - Peripheral bus registers (PCIe, SPI, I2C) often define specific endianness.
 * - In C, checking endianness at runtime is frequently done using a union or
 *   by casting a multi-byte integer pointer to `uint8_t *`.
 */

union u_tag {
    u16 a;
    u8 b[2];
};

void check_host_endianness(void)
{
    union u_tag u;
    u.a = 0x1234;

    printf("Original question output on this machine:\n");
    printf("u.b[0] = 0x%x, u.b[1] = 0x%x\n\n", u.b[0], u.b[1]);

    if (u.b[0] == 0x34 && u.b[1] == 0x12) {
        printf("Detected Architecture: LITTLE-ENDIAN (LSB at lowest address)\n");
    } else if (u.b[0] == 0x12 && u.b[1] == 0x34) {
        printf("Detected Architecture: BIG-ENDIAN (MSB at lowest address)\n");
    } else {
        printf("Detected Architecture: UNKNOWN / MIXED-ENDIAN\n");
    }
}

int main(void)
{
    check_host_endianness();
    return 0;
}
