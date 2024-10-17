#include <stdio.h>

int main(int ac, char **av)
{
    int i = 1;
    while(av[i])
    {
        printf("%s ", av[i]);
        i++;
    }
    printf("\n%d", i - 1);
}