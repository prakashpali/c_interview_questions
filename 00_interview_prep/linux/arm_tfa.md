# ARM Trusted Firmware-A (TF-A) Deep Dive

## 1. What is ARM TF-A?
ARM Trusted Firmware-A (TF-A) is the reference implementation of secure world software for ARMv7-A and ARMv8-A (and newer) architectures. It acts as the foundational layer of firmware that bootstraps the system securely and provides persistent runtime services to the rich operating system (like Linux).

Its two primary responsibilities are:
1. **Secure Boot (Chain of Trust)**: Bootstrapping the system from hardware reset up to the main OS, ensuring every piece of firmware is cryptographically authenticated before execution.
2. **Secure Monitor (EL3 Runtime)**: Acting as the gatekeeper between the Secure World (TrustZone) and the Non-Secure World (Linux), handling context switches and providing standardized power management APIs.

---

## 2. The Boot Stages (BL0, BL1, BL2, BL3x)
To establish a verifiable Chain of Trust (CoT), the TF-A boot architecture is broken down into specific Boot Loader (BL) stages. Each stage is responsible for initializing a small part of the hardware, authenticating the next stage using public key cryptography, and handing over control.

* **BL0 (Hardware / Boot ROM)**: This is immutable code permanently burned into silicon (ROM) by the SoC vendor. It is the absolute root of trust. It initializes basic clocks and the on-chip SRAM, verifies the signature of BL1, and loads BL1 into SRAM.
* **BL1 (AP Trusted ROM)**: The first actual TF-A software stage. It runs from secure SRAM at the highest privilege level (Exception Level 3 / EL3). Its main job is to configure basic CPU architecture settings, establish the initial TrustZone memory boundaries, and securely load/authenticate BL2.
* **BL2 (Trusted Boot Firmware)**: Also runs in secure SRAM. Its critical job is to initialize the main system DDR memory. Once DDR is up, BL2 loads all the subsequent "BL3" images into the massive DDR space, authenticates them, and passes control.
* **BL3 (The Payload Stages)**:
  * **BL31 (EL3 Runtime Firmware)**: This is the core resident component of TF-A. After the boot sequence is finished, BL1 and BL2 are discarded from SRAM, but BL31 stays resident in secure memory forever. It handles all `SMC` (Secure Monitor Call) exceptions.
  * **BL32 (Secure-EL1 Payload / TEE)**: This is the Trusted Execution Environment (TEE) Operating System, such as OP-TEE or Trusty. It runs in the Secure World (S-EL1) and handles secure operations like DRM, cryptography, and secure key storage.
  * **BL33 (Non-Trusted Firmware)**: This is the normal world bootloader (e.g., U-Boot, UEFI, or EDK2). It runs in the Non-Secure World (EL2 or EL1) and is entirely responsible for loading the final Rich OS (Linux).

---

## 3. How TF-A is Used by Other Firmware Elements

Once Linux is running, TF-A (specifically the resident **BL31**) sits quietly in the background at EL3, acting as a service provider for other software elements.

* **Power Management (PSCI)**: When U-Boot (BL33) or Linux wants to turn on a secondary CPU core, put a core to sleep, or reset the system, it *cannot* do this directly. The CPU power controls are locked in secure hardware. Linux issues an `SMC` instruction with a **PSCI** (Power State Coordination Interface) payload. TF-A traps the call, verifies it, and physically turns on the CPU core.
* **Communication with the Secure OS**: If a Linux user-space app needs to decrypt a DRM-protected video, it asks the Linux kernel. The kernel issues an `SMC` call. TF-A (BL31) catches the SMC, saves the Linux CPU context, restores the OP-TEE (BL32) context, and drops down to the Secure World so OP-TEE can process the decryption.
* **Erratum Workarounds**: CPU silicon bugs (errata) are often patched via TF-A at boot time by writing to undocumented, secure-only CPU registers before U-Boot or Linux ever runs.

---

## 4. How TF-A is Run on TrustZone

**TrustZone** is ARM's hardware-level security extension that partitions the CPU into two isolated worlds: Secure and Non-Secure. 

* **Exception Level 3 (EL3)** is the highest privilege level and the absolute gatekeeper between these two worlds.
* TF-A's runtime component (**BL31**) sits exclusively in EL3.
* When a normal world OS (Linux at EL1) needs to access a secure resource, it executes an `SMC` instruction.
* This instruction forces the CPU to trap directly into EL3 (TF-A). 
* TF-A saves the Non-Secure World context (GPRs, System Registers), restores the Secure World context, and executes an `ERET` (Exception Return) to drop down to the Secure OS (S-EL1). 
* From the perspective of Linux, the `SMC` instruction just looks like a function call that takes a few microseconds, but underneath, TF-A entirely swapped the CPU hardware state into the Secure World and back.

---

## 5. TrustZone Integration with Other CPUs and System Hardware

A common misconception is that TrustZone is just a CPU feature. In reality, TrustZone is a **system-wide bus architecture** (AMBA AXI/ACE).

* **The NS Bit**: Every hardware transaction on the system bus carries a Non-Secure (NS) bit. If the ARM CPU is in Secure state, it drives the bus with `NS=0`. If the CPU is in Non-Secure state (running Linux), it drives `NS=1`.
* **TZASC (TrustZone Address Space Controller)**: This hardware IP sits between the system bus and the DDR memory controller. TF-A configures the TZASC to designate certain regions of DDR as Secure-only. If Linux (`NS=1`) tries to read a Secure memory region, the TZASC blocks it in hardware and throws an exception.
* **TZPC (TrustZone Protection Controller)**: Similar to TZASC, but protects peripherals (e.g., locking a crypto engine or a secure I2C bus so only the Secure World can touch it).
* **Other Bus Masters (GPUs, DMA, Network Processors)**: Modern SoCs have multiple CPUs and bus masters (like a GPU or a DMA engine). These non-ARM masters also have an NS bit on the bus. If Linux programs a DMA engine to read secure memory, the TZASC will still block it because the DMA hardware transaction will be tagged as Non-Secure (`NS=1`). 
* **SMMU (System MMU)**: For complex co-processors (like GPUs or AI accelerators), ARM provides an SMMU. TF-A and the Secure OS configure the SMMU to act as a firewall, translating and policing memory accesses made by peripheral devices to ensure they cannot bypass TrustZone boundaries.
