
/*
 *
 */

int main(void)
{
    int num = 1;

    if(num == *((char *)&num)) // --> LE
    {
        printf("LE\n");
    }
    else
    {
        printf("BE\n");
    }

    return 0;

}

