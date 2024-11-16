#include "minishell.h"

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

// void prit_user_set(t_shell *data)
// {
//     t_list *temp = data->user_set;

//     while(temp != NULL)
//     {
//         printf("[[%s]]\n", temp->content);
//         temp = temp->next;
//     }
// }
int check_built_in(char **av, t_shell *data)
{
    if (ft_strncmp(av[0], "exit", 5) == 0)
        return(exit_shell(av, data), 1);
    else if(ft_strncmp(av[0], "env", 4) == 0)
        return(our_env(data->envir), 1);
    else if(ft_strncmp(av[0], "unset", 6) == 0)
        return(our_unset(av[1], &data->envir), 1);
    else if(ft_strncmp(av[0], "echo", 5) == 0)
        return(our_echo(av, data), 1);
    else if(ft_strncmp(av[0], "export", 7)== 0)
        return(our_export(av, data), 1);
    else if(ft_strncmp(av[0], "pwd", 4) == 0)
    {
        if(av[1] != NULL)
        {
            write(2, "pwd: too many arguments\n", 24);
            return(1);
            //echo $?// data->exit_code = 1
        }
        else    
            return(our_pwd(), 1);
    }
    else if(ft_strncmp(av[0], "cd", 3) == 0)
        return(our_cdir(av[1], data), 1);
    // else if(ft_strncmp(av[0], "user_set", 9) == 0) //REMOVE LATER, IT IS JUST FOR TESTING USER_SET VARIABLES
    //     return(prit_user_set(data), 1);
    return(-1);
}

void check_args(char **av, t_shell *data)
{
    int check;

    check = check_built_in(av, data);
    // if (check == -1)
    //     check = user_set(av, data);
}
// strdup the content so when u unset you free and set to NULL
void init_shell(t_shell *data, char **envp)
{
    t_list *new_node;
    int i;

    data->envi = envp;
    data->envir = NULL;
    // data->user_set = NULL;
    data->our_args = NULL;
    data->exit_code = 0;

    i = 0;
    if (envp)
    {   
        while(envp[i])
        {
            new_node = ft_lstnew(ft_strdup(envp[i]));
            if(!new_node)
            {
                write(2, "error malloc\n", 13);
                return ;
            }
            if(new_node)
                ft_lstadd_back(&data->envir, new_node);
            i++;
        }
    }
}

int main(int ac, char **av, char **envp)
{
    t_shell data;
    char *line;
    (void)ac;
    int i = 0;
    (void)envp;
    (void)av;
    //t_token *tokens;
    //int j = 0;
    t_toklist *tokens;
    t_toklist *tmp;

    init_shell(&data, envp);
    while(1)
    {
        i = 0;
        line = readline("minishell♣\n");
        // if(ft_strncmp(line, "exit", 4) == 0)
        // {
        //     free(line);
        //     exit(0);
        // }
        if(!line)
            exit(1);
        printf("\nbefore_trim - {%s}\n", line);
        av = our_tokenize(line);
        while(av[i])
        {
            printf("%d - [%s]\n", i + 1, av[i]);
            i++;
        }
        i--;
        //tokens = array_to_token_array(av, i);
        tokens = array_token_list(av, i);
        tmp = tokens;
        while(tmp)
        {
            printf("token: %s, type: %d\n", tmp->token, tmp->type);
            tmp = tmp->next;
        }
        // while(tokens[j].token)
        // {
        //     printf("hello\n");
        //     printf("token: %s, type:%d\n", (char *)tokens[j].token, (int)tokens[j].type);
        //     j++;
        // }
        if (av && av[0])
            check_args(av, &data);
        if(line)
            add_history(line);
        free(line);
        //we need clean everything before next line the allocations
    }
    return(0);
}

///// if (s[0] = -)
/// num= ft_atoi2(s)
//if 
//    dasdasd dsad s | " "      