
#include "../utils.h"

static unsigned int reverse_num(unsigned int num)
{
    unsigned int rev = 0;

    while(num > 0)
    {
        int digit = num % 10;
        rev = rev * 10 + digit;
        num /= 10;
    }

    return rev;
}

static bool is_palindrome(unsigned int num)
{
    unsigned int reversed = 0;
    unsigned int original = num;

    reversed = reverse_num(num);

    return original == reversed;
}

int main()
{
    unsigned int number = 12321;

    bool result = is_palindrome(number);

    printf("%u is %sa palindrome number.\n", number, result ? "" : "not ");

    return 0;
}