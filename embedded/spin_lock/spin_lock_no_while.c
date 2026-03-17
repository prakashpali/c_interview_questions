/**
 * @file spin_lock_no_while.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-03-16
 *
 * @copyright Copyright (c) 2026
 *
 * ### Scenario: The Spinlock
 *
 * On an Apple A-series chip, you have multiple "Performance" cores. If two cores try to write to your log_buffer at once, the data will be corrupted. We need a Spinlock.
 *
 * ### Your Task
 *
 * Define a lock variable.
 *
 * Implement void lock(volatile int *lock_var). Use the atomic intrinsic __sync_lock_test_and_set(lock_var, 1). This function should "spin" (loop) until it successfully acquires the lock.
 *
 * Implement void unlock(volatile int *lock_var).
 *
 * The Silicon Twist: Inside the lock spin-loop, what instruction should you use to save power and prevent the CPU from overheating while it waits? (Hint: Think about the PAUSE or WFE/YIELD instructions).
 *
 */

#include "../../utils.h"

#if defined(__arm__) || defined(__aarch64__)
    #define CPU_PAUSE() __asm__ __volatile__("wfe" : : : "memory")
    // Or for YIELD: #define CPU_PAUSE() __asm__ __volatile__("yield" : : : "memory")
#else
    #define CPU_PAUSE() do {} while (0) // No operation for other architectures
#endif

/**
 * Spin (loop) until the lock is successfully acquired.
 * __sync_lock_test_and_set atomically sets the lock_var to 1 and returns its old value.
 * If the old value was 0, the lock was free and is now acquired.
 * If the old value was 1, the lock was held by another thread, so we continue to spin.
 */
void lock(volatile int *lock_var) {
    while (__sync_lock_test_and_set(lock_var, 1)) {
        /*
         * Inside the spin-loop, use the power-saving instruction to hint to the processor
         * that it is in a spin-wait loop. This saves power and improves performance
         * (especially on hyper-threaded systems) by avoiding costly pipeline flushes.
         */
        CPU_PAUSE();
    }
}

/**
 * Release the lock by atomically setting the lock_var to 0.
 * The __sync_lock_release intrinsic creates a release memory barrier.
 * On ARM, an explicit SEV instruction might be used to wake up waiting cores in some scenarios,
 * although in many modern ARMv8-A implementations, a store to the lock variable
 * automatically generates an event to wake up WFE-waiting cores.
 */
void unlock(volatile int *lock_var) {
    __sync_lock_release(lock_var);
}
