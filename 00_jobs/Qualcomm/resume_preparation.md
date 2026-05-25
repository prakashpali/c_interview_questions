
# Resume Preparation

## 1. Complete root-of-trust
### 1.1. Full block diagram

### 1.2. Authentication of secure-patches

### 1.3. Authentication of SBL

### 1.4. Authentication of other sub-system using IPC

### 1.5. Keys used for authentication

Silicon real estate is expensive, and One-Time Programmable (OTP) memory like eFuses takes up physical space. Storing a full `RSA-3072` public key (384 bytes) or even an `ECDSA P-256` key (64 bytes) directly in eFuses is highly inefficient and costly for mass production.

| HSM   | ROOTID | PERSO | ECDSA | RSA  |
| :---  | :---   | :---  | :---  | :--- |
|  TBD  |  TBD   |  TBD  |  TBD  | TBD  |

### 1.6. Attestation

### 1.7. Optimization of boot time using TMC configurations

## 2. Optimizations to boot firmware

## 3. Supporting DV testing of secure-subsystem

## 4. IPC between sub-systems

## 5. Crashdump implementation

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
