#include "../minishell.h"

char *handle_sq(char *str, char *res, int *i)
{
    char *temp;
    int start;

    start = ++(*i);
    while(str[*i] && str[*i] != '\'')
        (*i)++;
    temp = ft_substr(str, start, (*i) - start);
    if(!temp)
        return(perror("malloc"), free(res), NULL);
    res = join_free(res, temp);
    if(!res)
        return(perror("malloc"), NULL);
    if(str[*i] == '\'')
        (*i)++;
    return(res);
}
char *handle_any(char *str, char *res, int *i)
{
    int start;
    char *temp;

    start = (*i);
    while(str[*i] && str[*i] != '\'' && str[*i] != '\"' && str[*i] != '$')
        (*i)++;
    temp = ft_substr(str, start, (*i) - start);
    if(!temp)
        return(free(res), perror("malloc"), NULL);
    res = join_free(res, temp);
    if(!res)
        return (perror("malloc"), NULL);
    return (res);
}
char *handle_any_dq(char *str, char *res, int *i)
{
    int start;
    char *temp;

    start = (*i);
    while(str[*i] && str[*i] != '\"' && str[*i] != '$')
        (*i)++;
    temp = ft_substr(str, start, (*i) - start);
    if(!temp)
        return(free(res), perror("malloc"), NULL);
    res = join_free(res, temp);
    if(!res)
        return (perror("malloc"), NULL);
    return (res);
}

char *handle_dq_help(char *str, char *res, int i, int start)
{
    char *temp;

    temp = ft_substr(str, start, i - start);
    if(!temp)
        return(free(res), NULL);
    res = join_free(res, temp);
    if(!res)
        return (NULL);
    return (res);
}

char *handle_dq(char *str, char *res, int *i, t_shell *data)
{
    int start;

    start = ++(*i);
    while(str[*i] && str[*i] != '\"')
    {
        if(str[*i] == '$' && str[*i + 1] != '\"')
        {
            printf("str[*i] = %c\n", str[*i]);
            res = handle_any_dq(str, res, &start); 
            if(!res)
                return(NULL);
            res = handle_ex(str, res, i, data);
            if(!res)
                return(NULL);
            start = *i;
        }
        else
            (*i)++;
    }
    res = handle_dq_help(str, res, *i, start);
    if(!res)
        return (NULL);
    if(str[*i] == '\"')
        (*i)++;
    return (res);
}
