
/**
 * Different cases of simple boot
 *
 * Case 1: Boot from RAM (ROM -> RAM)
 *
 * Case 2: Boot from FLASH (ROM -> FLASH(copied to RAM))
 *
 * Case 3: Boot from FLASH (ROM -> Execute from FLASH (XIP))
 *
 *          eFuse
 *            ^
 *            |
 *           I2C
 *            |
 *     |------------|
 *     |            | <====GPIOs===> Boot strap
 *     |    Boot    | <==QSPI/SPI==> FLASH
 *     |            | <==SPMI/I2C==> PMIC
 *     |------------|
 *
 */

/**
 * Case 1: Boot from RAM (ROM -> RAM)
 *
 *  - Power on -> Reset Handler
 *  - Initialize main stack pointer (MSP)
 *  - Initialize MPU/FPU
 *  - Initialize I2C to read eFUSE
 *  - Read eFUSE to get boot modes, other boot cofigs
 *  - Initialize .bss section to zero
 *  - Jump to the RAM entry address
 *  - Can copy vector table to RAM
 *
 */

/**
 * Case 2: Boot from FLASH (ROM -> FLASH(copied to RAM))
 *
 *  - Power on -> Reset Handler
 *  - Initialize main stack pointer (MSP)
 *  - Initialize MPU/FPU
 *  - Initialize I2C to read eFUSE
 *  - Read eFUSE to get boot modes, FLASH modes, other boot cofigs
 *  - Copy .text section to RAM
 *  - Copy RW data to RAM
 *  - Initialize .bss section to zero
 *  - Initialize RW .data section to initial value
 *  - Jump to the RAM entry
 *  - Can copy vector table to RAM
 *
 */