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
    // int i;

    // i = 0;
    t_list *tmp;

    tmp = envir;
    printf("our own env\n");
    while(tmp)
    {
        printf("%s\n", (char *)tmp->content);
        tmp = tmp->next;
    }
}

void our_exenv(t_shell *data, char **envp)
{
    int i;
    int j;
    char *tmp; 
    
    i = 0;
    while(envp)
    {
        j = 0;
        if(ft_strchr(&envp[i][j], '='))
        {
            tmp = &envp[i][j];
            data->envi[i][j] = *ft_strjoin(&envp[i][j], "\"");
            free(tmp);
            while(envp[i][j])
                j++;
            j--;
            tmp = &envp[i][j];
            data->envi[i][j] = *ft_strjoin(&envp[i][j], "\"");
            free(tmp);
        }
        i++;
    }
}
int main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
    t_shell data;

    our_exenv(&data, envp);
    int i =0;
    while(data.envi[i])
        printf("declare -x %s\n", data.envi[i++]);
}