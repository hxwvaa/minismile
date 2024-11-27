#include "minishell.h"

char *before_equal(char *str)
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
char *after_equal(char *str)
{
    int i;
    
    i = 0;
    while(str[i] && str[i] != '=')
        i++;
    if (str[i] == '=')
        i++;
    if (!str[i])
        return(NULL);
    return(ft_strdup(str + i));
}

char *our_expand(char *var, t_shell *data)
{
    char *str;
    t_list *temp;
    
    str = NULL;
    temp = data->envir;
    if (ft_strncmp(var, "?", 2) == 0)
        return(ft_itoa(data->exit_code));
    while(temp)
    {
        str = before_equal(temp->content);
        if(!str)
            return(NULL);
        if(ft_strncmp(var, str, ft_strlen(var) + 1) == 0)
        {
            return(free(str), after_equal(temp->content));
        }
        free(str);
        temp = temp->next;
    }
    return(ft_strdup(""));
}
