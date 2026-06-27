
Q1. What will get printed

printf("%d", printf("Hello")); // Hello6


Q2.

int i = 5;
printf("%d %d %d", i++, i++, i++); // 5 6 7 / 7 6 5, i=8

Q3.

char *p = "hello";
p[0] = 'H'; // "Hello"

Q4.
int a[] = {1,2,3,4};
printf("%d", *(a + 2)); // 3

Q5. Can we call main under main

int main(void)
{
    main();

    return 0;
}

