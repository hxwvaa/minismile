#include "../minishell.h"

//need to deal with the quotes still

void our_echo(char **arg)
{
    int flag_n;
    int i;
    char *echo_arg;

    i = 1;
    flag_n = 1;
    if(!arg[i])
        write(1, " ", 1);
    else
    {
        if(ft_strncmp(arg[i], "-n", 2) == 0)
        {
            flag_n = 0;
            i++;
        }
        echo_arg = arg[i];
        if (arg[i][0] == '$')
            echo_arg = our_expand(); //NEED THE T_SHELL *DATA
        while(arg[i])
        {
            write(1, arg[i], ft_strlen(arg[i]));
            if((arg[i + 1]))
                write(1, " ", 1);
            i++;
        }
    }
    if(flag_n)
        write(1, "\n", 1);
}
