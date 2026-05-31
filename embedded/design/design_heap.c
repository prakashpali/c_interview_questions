/**
 * Basic Heap Design (Malloc and Free)
 * 
 * Key Characteristics:
 * - Implements a simple first-fit memory allocator.
 * - Block splitting is implemented to avoid wasting huge chunks of memory.
 * - Coalescing (merging adjacent free blocks) is INTENTIONALLY OMITTED as per requirements.
 *
 * Behavior on Back-to-Back Malloc and Free:
 * - \b Scenario A (Same Size): If you call `ptr = my_malloc(64)` and then `my_free(ptr)` repeatedly, 
 *   the allocator will find the exact same 64-byte block during the next First-Fit search. 
 *   It will reuse it perfectly without causing any further fragmentation.
 *
 * - \b Scenario B (Increasing Sizes): If you call `my_malloc(16)`, `my_free()`, and then `my_malloc(32)`,
 *   the 16-byte block is now too small. The allocator skips it and splits the next large chunk.
 *   Because coalescing is disabled, that 16-byte block becomes a permanent "hole" unless a future 
 *   allocation requests <= 16 bytes. Over time, these varying-sized back-to-back calls 
 *   will severely fragment the heap.
 */

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define HEAP_SIZE 10240 // 10 KB Heap
#define ALIGNMENT 8

// Macro to align memory allocations to an 8-byte boundary
#define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))

/**
 * @brief Memory Block Header
 * Every allocated and free chunk of memory is preceded by this header.
 */
typedef struct BlockHeader {
    size_t size;                // Size of the usable data block (excluding this header)
    bool is_free;               // Status flag: true if block is available
    struct BlockHeader* next;   // Pointer to the next block header in the heap
} BlockHeader;

// ---------------------------------------------------------
// Global Variables for the Heap
// ---------------------------------------------------------

// The actual chunk of memory we will manage
static uint8_t heap_memory[HEAP_SIZE];

// Pointer to the start of our linked list of memory blocks
static BlockHeader* heap_head = NULL;

// ---------------------------------------------------------
// APIs
// ---------------------------------------------------------

/**
 * @brief Initialize the heap system
 */
void heap_init(void) {
    // Point the head to the start of the raw memory array
    heap_head = (BlockHeader*)heap_memory;
    
    // The initial block takes up the entire heap (minus its own header)
    heap_head->size = HEAP_SIZE - sizeof(BlockHeader);
    heap_head->is_free = true;
    heap_head->next = NULL;
}

/**
 * @brief Custom Malloc implementation (First-Fit Algorithm)
 * 
 * Coding Logic:
 * 1. Validate input size and auto-initialize the heap if it's the first call.
 * 2. Align the requested size to ensure hardware memory access boundaries are respected.
 * 3. Traverse the linked list of blocks starting from 'heap_head' (First-Fit strategy).
 * 4. When a suitable free block is found:
 *    a. If it's significantly larger than needed, split it into two blocks to minimize internal fragmentation.
 *    b. Mark the block as allocated.
 *    c. Return the pointer to the user payload area (skipping the BlockHeader).
 * 5. Return NULL if no suitable block is found.
 */
void* my_malloc(size_t size) {
    if (size == 0) {
        return NULL;
    }
    
    // Auto-initialize on first call
    if (heap_head == NULL) {
        heap_init();
    }

    // Step 2: Align the requested size to an 8-byte boundary
    size_t aligned_size = ALIGN(size);
    BlockHeader* current = heap_head;

    // Step 3: Traverse the linked list (First-Fit Search)
    while (current != NULL) {
        // Look for the first block that is both FREE and LARGE ENOUGH
        if (current->is_free && current->size >= aligned_size) {
            
            // Step 4a: Block Splitting Logic
            // We split only if the remaining space can hold a new BlockHeader + at least one aligned payload chunk.
            // This prevents creating uselessly small memory blocks (slivers).
            if (current->size >= aligned_size + sizeof(BlockHeader) + ALIGNMENT) {
                
                // Calculate the memory address where the new split block's header will reside
                BlockHeader* new_block = (BlockHeader*)((uint8_t*)current + sizeof(BlockHeader) + aligned_size);
                
                // Configure the new remaining free block
                new_block->size = current->size - aligned_size - sizeof(BlockHeader);
                new_block->is_free = true;
                new_block->next = current->next;
                
                // Update the current block to reflect its newly reduced size
                current->size = aligned_size;
                current->next = new_block;
            }
            
            // Step 4b: Mark the current block as allocated
            current->is_free = false;
            
            // Step 4c: Return a pointer to the data payload
            // (current + 1) increments the pointer by sizeof(BlockHeader), jumping exactly over the header.
            return (void*)(current + 1); 
        }
        
        // Move to the next block in the linked list
        current = current->next;
    }

    // Step 5: Out of memory (or heap is too fragmented)
    return NULL;
}

/**
 * @brief Custom Free implementation
 * 
 * Coding Logic:
 * 1. Validate the input pointer.
 * 2. Retrieve the BlockHeader by stepping backwards in memory from the payload pointer.
 * 3. Mark the block's 'is_free' flag as true.
 * Note: Intentionally ignores coalescing (leaving holes as per requirements).
 */
void my_free(void* ptr) {
    if (ptr == NULL) {
        return;
    }

    // Step 2: Calculate the address of the header
    // Casting to (BlockHeader*) and subtracting 1 moves the pointer backwards by exactly sizeof(BlockHeader) bytes.
    BlockHeader* block = (BlockHeader*)ptr - 1;
    
    // Step 3: Mark it as free so my_malloc can reuse it during the next First-Fit search.
    // Because we do not check if adjacent blocks are free (no coalescing), this creates a "hole".
    block->is_free = true;
}
