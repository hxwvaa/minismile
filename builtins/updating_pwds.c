#include "../minishell.h"

int del_dir(char *path, char *prevdir, t_shell *data)
{
    char *pwd;
    char *fullpath;

    write(2,
        "cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n",
        108); // try using perror("getcwd")
    pwd = ft_strjoin(prevdir, "/");
    if(!pwd)
        return(free(prevdir),  -1);
    fullpath = ft_strjoin(pwd, path);
    free(pwd);
    if(!fullpath)
        return(free(prevdir), -1);
    if (update_pwd(data, fullpath) == -1)
        return(free(fullpath), free(prevdir), -1);
    if (update_oldpwd(data, prevdir) == -1)
        return(free(fullpath), free(prevdir), -1);
    free(fullpath);
    free(prevdir);
    return (0);
}

int update_existing(t_list *current, char *str, int flag)
{
    char *new;
    
    new = NULL;
    if(flag == 1)
        new = ft_strjoin("PWD=", str);
    else if(flag == 2)
        new = ft_strjoin("OLDPWD=", str);
    if(!new)
        return(perror("malloc"), -1);
    free(current->content);
    current->content = new;
    return(0);
}

int update_pwd(t_shell *data, char *pwd)
{
    t_list *current;
    int found;

    found = 0;
    current = data->envir;
    while(current)
    {
        if(ft_strncmp(current->content, "PWD=", 4) == 0)
        {
            found = 1;
            if(update_existing(current, pwd, 1) == -1)
                return(-1);
            break;
        }
        current=current->next;
    }
    if(found == 0)
    {
        if(data->backup_pwd)
            free(data->backup_pwd);
        data->backup_pwd = ft_strdup(pwd);
        if(!data->backup_pwd)
            return(perror("malloc"), -1);
    }
    return (0);
}


int add_new(t_shell *data, char *oldpwd)
{
    t_list *new;
    char *old;

    old = ft_strjoin("OLDPWD=", oldpwd);
    if(!old)
        return(perror("malloc"), -1);
    new = ft_lstnew(old);
    if(!new)
        return(perror("malloc"), free(old), -1);
    ft_lstadd_back(&data->envir, new);
    return (0);
}

int update_oldpwd(t_shell *data, char *oldpwd)
{
    t_list *current;
    int found;

    found = 0;
    current = data->envir;
    while(current)
    {
        if(ft_strncmp(current->content, "OLDPWD=", 7) == 0)
            {
                if(update_existing(current, oldpwd, 2) == -1)
                    return(-1);
                found = 1;
                break ;
            }
        current = current->next;
    }
    if(!found)
        return(add_new(data, oldpwd));
    return (0);
}
