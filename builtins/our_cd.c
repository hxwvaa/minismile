#include "../minishell.h"


//check it later it works

int change_dir_help(char *path, char *prevdir, t_shell *data)
{
    char *curdir;

    curdir = get_curr_pwd();
    if(!curdir)
        return(del_dir(path, prevdir, data));
    if (update_pwd(data, curdir) == -1)
    {
        free(curdir);
        free(prevdir);
        return(-1);
    }
    if (update_oldpwd(data, prevdir) == -1)
    {
        free(curdir);
        free(prevdir);
        return(-1);
    }
    free(curdir);
    free(prevdir);
    return (0);
}

int change_dir(char *path, t_shell *data)
{
    char *prevdir;

    prevdir = get_pwd_value(data);
    if(!prevdir)
         return (-1);
    if(chdir(path) == -1)
    {
        write(2, "cd: ", 4);
        write(2, path, ft_strlen(path));
        write(2, ": No such file or directory\n", 28);
        free(prevdir);
        return (1);
    }
    return (change_dir_help(path, prevdir, data));
}

int handle_home(char **path, char **temp, t_shell *data)
{
    *path = get_value_env("HOME=", data);
    if(!*path)
    {
        if(errno == ENOMEM)
        {
            free_all(data);
            exit(errno); // call free_all function before exiting
        }
        write(2, "cd : HOME is not set\n", 21);
        return (1);
    }
    *temp = *path;
    return (0);
}

int handle_flag(char **path, char **temp, t_shell *data)
{
   if(ft_strncmp(*path, "-", 2) == 0)
    {
        *path = get_value_env("OLDPWD=", data);
        if(!*path)
        {
            if(errno == ENOMEM)
                exit(errno); // call free_all function before exiting
            write(2, "cd : OLDPWD is not set\n", 23);
            return (1);
        }
        printf("%s\n", *path);
        *temp = *path;
        return (0);
    }
    else // check on mac bash 
    {
        write(2, "cd: ", 5);
        write(2, *path, ft_strlen(*path));
        write(2, " invalid option\n", 16);
        return (1); // maybe 1 here instead of 2
    }
}

int our_cdir(char *path, t_shell *data)
{
    char *temp;
    int ret;

    temp = NULL;
    if(!path)
    {
        ret = handle_home(&path, &temp, data);
        if(ret != 0)
            return (ret);
    }
    else if (path[0] == '-')
    {
        ret = handle_flag(&path, &temp, data);
        if (ret != 0)
            return (ret);
    }
    ret = change_dir(path, data);
    if(temp)
        free(temp);
    if (ret == -1)
    {
        if(errno == ENOMEM)
            exit(errno); // call free_all function before exiting
    }
    return (ret);
}

