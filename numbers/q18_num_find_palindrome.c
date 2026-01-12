
#include "../utils.h"

static int reverse_num(int num)
{
    int rev = 0;

    while(num > 0)
    {
        int digit = num % 10;
        rev = rev * 10 + digit;
        num /= 10;
    }

    return rev;
}

static bool is_palindrome(int num)
{
    int reversed = 0;
    int original = num;

    reversed = reverse_num(num);

    return original == reversed;
}

int main()
{
    int number = 12321;

    bool result = is_palindrome(number);

    printf("%d is %sa palindrome number.\n", number, result ? "" : "not ");

    return 0;
}