#include <stdio.h>
#include <string.h>

int main()
{
    char *str = "His";
    int i;

    for (i = 0; i < strlen(str); i++)
    {
        printf("%s\n", str++);
        printf("%lu\n", strlen(str));
    }
    return 0;
}