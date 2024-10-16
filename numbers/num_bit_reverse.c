/*
Reverse bits in a byte

*/

#include <stdio.h>
#include <stdlib.h>

int reverse_bits_using_loop(unsigned int num)
{
    unsigned int res = 0;
    int bit_len = 8 * sizeof(num);

    for (int i = 0; i < bit_len; i++)
    {
        if (num & (1 << i))
        {
            res |= (1 << (bit_len - 1 - i));
        }
    }

    return res;
}

unsigned int reverse_bits_8(unsigned int x)
{
    x = (((x & 0xaa) >> 1) | ((x & 0x55) << 1));
    x = (((x & 0xcc) >> 2) | ((x & 0x33) << 2));
    x = (((x & 0xf0) >> 4) | ((x & 0x0f) << 4));
    return x;
}


unsigned int reverse_bits_16(unsigned int x)
{
    x = (((x & 0xaaaa) >> 1) | ((x & 0x5555) << 1));
    x = (((x & 0xcccc) >> 2) | ((x & 0x3333) << 2));
    x = (((x & 0xf0f0) >> 4) | ((x & 0x0f0f) << 4));
    x = (((x & 0xff00) >> 8) | ((x & 0x00ff) << 8));
    return x;
}

unsigned int reverse_bits_32(unsigned int x)
{
    x = (((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1));
    x = (((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2));
    x = (((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4));
    x = (((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8));
    x = ((x >> 16) | (x << 16));
    return x;
}

int main(void)
{
    unsigned int num = 0xC0;

    printf("=====================================================\n");
    printf("og num   : 0x%02X\n", num);
    // num = reverse_bits_32(num);
    // num = reverse_bits_16(num);
    num = reverse_bits_8(num);
    printf("rev of og: 0x%02X\n", num);
    printf("=====================================================\n");
}
