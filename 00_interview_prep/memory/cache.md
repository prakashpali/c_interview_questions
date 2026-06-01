# CPU Cache Protocols and Policies

When dealing with CPU caches in embedded systems or high-performance computing, understanding how data moves between the CPU, the Cache, and Main Memory (RAM) is critical. This is dictated by Cache Policies and Coherence Protocols.

---

## 1. What happens during a CPU Memory Read?

When a CPU tries to read an instruction or data from a memory address, the cache controller checks if the data is already present in the cache. This results in either a **Read Hit** or a **Read Miss**.

### 1.1. Scenario A: Read Hit
If the data is already present in the cache (and the Valid Bit is `1`):
1. **Immediate Execution**: The CPU is immediately supplied with the data directly from the ultra-fast SRAM cache.
2. **No Stall**: The CPU pipeline continues executing without any stall or delay.
3. **No Bus Traffic**: Zero traffic is generated on the external memory bus, saving power and freeing up bandwidth for other cores or DMA engines.

### 1.2. Scenario B: Read Miss
If the data is *not* present in the cache, it is a **Read Miss**, and the following sequence occurs:

1. **Pipeline Stall**: The CPU pipeline halts and waits for the data to be fetched from slower lower-level memory (L2/L3 cache, or Main RAM).
2. **Block Fetch**: The cache controller doesn't just fetch the specific 4 or 8 bytes requested; it fetches an entire **Cache Line** (typically 32 or 64 bytes) to take advantage of *spatial locality*.
3. **Eviction (if full)**: If the cache set where this new line needs to be placed is already full, the controller must evict an existing cache line to make room. It uses a replacement policy (like **LRU** - Least Recently Used, or Pseudo-LRU) to select a victim line.
   * *Crucial Step*: If the victim line being evicted has its **Dirty Bit** set to `1` (meaning it was modified but hasn't been written back to RAM yet), the cache controller must pause and write that dirty line back to main memory *before* it can overwrite the slot.
4. **Update & Resume**: The new 64-byte line is placed into the cache, marked as **Valid**, and the requested bytes are supplied to the CPU so it can resume execution.

---

## 2. What happens when new data is written to the cache?

When the CPU executes a Write instruction, the behavior depends on the cache's **Write Policy** and whether the target address is currently in the cache (Write Hit) or not (Write Miss).

### 2.1. Scenario A: Write Hit (Data is already in cache)
If the data is already present, the CPU updates the cache line. But when does that update reach main RAM?
* **Write-Through**: Every time the CPU writes to the cache, the data is *simultaneously* written straight through to main memory. 
  * *Pros*: Memory is always perfectly in sync with the cache (high integrity).
  * *Cons*: Extremely slow and consumes massive memory bus bandwidth.
* **Write-Back**: The CPU only writes the new data to the cache. Main memory is *not* updated. Instead, the cache line is flagged with a **Dirty Bit** (`1`). The data is only written to main memory much later, specifically when that cache line is forced to be evicted.
  * *Pros*: Extremely fast, as a loop modifying a variable 10,000 times only generates RAM traffic once (upon eviction).
  * *Cons*: Requires complex cache coherency protocols in multi-core systems, and data is lost on sudden power failure.

### 2.2. Scenario B: Write Miss (Data is NOT in cache)
If the CPU wants to write to an address that is not currently cached, it follows an allocation policy:
* **Write Allocate (Fetch-on-Write)**: The cache controller fetches the entire 64-byte block from main memory into the cache, and *then* overwrites the specific bytes in the cache. (Usually paired with the Write-Back policy).
* **No-Write Allocate (Write Around)**: The cache controller bypasses the cache entirely and writes the new data directly to main memory. The data is *not* pulled into the cache. (Usually paired with the Write-Through policy).

---

## 3. What happens to cache data when new data is written directly to memory?

In modern SoCs, the CPU isn't the only hardware modifying RAM. A DMA engine (e.g., an Ethernet controller or PCIe SSD) or a secondary CPU core might write fresh data directly into main memory. If the primary CPU core holds an older copy of that data in its L1/L2 cache, we have a **Stale Data** problem.

To handle this, hardware uses **Cache Coherence Protocols** (the most famous being **MESI** - Modified, Exclusive, Shared, Invalid).

Here is what happens when another hardware master writes new data to RAM:
1. **Bus Snooping (Sniffing)**: The CPU's cache controller constantly monitors ("snoops") the system bus for write transactions made by other devices.
2. **Detection**: If the cache controller sees a write transaction on the bus targeting a physical memory address that it currently holds in its own cache, it immediately reacts.
3. **Invalidation**: The cache controller marks its own cached copy of that line as **Invalid** (changes the Valid bit to `0`).
4. **Forced Refresh**: The next time the CPU tries to read that memory address, the cache will see the Invalid bit, treat it exactly like a **Read Miss**, and be forced to fetch the fresh, newly written data directly from main memory.

*(Note: In software-managed coherence scenarios, such as writing a kernel driver for a DMA engine on a system without hardware snooping, the software must manually call cache invalidation instructions like `DC IVAC` on ARM before reading the buffer to ensure it doesn't read stale cached data).*
