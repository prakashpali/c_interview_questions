#include <stdio.h>

void function(char **ptr)
{
    char *ptr1;
    ptr1 = (ptr += sizeof(int))[-2];
    printf("%s\n", ptr1);
}

// int main()
// {
//     char *arr[] = {"ant", "bat", "cat", "dog", "egg", "fly"};
//     function(arr);
//     return 0;
// }

// int main()
// {
//     char *ptr = "Pointer in c", arr[15];
//     arr[14] = *ptr;
//     printf("%c", arr[0]);
//     return 0;
// }

// int main()
// {
//     int *iptr;
//     int i, arr[2][2] = {10, 11, 12, 13};
//     iptr = *arr;

//     printf("0x%X \n", arr);
//     printf("0x%X \n", (arr + 1));
//     printf("0x%X \n", *(arr + 1));
//     printf("0x%X \n", arr[1]);
//     printf("\n");

//     printf("0x%X \n", &arr[0][0]);
//     printf("0x%X \n", &arr[0][1]);
//     printf("0x%X \n", &arr[1][0]);
//     printf("0x%X \n", &arr[1][1]);

//     printf("0x%X \n", iptr);
//     printf("%d ", *(iptr + 2));
//     return 0;
// }

// int main()
// {
//     char arr[10] = "Mango", *ptr;
//     ptr = (&arr[1]++);
//     printf("%s", ptr++);
//     return 0;
// }

int main()
{
    char *ptr = "void pointer";
    void *vptr;
    vptr = &ptr;
    printf("%s", *(char **)vptr);
    return 0;
}