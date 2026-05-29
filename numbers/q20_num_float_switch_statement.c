#include "../utils.h"
 
int main()
{
    float val = 2;
 
    switch (val) /* Switch case only takes a value of integer types */
    {
        case 1.0f: /* Using f here is invalid */
            printf("Value is 1\n");
            break;
 
        case 2.0f:
            printf("Value is 2\n");
            break;
 
        case 3.0f:
            printf("Value is 3\n");
            break;
 
        default:
            printf("Unknown value\n");
            break;
    }
 
    return 0;
}