
#include <stdio.h>
#include <stdlib.h>

int arr[] = {11, 22, 33, 44, 55};

int main(void)
{
    int *ptr = &arr[1];

    printf("%d\n", *ptr++); // 22
    printf("%d\n", *++ptr); // 44
    printf("%d\n", *--ptr); // 33


    /* This is not a valid assignment. ptr1 is a double pointer. &arr is pointer to an array of 5 elements. */
    // int **ptr1 = &arr;

    /* This is a valid assignment. *ptr1 is a pointer to array of 5 elements. */
    int (*ptr1)[5] = &arr;
    printf("sizeof(arr) = %lu\n", sizeof(arr));
    printf("sizeof(ptr1) = %lu\n", sizeof(ptr1));
    printf("sizeof(*ptr1) = %lu\n", sizeof(*ptr1));

    for(int i = 0; i < 5; i++)
    {
        printf("(*ptr1)[%d] = %d\n", i, (*ptr1)[i]);
    }

    int temp = 10;
    int (*ptr2)[temp] = &arr;
    printf("sizeof(arr) = %lu\n", sizeof(arr));
    printf("sizeof(ptr2) = %lu\n", sizeof(ptr2));
    printf("sizeof(*ptr2) = %lu\n", sizeof(*ptr2));

    for(int i = 0; i < temp; i++)
    {
        printf("(*ptr2)[%d] = %d\n", i, (*ptr2)[i]);
    }

}