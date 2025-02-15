/**
 * @file q5_arr_stack.c
 * @author Prakash Pali (prakash14pali@gmail.com)
 * @brief Q5. WAP to implement a stack using array.
 * @version 0.1
 * @date 2025-02-15
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "../utils.h"

#define STACK_SIZE  (5)

int stack[STACK_SIZE] = {-1};
int stack_top = -1;

static void push(int data)
{
    if(stack_top >= (STACK_SIZE - 1))
    {
        printf("stack overflow\n");
        return;
    }

    stack[++stack_top] = data;

}

static int pop(void)
{
    if(stack_top < 0)
    {
        printf("stack underflow\n");
        return -1;
    }

    return stack[stack_top--];
}

int main()
{
    push(2);
    push(4);
    push(5);
    push(6);
    push(7);
    push(8);


    printf("=====================================================\n");
    arr_print(stack, (stack_top+1));

    printf("Popped data = %d\n", pop());
    printf("Popped data = %d\n", pop());
    printf("Popped data = %d\n", pop());
    printf("Popped data = %d\n", pop());
    printf("Popped data = %d\n", pop());
    printf("Popped data = %d\n", pop());
    printf("=====================================================\n");

    return 0;
}

