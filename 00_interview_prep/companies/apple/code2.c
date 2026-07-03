#include <stdio.h>
#include <string.h>

/**
 * Write a function that takes a string and returns an index of the first non-repeating character in the given string.
 * Input: abc
 * Output: 0
 * Input: fabbccdef
 * Output: 1
 * Input: abcabcabcd
 * Output: 9
 *
 * This can also be solved by using dynamic programming approach with an array to store frequency of each character.
 */

int find_non_rep_idx(char *str, int N)
{
  int idx = -1;
  char dup_found;
  int i,j;

  for (i = 0; i < N - 1; i++)
  {
    if(str[i] == '*')
      continue;

    dup_found = 0;
    for (j = i + 1; j < N; j++)
    {
      if(str[j] == '*')
      {
        continue;
      }
      if (str[i] == str[j])
      {
        dup_found = 1;
        str[j] = '*';
      }
    }

    if (dup_found)
    {
      str[i] = '*';
    }
    else
    {
      idx = i;
      break;
    }

    printf("%s\n", str);

  }

  if(-1 == idx && str[N-1] != '*')
  {
    idx = N-1;
  }

  return idx;
}

int main(void)
{
  char str[] = "aaaa";
  int N = strlen(str);

  int idx = find_non_rep_idx(str, N);

  printf("======================================\n");
  if (-1 == idx)
    printf("Found all duplicates\n");
  else
    printf("Element at index %d is not duplicate\n", idx);
  printf("======================================\n");

  return 0;
}
