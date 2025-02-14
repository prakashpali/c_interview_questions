/*
    Check endianness of the system.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum end
{
    LITTLE_END,
    BIG_END,
} endianness;

endianness get_endianness(void)
{
    unsigned short num = 0xCAFE;
    unsigned char *ptr = (unsigned char *)&num;
    unsigned short new_num = 0;

    new_num |= *ptr++;
    new_num |= *ptr << 8;

    if (new_num == num)
    {
        return LITTLE_END;
    }
    else
    {
        return BIG_END;
    }
}

int main(void)
{
    endianness end = get_endianness();

    printf("=====================================================\n");
    switch(end)
    {
        case LITTLE_END:
            printf("LITTLE_ENDIAN\n");
            break;
        case BIG_END:
            printf("BIG_ENDIAN\n");
            break;
        default:
            break;
    }
    printf("=====================================================\n");

    return 0;
}