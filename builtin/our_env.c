#include "../minishell.h"

// void our_env(char **env)
// {
//     int i;

//     i = 0;
//     while(env[i])
//     {
//         printf("%s\n", env[i]);
//         i++;
//     }
// }

void our_env(t_list *envir)
{
    t_list *tmp;

    tmp = envir;
    printf("our own env\n");
    while(tmp)
    {
        if(ft_strchr(tmp->content, '='))
            printf("%s\n", (char *)tmp->content);
        tmp = tmp->next;
    }
}

t_list *clone_list(t_list *o_list)
{
    t_list *list;
    t_list *temp;
    t_list *new_l;

    list = o_list;
    new_l = NULL;
    while(list)
    {
        temp = ft_lstnew(list->content);
        if (!temp)
            return(NULL);
        ft_lstadd_back(&new_l, temp);
        list = list->next;
    }
    return(new_l);
}

t_list *sort_exp(t_list *list)
{
    t_list *final;
    t_list *n_list;
    void *temp;

    n_list = clone_list(list);
    if(!n_list)
        return(NULL);
    final = n_list;
    while(n_list)
    {
        if (n_list->next && ft_strncmp((char *)n_list->content, (char *)n_list->next->content, ft_strlen((char *)n_list->content)) > 0)
        {
            temp = n_list->content;
            n_list->content = n_list->next->content;
            n_list->next->content = temp;
            n_list = final;
        }
        else
            n_list = n_list->next;
    }
    return(final);
}

void our_expenv(t_shell *data)
{
    t_list *tmp;
    tmp = sort_exp(data->envir);
    // if (!tmp)
    //     ; //ERROR
    while(tmp)
    {
        char *equal = ft_strchr((char *)tmp->content, '=');
        if(equal)
        {
            printf("declare -x %.*s=\"%s\"\n", (int)(equal - (char *)tmp->content), (char *)tmp->content, equal + 1);
        }
        else
            printf("declare -x %s\n", (char *)tmp->content);
        tmp = tmp->next;
    }
}
// void init_shell(t_shell *data, char **envp)
// {
//     t_list *new_node;
//     int i;

//     data->envi = envp;
//     data->envir = NULL;
//     data->our_args = NULL;
//     data->exit_code = 0;

//     i = 0;
//     if (envp)
//     {   
//         while(envp[i])
//         {
//             new_node = ft_lstnew(envp[i]);
//             if(!new_node)
//             {
//                 write(2, "error malloc\n", 13);
//                 return ;
//             }
//             if(new_node)
//                 ft_lstadd_back(&data->envir, new_node);
//             i++;
//         }
//     }
// }
// int main(int ac, char **av, char **envp)
// {
//     (void)ac;
//     (void)av;
//     t_shell data;

//     init_shell(&data, envp);

//     our_expenv(&data);
    
//     int i =0;
//     printf("-------------------------------\n");
//     while(envp[i])
//     {
//         printf("%s\n", envp[i++]);
//     }
//     // while(data.envi[i])
//     //     printf("%s\n", data.envi[i++]);
// }