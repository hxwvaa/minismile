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
char *pre_dollar(char *str, char *bef_do)
{
    char *dollar;
    //char *new_str;
    int i;
    int j;
    int doll;
    
    bef_do = ft_strdup("");
    if(!bef_do)
        return(perror("malloc"), NULL);
    dollar = ft_strchr(str, '$');
    doll = (int)(dollar - str);
    if(doll > 0)
    {   
        free(bef_do);
        i = ft_strlen(str);
        j = ft_strlen(str + doll);
        bef_do = ft_substr(str, 0, (i - j)); // it was -1
        if(!bef_do)
            return(perror("malloc"), NULL); // exit cleanly
        //bef_do = ft_strdup(temp->token - doll);
    }
    return (bef_do);
}
// int update_token(t_toklist *temp, char *bef_do, char *new_tok, int qtype)
// {
//     free(temp->token);
//     temp->token = ft_strjoin(bef_do, new_tok);
//     if(!temp->token)
//         return (perror("malloc"), free(bef_do), free(new_tok), -1); // exit cleanly
//     if(ft_strncmp(temp->token, "", 2) == 0)
//     {
//         if(qtype == 0)
//         {
//             temp->em_ex = 1;
//             if(temp->next && (temp->next->type == FLAG || temp->next->type == ARGS))
//             {
//                 temp->next->type = CMD;
//                 //temp->next->em_ex = 0;
//             }
//         }
//     }
//     free(new_tok);
//     return (0);
// }

char *final_tokstring(t_toklist *temp, char *res, int qtype)
{
    char *remains;

    remains = ft_strdup(temp->token);
    free(temp->token);
    if(!remains)
        return(perror("malloc"), free(res), NULL);
    res = join_strs(res, remains, temp->token);
    if (!res)
        return(perror("malloc"), NULL);
    if(ft_strncmp(res, "", 2) == 0)
    {
        if(qtype == 0)
        {
            temp->em_ex = 1;
            if(temp->next && (temp->next->type == FLAG || temp->next->type == ARGS))
            {
                temp->next->type = CMD;
                //temp->next->em_ex = 0;
            }
        }
    }
    return(res);
}

char    *expand_tok(t_toklist *temp, t_shell *data, int len)
{
	char    *res;

	res = ft_strdup("");
	if (!res)
		return (perror("malloc"), NULL);
	while(find_dollar(temp->token))
	{
        res = handle_expand(temp->token, data, &len, res);
        if (!res)
            return (NULL);
        temp->token = update_line(temp->token, res, len);
        if (!temp->token)
            return (NULL);  
	}
	return (final_tokstring(temp, res, temp->q_type));
}

int expand_tokens(t_toklist *tokens, t_shell *data)
{
    t_toklist *temp;

    temp = tokens;
    while(temp)
    {
        if(temp->type == CMD || temp->type == ARGS || temp->type == FILE_NAME || temp->type == FLAG)
        {
            if(find_dollar(temp->token) == 1 && (temp->q_type == DQ || temp->q_type == 0))
            {
                temp->token = expand_tok(temp, data, 0);
                if(!temp->token)
                    return(-1);
            }
        }
        temp = temp->next;
    }
    return(0);
}

// int expand_tokens(t_toklist *tokens, t_shell *data)
// {
//     t_toklist *temp;
//     //char *new_tok;
//     // char *bef_do;
//     // char *res;
//     // char *to_ex;
//     // int len;

//     // len = 0;
//     temp = tokens;
//     //bef_do = NULL;
//     while(temp)
//     {
//         // bef_do = ft_strdup("");
//         // if(!bef_do)
//         //     return (perror("malloc"), -1);
//         if(temp->type == CMD || temp->type == ARGS || temp->type == FILE_NAME || temp->type == FLAG)
//         {
//             if(find_dollar(temp->token) == 1 && (temp->q_type == DQ || temp->q_type == 0))
//             {

//                 temp->token = expand_tok(temp, data, 0);
//                 // res = ft_strdup("");
//                 // if(!res)
//                 //     return(perror("malloc"), -1);
//                 // while(find_dollar(temp->token))
//                 // {
//                 //     bef_do = pre_dollar(temp->token, NULL);
//                 //     if(!bef_do)
//                 //         return(free(res), perror("malloc"), -1);
//                 //     to_ex = expand_what(temp->token, (ft_strlen(bef_do) + 1), &len);
//                 //     if(!to_ex)
//                 //          return(free(bef_do), free(res), perror("malloc"), -1);
//                 //     res = join_strs(res, bef_do, temp->token);
//                 //     if (!res)
//                 //         return(perror("malloc"), -1);
//                 //     res = join_strs(res, our_expand(to_ex, data), temp->token);
//                 //     free(to_ex);
//                 //     temp->token = update_line(temp->token, res, len);
//                 //     if(!temp->token)
//                 //         return(-1);
//                 // }
//                 // temp->token = final_tokstring(temp, res, temp->q_type);
//                 if(!temp->token)
//                     return(-1);
//                 // bef_do = pre_dollar(temp->token, bef_do);
//                 // if(!bef_do)
//                 //     return (-1);
//                 // //printf("bef_do:%s\n", bef_do + 1);
//                 // new_tok = our_expand(temp->token + (ft_strlen(bef_do) + 1), data);
//                 // if(!new_tok)
//                 //     return (perror("malloc"), free(bef_do), -1); // exit cleanly
//                 // if(update_token(temp, bef_do, new_tok, temp->q_type) == -1)
//                 //     return (-1);
//                 //}
//             }
//         }
//         //free(bef_do);
//         temp = temp->next;
//     }
//     return(0);
// }

// int expand_tokens(t_toklist *tokens, t_shell *data)
// {
//     t_toklist *temp;
//     char *new_tok;
//     char *dollar;
//     char *bef_do;
//     int doll;

//     temp = tokens;
//     while(temp)
//     {
//         bef_do = ft_strdup("");
//         if(!bef_do)
//             return (perror("malloc"), -1);
//         if(temp->type == CMD || temp->type == ARGS || temp->type == FILE_NAME || temp->type == FLAG)
//         {
//             printf("q_type: %d\n", temp->q_type);
//             if(find_dollar(temp->token) == 1)
//             {
//                 if(temp->q_type == DQ || temp->q_type == 0)
//                 {
//                     dollar = ft_strchr(temp->token, '$');
//                     printf("dollar : %s\n", dollar);
//                     doll = (int) (dollar - temp->token);
//                     printf("doll : %d\n", doll);
//                     if(doll > 0)
//                     {   
//                         free(bef_do);
//                         int i = ft_strlen(temp->token);
//                         int j = ft_strlen(temp->token + doll);
//                         bef_do = ft_substr(temp->token, 0, (i - j)); // it was -1
//                         if(!bef_do)
//                            return(perror("malloc"), -1); // exit cleanly
//                         //bef_do = ft_strdup(temp->token - doll);
//                         printf("bef_do: %s\n", bef_do);
//                     }
//                     new_tok = our_expand(temp->token + (doll + 1), data);
//                     if(!new_tok)
//                         return (perror("malloc"), free(bef_do), -1); // exit cleanly
//                     free(temp->token);
//                     printf("expanded string: {%s}\n", new_tok);
//                     temp->token = ft_strjoin(bef_do, new_tok);
//                     if(ft_strncmp(temp->token, "", 2) == 0)
//                     {
//                         printf("temp->token: {%s}\n", temp->token);
//                         temp->em_ex = 1;
//                         if(temp->next && (temp->next->type == FLAG || temp->next->type == ARGS))
//                         {
//                             //temp = temp->next;
//                             printf("next token: %s", temp->token);
//                             temp->next->type = CMD;
//                             printf("type: %d\n", temp->type);
//                             //temp->next->em_ex = 0;
//                         }
//                     }
//                     //printf("temp->token: {%s}\n", temp->token);
//                     if(!temp->token)
//                         return (perror("malloc"), free(bef_do), free(new_tok), -1); // exit cleanly
//                     free(new_tok);
//                     //temp->token = new_tok;
//                 }
//             }
//         }
//         free(bef_do);
//         temp = temp->next;
//     }
//     // if(bef_do)
//     //     free(bef_do);
//     return(0);
// }