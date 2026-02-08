
#include "../utils.h"

static void swap(int *a, int *b)
{
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) {
    int i = m-1, j = n-1, k = m+n-1;

    while(i >= 0 && j >= 0)
    {
        if (nums1[i] > nums2[j])
        {
            nums1[k--] = nums1[i--];
        }
        else // (nums1[i] <= nums2[j])
        {
            nums1[k--] = nums2[j--];
        }
    }

    while(i > 0)
    {
        nums1[k--] = nums1[i--];
    }
    while(j > 0)
    {
        nums1[k--] = nums2[j--];
    }
}

int main()
{
    int nums1[] = {1, 2, 0, 0, 0};
    int nums2[] = {};
    int m = 2;
    int n = 0;

    merge(nums1, sizeof(nums1)/sizeof(nums1[0]), m, nums2, sizeof(nums2)/sizeof(nums2[0]), n);

    printf("Merged array: ");
    arr_print(nums1, (m + n));

    return 0;
}