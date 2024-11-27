#include "minishell.h"


char check_for_qoutes(char *str)
{
    int i;
    char q;

    q = 0;
    i = 0;
    while(str[i])
    {
        if(str[i] == '\"' || str[i] == '\'')
        {
            q = str[i];
            break ;
        }
        i++;
    }
   return(q);
}

char *remove_qiute(char *str, char q)
{
    char **array;
    int i;
    char *s;
    char *temp;

    i = 0;
    s = NULL;
    //maybe check for cmd, because for command we need to strdup("''"), but for args flag ft_strdup("")
    if((str[0] == '\"' && str[1] == '\"' && !str[2]) || (str[0] == '\'' && str[1] == '\'' && !str[2])) // if we have "" || '' we need to strdup ''
    {
        printf("inside if!str\n");
        s = ft_strdup("");
        // if(!s)
        //     return(perror("malloc"), NULL);
        return(s);
    }
    array = ft_split(str, q);
    if(!array)
        return((perror("malloc"), NULL));
    while(array[i])
    {
        temp = s;
        s = ft_strjoin(s, array[i]);
        if(!s)
            return((perror("malloc"), free_arr(array), NULL));
        if (temp)
            free(temp);
        i++;
    }
    free_arr(array);
    return(s);
}
void rm_quotes(t_toklist *tokens)
{
    t_toklist *temp;
    char *new_tok;
    char q;

    //i = 0;
    temp = tokens;
    while(temp)
    {
        if(temp->type == CMD || temp->type == ARGS || temp->type == FILE_NAME || temp->type == LIMITER || temp->type == FLAG)
        {
            q = check_for_qoutes(temp->token);
            printf("quote is = %c\n", q);
            if(q != 0)
            {
                
                new_tok = remove_qiute(temp->token, q);
                printf("new_tok = %s\n", new_tok);
                if(!new_tok)
                    (perror("malloc")); // and exit clean everything // this line will print malloc success on stdout incase of ""
                free(temp->token);
                temp->token = new_tok;
                if(q == '\'')
                    temp->q_type = SQ;
                else
                    temp->q_type = DQ;
            }
        }
        temp = temp->next;
    }
}

int find_dollar(char *str)
{
    int i;

    i = 0;
    if(!str)
        return(0);
    while(str[i])
    {
        if(str[i] == '$')
            return(1);
        i++;
    }
    return (0);
}
int expand_tokens(t_toklist *tokens, t_shell *data)
{
    t_toklist *temp;
    char *new_tok;
    char *dollar;
    char *bef_do;
    int doll;

    temp = tokens;
    while(temp)
    {
        bef_do = ft_strdup("");
        if(!bef_do)
            return (perror("malloc"), -1);
        if(temp->type == CMD || temp->type == ARGS || temp->type == FILE_NAME || temp->type == FLAG)
        {
            printf("q_type: %d\n", temp->q_type);
            if(find_dollar(temp->token) == 1)
            {
                if(temp->q_type == DQ || temp->q_type == 0)
                {
                    dollar = ft_strchr(temp->token, '$');
                    printf("dollar : %s\n", dollar);
                    doll = (int) (dollar - temp->token);
                    printf("doll : %d\n", doll);
                    if(doll > 0)
                    {   
                        free(bef_do);
                        int i = ft_strlen(temp->token);
                        int j = ft_strlen(temp->token + doll);
                        bef_do = ft_substr(temp->token, 0, (i - j)); // it was -1
                        if(!bef_do)
                           return(perror("malloc"), -1); // exit cleanly
                        //bef_do = ft_strdup(temp->token - doll);
                        printf("bef_do: %s\n", bef_do);
                    }
                    new_tok = our_expand(temp->token + (doll + 1), data);
                    if(!new_tok)
                        return (perror("malloc"), free(bef_do), -1); // exit cleanly
                    free(temp->token);
                    temp->token = ft_strjoin(bef_do, new_tok);
                    if(!temp->token)
                        return (perror("malloc"), free(bef_do), free(new_tok), -1); // exit cleanly
                    free(new_tok);
                    //temp->token = new_tok;
                }
            }
        }
        free(bef_do);
        temp = temp->next;
    }
    // if(bef_do)
    //     free(bef_do);
    return(0);
}
