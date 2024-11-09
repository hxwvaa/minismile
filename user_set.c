
#include "minishell.h"

char *find_b_equal(char *str)
{
    int i;
    char *new_s;
    
    i = 0;
    while(str[i] && str[i] != '=')
        i++;
    if (str[i] == '=')
    {
        new_s = malloc(i + 1);
        if (!new_s)
            return(NULL);
    }
    else
        return("");
    i = 0;
    while(str[i] != '=')
    {
        new_s[i] = str[i];
        i++;
    }
    new_s[i] = '\0';
    return(new_s);
}

int user_set(char **av, t_shell *data)
{
    char *var;
    char *env_var;
    t_list *temp;

    var = find_b_equal(av[0]);
    if (!var)
        ;//malloc error
    if (!var[0])
        return(-1);
    temp = data->envir;
    while(temp != NULL)
    {   
        env_var = find_b_equal(temp->content);
        if (ft_strncmp(var, env_var, ft_strlen(var) + 1) == 0)
        {
            free(temp->content);
            temp->content = ft_strdup(av[0]);
            if (!temp->content)
                ;//malloc error
            return(1);
        }
        temp = temp->next;
    }
    ft_lstadd_back(&data->user_set, ft_lstnew(ft_strdup(av[0])));
    return(1);
}
