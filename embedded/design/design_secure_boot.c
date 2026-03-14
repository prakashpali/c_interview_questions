
/**
 * ## 4. Final Strategic Step: The System Design
 *
 * ### The Challenge: The Secure Bootloader
 *
 * Scenario: You are designing the First Stage Bootloader (FSBL) for a new Silicon chip.
 *
 * The Goal: The ROM code needs to load a 128KB firmware image from an external
 * SPI Flash into internal SRAM and execute it.
 *
 * The Constraint: The external SPI Flash is untrusted (an attacker could swap it).
 *
 * The Question: Describe the step-by-step process of Verified Boot. How do you
 * use a Public Key, a Hash (SHA-256), and a Signature (RSA/ECDSA) to ensure the
 * code you are about to run is authentic?
 */


/**
 * BootROM (FLASH -> Authenticate -> RAM)
 *
 *  - Power on -> Reset Handler
 *  - Initialize stack pointers (MSP)
 *  - Initialize MPU/FPU
 *  - Initialize I2C to read eFUSE
 *  - Read eFUSE to get boot modes, FLASH modes, other boot cofigs
 *  - Initialize FLASH
 *  - Read elf headers from FLASH and move code sections to a temporary SRAM just to make further processing easier.
 *  - Calculate HASH/SIGN for each section and store it in a different offset of RAM
 *  - Repeat this till all sections are copied
 *  - Finally calculate hash of all hashes calculated so far.
 *  - For ECDSA type signing, public key is read from OTP. Which later is used to calculate signature.
 *  - The final hash value gets signed with RSA/ECDSA. The final value can be called signature.
 *  - This signature calculated is compared to stored signature in image header/footer.
 *  - Now the image is authenticated.
 *  - After this, the image version is read and compared to allowed version value stored in OTP.
 *  - If everything is alright, then image is moved to respective physical SRAM memory.
 *  - Execution starts hereafter
 *
 */