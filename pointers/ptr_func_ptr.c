
#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>

void print_hi(int times)
{
    int k;
    for (k = 0; k < times; k++)
        printf("Hi\n");
}

int main(void)
{
    void (*function_ptr)(int); /* function pointer Declaration */
    function_ptr = print_hi;   /* pointer assignment */
    function_ptr(3);           /* function call */

    void *(*get_mem)(unsigned long size) = malloc;
    void (*free_mem)(void *ptr) = free;

    void *ptr = get_mem(10);
    printf("ptr = 0x%lX\n", (unsigned long)ptr);
    free_mem(ptr);
}