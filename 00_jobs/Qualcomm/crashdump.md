# RISC-V Crashdump System Design

## 1. Overview
The objective of the Crashdump system is to capture the processor state and critical memory regions immediately following an unrecoverable system error (e.g., Kernel Panic, Hardware Exception, or Watchdog Timeout). This data allows developers to perform post-mortem analysis to identify the root cause of the failure.

## 2. Triggering Mechanisms
The crashdump sequence is initiated by:
- **Synchronous Exceptions**: Hardware traps such as Instruction Page Faults, Illegal Instructions, or Load Alignment Faults.
- **Software Panics**: Explicit calls to `panic()` when the operating system detects an inconsistent state.
- **Watchdog Timer (WDT)**: A hardware-triggered reset where the "pre-reset" interrupt is used to capture state before the final reset occurs.

## 3. Data Capture Strategy

### 3.1 Register Context (CPU State)
For every Hart (core) in the system, the following must be captured:
- **General Purpose Registers (GPRs)**: x1 (ra) through x31 (t6). Note: x0 is always zero.
- **Control and Status Registers (CSRs)**:
    - `mstatus` / `sstatus`: Processor mode, interrupt enables, and memory protection state.
    - `mepc` / `sepc`: The program counter where the fault occurred.
    - `mcause` / `scause`: The numeric code indicating the reason for the trap.
    - `mtval` / `stval`: The faulting address or instruction bits.
    - `mscratch` / `sscratch`: To help identify the context during the trap.

### 3.2 Memory Snapshots
To keep the dump size manageable while maintaining utility, the following regions are prioritized:
- **Current Stack**: The stack frame belonging to the faulting thread (at least 4KB-8KB).
- **Global Data (.data / .bss)**: Critical system state variables.
- **Log Buffers**: The circular buffer containing the last set of system logs (`dmesg` or `printk` output).
- **Peripheral State**: Optional capture of critical hardware registers (e.g., Interrupt Controller status).

## 4. Storage and Persistence

### 4.1 Storage Options
| Strategy | Description | Persistence |
| :--- | :--- | :--- |
| **Reserved RAM** | A dedicated DDR region not used by the OS. | High (survives warm reset). |
| **Flash/NVRAM** | Writing the dump to non-volatile storage. | Very High (survives power cycle). |
| **UART/Streaming** | Streaming the binary data over a serial port. | Low (requires external capture). |

### 4.2 Warm Boot Preservation
On RISC-V systems, it is common to use a "Warm Boot" strategy where the DDR is not re-initialized by the Bootloader if a crash is detected. The Crashdump header is placed at a fixed physical address with a "Magic Number" to signal the bootloader to preserve the region.

## 5. Crashdump Format
The dump should follow a structured format for compatibility:
- **Header**: Magic number, version, timestamp, and Build-ID (to match the symbol file).
- **CPU Context Section**: Array of register sets for all active Harts.
- **Memory Map Section**: A list of descriptors (Address, Length, Type) followed by raw data.

*Recommendation*: Using a format compatible with `ELF` core dumps allows standard `gdb` to load the crashdump directly against a `vmlinux` or firmware binary.

## 6. Execution Flow (The "Panic" Path)
Before the system begins saving data, the entry point differs based on the trigger mechanism:

| Metric | Synchronous Exception | Software Panic | Watchdog (WDT) |
| :--- | :--- | :--- | :--- |
| **Trigger Source** | CPU Internal (e.g., Fault) | Kernel Code (e.g., `ASSERT`) | External Timer Hardware |
| **PC Precision** | **High**: Points to faulting instr | **Medium**: Points to `panic()` call | **Low**: Points to "point of hang" |
| **CSR Validity** | Hardware sets `mcause`/`mtval` | Manual/Software-defined codes | Captured via NMI/IRQ context |
| **Entry Path** | Hardware Trap Vector | Function Call / API | High-Priority Interrupt (NMI) |



1. **Halt Secondary Harts**: Send a Non-Maskable Interrupt (NMI) or Inter-Processor Interrupt (IPI) to stop other cores and freeze their state.
2. **Switch Stack**: Move to a dedicated "Emergency Stack" to avoid corrupting or overflowing the existing stack during dump generation.
3. **Save Context**: Store GPRs and CSRs into the reserved crash memory.
4. **Checksum**: Calculate a CRC32 or SHA-256 over the captured data to ensure integrity during the next boot.
5. **System Reset**: Trigger a hardware reset to return the system to a known good state.

## 7. Analysis Tooling
- **GDB**: Used for inspecting the call stack and variable values.
- **Scripts**: Custom Python scripts to decode `mcause` and `mtval` into human-readable descriptions based on the RISC-V Privileged Architecture Spec.
- **Crash Utility**: For Linux-based systems, ensuring the dump format is compatible with the `crash` tool.

## 8. Security Considerations
- **Sensitive Data**: Crashdumps may contain keys or user data. Consider encrypting the dump at rest using a public key stored in OTP (One-Time Programmable) memory.
- **Integrity**: Ensure the crash handler code itself is stored in a read-only section (Secure Boot) to prevent an attacker from redirecting the panic flow.

## 9. Panic Flow Diagram
The following diagram details the execution path when `panic()` is called, showing the transition from error detection to system restoration.

```mermaid
flowchart TD
    Start([panic Called]) --> DisableIRQ[Disable Global Interrupts - mstatus.MIE=0]
    DisableIRQ --> HaltOthers[Halt Secondary Harts - Send IPI/NMI]
    HaltOthers --> WDT[Disable/Reconfigure Watchdog Timer]
    WDT --> StackSwap[Switch to Emergency Stack - Save original SP]
    StackSwap --> CaptureRegs[Read GPRs x1-x31 & CSRs - mstatus, mepc, mcause]
    CaptureRegs --> CaptureMem[Read Stack, Heap, & Global Data - .data/.bss]
    CaptureMem --> WriteReserved[Store Data to Reserved DDR/SRAM]
    WriteReserved --> Header[Write Header - Magic Number, Build-ID, Checksum]
    Header --> Reset[Trigger Hardware System Reset]
    Reset --> Boot[Bootloader / FSBL Entry]
    Boot --> CheckDump{Valid Magic & Checksum?}
    CheckDump -- Yes --> WarmBoot[Warm Boot: Skip DDR Init & Signal OS]
    CheckDump -- No --> ColdBoot[Cold Boot: Normal System Init]
    WarmBoot --> Main[Jump to Kernel Entry / main]
    ColdBoot --> Main
```
