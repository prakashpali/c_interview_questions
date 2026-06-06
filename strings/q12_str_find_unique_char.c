
/**
 * Given a string, every character appears twice except for one. Find that single one.
 *
 * You must implement a solution with a linear runtime complexity and use only constant extra space.
 *
 * Example 1:
 *   Input: str = "ssa"
 *   Output: 1a
 *
 * Example 2:
 *   Input: str = "fotot"
 *   Output: f
 *
 * Example 3:
 *   Input: str = "o"
 *   Output: o
 */

#include "../utils.h"

char find_unique(char *str)
{
    char c = 0;

    while(*str != '\0')
    {
        c ^= *str;
        str++;
    }
    return c;
}

int main(void)
{
    char *str = "o";

    printf("Unique char = %c\n", find_unique(str));

    return 0;
}