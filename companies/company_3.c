
Q1. What does the expression y = (*packet).x; do, and what is the preferred alternative syntax?

y = packet->x
y = (*packet)->x // if packet is a douple pointer



-----------------------------------------
Q2. Identify the issue in the following code snippet meant to print even numbers from 0 to 100 (including 0 and 100):

i = 1;

n = 2; // n = 0

do {

    printf("%d ", n);

    n += 2;

    if (n = 100) { // n > 100

        i = 0;

    }

} while (i);

// 2


-----------------------------
Q3. Value of Sum

uint32_t a[] = {10, 10, 10, 10, 10, 10};

uint32_t sum = 0;

for (int i = 0; i < sizeof(a); i++) { // i < (sizeof(a)/sizeof(a[0]))

    sum += a[i];

}

printf("Sum = %u\n", sum);

-----------------------------

Q4. You need to store 64 elements, where each element can have a value between 0 and 0xF (4 bits).
   Optimize the storage to use 32 bytes and implement the set and get APIs.
   B0   |  B1    |  B2    | ------------------------ | B31    |
   E0,E1  | E2,E3  | E4,E5  | ------------------------ | E62,E63|

#define LEN (32)

typedef union ux
{
    struct ex
    {
        unit8_t e1:4;
        unit8_t e2:4;
    }
    uint8_t bx;
} ux_t;

ux_t elements[LEN] = {0};


void set_element(uint32_t idx, char val)
{
    if (idx%2)
    {
        idx = idx/2;
        elements[idx].e1 = val & 0xf;
    }
    else
    {
        idx = idx/2;
        elements[idx].e2 = val & 0xf;
    }
}

char get_element(int idx)
{
    // return values with similar logic
}

