/**
 * @file arr_queue_circular_google.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-03-13
 *
 * @copyright Copyright (c) 2026
 *
 * ### The Challenge: Circular Buffer (FIFO)
 * Goal: Implement a thread-safe, fixed-size Circular Buffer in C.
 * Requirements:
 * Buffer Structure: Define a struct to hold the buffer, head, and tail.
 * push(): Add an element. If full, return an error (don't overwrite unless specified).
 * pop(): Remove and return an element. If empty, return an error.
 * No count variable: Distinguish between Full and Empty using only head and tail.
 *
 * ### Technical Strategy Hints
 * Before you write the code, consider these "Silicon Team" requirements:
 * Power of 2: If the buffer size is a power of 2 (e.g., 256), you can use a bitwise & (masking) instead of the modulo % operator.
 * Modulo is expensive on many embedded CPUs (often requiring a library call or many cycles).
 * Atomic Operations: In a real driver, the push might happen in an Interrupt (ISR) and the pop in the Main Thread. How do you prevent a race condition on the indices?
 * Volatile: Should the indices be marked volatile? Why?
 *
 * ### Your Task
 * Write the C implementation for:
 * The struct definition.
 * int8_t circular_buffer_push(buffer_t *cb, uint8_t data);
 * int8_t circular_buffer_pop(buffer_t *cb, uint8_t *data);
 * Bonus: Explain how you handle the "Full" condition without using a count variable.
 *
 */

#include "../../utils.h"

#define QUEUE_SIZE      (8U)
#define QUEUE_SIZE_MASK (0x7U)


typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned int    uint32_t;

typedef short           int16_t;
typedef int             int32_t;

typedef struct cir_queue_s
{
    uint8_t buf[QUEUE_SIZE];
    volatile int32_t head;
    volatile int32_t tail;
} buffer_t;

static buffer_t cb = {
    .buf = {0},
    .head = -1,
    .tail = -1,
};

static bool is_buffer_empty(buffer_t *cb)
{
    bool ret = false;
    if (cb->head >= cb->tail)
    {
        ret = true;
    }
    return ret;
}

static bool is_buffer_full(buffer_t *cb)
{
    bool ret = false;
    if (cb->tail - cb->head >= QUEUE_SIZE)
    {
        ret = true;
    }
    return ret;
}

int8_t circular_buffer_push(buffer_t *cb, uint8_t data)
{
    if (is_buffer_full(cb))
    {
        return -1;
    }

    cb->buf[(++cb->tail & QUEUE_SIZE_MASK)] = data;

    return 0;
}

int8_t circular_buffer_pop(buffer_t *cb, uint8_t *data)
{
    if (is_buffer_empty(cb))
    {
        cb->tail = -1;
        cb->head = -1;

        return -1;
    }

    *data = cb->buf[(++cb->head & QUEUE_SIZE_MASK)];

    return 0;
}

int main(void)
{
    for (int i = 0; i < QUEUE_SIZE + 1; i++)
    {
        if (circular_buffer_push(&cb, i))
        {
            printf("Buffer Full\n");
        }
        else
        {
            printf("Pushed data = %d\n", i);
        }
    }

    for (int i = 0; i < QUEUE_SIZE + 1; i++)
    {
        uint8_t data;
        if (circular_buffer_pop(&cb, &data))
        {
            printf("Buffer Empty\n");
        }
        else
        {
            printf("Popped data = %d\n", data);
        }
    }

}