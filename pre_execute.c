#include "minishell.h"

// t_token *array_to_token_array(char **split, int count)
// {
//     int i;
//     int first;

//     i = 0;
//     first = 1;
//     t_token *tokens = malloc(count * sizeof(t_token));
//     if(!tokens)
//         return (perror("malloc"), NULL);
//     while(split[i] && i <= count)
//     {
//         printf("split[i] : %s\n", split[i]);
//         if((ft_strncmp(split[i], ">", 2) == 0) && (ft_strncmp(split[i + 1], ">", 2) == 0))
//             tokens[i].token = ft_strdup(">>");
//         else if(((ft_strncmp(split[i], "<", 2) == 0) && (ft_strncmp(split[i + 1], "<", 2) == 0)))
//             tokens[i].token = ft_strdup("<<");
//         else
//             tokens[i].token = ft_strdup(split[i]);
//         tokens[i].type = set_token_type(split[i], &i, split, &first);
//         // if (ft_strncmp(tokens[i].token, "<<", 3) == 0 || ft_strncmp(tokens[i].token, ">>", 3) == 0)
//         //     i++;
//         // if (tokens[i].type == APPEND || tokens[i].type == HERE_DOC)
//         //     i++;
//         // if(tokens[i].type == APPEND || tokens[i].type == HERE_DOC)
//         // {
//         //     if(tokens[i].type == APPEND)
//         //         tokens[i].token = ft_strdup(">>");
//         //     else if(tokens[i].type == HERE_DOC)
//         //         tokens[i].token = ft_strdup("<<");
//         // }
//         // else
//         // printf("token = %s, type :%d\n", tokens[i].token, tokens[i].type);
//         i++;
//     }
//     tokens[i].token = NULL;
//     i = 0;
//     while(tokens[i].token)
//     {
//         printf("token = %s, type :%d\n", tokens[i].token, tokens[i].type);
//         i++;
//     }
//     return (tokens);
// }
//t_cmd set_token_type(char **)


// int set_token_type(char *token, int *first, int *file)
// {
//     if(ft_strncmp(token, "|", 2) == 0)
//     {
//         (*first) = 1;
//         return (PIPE);
//     }
//     else if(ft_strncmp(token, "<", 2) == 0)
//         return (*file = 1, REDIR_IN);
//     else if(ft_strncmp(token, ">", 2) == 0)
//         return (*file = 1, REDIR_OUT);
//     else if(ft_strncmp(token, ">>", 3) == 0)
//         return (*file = 1, APPEND);
//     else if(ft_strncmp(token, "<<", 3) == 0)
//         return (*file = 2, HERE_DOC);
//     else if (token[0] == '-' && !*first)
//         return (FLAG);
//     else if(*file == 1)
//         return(*file = 0, FILE_NAME);
//     else if (*file == 2)
//         return(*file = 0, LIMITER);
//     else if (*first)
//     {
//         *first = 0;
//         return(CMD);
//     }
//     return (ARGS);
// }

int	set_token_type(char *token, int *first, int *file)
{
	if (ft_strncmp(token, "|", 2) == 0)
	{
		(*first) = 1;
		return (PIPE);
	}
	else if (ft_strncmp(token, "<", 2) == 0)
		return (*file = 1, REDIR_IN);
	else if (ft_strncmp(token, ">", 2) == 0)
		return (*file = 1, REDIR_OUT);
	else if (ft_strncmp(token, ">>", 3) == 0)
		return (*file = 1, APPEND);
	else if (ft_strncmp(token, "<<", 3) == 0)
		return (*file = 2, HERE_DOC);
	else if (token[0] == '-' && !*first)
		return (FLAG);
	else if (*file == 1)
		return (*file = 0, FILE_NAME);
	else if (*file == 2)
		return (*file = 0, LIMITER);
	else if (*first)
	{
		*first = 0;
		return (CMD);
	}
	return (ARGS);
}

// int set_token_type(char *token, int *i, char **tokens, int *first)
// {
//     if(ft_strncmp(token, "|", 2) == 0)
//     {
//         (*first) = 1;
//         return (PIPE);
//     }
//     else if(ft_strncmp(token, "<", 2) == 0)
//     {
//         // if(tokens[(*i) + 1])
//         // {
//         //     if(ft_strncmp(tokens[(*i) + 1], "<", 2) == 0)
//         //     {
//         //         (*i)++;
//         //         return (HERE_DOC);
//         //     }
//         // }
//         //else 
//             return (REDIR_IN);
//     }
//     else if(ft_strncmp(token, ">", 2) == 0)
//     {
//     //    if(tokens[(*i) + 1])
//     //     {
//     //         if(ft_strncmp(tokens[(*i) + 1], ">", 2) == 0)
//     //         {
//     //             (*i)++;
//     //             return (APPEND);
//     //         }
//     //     }
//         //else
//             return (REDIR_OUT);
//     }
//     else if(ft_strncmp(token, ">>", 3) == 0)
//         return (APPEND);
//     else if(ft_strncmp(token, "<<", 3) == 0)
//         return (HERE_DOC);
//     else if (token[0] == '-' && !*first)
//         return (FLAG);
//     else if (*first)
//     {
//         *first = 0;
//         return(CMD);
//     }
//     //else
//         return (ARGS);
// }


t_toklist *our_tlstlast(t_toklist *lst)
{
    t_toklist *ptr;

    if(!lst)
        return (NULL);
    ptr = lst;
    while(ptr->next != NULL)
        ptr = ptr->next;
    return(ptr);

}

void    our_tlstadd_back(t_toklist **lst, t_toklist *new)
{
    if(!new)
        return;
    if(!*lst)
        *lst = new;
    else
        our_tlstlast(*lst)->next = new;
}

t_toklist	*our_tlstnew(char *token, int type)
{
	t_toklist	*list;
    if(!token)
    {
        return (NULL);
    }
	list = malloc(sizeof(t_toklist));
	if (list == NULL)
		return (NULL);
	list->token = token;
    list->type = type;
    list->q_type = 0;
    list->em_ex = 0;
	list->next = NULL;
	return (list);
}
t_toklist *array_token_list(t_shell *data, char **split, int count)
{
    int i;
    int first;
    t_toklist *new;
    int file;

    file = 0;
    i = 0;
    first = 1;
    while(split[i] && i <= count)
    {
        // if((ft_strncmp(split[i], ">", 2) == 0) && split[i + 1] && (ft_strncmp(split[i + 1], ">", 2) == 0))
        //     new = our_tlstnew(ft_strdup(">>"), set_token_type(split[i], &i, split, &first));
        // else if((ft_strncmp(split[i], "<", 2) == 0) && split[i + 1] && (ft_strncmp(split[i + 1], "<", 2) == 0))
        //     new = our_tlstnew(ft_strdup("<<"), set_token_type(split[i], &i, split, &first));
        // else    
            new = our_tlstnew(ft_strdup(split[i]), set_token_type(split[i], &first, &file));
        if(!new)
            return(perror("malloc"), NULL);
        if(new)
            our_tlstadd_back(&data->tokens, new);
        i++;
    }
    //free split array
    return(data->tokens);
}
