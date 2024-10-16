/**
 * Convert binary number directly into an integer
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int b = 1011;
    int count = 0;
    int n = 0;

    while(b)
    {
        n += (b%10) * (1 << count);
        b = b/10;
        ++count;
    }

    printf("number n = %d\n",n);

    return 0;
}