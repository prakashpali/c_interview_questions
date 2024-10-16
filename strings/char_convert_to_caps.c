
// Convert uppercase character to lowercase
#include <stdio.h>

char convert_to_small_letters(char c)
{
    char ret = c;
    if(c >= 'A' && c <= 'Z')
    {
        ret = c | ' ';
    }

    return ret;
}

char convert_to_caps_letters(char c)
{
    char ret = c;
    if(c >= 'a' && c <= 'z')
    {
        ret = c & '_';
    }

    return ret;
}

int main(void)
{
    char c = 'A';
    char ch = 'a';

    printf("=====================================================\n");
    printf("Converting %c to %c\n", c, convert_to_small_letters(c));
    printf("Converting %c to %c\n", ch, convert_to_caps_letters(ch));
    printf("=====================================================\n");

    return 0;
}
