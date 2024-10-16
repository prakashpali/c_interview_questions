
// C program to add two strings, both store binary numbers

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* addBinary(char* a, char* b) {

    int len_a = strlen(a);
    int len_b = strlen(b);
    printf("a = %s, b = %s\n", a, b);
    printf("len_a = %d, len_b = %d\n", len_a, len_b);

    int len_min = len_a < len_b ? len_a : len_b;
    int len_max = len_a > len_b ? len_a : len_b;
    int ia = len_a - 1;
    int ib = len_b - 1;

    char * final_sum = (char *)malloc((len_max + 1) * sizeof(char));
    int is = (len_max);

    int carry = 0;
    int sum;
    while(ia >= 0 || ib >= 0)
    {
        sum = carry;
        if(ia >= 0)
        {
            sum += (a[ia] - '0');
            ia--;
        }
        if(ib >= 0)
        {
            sum += (b[ib] - '0');
            ib--;
        }

        carry = sum > 1 ? 1 : 0;
        sum = sum & 1;
        printf("ia = %d, ib = %d, is = %d\n", ia, ib, is);

        final_sum[is--] = (char)(sum + '0');
    }

    final_sum[0] = (char)(carry + '0');

    printf("ia = %d, ib = %d, is = %d\n", ia, ib, is);
    printf("final_sum = %s\n", final_sum);

    return final_sum;

}


int main()
{
    char *a = "11";
    char *b = "1";
    char *sum;
    printf("=====================================================\n");
    printf("a = %s, b = %s\n", a, b);
    sum = addBinary(a, b);
    printf("sum = %s\n", sum);
    free(sum);
    printf("=====================================================\n");

    return 0;
}
