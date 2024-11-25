#include "minishell.h"

// char *rm_quote_token(char *arg, int i)
// {
//     int j;
//     char q;
//     char *new_arg;

//     j = 0;
//     q = arg[0];
//     while(arg[i])
//     {
//         if(arg[i] == '\"' || arg[i] == '\'')
//         {
//             i++;
//             j = i;
//             while(arg[i] != '\"')
//                 i++;
//         }
//         if(arg[i] == '\'')
//         {
//             i++;
//             k = i;
//             while(arg[i] != '\'')
//                 i++;
//         }
//         i++;
//     }
//     if(k == 0)
//         new_arg = ft_calloc((i - j))
//     return()
// }
// void	ft_strcpy(char *des, char *src, int j)
// {
// 	int	i;

// 	i = 0;
// 	while (src[i] && i < j)
// 	{
// 		des[i] = src[i];
// 		i++;
// 	}
// 	des[i] = '\0';
// }

// char *split_by_quotes(char *str)
// {
//     int i;
//     int j;
//     char q;
//     char *nstr;
//     char *temp;

//     i = 0;
//     //q = str[0];
//     temp = ft_strdup("");
//     if(!temp)
//         return (perror("malloc"), NULL); // exit cleanly
//     while(str[i])
//     {
//         if(str[i] == '\'')
//             q = str[i];
//         else if(str[i] == '\"')
//             q = str[i];
//         i++;
//         j = i;
//         while(str[i] != q)
//         {
//             i++;
//         }
//         nstr = ft_calloc((i - j) + 1, sizeof(char));
//         if(!nstr)
//             return((free(temp),perror("malloc")), NULL); // exit cleanly
//         ft_strcpy(nstr, str + j, i - j);
//         nstr = ft_strjoin(temp, nstr);
//         if(!nstr)
//             return(free(temp), perror("malloc"), NULL); // exit cleanly
//         free(temp);
//         temp = nstr;
//         i++;
//     }
//     if(temp)
//         free(temp);
//     return (nstr);
// }

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
        if(temp->type == CMD || temp->type == ARGS || temp->type == FILE_NAME || temp->type == LIMITER)
        {
            q = check_for_qoutes(temp->token);
            if(q != 0)
            {
                
                new_tok = remove_qiute(temp->token, q);
                if(!new_tok)
                    (perror("malloc")); // and exit clean everything
                free(temp->token);
                temp->token = new_tok;
            }
        }
        temp = temp->next;
    }
}

// int main(int ac, char **av)
// {
//     int i;

//     i = 1;
//     // char **asv = {"'hello'", "hii", "hello", NULL};
//     if(ac > 1)
//     {
//         while(av[i])
//         {
//             char *s = remove_qiute(av[i]);
//             if(!s)
//             {
//                 perror("malloc");
//                 break;
//             }
//             printf("string: %s\n", s);
//             free(s);
//             i++;
//         }
//     }
//     else
//         write(2, "nono\n", 5);
// }
