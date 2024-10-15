#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
int main(int ac, char **av)
{
    char *line;
    (void)ac;
    // (void)env;
     (void)av;

    while(1)
    {
        line = readline("minishell$\n");
        printf("my line: %s\n", line);
        //av = ft_tokenize(line);
        ft_tokenize(line);
        if(!line)
            exit(1);
    }
    return(0);
}
