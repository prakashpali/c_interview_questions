# What is ABI?

An ABI, or Application Binary Interface, is the low-level, machine-code boundary between two program modules.

While an API (Application Programming Interface) defines how software components interact at the source code level (like function names and parameters in C/C++), an ABI defines how those interactions are translated and executed at the silicon and compiler level.

When you compile a C program, the compiler uses the ABI to determine exactly how to generate the assembly code so that different modules—even if compiled at different times or by different compilers (like GCC vs. Clang)—can safely execute together.

Here is a breakdown of what an ABI actually dictates:

## 1. Calling Conventions
This is the most critical part of an ABI for embedded and kernel engineers. It dictates exactly how functions communicate.

Argument Passing: Which CPU registers are used to pass arguments to a function? (e.g., in ARMv8, arguments go into X0-X7; in RISC-V, they use a0-a7). If there are more arguments than registers, how are they pushed onto the stack?

Return Values: Which register holds the result when the function finishes?

Register Preservation: Which registers must the called function (callee) restore to their original state before returning, and which can it overwrite freely?
- **Caller-saved (Volatile):** The calling function is responsible for saving these if it needs the values after the call. The callee can overwrite them without warning.
- **Callee-saved (Non-volatile):** The called function must save these to the stack if it intends to use them and restore them before returning.

**Caller vs. Callee:**
- **Caller:** The function that initiates a call (the "parent").
- **Callee:** The function being executed (the "child").

## 2. Data Layout and Alignment
The ABI ensures that different modules interpret memory identically.

Data Sizes: It defines the exact bit-width of standard C types (e.g., defining that an `int` is 32 bits and a `long` is 64 bits on a specific architecture).

Endianness: It dictates whether the architecture uses Big-Endian or Little-Endian memory storage.

Padding and Alignment: It specifies how structures are padded in memory to align with the CPU's memory fetch boundaries, which is critical for preventing unaligned memory access faults.

## 3. System Call (Syscall) Interface
When a user-space application needs the Linux Kernel to do something (like read a file or allocate memory), it cannot just call a kernel function. The ABI defines the exact mechanism for this context switch.

It dictates the specific assembly instruction used to trap into the kernel (e.g., `SVC` in ARM, `ecall` in RISC-V).

It defines which register holds the "Syscall Number" so the kernel knows what service is being requested.

**Examples:**
- **ARM (AArch64):** The syscall number is placed in `x8`, and arguments in `x0-x5`.
- **RISC-V:** The syscall number is placed in `a7`, and arguments in `a0-a5`.
- **x86_64:** The syscall number is placed in `rax`.

**Common Syscall Examples (RISC-V):**
- `read()`: Syscall #63 (a7=63, a0=fd, a1=buf, a2=count)
- `write()`: Syscall #64 (a7=64, a0=fd, a1=buf, a2=count)
- `exit()`: Syscall #93 (a7=93, a0=status)


## 4. Executable Format and Linking
The ABI dictates the structure of the compiled binaries (usually the ELF format in Linux/RTOS). It defines how the dynamic linker loads the program into memory, where the `.text` (code), `.data`, and `.bss` sections are placed, and how shared libraries (.so files) are resolved at runtime.

Why this matters for Architecture and Virtualization
In the context of hypervisors, kernel development, and architectures like RISC-V, you are constantly interacting directly with the ABI:

Debugging Kernel Panics: When you use tools like kgdb or crash to analyze a memory dump, you are manually decoding the ABI. You must know which registers held the arguments and how the stack frames are linked to reconstruct the call trace.

Context Switching: When writing an RTOS scheduler or a hypervisor (like KVM), your assembly code must manually save and restore the exact CPU registers dictated by the ABI to ensure the suspended task can resume flawlessly.

RISC-V SBI: In RISC-V specifically, there is an additional layer called the `SBI` (Supervisor Binary Interface). Just as the standard `ABI` sits between user-space and the kernel, the SBI defines how the Linux Kernel communicates with the hypervisor or the highest-privileged machine mode (M-mode) firmware, which is essential for Confidential Compute and TEEs.