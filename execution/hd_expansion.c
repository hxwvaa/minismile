#include "../minishell.h"


// char *handle_predoll(char *line, char *res, char **bef_do)
// {
//     *bef_do = pre_dollar(line, *bef_do);
//     if(!*bef_do)
//         return(perror("malloc"), free(res), NULL);
//     res = join_strs(res, *bef_do, line);
//     if (!res)
//         return (NULL);
//     return(res);
// }

char    *handle_expand(char *line, t_shell *data, int *len, char *res)
{
    char    *ex_str;
    char    *to_ex;
    char    *bef_do;
    
    bef_do = pre_dollar(line, NULL);
    if(!bef_do)
        return(perror("malloc"), free(res), NULL);
    to_ex = expand_what(line, (ft_strlen(bef_do) + 1), len); //maybe add the check here for isalnum, != _ 
	if (!to_ex)
		return (perror("malloc"), free(bef_do), free(res), NULL);
    res = join_strs(res, bef_do, line);
    if (!res)
        return (NULL);
    ex_str = our_expand(to_ex, data);
    free(to_ex);
    if (!ex_str)
        return (perror("malloc"), free(res), NULL);
    res = join_strs(res, ex_str, line);
    if (!res)
        return (perror("malloc"), NULL);
    return (res);
}

char *update_line(char *line, char *res, int len)
{
    char *new;

    new = ft_strdup(line + len);
    free(line);
    if (!new)
        return (perror("malloc"), free(res), NULL);
    return (new);
}

char *final_string(char *line, char *res)
{
    char *remains;

    remains = ft_strdup(line);
    free(line);
    if(!remains)
        return(perror("malloc"), free(res), NULL);
    res = join_strs(res, remains, line);
    if (!res)
        return(perror("malloc"), NULL);
    return(res);
}

char    *expand_hd(char *line, t_shell *data, int len)
{
	char    *res;

	res = ft_strdup("");
	if (!res)
		return (perror("malloc"), NULL);
	while(find_dollar(line))
	{
        res = handle_expand(line, data, &len, res);
        if (!res)
            return (NULL);
        line = update_line(line, res, len);
        if (!line)
            return (NULL);
	}
	return (final_string(line, res));
}
