

/** Structure arithmetic. */

#include "../utils.h"

struct s1
{
    int a;
    int b;
} s1;

struct s2
{
    int a;
    int b;
} s2;

int main(void)
{
    struct s1 x;
    struct s2 y;
    
    x.a = 10;
    x.b = 11;

    printf("x.a = %d\n", x.a);
    printf("x.b = %d\n", x.b);

    y = x; /* This will generate a compiler error */
    printf("y.a = %d\n", y.a);
    printf("y.b = %d\n", y.b);


}
