

int reverse_num(int val)
{
    // 234 --> rev = 4 --> val = 23
    // 23 --> rev = 43 --> val = 2
    // 2
    int rev = 0;

    while( val > 0)
    {
        rev = rev * 10;
        rev += val%10;
        val = val/10;
    }

    return rev;
}

int main(void)
{
    int num = 234;

    int rev = reverse_num(num);

    return 0;
}