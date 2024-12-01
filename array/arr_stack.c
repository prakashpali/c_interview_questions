/**
 * Stack using array.
 */

#include "../utils.h"

#define STACK_SIZE  (20)

int stack[] = {0,1,2,3,4,5,6,7,8,9};
int stack_top = -1;

static void push(int data)
{
    if(stack_top > STACK_SIZE)
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
    printf("Popped data = %d\n", pop());
    printf("=====================================================\n");

    return 0;
}

