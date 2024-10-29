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
    t_list *current;
    t_list *new;
    char *key;
    int varl;
    int found;

    i = 1;
    //found = 0;
    if(!arg[i]) // if export with no args, print export list
    {
        our_expenv(data);
        return (true);
    }
    else
    {
        current = data->envir;
        while(arg[i])
        {
            found = 0;
            key = ft_strchr(arg[i], '=');
            if(key)
            {
                varl = (int)(key - arg[i]);
                while(current)
                {
                    if(ft_strncmp(current->content, arg[i], varl) == 0)
                    {
                        free(current->content);
                        current->content = ft_strdup(arg[i]);
                        if(!current->content)
                        {
                            write(2, "error malloc\n", 13);
                            return (false);
                        }
                        found = 1;
                        break ;
                    }
                    current = current->next;
                }
            }
            else if(!key)
            {
                while(current)
                {
                    if(ft_strncmp(current->content, arg[i], ft_strlen(arg[i])) == 0)
                    {
                        free(current->content);
                        current->content = ft_strdup(arg[i]);
                        if(!current->content)
                        {
                            write(2, "error malloc\n", 13);
                            return (false);
                        }
                        found = 1;
                        break ;
                    }
                    current = current->next;
                }
            }
            
            if(!found)
            {
                new = ft_lstnew(ft_strdup(arg[i]));
                if(!new)
                {
                    write(2, "error malloc\n", 13);
                    return false ;
                }
                ft_lstadd_back(&data->envir, new);
            }
            i++;
        }
    }
    return true;
}
