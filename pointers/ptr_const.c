/**
 * Const pointer and pointer to const and
 *
 */


#include "../utils.h"

int main()
{
    const int a = 5;
    int b = 4;

    /* 1. This is a non-const pointer, that can hold non-const integer. */
    int *ptr1;

    /* 2. This is a non-const pointer, that can hold const integer. */
    const int *ptr2;    // This is same as int const *ptr2

    /* 3. This is a const pointer, that can hold non-const integer.
          Const pointer must be initialized otherwise it may contain invalid pointer which can never be initialized. */
    int * const ptr3 = &b;

    /* 4. This is a const pointer, that can hold const integer. */
    const int * const ptr4 = &b;

    // ptr1 = &a;   /* This will generate warning. ptr1 cannot hold const integer but a is a const integer. */
    ptr1 = &b;      /* This will NOT. */

    ptr2 = &a;      /* This will NOT. ptr2 can hold const integer. */
    ptr2 = &b;      /* This will NOT. Value at ptr2 becomes const integer. See below instruction. */
    // (*ptr2)++;   /* Value of b can be modified but value of *ptr2 can not be modified. */

    // ptr3 = &b;   /* This will generate warning. ptr3 is a const pointer. */
    (*ptr3) = a;    /* This will NOT. Pointer is constant, but value can change. Notice that this will also change the value of b as ptr3 holds address of b. */

    // ptr4 = &b;   /* This will generate warning. ptr3 is a const pointer. */
    // (*ptr4) = b; /* This will generate warning. ptr3 can hold const data. */

    printf("Value of ptr1 = %d\n", *ptr1);
    printf("Value of ptr2 = %d\n", *ptr2);
    printf("Value of ptr3 = %d\n", *ptr3);
    printf("Value of ptr4 = %d\n", *ptr4);

    return 0;
}