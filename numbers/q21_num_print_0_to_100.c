

/* Print 0 to 100 without using loop or recursion. */

#include "../utils.h"

#define P1(n) printf("%d\n", n);
#define P10(n)  P1(n)  P1(n+1) P1(n+2) P1(n+3) P1(n+4) P1(n+5) P1(n+6) P1(n+7) P1(n+8) P1(n+9)
#define P100(n) P10(n) P10(n+10) P10(n+20) P10(n+30) P10(n+40) P10(n+50) P10(n+60) P10(n+70) P10(n+80) P10(n+90)

int main() {
    P100(0); // Expands into 100 sequential printf statements from 0 to 99
    printf("100\n"); // Print the final 100 manually
    return 0;
}