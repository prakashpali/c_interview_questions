// C program to find largest word in Dictionary
// by deleting some characters of given string

#include <stdio.h>
#include <string.h>

// Returns 1 if str1[] is a subsequence of str2[].
// m is length of str1 and n is length of str2
int isSubSequence(char str1[], char str2[])
{
    int m = strlen(str1), n = strlen(str2);

    int j = 0; // For index of str1 (or subsequence)

    // Traverse str2 and str1, and compare current
    // character of str2 with first unmatched char
    // of str1, if matched then move ahead in str1
    for (int i = 0; i < n && j < m; i++)
        if (str1[j] == str2[i])
            j++;

    // If all characters of str1 were found in str2
    return (j == m);
}

// Returns the longest string in dictionary which is a
// subsequence of str.
char *findLongestString(char dict[][10], int size,
                        char str[])
{
    char *result = "";
    int length = 0;

    // Traverse through all words of dictionary
    for (int i = 0; i < size; i++)
    {
        char *word = dict[i];
        // If current word is subsequence of str and is
        // largest such word so far.
        if (length < strlen(word) && isSubSequence(word, str))
        {
            result = word;
            length = strlen(word);
        }
    }

    // Return longest string
    return result;
}

// Driver program to test above function
int main()
{
    char dict[][10] = {"ale", "apple", "monkey", "plea"};
    char str[] = "abpcplea";
    char *longestString = findLongestString(
        dict, sizeof(dict) / sizeof(dict[0]), str);
    printf("%s\n", longestString);
    return 0;
}
