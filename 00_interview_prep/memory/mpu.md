# ARM Memory Protection Unit (MPU) Deep Dive

## 1. What is an MPU?
The Memory Protection Unit (MPU) is a hardware component found primarily in ARM Cortex-M (Microcontrollers) and Cortex-R (Real-time) processors. 

Unlike an MMU (Memory Management Unit) found in high-end Cortex-A processors, the **MPU does not translate virtual addresses to physical addresses**. It operates strictly on physical memory addresses. Its primary purpose is to partition the memory map into predefined "Regions" and enforce access permissions and cache policies on those regions.

---

## 2. How the Hardware Works
When the CPU attempts to fetch an instruction or read/write data, the physical memory address is immediately sent to the MPU *before* it hits the system bus matrix.

1. **Region Matching**: The MPU compares the requested address against a set of programmed hardware registers defining active "Regions".
2. **Attribute Checking**: If the address falls within a configured region, the MPU checks the Access Permissions (e.g., "Is the CPU currently in Unprivileged mode? Is this region marked Read-Only?").
3. **Fault Generation**: 
   * If there is a permission violation, the MPU immediately blocks the bus transaction and fires a synchronous hardware exception called a **MemManage Fault**.
   * If the address doesn't match *any* active region, it also fires a MemManage Fault (unless the default background map `PRIVDEFENA` is enabled).
4. **Execution**: If permissions are valid, the transaction proceeds to the bus with the specific memory attributes (Cacheable, Bufferable) defined by that region.

---

## 3. MPU Region Configurations (ARMv7-M)

Configuring the MPU involves programming specific memory-mapped registers. You select a region using the `MPU_RNR` (Region Number Register) and then configure its base address, size, and attributes.

### A. Size and Alignment Constraints
In the classic ARMv7-M architecture (e.g., Cortex-M3, M4, M7), configuring regions is notoriously rigid and difficult:
* **Size limitation**: A region's size must be a perfect power of 2, ranging from 32 Bytes up to 4 GB (e.g., 32B, 64B, 128B... 1MB, 2MB).
* **Alignment limitation**: The Base Address of the region *must* be aligned to a multiple of its size. (e.g., A 64 KB region can only start at a physical memory address that is perfectly divisible by 64 KB).

### B. Access Permissions (AP & XN)
Each region has an `AP` (Access Permission) bitfield determining read/write access based on the CPU's current privilege level (Privileged mode vs. Unprivileged/Thread mode).
* Typical AP states: 
  * `No Access` (often placed at Address `0x0` to catch NULL pointer dereferences).
  * `Privileged RW, Unprivileged None` (Kernel memory / RTOS data).
  * `Privileged RW, Unprivileged RO` (Configuration constants).
  * `Privileged RW, Unprivileged RW` (Shared memory).
* **XN (Execute Never)**: A single critical bit that, if set, prevents the CPU from fetching instructions from this region. This is crucial for preventing buffer overflow attacks (e.g., marking the RAM stack as `XN` so injected malicious code cannot be executed).

### C. Memory Attributes (TEX, C, B, S)
The MPU tells the L1 Cache and Bus Matrix *how* to handle the memory via these bits:
* **C (Cacheable)** and **B (Bufferable)**.
* **TEX (Type Extension)**.
* **S (Shareable)**.

Depending on the combination of these bits, memory is classified as:
1. **Strongly Ordered**: All accesses are strictly sequential; caches and write buffers are completely bypassed (used for critical memory-mapped peripheral registers).
2. **Device**: Similar to strongly ordered but allows slight write-buffer optimizations.
3. **Normal Memory**: Allows full L1/L2 caching, speculative fetching, and out-of-order execution (used for Flash/RAM).

### D. Sub-Region Disable (SRD)
Because of the strict "power of 2" size rule, the MPU provides an 8-bit `SRD` field. It logically divides the region into 8 exactly equal sub-regions. Setting a bit to `1` disables that specific 1/8th of the region. This is a crude hardware workaround to create regions of sizes that aren't perfect powers of 2 (e.g., creating a 28 KB region by creating a 32 KB region and disabling the final 4 KB sub-region).

---

## 4. Key Limitations of the MPU (ARMv7-M)

1. **Very Limited Number of Regions**: A typical Cortex-M chip only has 8 (sometimes 16) hardware regions available. When running an RTOS like FreeRTOS, the OS must dynamically reprogram the MPU registers on *every single context switch* to sandbox the incoming thread's specific memory.
2. **Massive Fragmentation via Alignment Rules**: The power-of-2 size and alignment constraints often force firmware developers to pad structures and waste massive amounts of expensive SRAM just to satisfy the MPU hardware boundary requirements. 
3. **No Address Translation**: Because it lacks an MMU, you cannot map a fragmented physical memory space into a contiguous virtual memory space. You cannot implement demand paging or swap space to disk.
4. **Overlapping Regions**: Regions are allowed to overlap. The region with the *highest* Region Number dictates the permissions. This can lead to incredibly complex and hard-to-debug configuration bugs.

---

## 5. Modern Improvements: ARMv8-M (Cortex-M23/M33)
To address massive developer complaints regarding the rigid constraints of ARMv7-M, ARM completely redesigned the MPU for the ARMv8-M architecture:

* **No more Power-of-2 constraints**: The biggest change! Regions are now defined simply by a **Base Address** and a **Limit Address**.
* **32-byte granularity**: You can define a region starting and ending at any multiple of 32 bytes, entirely eliminating the memory fragmentation/padding issues.
* **MAIR Registers**: The complex `TEX/C/B` attributes were moved to separate MAIR (Memory Attribute Indirection Registers) to standardize and simplify cache policy programming.
