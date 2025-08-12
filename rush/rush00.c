int ft_putchar(char c);

int rush(int x, int y)
{
    int i = 0;
    int j = 0;

    while(j <= y)
    {
        i = 0;
        while(i <= x)
        {
            ft_putchar('o');
            i++;
        }
        ft_putchar('\n');
        j++;
    }
    return 0;
}