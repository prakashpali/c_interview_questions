
/**
 * Given a string, the task is to reverse the order of the words in the given string.
 *
 * Input: s = “geeks quiz practice code”
 * Output: s = “code practice quiz geeks”
 *
 * Input: s = “i love programming very much”
 * Output: s = “much very programming love i”
 */

// C program to reverse a string
#include <stdio.h>

char s[] = "i like this program very much";

void reverse(char* begin, char* end)
{
    char temp[1];

    while(begin < end)
    {
        *temp = *begin;
        *begin = *end;
        *end = *temp;
        ++begin;
        --end;
    }
}


// Driver Code
int main()
{
    // reverse each word - "i ekil siht margorp yrev hcum"
    // reverse entire string - "much very program this like i"
    printf("=====================================================\n");
    printf("%s\n", s);

    // Driver code
    int str_size = sizeof(s)/sizeof(s[0]);

    char* word_s = s;
    char* word_e;

    for (int i = 0; i < str_size; ++i)
    {
        if (s[i] == ' ')
        {
            word_e = &s[i-1];
            reverse(word_s, word_e);
            word_s = &s[i+1];
        }
        if (s[i] == '\0')
        {
            word_e = &s[i-1];
            reverse(word_s, word_e);
            reverse(s, word_e);
        }
    }

    printf("%s\n", s);
    printf("=====================================================\n");

    return 0;
}
