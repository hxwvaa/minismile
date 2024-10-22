#include "minishell.h"

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int is_digit_exit_code (char **av)
{
    int n ;
    n = 0;

    while(av[1][n])
    {
        if (ft_isdigit(av[1][n]))
            ;
        else
            return (0);
        n++;
    }
    return(1);
}

void exit_av_more_than_2(char **av)
{
    if (is_digit_exit_code(av))
    {
        (printf("exit\n"), printf("shell: exit: too many arguments\n"));
        return ;
    }
    else
    {
        printf("exit\n"); 
        printf("shell: exit: %s: numeric argument required\n", av[1]);
        exit(255);
    }
}

void exit_av_is_equal_2(char **av)
{
    unsigned long long n;
    if (is_digit_exit_code(av))
    {
        n = ft_atol(av[1]);
        printf("exit\n");
        exit(ft_atol(av[1]) % 256); // doesnt work for av[1] graeater than 9223372036854775807 yet
    }
    else
        printf("exit\n"); 
        printf("shell: exit: %s: numeric argument required\n", av[1]);
        exit(255);
}

void exit_shell(char **av)
{
    int i;
    i = 0;
    while(av[i])
        i++;
    if (i == 1)
        (printf("exit\n"), exit(0));
    else if (i == 2)
        exit_av_is_equal_2(av);
    else
        exit_av_more_than_2(av);
}

void check_built_in(char **av)
{
    int i;

    i = 0;
    if (ft_strncmp(av[i], "exit", 5) == 0)
        exit_shell(av);
}

void check_args(char **av)
{
    // int i;

    // i = 0;
    check_built_in(av);

}

int main(int ac, char **av)
{
    char *line;
    (void)ac;
    int i = 0;
    // (void)env;
     (void)av;

     
    while(1)
    {
        i = 0;
        line = readline("minishell♣\n");
        if(ft_strncmp(line, "exit", 4) == 0)
        {
            free(line);
            exit(0);
        }
        if(!line)
            exit(1);
        printf("\nbefore_trim - {%s}\n", line);
        av = our_tokenize(line);
        while(av[i])
        {
            printf("%d - [%s]\n", i + 1, av[i]);
            i++;
        }
        check_args(av);
        add_history(line);
    }
    return(0);
}
