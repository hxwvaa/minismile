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

void unset_loop(t_list **current, char *var, t_list *prev, t_list **envir)
{
    while((*current))
    {
        if(ft_strncmp((*current)->content, var, len_b4_eq((*current)->content)) == 0)
        {
            if(prev == NULL)
                *envir = (*current)->next;
            else
                prev->next = (*current)->next;
            free((*current)->content);
            (*current)->content = NULL;
            free(*current);
            *current = NULL;
            return ;
        }
        prev = (*current);
        (*current) = (*current)->next;
    }
}

bool our_unset(char **var, t_list **envir)
{
    t_list *current;
    t_list *prev;
    t_list *temp;
    int i;

    if(!var[1])
        return (false);
    temp = *envir;
    current = *envir;
    prev = NULL;
    i = 1;
    while(var[i])
    {
        unset_loop(&current, var[i], prev, envir);
        prev = NULL;
        current = temp;
        i++;
    }
    return (false);
}
