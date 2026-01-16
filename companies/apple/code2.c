#include <stdio.h>

/**
 * Write a function that takes a string and returns an index of the first non-repeating character in the given string.
 * Input: abc
 * Output: 0
 * Input: fabbccdef
 * Output: 1
 * Input: abcabcabcd
 * Output: 9
 */

int find_non_rep_idx(char *str, int N)
{
  int idx = -1;
  char dup_found;
  int i;

  for (i = 0; i < N-1; i++)
  {
    if('_' == str[i])
    {
        i++;
        continue;
    }
    dup_found = 0;
    for (int j = i+1; j < N; j++)
    {
        if('_' == str[j])
        {
            j++;
        }
      if (str[i] == str[j])
      {
        dup_found = 1;
        str[j] = '_'; // Mark duplicate character
      }
    }

    if(1 == dup_found)
    {
        str[i] = '_'; // Mark duplicate character
    }

    if(0 == dup_found && i < N-1)
    {
      idx = i;
      break;
    }

  }

  // Add a logic to check the last character
  if(i == N-1 && dup_found == 0)
  {
    idx = N-1;
  }

  return idx;
}

int main(void)
{
  char str[] = "abcabcabcd";
  int N = sizeof(str)/sizeof(str[0]);

  int idx = find_non_rep_idx(str, N);

  if (-1 == idx)
    printf("Found all duplicates\n");
  else
    printf("Element at index %d is not duplicate\n", idx);
}
