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

void our_expenv(t_shell *data)
{
    t_list *tmp;

    tmp = data->envir;

    while(tmp)
    {
        char *equal = ft_strchr((char *)tmp->content, '=');
        if(equal)
        {
            printf("declare -x %.*s=\"%s\"\n", (int)(equal - (char *)tmp->content), tmp->content, equal + 1);
        }
        else
            printf("declare -x %s\n", tmp->content);
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