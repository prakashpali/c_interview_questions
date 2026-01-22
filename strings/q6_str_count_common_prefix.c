
/**
 * Write a function to count longest common prefix string amongst an array of strings.
 * If there is no common prefix, return zero.
 *
 * Example 1:
 * Input: strs = ["flower","flow","flight"]
 * Output: 2
 *
 * Example 2:
 * Input: strs = ["dog","racecar","car"]
 * Output: 0
 * Explanation: There is no common prefix among the input strings.
 */

#include <stdio.h>

int count_common_chars(char* str1, char* str2)
{
    int count = 0;

    while((*str1 != '\0') && (*str2 != '\0'))
    {
        if(*str1 == *str2)
        {
            ++count;
        }
        else
        {
            break;
        }

        ++str1;
        ++str2;
    }

    return count;
}

int main()
{
    char *ar[] = {"geeksforgeeks", "geeks", "geek", "geezer"};

    printf("=====================================================\n");

    printf("Size of array %lu\n", sizeof(ar));

    int n = sizeof(ar)/sizeof(ar[0]);

    printf("%d\n", n);

    int count = 0xff;

    for(int i = 0; i < n; i++)
    {
        int new_count = count_common_chars(ar[i], ar[(i+1)%n]);
        count = count < new_count ? count : new_count;
    }

    printf("%d\n", count);

    printf("=====================================================\n");

    return 0;
}
