#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
int main(int ac, char **av)
{
    char *line;
    (void)ac;
    // (void)env;
    // (void)av;

    while(1)
    {
        line = readline("minishell♣\n");
        if(!line)
            exit(1);
        printf("\nbefore_trim - {%s}\n", line);
        av = our_tokenize(line);
        add_history(line);
    }
    return(0);
}
