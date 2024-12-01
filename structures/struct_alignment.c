/**
 * Alignment test.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char c; // 1 (4)
    int a;  // 4
    int b;  // 4
} node1;    // -> size = 12

typedef struct
{
    char c;     // 1
    short s;    // 2 (aligned to make c & s take 4 bytes)
    int a;      // 4
    int b;      // 4
} node2;        // -> size = 12

typedef struct
{
    int a;  // 4
    int b;  // 4
    char c; // 1
} node3;    //-> size = 12

typedef struct __attribute__((packed))
{
    char c;  // 1
    int a;   // 4
    int b;   // 4
} node4;     //-> size = 9 because of packed attribute

typedef struct
{
    char c[9];
} node5; //-> size = 9

typedef struct
{
    short a;  // 2
    char c;   // 1
    int b[0]; // 0
} node6;      //-> size = 4

node1 n1;
node2 n2;
node3 n3;
node4 n4;
node5 n5;
node6 n6;

int main()
{
    printf("=====================================================\n");
    printf("Size of n1=%lu\n", sizeof(n1));
    printf("Size of n2=%lu\n", sizeof(n2));
    printf("Size of n3=%lu\n", sizeof(n3));
    printf("Size of n4=%lu\n", sizeof(n4));
    printf("Size of n5=%lu\n", sizeof(n5));
    printf("Size of n6=%lu\n", sizeof(n6));
    printf("=====================================================\n");

    return 0;
}

