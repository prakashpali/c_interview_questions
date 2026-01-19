#include <stdio.h>
#include <string.h>

int main()
{
    char *str = "His";
    int i;

    printf("String length: %lu\n", strlen(str));

    /* This loop keeps incrememting str, strlen(str) will keep reducing. This loop will exit early. */
    for (i = 0; i < strlen(str); i++)
    {
        printf("Value of i: %d\n", i);
        printf("%s\n", str++);
        printf("%lu\n", strlen(str));
    }
    return 0;
}