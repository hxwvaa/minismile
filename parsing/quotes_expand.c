#include "../minishell.h"

char *join_free(char *s1, char *s2)
{
    char *result;

    result = ft_strjoin(s1, s2);
    free(s1);
    free(s2);
    if(!result)
        return(perror("malloc"), NULL);
    return (result);
}

int do_expand_help(t_toklist *temp, t_shell *data, char **res, int *i)
{
    if(temp->token[*i] == '\"') //same issue
    {
        *res = handle_dq(temp->token, *res, i, data);
        if(!*res)
            return(-1);
        temp->q_type = DQ;
    }
    else if(temp->token[*i] == '$') // missing small issue if $ on its own should get executed, same for $PWD$ should be /home/gaz$
    {
        //ithink issue solved
        *res = handle_ex(temp->token, *res, i, data);
        if(!*res)
            return (-1);
    }
    else
    {
        *res = handle_any(temp->token, *res, i);
        if(!*res)
            return (-1);
    }
    return (0);
}

char *do_expand(t_toklist *temp, t_shell *data, char *res, int i)
{
    if(!res)
        return(perror("malloc"), NULL);
    while(temp->token[i])
    {
        if(temp->token[i] == '\'')
        {
            res = handle_sq(temp->token, res, &i);
            if(!res)
                return(NULL);
            temp->q_type = SQ;
        }
        else if (do_expand_help(temp, data, &res, &i) == -1)
            return (NULL);
    }
    return (res);
}

int update_token(t_toklist *temp)
{
    t_toklist *ch;

    ch = temp;
    if(ft_strncmp(temp->token, "", 2) == 0)
    {
        if(temp->q_type == 0)
        {
            temp->em_ex = 1;
            while(ch && ch->type != PIPE)
            {
                if(ch->type == FLAG || ch->type == ARGS)
                {
                   ch->type = CMD;
                   break ;
                //temp->next->em_ex = 0;
                }
                ch = ch->next;
            }
        }
    }
    return (0);
}

int our_extok(t_toklist *tokens, t_shell *data)
{
    t_toklist *temp;
    char *expanded;
    
    temp = tokens;
    while(temp)
    {
        if(temp->type == CMD || temp->type == ARGS || temp->type == FILE_NAME || temp->type == FLAG)
        {
            expanded = do_expand(temp, data, ft_strdup(""), 0);
            if(!expanded)
                return(perror("malloc"), -1);
            free(temp->token);
            temp->token = expanded;
            update_token(temp);
        }
        temp = temp->next;
    }
    return(0);
}
