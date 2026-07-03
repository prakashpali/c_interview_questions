AMD
====

struct s
{
    int a;   // 4 bytes
    char b;  // 1 bytes
    short c; // 2 bytes
    // 1 bytes - alignment
} s_s;
// total - 8 byte aligned
printf("size = %llu\n", sizeof(s_s));

struct s_s *s_a;
struct s_s *s_b;


// s_a - s_b == size

//struct s_s *ptr1 = s_a + 1


printf("size = %llu\n", (ptr1 - s_a);


Q. Memory Layout

int y; // .bss (uninitialized)
void main()
{
    static int s = 0; // .data

}

Q. Heap

char *cp = (char *)malloc(100);

memset(cp, 0, 100);
free(cp);
cp = NULL;

// Can use realloc()

Q. Bit wise operators
//  <, >, &, |, ^, ~

char a = 21; // 0x15 --> 00010101b

// reverse the number op = 10101000

// use loops to reverse the number

// use bitwise operator

a = ((a & 0xaa) >> 1) | ((a & 0x55) << 1);
a = ((a & 0xcc) >> 2) | ((a & 0x33) << 2);
a = ((a & 0xf0) >> 4) | ((a & 0x0f) << 4);

// just for 8-bit
char rev = 0;
rev |= (a & 0x1) << 7;
rev |= (a & 0x2) << 6;
rev |= (a & 4) << 4;
rev |= (a & 8) << 2;
rev |= (a & 0x2) << 0;

Q. Process & Thread

Q. malloc() vs kmalloc()

Q. Paging
Page size for 32-bit - 2^32 = 4GB



