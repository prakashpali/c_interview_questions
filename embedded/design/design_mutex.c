/** 
 * Design mutex lock and unlock
 * 
 * Key Considerations & Edge Cases Handled:
 * 1. Passing by Reference: The mutex must be passed by pointer, not by value.
 * 2. Interrupt Context: Mutexes cannot be locked/unlocked from an ISR (blocking is not allowed in ISRs).
 * 3. Ownership Tracking: Track the owner to prevent non-owners from unlocking, and to detect recursive locking/deadlocks.
 * 4. Blocking vs Yielding: If locked, the thread should be added to a wait queue and blocked, not just yield and return false.
 * 5. Concurrency: Disable interrupts (or use atomic operations/spinlocks on SMP) to protect the mutex internal state.
 * 6. Priority Inversion: Add hooks for Priority Inheritance Protocol (PIP).
 * 7. Spurious Wakeups: Use a `while` loop when checking the lock state after waking up.
 */

#include "../../utils.h"

// Conceptual Structs & Types
typedef struct wait_queue wait_queue_t;
typedef void* thread_t;

typedef struct {
    bool is_locked;
    thread_t owner;
    wait_queue_t* wait_q; // Queue of threads waiting for this mutex
} mutex_t;

// Extern functions (Conceptual RTOS API)
extern bool is_int_ctxt(void);
extern void int_lock(void);
extern void int_unlock(void);
extern thread_t get_current_thread(void);
extern void thread_block(thread_t t, wait_queue_t* q);
extern void thread_unblock(wait_queue_t* q);
extern void schedule(void);
extern void trigger_priority_inheritance(thread_t owner, thread_t waiter);
extern void reset_priority_inheritance(thread_t owner);


/**
 * @brief Acquire a mutex lock
 * @return true if successfully acquired, false on error
 */
bool mutex_lock(mutex_t *mtx)
{
    // Edge Case 1: Invalid pointer
    if (mtx == NULL) {
        return false;
    }

    // Edge Case 2: Cannot block in an interrupt context
    if (is_int_ctxt()) {
        return false;
    }

    thread_t current_thread = get_current_thread();

    // Disable interrupts to protect mutex state checking/modification
    int_lock();

    // Edge Case 3: Recursive locking (or deadlock)
    // A thread trying to lock a mutex it already owns.
    if (mtx->is_locked && mtx->owner == current_thread) {
        // Depending on RTOS design, either support recursive locks via a counter, 
        // or return an error/panic to prevent deadlock.
        int_unlock();
        return false; 
    }

    // Wait until the lock is available
    // Edge Case 4: Use 'while' instead of 'if' to handle spurious wakeups
    while (mtx->is_locked) {
        
        // Feature: Priority Inheritance to prevent Priority Inversion
        // trigger_priority_inheritance(mtx->owner, current_thread);

        // Add current thread to mutex's wait queue and block it
        thread_block(current_thread, mtx->wait_q);
        
        // Context switch happens here. 
        // Note: The scheduler usually handles re-enabling interrupts atomically during the switch.
        schedule(); 
    }

    // Acquire the lock
    mtx->is_locked = true;
    mtx->owner = current_thread;

    // Enable global interrupts
    int_unlock();
    return true;
}


/**
 * @brief Release a mutex lock
 * @return true if successfully released, false on error
 */
bool mutex_unlock(mutex_t *mtx)
{
    // Edge Case 1: Invalid pointer
    if (mtx == NULL) {
        return false;
    }

    // Edge Case 2: Cannot unlock from an interrupt context
    if (is_int_ctxt()) {
        return false;
    }

    thread_t current_thread = get_current_thread();

    int_lock();

    // Edge Case 3: The mutex must be currently locked
    if (!mtx->is_locked) {
        int_unlock();
        return false;
    }

    // Edge Case 4: Only the owner can unlock the mutex!
    if (mtx->owner != current_thread) {
        int_unlock();
        return false;
    }

    // Release the lock
    mtx->is_locked = false;
    mtx->owner = NULL;

    // Feature: Reset priority if priority inheritance was used
    // reset_priority_inheritance(current_thread);

    // If there are threads waiting, unblock the highest priority one
    if (mtx->wait_q != NULL /* Check if queue is not empty conceptually */) { 
        thread_unblock(mtx->wait_q);
        
        // Call scheduler to immediately switch to the unblocked thread 
        // if its priority is higher than the current thread.
        schedule();
    }

    int_unlock();
    return true;
}
