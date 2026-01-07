/**
 * Given a list of words followed by two words, the task is to find
 * the minimum distance between the given two words in the list of words.
 *
 * Examples:
 *
 * Input: S = { “the”, “quick”, “brown”, “fox”, “quick”}, word1 = “the”, word2 = “fox”
 * Output: 3
 * Explanation: Minimum distance between the words “the” and “fox” is 3
 *
 * Input: S = {“geeks”, “for”, “geeks”, “contribute”,  “practice”}, word1 = “geeks”, word2 = “practice”
 * Output: 2
 * Explanation: Minimum distance between the words “geeks” and “practice” is 2
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Function to return shortest distance
int shortestDistance(char *s[], int n, char *word1, char *word2)
{
    int d1 = -1, d2 = -1;
    int ans = INT_MAX;

    // Traverse the string
    for (int i = 0; i < n; i++)
    {
        if (strcmp(s[i], word1) == 0)
            d1 = i;
        if (strcmp(s[i], word2) == 0)
            d2 = i;
        if (d1 != -1 && d2 != -1)
            ans = ans < abs(d1 - d2) ? ans : abs(d1 - d2);
    }

    // Return the answer
    return ans;
}

// Driver Code
int main()
{
    char *S[] = {"the", "quick", "brown", "fox", "quick"};
    int n = 5;

    char *word1 = "the";
    char *word2 = "fox";

    // Function Call
    printf("%d", shortestDistance(S, n, word1, word2));

    return 0;
}
