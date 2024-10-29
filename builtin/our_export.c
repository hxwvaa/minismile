#include "../minishell.h"

//i should create a new list for export, because if you export arg without an '='
//it shows in the export list but not in the environment
//also export list have the values(what comes after '=') of the variables in double quotes//write export to see
//declare -x SHELL="/bin/zsh"  declare -x USER="mshaheen" these are two examples
// void print_exenv(t_shell *data)
// {
//     //print exported env
//     t_list *curr;
        
//         curr = data->envir;
//         while(curr)
//         {
//             printf("declare -x %s\n", (char *)curr->content);
//             curr = curr->next;
//         }
// }

// bool our_export(char **arg, t_list **envir)
// {
//     // if(!var || !ft_strchr(var, '='))
//     // {
//     //     write(2, "export: wrong format")
//     // }
//     int i;

//     i = 1;
//     if(!arg[i]) // if export with no args
//     {
//         our_expenv(&data);
//     }
//     else
//     while(arg[i])
//     {

//     }
// }

bool our_export(char **arg, t_shell *data)
{
    int i;

    i = 1;
    if(!arg[i]) // if export with no args, print export list
    {
        our_expenv(&data);
    }
    else
    {
        while(arg[i])
        {
            
        }
    }
}