
#include "../utils.h"
#include "ctype.h"

static bool is_valid_char(char c)
{
    bool ret = false;

    if (c >= 'a' && c <= 'z')
    {
        ret = true;
    }

    return ret;
}

static bool is_palindrome(const char* str)
{
    int len = strlen(str);
    printf("str len = %d\n", len);
    bool ret = 1;
    // for (int i = 0; i < len/2; i++)
    // {
    //     int start = i;
    //     int end = len - 1 - i;

    //     if(!(str[start] >= 'A' && str[start] <= 'z'))
    //     {
    //         start++;
    //     }
    //     if(!(str[end] >= 'A' && str[end] <= 'z'))
    //     {
    //         end--;
    //     }

    //     printf("%d:%c, %d:%c ", start, tolower(str[start]), end, tolower(str[end]));
    //     if (tolower(str[start]) != tolower(str[end]))
    //     {
    //         ret = 0;
    //         break;
    //     }
    // }

    int start = 0, end = len-1;

    while(start <= end)
    {
        // Madam, I'm Adam
        char char_start = tolower(str[start++]);
        char char_end = tolower(str[end--]);

        while(!is_valid_char(char_start))
        {
            char_start = tolower(str[start++]);
        }

        while(!is_valid_char(char_end))
        {
            char_end = tolower(str[end--]);
        }

        printf("[%d:%c, %d:%c]\n", start, char_start, end, char_end);
        if (char_start != char_end)
        {
            ret = 0;
            break;
        }
        // start++;
        // end--;
    }

    printf("\n");
    return ret;
}

int main()
{
    const char* string = "Madam, I'm Adam";

    bool result = is_palindrome(string);

    printf("\"%s\" is %sa palindrome string.\n", string, result ? "" : "not ");

    return 0;
}