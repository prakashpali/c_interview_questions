/**
 * Write a function to find the longest common prefix string amongst an array of strings.
 * If there is no common prefix, return an empty string "".
 *
 * Example 1:
 * Input: strs = ["flower","flow","flight"]
 * Output: "fl"
 *
 * Example 2:
 * Input: strs = ["dog","racecar","car"]
 * Output: ""
 * Explanation: There is no common prefix among the input strings.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int get_min_size(char** strs, int strsSize)
{
    unsigned int size = 200;

    for(int i = 0; i < strsSize; i++)
    {
        int new_size = strlen(strs[i]);
        if (new_size < size)
        {
            size = new_size;
        }
    }
    return size;
}

char* longestCommonPrefix(char** strs, int strsSize) {

    int min_size = get_min_size(strs, strsSize);
    char *common = "";
    char *new_common = (char *)malloc(sizeof(char)*(min_size+1));

    for(int i = 0; i < strsSize; i++)
    {
        char* str1 = strs[i];
        char* str2 = strs[(i+1)%strsSize];


        int len = 0;
        while((*str1 != '\0') && (*str2 != '\0'))
        {
            if(*str1 == *str2)
            {
                new_common[len++] = *str1;
            }
            else
            {
                break;
            }
            str1++;
            str2++;
        }

        new_common[len++] = '\0';

        if(strlen(new_common) > strlen(common))
        {
            common = new_common;
        }

    }

    return common;
}

int main()
{
    char *ar[] = {"geeksforgeeks", "geeks", "geek", "geezer"};

    printf("=====================================================\n");

    printf("Size of array %lu\n", sizeof(ar));

    int n = sizeof(ar)/sizeof(ar[0]);

    printf("%d\n", n);

    char *common = longestCommonPrefix(ar, n);

    if(0 == strlen(common))
    {
        printf("No common prefix found\n");
    }
    else
    {
        printf("Common prefix: %s\n", common);
    }

    printf("=====================================================\n");

    return 0;
}
