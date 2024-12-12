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

char *export_var (char *arg)
{
    int i;
    char *new_s;

    i = 0;
    while(arg[i] && arg[i] != '=')
        i++;

    new_s = malloc(i + 1);
    if (!new_s)
        return(NULL);
    i = 0;
    while(arg[i] && arg[i] != '=')
    {
        new_s[i] = arg[i];
        i++;
    }
    new_s[i] = '\0';
    return(new_s);
}

int check_exp_ident(char *arg)
{
    int i;
    char *b_equal;
    int flag;

    i = 0;
    flag = 0;
    b_equal = export_var(arg);
    printf("\nb_equal: %s\n", b_equal);
    if (!b_equal)
        return (write(2, "error malloc\n", 13), -1); // 
    if(!ft_isalpha(b_equal[i]) && b_equal[i] != '_')
        flag = 1;
    i++;
    while(b_equal[i] && flag == 0)
    {
        if(!ft_isalnum(b_equal[i]) && b_equal[i] != '_')
            flag = 1;
        i++;
    }
    if (flag == 1)
    {
        printf("minishell: export: `%s': not a valid identifier\n", arg);
        free(b_equal);
        return (1);
    }
    return(0);
}   

bool if_equal(char *arg, t_list *current, char *key, int *found)
{
    int varl;
    int chevk;
    
    varl = (int)(key - arg);

    chevk = check_exp_ident(arg);
    if(chevk == 1)
        return (false);
    if(chevk == -1)
        return (false);//return errno instead
    while(current)
    {
        if(ft_strncmp(current->content, arg, varl + 1) == 0)
        {
            free(current->content);
            current->content = ft_strdup(arg);
            if(!current->content)
            {
                write(2, "error malloc\n", 13);
                return (false);
            }
            *found = 1;
            break ;
        }
        current = current->next;
    }
    return(true);
}

bool if_not_equal(char *arg, t_list *current, int *found)
{
    int chevk;

    chevk = check_exp_ident(arg);
    if(chevk == 1)
        return (false);
    if(chevk == -1)
        return (false); // return errno instad

    while(current)
    {
        if(ft_strncmp(current->content, arg, ft_strlen(arg) + 1) == 0)
        {
            if(ft_strlen(current->content) == ft_strlen(arg))
            {
                free(current->content);
                current->content = ft_strdup(arg);
                if(!current->content)
                {
                    write(2, "error malloc\n", 13);
                    return (false);
                }
                *found = 1;
                break ;
            }
            else
                *found = 1;
        }
        current = current->next;
    }
    return(true);
}

// bool our_export_extend(char **arg, t_shell *data)
// {
    
// }

bool our_export(char **arg, t_shell *data, int i)
{
    t_list *current;
    t_list *new;
    char *key;
    int found;

    if(!arg[1]) // if export with no args, print export list
        return (our_expenv(data), true);
    while(arg[++i])
    {
        current = data->envir;
        found = 0;
        key = ft_strchr(arg[i], '=');
        if(key && !if_equal(arg[i], current, key, &found))
            return(false);
        else if(!key && !if_not_equal(arg[i], current, &found))
            return(false);
        if(!found)
        {
            new = ft_lstnew(ft_strdup(arg[i])); 
            if(!new)
                return (write(2, "error malloc\n", 13), false);
            ft_lstadd_back(&data->envir, new);
        }
    }
    return true;
}
