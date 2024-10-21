#include "../minishell.h"
int ft_strlen(char *s)
{
    int i = 0;

    while(s[i])
    {
        i++;
    }
    return(i);
}

void our_echo(char **arg)
{
    int flag_n;
    int i;

    i = 1;
    flag_n = 1;
    if(ft_strncmp(arg[i], "-n", 2) == 0)
    {
        flag_n = 0;
        i++;
    }
    while(arg[i])
    {
        write(1, arg[i], ft_strlen(arg[i]));
        if((arg[i + 1]))
            write(1, " ", 1);
        i++;
    }
    if(flag_n)
        write(1, "\n", 1);
}

int main(int ac, char **av)
{
    (void)ac;
    //int i;


    if(ft_strncmp(av[1], "echo", 4) == 0)
        our_echo(av + 1);
    else
        printf("\n");

}