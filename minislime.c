#include "minishell.h"

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void check_built_in(char **av, t_shell *data)
{
    int i;

    i = 0;
    if (ft_strncmp(av[i], "exit", 5) == 0)
        exit_shell(av);
    else if(ft_strncmp(av[i], "env", 3) == 0)
        our_env(data->envir);
    else if(ft_strncmp(av[i], "unset", 5) == 0)
        our_unset(av[i + 1], &data->envir);
    else if(ft_strncmp(av[i], "echo", 4) == 0)
        our_echo(av);
    else if(ft_strncmp(av[i], "export", 6)== 0)
        our_export(av, data);
    else if(ft_strncmp(av[i], "pwd", 3) == 0)
        our_pwd();
    else if(ft_strncmp(av[i], "cd", 2) == 0)
        our_cdir(av[i + 1], data);

}

void check_args(char **av, t_shell *data)
{
    // int i;

    // i = 0;

    check_built_in(av, data);

}
// strdup the content so when u unset you free and set to NULL
void init_shell(t_shell *data, char **envp)
{
    t_list *new_node;
    int i;

    data->envi = envp;
    data->envir = NULL;
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