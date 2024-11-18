/**
 * Design HWIO macros to read/write memory addresses.
 *
 * On complex systems, getting a valid address can be allocated statically using an array.
 * We can do HWIO operations on this memory.
 */

#include "../../utils.h"

volatile unsigned char memory[256] = {0};

#define PTR_TO_UINT(addr)                   ((unsigned long)addr)

#define HWIO_OUT(addr, val)                 (*((volatile int *)(addr)) = (val))
#define HWIO_IN(addr)                       (*((volatile int *)(addr)))
#define HWIO_OUTM(addr, mask, val)          (*((volatile int *)(addr)) = ((val) & (mask)))
#define HWIO_INM(addr, mask)                (*((volatile int *)(addr)) & (mask))
#define HWIO_INF(addr, mask, shft)          (HWIO_INM(addr, mask) >> (shft))
#define HWIO_OUTF(addr, mask, shft, val)    (HWIO_OUT(addr, ((HWIO_IN(addr) & ~(mask)) | ((val) << (shft)))))

int main()
{
    /* Using memory as a 32-bit integer pointer */
    unsigned int *ptr = (unsigned int *)&memory[0];
    unsigned int val;
    unsigned int mask;
    unsigned int shft;

    printf("=====================================================\n");

    val = 0x12345678;
    printf("Writing 0x%X to 0x%lX\n", val, PTR_TO_UINT(ptr));
    HWIO_OUT(ptr, val);
    printf("Value at 0x%lX is 0x%X\n", PTR_TO_UINT(ptr), HWIO_IN(ptr));

    val = 0x1;
    mask = 0xF0;
    shft = 0x4;
    printf("Writing 0x%X to 0x%lX\n", val, PTR_TO_UINT(ptr));
    HWIO_OUTF(ptr, mask, shft, val);
    printf("Value at 0x%lX is 0x%X\n", PTR_TO_UINT(ptr), HWIO_IN(ptr));

    printf("=====================================================\n");

    return 0;
}
