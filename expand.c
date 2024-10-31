#include "minishell.h"

void our_expand(char *var, t_shell *data)
{
    t_list *current;

    current = data->envir;
    while(current)
    {
        if(ft_strncmp(var, current->content, ft_strlen(var) == 0))
        {
            //search for the var then strdup the value of that into
            //a char *
        }
    }
    //then print that value to stdout + \n, if var not found just print
    // a newline
}