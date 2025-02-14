
/**
 * Case 1: Boot from FLASH (ROM -> FLASH(copied to RAM))
 *
 *  - Power on -> Reset Handler
 *  - Initialize stack pointers (MSP)
 *  - Initialize MPU/FPU
 *  - Initialize I2C to read eFUSE
 *  - Read eFUSE to get boot modes, FLASH modes, other boot cofigs
 *  - Initialize FLASH
 *  - Read elf headers and move code sections to right locations
 *  - Calculate HASH/SIGN for each section to
 *  - Initialize .bss section to zero
 *  - Initialize RW .data section to initial value
 *  -
 *
 */