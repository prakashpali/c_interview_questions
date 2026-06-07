
# Resume Preparation

## 1. Complete root-of-trust
### 1.1. Full block diagram
Key FW components:

```
AP ROM - Authenticate and executes Patch images from QSPI
AP ROM - Authenticate and execute Application images from QSPI
SS ROM - Authenticate and execute MW images from QSPI
SS MW - Authenticate and execute networking workloads from QSPI
```

### 1.2. Authentication of secure-patches

### 1.3. Authentication of SBL

### 1.4. Authentication of other sub-system using IPC

### 1.5. Keys used for authentication

Silicon real estate is expensive, and One-Time Programmable (OTP) memory like eFuses takes up physical space. Storing a full `RSA-3072` public key (384 bytes) or even an `ECDSA P-256` key (64 bytes) directly in eFuses is highly inefficient and costly for mass production.

### 1.5.1. Signing process
This is how the signing process looks like on the Host:
- Hash of all sections is calculated, this gives say N hashes
- Has of all N hashes are calculated, this gives the final hash
- This final hash is signed using the private key, the final value is called the signature
- Raw binary, signature, public key is stored stored together in FLASH

### 1.5.2. Authentication process
This is how authentication process looks like on the Device:
- BootROM reads the signature and public key from flash memory.
- Hash of public key is calculated.
- This PK-hash is matched witht the public-key hash present in eFuse. This way PK integrity is achieved.
- Hash of all sections are calculated, this gives N hashes.
- Hash of all N hashes are calculaed to get final hash.
- Signature, final hash and public key is shared to crypto algorithm to verify the signature.
- If signature is correct, the crypto algo returns success.
- This finally validates the authenticity of bootloader.

### 1.5.3. RSA vs ECDSA

| RSA   | ECDSA |
| :---  | :---  |
| RSA relies on the difficulty of factoring large integers into their prime factors. | ECDSA relies on the difficulty of the elliptic curve discrete logarithm problem (ECDLP). |
| A 3072-bit RSA key offers roughly equivalent security to a 256-bit ECDSA key. | A 256-bit ECDSA key provides similar security to a 3072-bit RSA key. |
| RSA is computationally more expensive for equivalent security levels. | ECDSA is generally faster and requires less computational power. |
| RSA keys are longer (e.g., 3072 bits) for equivalent security. | ECDSA keys are much shorter (e.g., 256 bits) for comparable security. |

### 1.5.4. Generating Private keys (ECDSA)
Generating the private key is mathematically trivial but practically the most critical point of failure in embedded systems.
The private key, usually denoted as `d`, is simply a cryptographically secure random integer.
- **Constraint**: It must be selected such that $1 \le d \le n-1$.
- **Hardware Implementation**: In an SoC, this relies heavily on a True Random Number Generator (TRNG) utilizing physical entropy (like thermal noise in the silicon). If the random number generator is predictable, the private key can be easily compromised.

### 1.5.5. Generating Public keys (ECDSA)

The public key is not just a random string of numbers; it is a specific set of spatial coordinates $(x, y)$ that represent a point on the elliptic curve.

Public key is shared with the binary and sits in the silicon.

### 1.6. Optimization of boot time using TMC configurations


## 2. Optimizations to boot firmware

## 3. Supporting DV testing of secure-subsystem

## 4. IPC between sub-systems

## 5. Crashdump implementation
More details at [crashdump.md](crashdump.md)

## 6. Driver development

### 6.1. FreeRTOS vs Zephyr

### 6.2. MPU

### 6.3. GPIO

### 6.4. I2C

### 6.5. I3C

### 6.6. UART

### 6.7. SPI

### 6.8. QSPI

### 6.9. FLASH/PSRAM

### 6.10. GPIO interrupt

### 6.11. GPIO timestamp

### 6.12. GPIO wakeup

## 7. Feature Development

### 7.1. Coredump

### 7.2. Secure heap
