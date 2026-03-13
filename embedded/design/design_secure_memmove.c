/**
 * @file design_secure_memmove.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-03-13
 *
 * @copyright Copyright (c) 2026
 * ### The Challenge: custom_memmove
 *
 * Scenario: You are working on the Security Firmware (Root of Trust) for a new chip. You need to implement a version of custom_memmove that is resistant to basic buffer overflow and handles overlapping memory regions (like memmove).
 *
 * Requirements:
 *
 * Implement void* custom_memmove(void* dest, const void* src, size_t n);
 *
 * Constraint: You cannot use any standard library functions.
 *
 * Efficiency: Optimize for Word-aligned transfers (copying 4 or 8 bytes at a time) rather than just byte-by-byte, but handle the "tail" bytes correctly.
 *
 * Security Twist: How would you ensure the memory is actually "cleared" from the CPU caches after a sensitive copy (like an AES key)?
 *
 */

#include "../../utils.h"
#include <stddef.h> // For size_t
#include <stdint.h> // For uintptr_t

void* custom_memmove(void* dest, const void* src, size_t n)
{
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;

    if (d == s || n == 0) return dest;

    // Overlap detection: if dest is within the range [src, src+n),
    // we must copy backwards to avoid overwriting data not yet read.
    if (d > s && d < s + n) {
        // Copy backwards
        d += n;
        s += n;
        // Tail handling: Copy bytes one by one until 8-byte aligned
        while (n > 0 && ((uintptr_t)d & 7) != 0) {
            *--d = *--s;
            n--;
        }
        // Word-aligned transfer
        size_t* d_word = (size_t*)d - 1;
        const size_t* s_word = (const size_t*)s - 1;
        while (n >= sizeof(size_t)) {
            *d_word-- = *s_word--;
            n -= sizeof(size_t);
        }
        // Remaining bytes
        d = (unsigned char*)(d_word + 1);
        s = (const unsigned char*)(s_word + 1);
        while (n > 0) {
            *--d = *--s;
            n--;
        }
    } else {
        // Forward copy (No overlap or dest < src)
        // Tail handling: Copy bytes one by one until 8-byte aligned
        while (n > 0 && ((uintptr_t)d & 7) != 0) {
            *d++ = *s++;
            n--;
        }
        // Word-aligned transfer
        size_t* d_word = (size_t*)d;
        const size_t* s_word = (const size_t*)s;
        while (n >= sizeof(size_t)) {
            *d_word++ = *s_word++;
            n -= sizeof(size_t);
        }
        // Remaining bytes
        d = (unsigned char*)d_word;
        s = (const unsigned char*)s_word;
        while (n > 0) {
            *d++ = *s++;
            n--;
        }
    }

    /* To handle AES key type sensitive data, using volatile word makes sure data
     * at actual memory is cleared and cache is also updated.
     */
    volatile unsigned char *d = (volatile unsigned char *)dest;
    while (n--) *d++ = 0;

    return dest;
}
