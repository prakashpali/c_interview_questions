/*
Question:-
Given a monochrome bitmap represented as a flat array of bytes with one bit per pixel, flip it horizontally in-place.

A[] =  {1, 2, 3, 4, // reverse each bits in a byte, then reverse elements at each line
        2, 4, 5, 6,
        4, 5, 7, 7,
        1, 3, 4, 5};

*/

#include <stdio.h>
#include <stdlib.h>

char reverse_bits(char num)
{
    char res = 0;
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

void reverse_arr(char A[], int size)
{
    for (int i = 0; i < size; i++)
    {
        char tmp = A[i];
        A[i] = A[size - 1];
        A[size - 1] = tmp;

        --size;
    }
}

void flipHorizontal(char A[], int width, int height)
{
    int idx1, idx2;

    for (int j = 0; j < height; j++)
    {
        for (int i = (width * j); i < (width * (j + 1)); i++)
        {
            // reverse bits in byte
            A[i] = reverse_bits(A[i]);
        }

        reverse_arr(&A[width * j], width);
    }
}

void printArray(char A[], int width, int height)
{
    for(int i = 0; i < height*width; i++)
    {
        printf("0x%02X, ", (unsigned char)A[i]);
        if (((i + 1) % width) == 0)
        {
            printf("\n");
        }
    }
    printf("\n\n");

}

int main(void)
{
    char A[] = {1, 2, 3, 4, // reverse each bits in a byte, then reverse elements at each line
               2, 4, 5, 6,
               4, 5, 7, 7,
               1, 3, 4, 5};

    printArray(A, 4, 4);
    flipHorizontal(A, 4, 4);
    printArray(A, 4, 4);

}
