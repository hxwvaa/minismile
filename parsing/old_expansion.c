

// char *pre_dollar(char *str, char *bef_do)
// {
//     char *dollar;
//     //char *new_str;
//     int i;
//     int j;
//     int doll;
    
//     bef_do = ft_strdup("");
//     if(!bef_do)
//         return(perror("malloc"), NULL);
//     dollar = ft_strchr(str, '$');
//     doll = (int)(dollar - str);
//     if(doll > 0)
//     {   
//         free(bef_do);
//         i = ft_strlen(str);
//         j = ft_strlen(str + doll);
//         bef_do = ft_substr(str, 0, (i - j)); // it was -1
//         if(!bef_do)
//             return(perror("malloc"), NULL); // exit cleanly
//         //bef_do = ft_strdup(temp->token - doll);
//     }
//     return (bef_do);
// }

// int find_dollar(char *str)
// {
//     int i;

//     i = 0;
//     if(!str)
//         return(0);
//     while(str[i])
//     {
//         if(str[i] == '$')
//             return(1);
//         i++;
//     }
//     return (0);
// }

// char *join_free(char *s1, char *s2)
// {
//     char *result;

//     result = ft_strjoin(s1, s2);
//     free(s1);
//     free(s2);
//     if(!result)
//         return(perror("malloc"), NULL);
//     return (result);
// }
// char *handle_sq(char *str, char *res, int *i)
// {
//     char *temp;
//     int start;

//     start = ++(*i);
//     while(str[*i] && str[*i] != '\'')
//         (*i)++;
//     temp = ft_substr(str, start, (*i) - start);
//     if(!temp)
//         return(perror("malloc"), free(res), NULL);
//     res = join_free(res, temp);
//     if(!res)
//         return(perror("malloc"), NULL);
//     if(str[*i] == '\'')
//         (*i)++;
//     return(res);
// }
// char *handle_any(char *str, char *res, int *i)
// {
//     int start;
//     char *temp;

//     start = (*i);
//     while(str[*i] && str[*i] != '\'' && str[*i] != '\"' && str[*i] != '$')
//         (*i)++;
//     temp = ft_substr(str, start, (*i) - start);
//     if(!temp)
//         return(free(res), perror("malloc"), NULL);
//     res = join_free(res, temp);
//     if(!res)
//         return (perror("malloc"), NULL);
//     return (res);
// }
// char *handle_any_dq(char *str, char *res, int *i)
// {
//     int start;
//     char *temp;

//     start = (*i);
//     while(str[*i] && str[*i] != '\"' && str[*i] != '$')
//         (*i)++;
//     temp = ft_substr(str, start, (*i) - start);
//     if(!temp)
//         return(free(res), perror("malloc"), NULL);
//     res = join_free(res, temp);
//     if(!res)
//         return (perror("malloc"), NULL);
//     return (res);
// }

// char *handle_ex(char *str, char *res, int *i, t_shell *data)
// {
//     int start;
//     char *to_ex;
//     char *temp;

//     //start = ++(*i);
//     // start = *i + 1;
//     if(!str[*i + 1])
//     {
//         temp = ft_substr(str, *i, 1);
//         if(!temp)
//             return (free(res), NULL);
//         res = join_free(res, temp);
//         printf("result:%s\n", res);
//         if(!res)
//             return(NULL);
//         if(str[*i])
//             (*i)++;
//         return(res);
//     }
//     if(str[*i + 1] == '?')
//     {
//         //if(str[*i])
//         (*i) = (*i) + 2;
//         return(free(res), ft_itoa(data->exit_code));
//     }
//     start = ++(*i);
//     while(str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
//         (*i)++;
//     to_ex = ft_substr(str, start, (*i) - start);
//     if(!to_ex)
//         return(perror("malloc"), free(res), NULL);
//     temp = our_expand(to_ex, data);
//     free(to_ex);
//     if(!temp)
//         return(free(res), perror("malloc"), NULL);
//     res = join_free(res, temp);
//     if(!res)
//         return(perror("malloc"), NULL);
//     return(res); 
// }


// char *handle_dq_help(char *str, char *res, int i, int start)
// {
//     char *temp;

//     temp = ft_substr(str, start, i - start);
//     if(!temp)
//         return(free(res), NULL);
//     res = join_free(res, temp);
//     if(!res)
//         return (NULL);
//     return (res);
// }
// char *handle_dq(char *str, char *res, int *i, t_shell *data) //new one with handle_dq_help
// {
//     int start;

//     start = ++(*i);
//     while(str[*i] && str[*i] != '\"')
//     {
//         if(str[*i] == '$')
//         {
//             res = handle_any_dq(str, res, &start); 
//             if(!res)
//                 return(NULL);
//             res = handle_ex(str, res, i, data);
//             if(!res)
//                 return(NULL);
//             start = *i;
//         }
//         else
//             (*i)++;
//     }
//     res = handle_dq_help(str, res, *i, start);
//     if(!res)
//         return (NULL);
//     if(str[*i] == '\"')
//         (*i)++;
//     return (res);
// }


// int do_expand_help(t_toklist *temp, t_shell *data, char **res, int *i)
// {
//     if(temp->token[*i] == '\"') //same issue
//     {
//         *res = handle_dq(temp->token, *res, i, data);
//         if(!*res)
//             return(-1);
//         temp->q_type = DQ;
//     }
//     else if(temp->token[*i] == '$') // missing small issue if $ on its own should get executed, same for $PWD$ should be /home/gaz$
//     {
//         //ithink issue solved
//         *res = handle_ex(temp->token, *res, i, data);
//         if(!*res)
//             return (-1);
//     }
//     else
//     {
//         *res = handle_any(temp->token, *res, i);
//         if(!*res)
//             return (-1);
//     }
//     return (0);
// }

// char *do_expand(t_toklist *temp, t_shell *data, char *res, int i) //comments are what was before norminetting
// {
//     if(!res)
//         return(perror("malloc"), NULL);
//     while(temp->token[i])
//     {
//         if(temp->token[i] == '\'')
//         {
//             res = handle_sq(temp->token, res, &i);
//             if(!res)
//                 return(NULL);
//             temp->q_type = SQ;
//         }
//         else if (do_expand_help(temp, data, &res, &i) == -1)
//             return (NULL);
//         // else if(temp->token[i] == '\"') //same issue
//         // {
//         //     res = handle_dq(temp->token, res, &i, data);
//         //     if(!res)
//         //         return(NULL);
//         //     temp->q_type = DQ;
//         // }
//         // else if(temp->token[i] == '$') // missing small issue if $ on its own should get executed, same for $PWD$ should be /home/gaz$
//         // {
//         //     //ithink issue solved
//         //     res = handle_ex(temp->token, res, &i, data);
//         //     if(!res)
//         //         return (NULL);
//         // }
//         // else
//         // {
//         //     res = handle_any(temp->token, res, &i);
//         //     if(!res)
//         //         return (NULL);
//         // }
//     }
//     return (res);
// }

// int update_token(t_toklist *temp)
// {
//     t_toklist *ch;

//     ch = temp;
//     if(ft_strncmp(temp->token, "", 2) == 0)
//     {
//         if(temp->q_type == 0)
//         {
//             temp->em_ex = 1;
//             while(ch && ch->type != PIPE)
//             {
//                 if(ch->type == FLAG || ch->type == ARGS)
//                 {
//                    ch->type = CMD;
//                    break ;
//                 //temp->next->em_ex = 0;
//                 }
//                 ch = ch->next;
//             }
//         }
//     }
//     return (0);
// }

// int our_extok(t_toklist *tokens, t_shell *data)
// {
//     t_toklist *temp;
//     char *expanded;
    
//     temp = tokens;
//     while(temp)
//     {
//         if(temp->type == CMD || temp->type == ARGS || temp->type == FILE_NAME || temp->type == FLAG)
//         {
//             expanded = do_expand(temp, data, ft_strdup(""), 0);
//             if(!expanded)
//                 return(perror("malloc"), -1);
//             free(temp->token);
//             temp->token = expanded;
//             update_token(temp);
//         }
//         temp = temp->next;
//     }
//     return(0);
// }