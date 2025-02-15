/**
 * @file q6_arr_queue.c
 * @author Prakash Pali (prakash14pali@gmail.com)
 * @brief Q6. WAP to implement a queue using array.
 * @version 0.1
 * @date 2025-02-15
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "../utils.h"

#define QUEUE_SIZE (5)

int queue[QUEUE_SIZE] = {-1};
int head = -1;
int tail = -1;

static void enqueue(int data)
{
    if (tail >= (QUEUE_SIZE - 1))
    {
        printf("Queue full\n");
        return;
    }

    queue[++tail] = data;
    if (0 == tail)
    {
        head = 0;
    }
}

static int dequeue(void)
{
    if (head > tail)
    {
        printf("Queue empty\n");
        return -1;
    }

    return queue[head++];
}

int main(void)
{
    enqueue(2);
    enqueue(4);
    enqueue(3);
    enqueue(7);
    enqueue(6);
    enqueue(9);

    printf("=====================================================\n");
    arr_print(queue, (tail + 1));

    printf("Dequeue data = %d\n", dequeue());
    printf("Dequeue data = %d\n", dequeue());
    printf("Dequeue data = %d\n", dequeue());
    printf("Dequeue data = %d\n", dequeue());
    printf("Dequeue data = %d\n", dequeue());
    printf("Dequeue data = %d\n", dequeue());
    printf("=====================================================\n");

    return 0;
}