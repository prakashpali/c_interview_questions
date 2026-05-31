# FreeRTOS Deep Dive & Architectural Concepts

## 1. Scheduling Mechanisms

FreeRTOS primarily operates as a preemptive, real-time operating system, but its exact behavior is controlled by configurations (`configUSE_PREEMPTION` and `configUSE_TIME_SLICING`).

* **Preemptive Scheduling**: The scheduler guarantees that the highest priority Ready task will always be given the CPU. If a lower priority task is running and a high priority task becomes Ready (e.g., due to an interrupt or a Mutex unlocking), the scheduler instantly preempts the low priority task and switches context.
* **Time Slicing (Round Robin)**: If multiple tasks share the *same* highest priority, the scheduler uses the periodic RTOS Tick interrupt to switch between them fairly. Each task gets a "slice" of CPU time equal to one tick period.
* **Cooperative Scheduling**: If preemption is disabled, a task runs continuously until it explicitly yields (via `taskYIELD()`) or enters the Blocked state. The OS will not forcefully preempt it, even if a higher priority task becomes ready.

## 2. Scheduling Implementation: ARM vs. RISC-V

Context switching fundamentally relies on hardware timers (for the RTOS Tick) and software interrupts (for the actual context switch).

### 2.1. ARM Cortex-M
* **SysTick Timer**: A core timer configured to fire an interrupt periodically (e.g., every 1ms). The SysTick ISR increments the RTOS tick count and evaluates if a context switch is needed (e.g., a delay expired).
* **PendSV (Pendable Service Call)**: If a context switch is required, the OS triggers the PendSV interrupt. PendSV is deliberately configured to run at the **lowest possible hardware priority**. This ensures context switching doesn't delay critical hardware interrupts. The PendSV handler executes in assembly: it saves the current task's registers to its stack, saves the stack pointer to the Task Control Block (TCB), loads the new task's stack pointer from its TCB, and restores its registers.

### 2.2. RISC-V
* **Machine Timer (`mtime` / `mtimecmp`)**: Acts identically to ARM's SysTick. It triggers a Machine Timer Interrupt (`MTIP`) to track time.
* **Software Interrupt (`MSIP` / `ecall`)**: RISC-V uses Machine Software Interrupts to handle context switching, analogous to PendSV. The ISR saves `x1` through `x31` (GPRs) and critical CSRs (like `mepc`) to the task's stack and swaps the pointers.

## 3. Tickless Idle Mode

In standard operation, the RTOS wakes up the CPU every 1ms (the Tick) just to see if a task needs to run. If the system is idle, these periodic wakeups burn enormous amounts of battery.

**Tickless Mode (`configUSE_TICKLESS_IDLE`)** solves this:
1. When the Idle Task runs, it calculates exactly how many ticks remain until the closest task needs to wake up from the Blocked state.
2. It stops the periodic SysTick timer and programs a low-power hardware timer (like an RTC) to fire *exactly* when that task needs to wake up.
3. It calls a port-specific macro (`vPortSuppressTicksAndSleep()`) which puts the CPU into a deep sleep state (e.g., `WFI` - Wait For Interrupt).
4. When the CPU finally wakes up, it calculates how much time actually passed, updates the RTOS tick count in one large leap to catch up, and resumes scheduling.

## 4. Core Primitives (Queues, Mutexes, Semaphores, Signals)

In FreeRTOS, almost all classic IPC primitives are secretly built on top of a single core data structure: **The Queue**.

* **Message Queues**: A thread-safe FIFO buffer. Data is copied *by value* into the queue memory. If the queue is full, a writing task enters the Blocked state. If empty, a reading task Blocks until data arrives.
* **Semaphores**:
  * Internally implemented as a Queue with a length of `N` but an item size of `0` bytes! 
  * It only tracks the number of items (the count), wasting no RAM on data. Taking a semaphore is "reading" a 0-byte item; Giving is "writing".
  * **Binary Semaphore**: Length = 1. Used for synchronization (e.g., an ISR unblocking a task).
  * **Counting Semaphore**: Length = N. Used for managing a finite pool of resources.
* **Mutex**: A special Binary Semaphore that includes **Priority Inheritance** (see below). Furthermore, only the specific task that takes a Mutex is allowed to give it back. Used strictly for mutual exclusion of shared resources.
* **Signals (Task Notifications)**: A direct-to-task signaling mechanism. It **does not** use Queues. Every TCB has a built-in 32-bit notification value. This is dramatically faster and uses far less RAM than Semaphores, but can only notify one specific, predetermined target task.

## 5. Thread States

A FreeRTOS task exists in exactly one of these states:
1. **Running**: The task is currently executing instructions on the CPU core. (On a single-core system, only 1 task can be here).
2. **Ready**: The task is fully prepared to run but is waiting because a higher or equal priority task is currently Running.
3. **Blocked**: The task is waiting for an event (e.g., a Queue to receive data, a Mutex to unlock, or a delay timer to expire). It consumes **0 CPU cycles** and is completely ignored by the scheduler.
4. **Suspended**: The task is explicitly paused via `vTaskSuspend()`. It will absolutely not run again, regardless of any events or timeouts, until explicitly resumed via `vTaskResume()`.

## 6. Priority Inversion

**The Problem**: 
A Low priority task (`L`) acquires a Mutex. A High priority task (`H`) tries to acquire the same Mutex and goes to the Blocked state. A Medium priority task (`M`) becomes Ready and preempts `L`. Now `M` is running indefinitely, preventing `L` from ever releasing the Mutex. As a result, `H` is effectively blocked by `M`, meaning priority has been severely inverted!

**The Solution (Priority Inheritance)**: 
When `H` blocks on a Mutex held by `L`, FreeRTOS temporarily elevates `L`'s priority to match `H`. This prevents `M` from preempting `L`. `L` finishes its critical section quickly, releases the Mutex, and its priority instantly drops back down, allowing `H` to acquire the Mutex and run.

## 7. `vTaskDelay` / `thread_sleep()`

* **What it does**: Moves the calling task from the **Running** state to the **Blocked** state for a specified number of RTOS ticks.
* **Why it's critical**: Using a `for` or `while` loop to delay (busy-waiting) keeps the task in the **Running** state. This burns 100% of CPU cycles and starves lower-priority tasks. `vTaskDelay` frees the CPU completely.
* **Use Cases**:
  * Debouncing mechanical switches/buttons.
  * Polling slow hardware where interrupts aren't available (e.g., polling an I2C temperature sensor every 500ms).
  * Note: For strict periodic execution (e.g., exactly every 10ms regardless of how long the task takes to run), `vTaskDelayUntil()` is used instead to avoid timing drift.

## 8. Symmetric Multiprocessing (SMP) Support

**Does FreeRTOS support SMP?**
Yes! Historically, FreeRTOS was strictly a single-core RTOS. Multi-core chips (like the dual-core ESP32 or Raspberry Pi RP2040) relied on custom forks of FreeRTOS maintained by the silicon vendors. However, as of **FreeRTOS V11.0.0**, SMP support has been officially merged into the mainline kernel.

### 8.1. Key SMP Concepts in FreeRTOS:
* **One Scheduler, Multiple Cores**: A single unified instance of the FreeRTOS kernel manages the ready lists and scheduling for all available cores simultaneously. 
* **Core Affinity**: You can restrict a task to run only on a specific core (or a specific set of cores) using `vTaskCoreAffinitySet()`. This is highly useful for optimizing CPU cache hits or ensuring that a high-priority real-time task on Core 0 is never preempted by a generic UI task spinning on Core 1.
* **True Concurrency**: In the **Running** state, there can now be up to *N* tasks running at the exact same physical time (where *N* is the number of cores).
* **Spinlocks for Critical Sections**: In a single-core system, FreeRTOS protects its internal data structures (like moving a task from the Ready list to the Blocked list) simply by disabling interrupts (`taskENTER_CRITICAL()`). In an SMP system, disabling interrupts on Core 0 doesn't stop Core 1 from modifying that exact same list! Therefore, the SMP kernel introduces hardware **Spinlocks** under the hood to achieve true mutual exclusion across multiple physical cores.

### 8.2. Under the Hood: How SMP is Implemented
To upgrade from a single-core RTOS to an SMP RTOS, the FreeRTOS kernel engineers made a few critical architectural additions:

1. **Inter-Processor Interrupts (IPI) / Yielding**: 
   Imagine Core 0 is running an ISR and unblocks a high-priority task. However, Core 1 is currently running a low-priority background task. Core 0 needs a way to force Core 1 to do a context switch immediately. It achieves this by firing a hardware **Inter-Processor Interrupt (IPI)** to Core 1. When Core 1 receives the IPI, it enters an ISR, runs the scheduler, and yields to the new high-priority task.
2. **Upgraded Critical Sections (`taskENTER_CRITICAL`)**: 
   The port macro for critical sections was completely rewritten. Now, when a task calls `taskENTER_CRITICAL()`, it disables its *local* core's interrupts AND attempts to acquire a global hardware spinlock. If Core 1 already holds the spinlock, Core 0 will loop ("spin") until Core 1 releases it.
3. **Task Control Block (TCB) Expansion and Location**: 
   In an SMP architecture, all cores share the same physical memory map. Therefore, the `TCB_t` structures are located in standard **shared system RAM** (allocated via the heap or statically in `.bss`), meaning any core can access any task's TCB. To support this shared access safely, the `TCB_t` structure itself was expanded. It now tracks:
   * `xCoreID`: Which specific core the task is currently executing on (crucial so the scheduler doesn't accidentally try to run the same task on two cores at once!).
   * `uxCoreAffinityMask`: A bitmask determining which cores the task is allowed to run on.

## 9. Other Critical FreeRTOS Concepts

For a comprehensive Staff-level understanding, there are a few more critical concepts that frequently come up in technical interviews:

### 9.1. Memory Management (The 5 Heaps)
FreeRTOS does not rely on the standard C library `malloc()` / `free()` by default because they are often not thread-safe and suffer from non-deterministic execution times. Instead, FreeRTOS provides 5 different custom heap implementations:
* **`heap_1`**: The simplest. Can only allocate memory; it cannot free memory. Perfect for safety-critical systems where dynamic allocation after boot is strictly forbidden.
* **`heap_2`**: Supports allocate and free. Uses a best-fit algorithm but **does not** coalesce adjacent free memory blocks. This leads to heavy fragmentation over time. (Mostly deprecated).
* **`heap_3`**: A simple thread-safe wrapper around the compiler's standard C library `malloc()` and `free()`.
* **`heap_4`**: Uses a first-fit algorithm and **coalesces** (merges) adjacent free blocks into single larger blocks to combat fragmentation. This is the most commonly used general-purpose heap today.
* **`heap_5`**: Exactly like `heap_4`, but can span memory allocations across multiple disparate physical RAM regions (e.g., combining internal on-chip SRAM and external DDR into one single logical heap).

### 9.2. Deferred Interrupt Processing (`FromISR` APIs)
In FreeRTOS, you must **never** call standard blocking APIs (like `xQueueSend()`) from inside a hardware Interrupt Service Routine (ISR).
* **Why?**: An ISR runs in the hardware exception context, not a thread context. If an ISR "Blocked" waiting for a queue, the entire CPU core would deadlock.
* **The Solution**: FreeRTOS provides special `*FromISR()` APIs (e.g., `xQueueSendFromISR()`). These functions will *never* block. If a Queue is full, they instantly return an error. 
* **`xHigherPriorityTaskWoken`**: When you push data to a Queue from an ISR, it might unblock a high-priority task. The `FromISR` API will set this boolean flag to `pdTRUE`. At the very end of your ISR, you must manually trigger a context switch (via `portYIELD_FROM_ISR()`) so the CPU immediately jumps to the newly unblocked task rather than returning to whatever low-priority task it originally interrupted.

### 9.3. Software Timers & The Timer Service Task
FreeRTOS allows you to create Software Timers that execute a callback function when they expire.
* **How they work**: They do not use individual hardware interrupts. Instead, FreeRTOS spawns a hidden system task called the **Timer Service Task** (`Tmr Svc`). 
* **The Timer Command Queue**: When you start or stop a software timer from your code, you are actually just sending a message to a hidden "Timer Command Queue". The Timer Service Task reads this queue and executes the requested callbacks.
* **Golden Rule**: Timer callbacks run in the context of the Timer Service Task. Therefore, a callback must **never** enter the Blocked state (e.g., calling `vTaskDelay` or waiting on a Mutex), because doing so would halt all other software timers in the entire system!

### 9.4. Event Groups
While a Queue transfers data, and a Semaphore signals a single event, an **Event Group** allows a task to wait in the Blocked state for a *combination* of multiple different events to occur simultaneously. It is essentially a 32-bit integer where each bit represents a distinct flag, allowing for complex multi-thread synchronization (e.g., "Stay Blocked until Bit 0 AND Bit 2 are both set by other tasks").
