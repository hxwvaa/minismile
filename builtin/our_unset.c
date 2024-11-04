#include "../minishell.h"


// bool our_unset(char *var, t_list **envir)
// {
//     if(!var)
//     {
//         write(2, "unset: not enough arguments\n", 28);
//         //data->exit_code = 1
//         return (false);
//     }
//     t_list *current;
//     t_list *prev;
//     int len;

//     current = *envir;
//     prev = NULL;
//     len = ft_strlen(var);
//     while(current)
//     {
//         if(ft_strncmp(current->content, var, len) == 0)
//         {
//             if(prev == NULL)
//                 *envir = current->next;
//             else
//                 prev->next = current->next;
//             free(current->content);
//             free(current); 
//             return(true);
//         }
//         prev = current;
//         current = current->next;
//     }
// }

// it should be char **arg instead of var because it can have x number of args
//or i can check but the calling of this function in a while loo
// i think i might need to remove the error message
bool our_unset(char *var, t_list **envir)
{
    if(!var)
    {
        write(2, "unset: not enough arguments\n", 28);
        //data->exit_code = 1
        return (false);
    }
    t_list *current;
    t_list *prev;
    int len;

    current = *envir;
    prev = NULL;
    len = ft_strlen(var);
    printf("%s, len:%d\n", var, len);
    while(current)
    {
        if(ft_strncmp(current->content, var, len) == 0)
        {
            if(prev == NULL)
                *envir = current->next;
            else
                prev->next = current->next;
            //printf("%s\n", current->content);
            free(current->content);
            free(current); 
            return(true);
        }
        prev = current;
        current = current->next;
    }
    //free at the end the list
    return (false);
}
