#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

//EXIT BASICALLY DONE EXCEPT FOR THE PART WHERE I NEED TO SET THE "EXIT STATUS" IN THE STRUCT TO 1 WHEN THERE ARE MULTIPLE ARGS AND 1ST ARG IS NUMBER
//AND ALSO NEED TO PUT THIS IN THE BUILTINS FORLDER

int is_digit_exit_code (char **av)
{
    int n ;
    n = 0;

    if (av[1][n] == '-' || av[1][n] == '+')
        n++;
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

bool is_num_very_small(char *str)
{
    size_t i = 0;
    long long nb = 0;

	i = 0;
	nb = 0;
	if (ft_atol(str) == LONG_MIN)
		return(false);
	if (str[i] == '-')
		i++;
    if (ft_strlen(str) > 19)
        return(true);
	else if (ft_strlen(str) < 19)
		return(false);
	while (i < ft_strlen(str) && str[i] >= '0' && str[i] <= '9')
    	nb = nb * 10 + str[i++] - '0';
    if (nb * -1 < LONG_MIN)
        return(true);
    i = str[i] - '0';
    if (i > 8)
        return(true);
    return(false);
}

void exit_av_more_than_2(char **av)
{
    if (is_digit_exit_code(av))
    {
        (printf("exit\n"), printf("shell: exit: too many arguments\n"));
        //set exit status to 1
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
    bool b;
    unsigned long long n;

    b = false;
    n = 0;
    if (is_digit_exit_code(av))
    {
        if (av[1][0] == '-')
            b = is_num_very_small(av[1]);
        if (b == false)
        {
            if (av[1][0] != '-')
                n = ft_atoull(av[1]);
            if ((n <= LONG_MAX && b == false) || (av[1][0] == '-' && b == false))
            {
                printf("exit\n");
                exit(ft_atol(av[1]) % 256); 
            }
        }
    }
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
    // (void)av;

    while(1)
    {
        i = 0;
        line = readline("minishell♣\n");
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
