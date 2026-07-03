#include <stdio.h>

/**
 * Write a function to find index of an element in a list using binary search. Give it’s time complexity.
 */

int find_idx(int *arr, int N, int element)
{
  int idx = -1;

  for (int i = 0; i < N; i++)
  {
    if (element == arr[i])
    {
      idx = i;
      break;
    }
  }

  return idx;
}

int main(void)
{

  int arr[] = {1, 2, 3, 4, 5, 6, 7};

  int N = sizeof(arr) / sizeof(arr[0]);

  int element = 6;

  int idx = find_idx(arr, N, element);

  if (-1 == idx)
    printf("Element not found\n");
  else
    printf("Element %d is at index %d\n", element, idx);

  return 0;
}
