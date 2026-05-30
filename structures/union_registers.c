
/** How to read register using structures, enable raw read, byte by byte read, bit-fields.  */

#include <stdint.h>
#include "../utils.h"

/* 
 * Pro-Tip for Registers:
 * 1. Use fixed-width integers (uint32_t, uint8_t) to guarantee sizes across architectures.
 * 2. Use C11 anonymous structs to avoid typing extra struct names (e.g., reg->byte0 instead of reg->bytes.byte0).
 * 3. WARNING: Bit-field packing order (LSB first vs MSB first) and struct padding are 
 *    compiler and endianness dependent. For highly portable code, bitwise macros are safer than bit-fields.
 */
typedef union {
    uint32_t raw;
    
    // Anonymous struct for byte access (C11 feature)
    struct {
        uint8_t byte0; // LSB (on Little Endian)
        uint8_t byte1;
        uint8_t byte2;
        uint8_t byte3; // MSB (on Little Endian)
    };
    
    // Anonymous struct for bit-field access (C11 feature)
    struct {
        // Example: A typical Control Register layout
        uint32_t enable         : 1;  // Bit 0
        uint32_t mode           : 3;  // Bits 1-3
        uint32_t interrupt_mask : 4;  // Bits 4-7
        uint32_t reserved       : 24; // Bits 8-31
    };

} reg_t;

// Simulate a hardware register at a specific memory address
uint32_t hardware_reg_memory = 0x11223344;

int main(void)
{
    // Hardware registers must be accessed via volatile pointers
    volatile reg_t *reg = (volatile reg_t *)&hardware_reg_memory;

    printf("--- Raw Access ---\n");
    printf("reg->raw = 0x%08X\n\n", reg->raw);

    printf("--- Byte Access (Assumes Little Endian) ---\n");
    printf("reg->byte0 = 0x%02X\n", reg->byte0);
    printf("reg->byte1 = 0x%02X\n", reg->byte1);
    printf("reg->byte2 = 0x%02X\n", reg->byte2);
    printf("reg->byte3 = 0x%02X\n\n", reg->byte3);

    printf("--- Bit-Field Access ---\n");
    printf("reg->enable         = 0x%X\n", reg->enable);
    printf("reg->mode           = 0x%X\n", reg->mode);
    printf("reg->interrupt_mask = 0x%X\n", reg->interrupt_mask);
    printf("reg->reserved       = 0x%X\n", reg->reserved);

    return 0;
}