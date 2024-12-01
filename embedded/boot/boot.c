/**
 * Understand boot flow.
 */



/**
 *
 *  - PBL (ROM):
 *  - Power On
 *  - Jump to Reset Vector in ROM
 *  - Initialize stack pointers
 *  - Iitialize stack
 *  - Copy RW data to RAM
 *  - Initialize .bss section to zero
 *  - Initialize .data section to initial value
 *  - Initialize I2C to read eFUSE
 *  - Read eFUSE to get boot modes, FLASH modes, other boot cofigs
 *  - Initialize FLASH and read ELF headers
 *  - Parse ELF sections and move them to right memory locations
 *  - Initialize .bss section and .data section
 *  - Jump to the SBL Reset Vector
 *
 *  - SBL (FLASH -> RAM):
 *  - Code in this part could be Secondary boot loader
 *  - Initialize stack pointers
 *  - Iitialize stack
 *  - Copy RW data to RAM
 *  - Initialize .bss section to zero
 *  - Initialize .data section to initial value
 *  - Authenticate
 *  - If authentication passes, jump to MAIN image Reset Vector
 *
 *  - MAIN (FLASH -> RAM):
 *  - Initialize stack pointers
 *  - Iitialize stack
 *  - Copy RW data to RAM
 *  - Initialize .bss section to zero
 *  - Initialize .data section to initial value
 *  - Start MAIN()
 *  - Initialize clocks, timers, some peripherals
 *  - Initialize RTOS and spawn threads
 *  - Run IDLE thread and wait for interrupt, try to enter low power
 *
 */
