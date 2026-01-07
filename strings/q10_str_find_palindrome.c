
#include "../utils.h"

static bool is_palindrome(const char* str)
{
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++)
    {
        if (str[i] != str[len - 1 - i])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    const char* string = "racecard";

    bool result = is_palindrome(string);

    printf("%s is %sa palindrome string.\n", string, result ? "" : "not ");

    return 0;
}