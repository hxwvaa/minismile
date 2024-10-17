#include "minishell.h"

int main(int ac, char **av, char **env)
{
    char *line;
    (void)ac;
    // (void)env;
    //(void)av;

     
    while(1)
    {
        line = readline("minishell♣\n");
        if(ft_strncmp(line, "exit", 4) == 0)
        {
            free(line);
            exit(0);
        }
        if(!line)
            exit(1);
        printf("\nbefore_trim - {%s}\n", line);
        av = st_tokenize(line);
        pre_execute_cmd(av, env);
        add_history(line);
    }
    return(0);
}