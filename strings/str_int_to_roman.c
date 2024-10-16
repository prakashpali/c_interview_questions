/**
 * Program to convert Numbers to roman numerals
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This function returns value
// of a Roman symbol
/**
 * I  - 1
 * IV - 4
 * V  - 5
 * IX - 9
 * X  - 10
 * XL - 40
 * L  - 50
 * XC - 90
 * C  - 100
 * CD - 400
 * D  - 500
 * CM - 900
 * M  - 1000
 */

int n[] =    {  1,    4,   5,    9,  10,   40,  50,   90, 100,  400, 500,  900, 1000};
char *rom[] = {"I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M" };

void decimal_to_roman(unsigned int num)
{
    int idx = 12;
    while(num > 0)
    {
        int div = num / n[idx];
        while(div--)
        {
            printf("%s", rom[idx]);
        }
        num = num % n[idx];
        --idx;
    }
    printf("\n");
}

// Driver Code
int main()
{
    // Considering inputs given are valid
    unsigned int num = 3999;

    printf("=====================================================\n");
    decimal_to_roman(num);
    printf("=====================================================\n");

    return 0;
}
