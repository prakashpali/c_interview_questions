

#include "../utils.h"

#define ALIGNMENT_8B           (8U)
#define ALIGNMENT_32B          (32U)

/**
 * 1 --> 8
 * 2 --> 8
 * 3 --> 8
 * .
 * .
 * 7 --> 8
 * 8 --> 8
 * 9 --> 16
 */
/* Generic alignment macro: ALIGN_UP(num, align) */
#define ALIGN_UP(num, align)    (((num) + ((align) - 1U)) & ~((align) - 1U))

#define ALIGN_TO_8B(num)        ALIGN_UP((num), ALIGNMENT_8B)
#define ALIGN_TO_32B(num)       ALIGN_UP((num), ALIGNMENT_32B)

int main (void)
{
    int num;
    printf("==========================\n");
    num = 7;
    printf("num = %d, aligned num = %d\n", num, ALIGN_TO_8B(num));

    num = 15;
    printf("num = %d, aligned num = %d\n", num, ALIGN_TO_8B(num));

    num = 27;
    printf("num = %d, aligned num = %d\n", num, ALIGN_TO_32B(num));
    printf("==========================\n");

    return 0;
}