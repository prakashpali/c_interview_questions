
#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>

void print_hi(int times)
{
    int k;
    for (k = 0; k < times; k++)
        printf("Hi\n");
}

void print_bye(int times)
{
    int k;
    for (k = 0; k < times; k++)
        printf("Bye\n");
}

int main(void)
{
    void (*function_ptr)(int); /* function pointer Declaration */
    function_ptr = print_hi;   /* pointer assignment */
    function_ptr(3);           /* function call */

    /* Function pointer that takes unsigned long as parameter and returns void *. */
    void *(*get_mem)(unsigned long size) = malloc;

    /* Function pointer that takes void * as parameter and does not return anything. */
    void (*free_mem)(void *ptr) = free;

    void *ptr = get_mem(10);
    printf("ptr = 0x%lX\n", (unsigned long)ptr);
    free_mem(ptr);

    /* Array of two function pointers. */
    void(*func_arr[])(int) = { print_hi, print_bye };
    for(int i = 0; i < 2; i++)
    {
        /* Pass 5 to both functions. */
        (*func_arr[i])(5);
    }
}