#include "../utils.h"

/*
 * Pointer Concepts: const and volatile qualifiers
 *
 * Property of data       *    Property of Pointer
 * <----------------------|----------------------->
 *
 * int                    * p1;           <-- pointer to int
 *
 * int const              * p2;           }
 * const int              * p3;           } <-- int is a constant
 *
 * int                    * const p4;     <-- Pointer is a constant
 *
 * int const              * volatile p5;  }   data is constant
 * const int              * volatile p6;  } <-- pointer may change
 *
 * int volatile           * const p7;     } <-- Data may change
 * volatile int           * const p8;     }     but the pointer is constant
 *
 * int const              * const p9;     } <-- Data and Pointer
 * const int              * const p10;    }     both are constant
 */

/*
 * Pointer Concepts: Pointer in arrays, function etc
 *
 *
 * int                    *p1[10];               <-- Array of 10 pointers to int
 * int                   (*p1)[10];              <-- Pointer to array of 10 int
 * int                   (*p1)(void);            <-- Pointer to function taking no argument and returning int
 * int                   (*p2[10])(void);        <-- Array of 10 pointers to functions taking no args, returning int
 * Example -              void(*func_arr[])(int) = { print_hi, print_bye };
 * 
 */

int a;
int b = a = 10;

int main()
{
    return 0;
}
₹