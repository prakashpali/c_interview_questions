# ARM vs. RISC-V Instruction Set Architectures (ISA)

## Table of Contents
1. [Introduction to ISAs](#1-introduction-to-isas)
2. [Comparative Analysis of ARM and RISC-V](#2-comparative-analysis-of-arm-and-risc-v)
3. [Key Register Mapping](#3-key-register-mapping)
4. [Code Pattern: For Loop Expansion](#4-code-pattern-for-loop-expansion)
5. [Discussion of Key Elements](#5-discussion-of-key-elements)
    - [5.1 The Licensing and Innovation Gap](#51-the-licensing-and-innovation-gap)
    - [5.2 Modularity vs. Feature Richness](#52-modularity-vs-feature-richness)
    - [5.3 Execution Flow: Conditional vs. Branching](#53-execution-flow-conditional-vs-branching)
    - [5.4 Memory and Endianness](#54-memory-and-endianness)
6. [Conditional Execution Examples](#6-conditional-execution-examples)
    - [6.1 ARM (AArch32)](#61-arm-aarch32)
    - [6.2 ARM (AArch64)](#62-arm-aarch64)
    - [6.3 RISC-V](#63-risc-v)
7. [Conclusion](#7-conclusion)

This document provides an overview and comparison of the ARM and RISC-V Instruction Set Architectures, highlighting their key characteristics, differences, and typical use cases.

## 1. Introduction to ISAs

An Instruction Set Architecture (ISA) is an abstract model of a computer that defines how software controls the CPU. It specifies the set of instructions a processor can execute, the data types it can handle, the registers available, the memory architecture, and the interrupt handling mechanisms.

## 2. Comparative Analysis of ARM and RISC-V

| Feature | ARM ISA | RISC-V ISA |
| :--- | :--- | :--- |
| **Licensing Model** | Proprietary; requires licensing from ARM Holdings. | Open standard; royalty-free and open to all. |
| **Design Philosophy** | Evolved RISC with a rich, complex instruction set. | Clean-slate, modular design focused on simplicity. |
| **Instruction Logic** | Supports **Conditional Execution** for most instructions. | No conditional execution; uses branch-based logic. |
| **Modularity** | Standardized tiers (Cortex-A/R/M) with fixed features. | Highly modular (Base Integer + Optional Extensions). |
| **Instruction Set** | 32-bit (ARM), 16-bit (Thumb), 64-bit (AArch64). | 32/64/128-bit Base, 16-bit Compressed (RVC). |
| **Endianness** | **Bi-endian** (supports both Little and Big). | Primarily **Little-endian** (Base ISA). |
| **Customization** | Limited to features provided by ARM licenses. | **Highly Extensible**; allows custom instructions. |
| **Ecosystem Status** | Mature; decades of established toolchains and support. | Rapidly growing; modern but still maturing. |
| **Target Markets** | Mobile, laptops, servers, automotive. | Embedded, AI accelerators, HPC, research. |

## 3. Key Register Mapping

Understanding how registers are utilized for function calls and system state is vital for low-level debugging.

| Role | ARM (A32) | RISC-V (RV32) | Description |
| :--- | :--- | :--- | :--- |
| **Zero Register** | `N/A` | `x0` (`zero`) | Hardwired zero on RISC-V; ARM uses `#0`. |
| **Return Address** | `r14` (`LR`) | `x1` (`ra`) | Stores address to return to after calls. |
| **Stack Pointer** | `r13` (`SP`) | `x2` (`sp`) | Points to the current top of the stack. |
| **Frame Pointer** | `r11` (`FP`) | `x8` (`s0`/`fp`) | Points to the start of the current stack frame. |
| **Arguments / Return**| `r0` - `r3` | `x10` - `x17` (`a0`-`a7`) | Used for passing parameters and returning values. |
| **Temporary Regs** | `r0`-`r3`, `r12` | `x5`-`x7`, `x28`-`x31` | Caller-saved registers for scratch data. |
| **Saved Regs** | `r4` - `r11` | `x9`, `x18`-`x27` | Callee-saved registers (must be preserved). |
| **Program Counter** | `r15` (`PC`) | `pc` | Directly accessible on ARM A32 as `r15`. |

## 4. Code Pattern: For Loop Expansion

A standard C loop: `for (int i = 0; i < 10; i++) { sum += i; }`

| Step | ARM (A32 / v7-A) | RISC-V (RV32) |
| :--- | :--- | :--- |
| **Initialization** | `` `mov r0, #0` `` | `` `li t0, 0` `` |
| **Limit Load** | `` `(Immediate)` `` | `` `li t1, 10` `` |
| **Loop Label** | `` `loop:` `` | `` `loop:` `` |
| **Condition** | `` `cmp r0, #10` `` | `` `bge t0, t1, done` `` |
| **Branch Exit** | `` `bge done` `` | (Combined above) |
| **Body** | `` `add r1, r1, r0` `` | `` `add a0, a0, t0` `` |
| **Increment** | `` `add r0, r0, #1` `` | `` `addi t0, t0, 1` `` |
| **Jump Back** | `` `b loop` `` | `` `j loop` `` |
| **Exit Label** | `` `done:` `` | `` `done:` `` |

*Note: ARM A32 uses a `cmp` instruction to set condition flags followed by a conditional branch (`bge`), whereas RISC-V combines the comparison and branch into a single instruction.*

### 4.1. For loop expansion in ARM
```c
for (int i = 0; i < 10; i++) {
    # mov r0, #0
    # loop:
    # cmp r0, #10
    # bge done

    sum += i;
    # add r1, r1, r0
    # add r0, r0, #1
    # b loop
    # done:
}
```

### 4.2. For loop expansion in RISC-V
```c
for (int i = 0; i < 10; i++) {
    # li t0, 0
    # li t1, 10
    # loop:
    # bge t0, t1, done

    sum += i;
    # addi a0, a0, t0
    # addi t0, t0, 1
    # j loop
    # done:
}
```

## 5. Discussion of Key Elements

### 5.1 The Licensing and Innovation Gap
ARM's proprietary nature ensures high consistency and vendor verification, making it a "safe" choice for mass-market mobile devices. In contrast, RISC-V’s open nature removes royalty barriers and enables rapid architectural innovation, which is particularly valuable for domain-specific accelerators where custom instructions can provide a competitive edge.

### 5.2 Modularity vs. Feature Richness
ARM provides a heavy, feature-rich ISA (e.g., NEON for SIMD) which is powerful but can be overkill for tiny embedded sensors. RISC-V’s modularity allows designers to pick only the necessary extensions (like `RV32IMC`), reducing the hardware gate count and minimizing power consumption for resource-constrained IoT devices.

### 5.3 Execution Flow: Conditional vs. Branching
ARM historically relies on **Conditional Execution** to avoid pipeline flushes caused by branches. RISC-V omits this to keep the instruction decoder simple and the register file ports minimal. RISC-V instead relies on advanced branch predictors in high-performance implementations to achieve similar or better efficiency without the encoding complexity.

### 5.4 Memory and Endianness
ARM’s bi-endian support provides compatibility with legacy networking gear. RISC-V’s commitment to a strictly little-endian base ISA reflects a clean-slate approach that aligns with modern operating systems like Linux and hardware architectures like x86, simplifying cross-platform software development.

## 6. Conditional Execution Examples

To illustrate the difference, consider the C code: `if (a == b) { c = d + e; }`

### 6.1 ARM (AArch32)
In ARM's 32-bit mode, almost every instruction can be conditional based on the CPSR flags. This avoids a branch instruction and potential pipeline flush.

```assembly
CMP   R0, R1       @ Compare a and b
ADDEQ R2, R3, R4   @ c = d + e (Only executed if Zero Flag is set)
```

### ARM (AArch64)
In 64-bit mode, ARM moved away from universal conditional execution to improve scale, but still provides powerful conditional select instructions.

```assembly
CMP   W0, W1       @ Compare a and b
ADD   W5, W3, W4   @ Temp = d + e
CSEL  W2, W5, W2, EQ @ c = (cond == EQ) ? W5 : W2
```

### RISC-V
RISC-V follows a "Load/Store" and "Compare-and-Branch" philosophy. It intentionally omits conditional execution of arithmetic instructions to keep the hardware simpler and the instruction encoding cleaner.

```assembly
beq  x10, x11, skip  @ If a == b, skip the jump
j    continue        @ Else, continue
skip:
add  x12, x13, x14   @ c = d + e
continue:
```
*Note: Optimizing compilers for RISC-V usually invert the logic:*
```assembly
bne  x10, x11, over  @ If a != b, branch over the addition
add  x12, x13, x14   @ c = d + e
over:
```

## 6. Conclusion

Both ARM and RISC-V are powerful RISC architectures with distinct advantages. ARM benefits from a long history and a deeply entrenched ecosystem, making it a safe and proven choice for many applications. RISC-V, with its open, modular, and extensible design, offers unprecedented flexibility and freedom, making it an attractive option for innovation, customization, and avoiding vendor lock-in, particularly in emerging areas like specialized accelerators and open hardware. The choice between them often depends on project requirements, ecosystem needs, and strategic goals.
