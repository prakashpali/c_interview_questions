
#include "../utils.h"

static bool is_palindrome(int num)
{
    int reversed = 0;
    int original = num;

    while (num > 0)
    {
        int digit = num % 10;
        reversed = reversed * 10 + digit;
        num /= 10;
    }

    return original == reversed;
}

int main()
{
    int number = 123212;

    bool result = is_palindrome(number);

    printf("%d is %sa palindrome number.\n", number, result ? "" : "not ");

    return 0;
}