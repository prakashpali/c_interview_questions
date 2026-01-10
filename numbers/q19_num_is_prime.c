/**
 * @file q19_num_is_prime.c
 * @author Prakash Pali (prakash14pali@gmail.com)
 * @brief Write a Program to check whether a number is prime or not
 * @version 0.1
 * @date 2026-01-10
 *
 * @copyright Copyright (c) 2026
 *
 */
#include "../utils.h"

int main(void)
{
    int num = 1;

    int is_prime = 1; // Assume number is prime

    /* Every number is divisible by 1. If a number num has a divisor greater than num/2,
     * it must also have a corresponding divisor less than num/2. It can be further optimized
     * by by using i * i <= num instead.
     */
    for (int i = 2; i <= num/2; i++)
    {
        if ((num % i) == 0)
        {
            is_prime = 0; // Number is not prime
            break;
        }
    }

    printf("%d is %s prime number.\n", num, is_prime ? "a" : "not a");

    return 0;
}