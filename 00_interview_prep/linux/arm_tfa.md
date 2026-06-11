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

## 6. ARM Exception Levels (ELs) and Privilege Mapping

To fully understand TF-A, you must understand the privilege architecture of modern ARM processors.

In older 32-bit ARM architectures (ARMv7), privilege was managed through several convoluted "Processor Modes" (User, Supervisor, Hypervisor, Secure Monitor, etc.). In modern 64-bit ARM architectures (ARMv8-A/AArch64), this was completely redesigned into a clean hierarchy of **4 Exception Levels (EL0 to EL3)**. Higher numbers dictate higher privilege.

### 6.1. Mapping ELs to Software (The Hierarchy)

*   **EL0 (Unprivileged / User Mode)**: The lowest privilege level. This is where standard user-space applications execute (e.g., a web browser, a Python script, or an Android app). Applications here cannot directly access hardware.
*   **EL1 (OS Privilege / Supervisor Mode)**: This is where the Operating System Kernel runs (e.g., the Linux Kernel or an RTOS). Code running at EL1 has full control over the MMU (Memory Management Unit), page tables, and hardware peripherals.
*   **EL2 (Hypervisor Privilege)**: This level is reserved for virtualization. A Hypervisor (like KVM or Xen) runs here to manage and isolate multiple Guest OSes running at EL1.
*   **EL3 (Secure Monitor Privilege)**: The absolute highest privilege level in the system. This is precisely where **ARM Trusted Firmware (TF-A)** executes. EL3 is the only level that has the authority to safely switch the entire CPU between the Secure World and the Normal World.

### 6.2. How Exception Levels Change in a Normal Scenario

An ARM processor cannot simply "branch" or jump from EL0 to EL1. Privilege escalation is strictly controlled by the hardware and can only happen by generating an **Exception**. When an exception is triggered, the CPU traps to a higher level; when the work is done, it executes an `ERET` (Exception Return) instruction to drop back down.

Here is how a system traverses the levels in a normal scenario:

1.  **EL0 -> EL1 (The `SVC` Call)**: An application running at EL0 wants to open a file or allocate memory. It cannot do this directly, so it executes the **`SVC` (Supervisor Call)** assembly instruction. This triggers a synchronous exception. The CPU instantly elevates to EL1 and jumps to a predefined memory address in the Linux Kernel (the exception vector table). Linux fulfills the request, and calls `ERET` to return the result to EL0.
2.  **EL1 -> EL2 (The `HVC` Call)**: A Guest OS running at EL1 wants to configure a virtualized network card. It executes the **`HVC` (Hypervisor Call)** instruction. The CPU traps up to EL2, where the Hypervisor intercepts the request, manages the hardware, and returns via `ERET`.
3.  **EL1/EL2 -> EL3 (The `SMC` Call)**: The Linux Kernel (at EL1) decides it needs to power down a CPU core (via PSCI), or it needs to request a cryptographic signature from the Secure OS. Linux executes the **`SMC` (Secure Monitor Call)** instruction. The CPU instantly traps to EL3. **TF-A (at EL3)** intercepts this call, saves the Linux context, switches the hardware state to the Secure World, and either handles the power-down request itself or passes the crypto request down to the Secure OS (like OP-TEE). Once finished, TF-A executes `ERET` to seamlessly drop back into the Non-Secure Linux kernel.

## 7. Deep Dive: EL0 to EL3 Implementation Flow (A TEE Crypto Call Example)

To understand exactly how the software and hardware interact, let's trace a real-world scenario step-by-step: A normal user-space application wants to generate a secure random number using a hardware crypto engine managed by the Secure OS (OP-TEE).

The path is: **App (EL0) -> Linux Kernel (EL1) -> TF-A (EL3) -> Secure OS (S-EL1)**

### Step 1: EL0 to EL1 (The System Call)
1. **Application (EL0)**: The C application opens the OP-TEE device node (`/dev/tee0`) and calls `ioctl()` to request the crypto operation.
2. **C Library (glibc)**: The standard library sets up the system call number in register `X8` and executes the **`SVC #0`** (Supervisor Call) assembly instruction.
3. **Hardware Trap**: The CPU immediately stops executing the application, elevates privilege to **EL1**, and jumps to the Linux Kernel's synchronous exception vector table.
4. **Linux Driver (EL1)**: Linux decodes the syscall and routes it to the OP-TEE kernel driver.

### Step 2: EL1 to EL3 (The Secure Monitor Call)
1. **SMC Calling Convention (SMCCC)**: The Linux OP-TEE driver packages the request. According to the ARM SMCCC standard, it places a specific "Function ID" in register `X0` and arguments in `X1-X7`.
2. **The SMC Instruction**: The driver executes the **`SMC #0`** (Secure Monitor Call) instruction.
3. **Hardware Trap**: The CPU immediately elevates to **EL3** and jumps into the ARM Trusted Firmware (TF-A) exception vector table.

### Step 3: Inside TF-A at EL3 (The Context Switch)
TF-A acts as the gatekeeper. It must safely pause the Non-Secure world and boot up the Secure world.
1. **Save Non-Secure State**: TF-A saves all of Linux's general-purpose registers (`X0-X30`), the EL1 stack pointer, and critical system registers into a "Non-Secure Context" memory block.
2. **Decode the SMC**: TF-A looks at register `X0`. It sees that this SMC is meant for the Secure Payload (OP-TEE), so it hands control to its internal **Secure Payload Dispatcher (SPD)** module.
3. **Flip the Hardware State**: TF-A modifies the **`SCR_EL3`** (Secure Configuration Register). Specifically, it clears the **`NS`** (Non-Secure) bit to `0`. At this exact moment, the CPU hardware transitions into the "Secure World".
4. **Restore Secure State**: TF-A loads the previously saved register state of the Secure OS (OP-TEE).
5. **Exception Return**: TF-A executes the **`ERET`** (Exception Return) instruction.

### Step 4: Down to Secure-EL1 (The Secure OS)
1. **Execution in S-EL1**: Because `SCR_EL3.NS` is `0`, the `ERET` instruction drops the CPU down into **Secure-EL1 (S-EL1)** instead of normal EL1.
2. **OP-TEE**: The Secure OS wakes up. It talks to the isolated hardware crypto engine, generates the random number, and places it into a shared memory buffer.
3. **Return to TF-A**: OP-TEE puts a success code in register `X0` and executes its own **`SMC #0`** instruction.

### Step 5: The Journey Back (EL3 -> EL1 -> EL0)
1. **TF-A (EL3)**: The CPU traps back up to TF-A. TF-A saves OP-TEE's secure context.
2. **Flip back to Non-Secure**: TF-A sets the `NS` bit in `SCR_EL3` back to `1`. The CPU is now Non-Secure again.
3. **Restore Linux**: TF-A restores Linux's EL1 context and calls **`ERET`**.
4. **Linux (EL1)**: The CPU drops back into the exact line of code in the Linux OP-TEE driver right after the original `SMC` instruction. The driver sees the success code in `X0`, finishes the `ioctl()`, and calls **`ERET`**.
5. **App (EL0)**: The CPU drops back to EL0, and the `ioctl()` function returns. The application now has its secure random number!
