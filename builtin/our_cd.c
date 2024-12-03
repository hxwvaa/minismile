#include "../minishell.h"


//check it later it works

char *get_value_env(char *var, t_shell *data)
{
    t_list *current;

    current = data->envir;
    while(current)
    {
        if(ft_strncmp(current->content, var, (ft_strlen(var))) == 0)
        {
            if(((char *)current->content)[5] == '\0') //what is this for ? 
                return(get_pwd());
            return(ft_strdup(current->content + 5)); // ??
        }
        current = current->next;
    }
    return (NULL);
}

char *get_pwd_value(t_shell *data)
{
    t_list *current;

    current = data->envir;
    while(current)
    {
        if(ft_strncmp(current->content, "PWD=", 4) == 0)
            return(ft_strdup(current->content + 4));
        current = current->next;
    }
    return (NULL);
}

void update_pwd(t_shell *data, char *pwd)
{
    t_list *current;

    current = data->envir;
    while(current)
    {
        if(ft_strncmp(current->content, "PWD=", 4) == 0)
        {
            free(current->content);
            //current->content = ft_strdup(pwd);
            current->content = ft_strjoin("PWD=", pwd);
            //free(pwd);
            break;
        }
        current=current->next;
    }
}
void update_oldpwd(t_shell *data, char *oldpwd)
{
    t_list *current;
    t_list *new;
    int found;

    found = 0;
    current = data->envir;
    while(current)
    {
        if(ft_strncmp(current->content, "OLDPWD=", 7) == 0)
            {
                free(current->content);
                current->content = ft_strjoin("OLDPWD=", oldpwd);
                found = 1;
                //free(oldpwd);
                break ;
            }
        current = current->next;
    }
    if(!found)
    {
        new = ft_lstnew(ft_strjoin("OLDPWD=", oldpwd));
        if(!new)
        {
            write(2, "error malloc\n", 13);
            return ;
        }
        ft_lstadd_back(&data->envir, new);
        //free(oldpwd);
    }
}



void change_dir(char *path, t_shell *data)
{
    int i;
    char *curdir;
    char *prevdir;
    char *pwd;
    //char *oldpwd;

    i = 0;
    //maybe i need to move this down after chdir because i get stuck
    //inside a unfound directory
    prevdir = get_pwd_value(data);
    if(!prevdir)
         return ; // or remove return
    i = chdir(path);
    if(i == -1)
    {
        write(2, "cd: ", 4);
        write(2, path, ft_strlen(path));
        write(2, ": No such file or directory\n", 28);
        free(prevdir);
        return ;
        // set variable to echo $? to 1;
        //exit(1);
    }
    curdir= get_pwd();
    printf("after\n");
    if(!curdir)
    {
        write(2,
		 	"cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n",
		 	108);
        pwd = ft_strjoin(prevdir, "/");
        
        update_pwd(data, ft_strjoin(pwd, path));
        update_oldpwd(data, prevdir);
        free(pwd);
        free(prevdir);
        return ;
    }
    // oldpwd = ft_strjoin("OLDPWD=", prevdir);
    // pwd = ft_strjoin("PWD=", curdir);
    // if(!pwd || !oldpwd)
    //     return ;
    printf("before updating pwd&old\n");
    update_pwd(data, curdir);
    update_oldpwd(data, prevdir);
    free(curdir);
    free(prevdir);
    // update_pwd(data, pwd);
    // update_oldpwd(data, oldpwd);

}

void our_cdir(char *path, t_shell *data)
{
//     int i;
//     i = 0;
    //char    pwd[1024];

    if(!path)
    {
        //path = getenv("HOME");
        path = get_value_env("HOME=", data);
        if(!path)
        {
            write(2, "cd : HOME is not set\n", 21);
            //data->exit_code = 1;
            return ;
        }
    }
    printf("inside cd before cd\n");

    // get_value_env ain't getting_the_value_env
    
    // if (path[0] == '-')    
    // {
    //     path = get_value_env("OLDPWD=", data);
    //     if(!path)
    //     {
    //         write(2, "cd : OLDPWD is not set\n", 23);
    //         data->exit_code = 1;
    //         return ;
    //     }
    // }
    // printf("\n%s\n", path);


    change_dir(path, data);
    // maybe add a case for if path is '..'


    // prevdir = our_pwd();
    // i = chdir(path);
    // if(i == -1)
    // {
    //     write(2, "cd: ", 4);
    //     write(2, path, ft_strlen(path));
    //     write(2, ": No such file or directory\n", 28);
    //     // set variable to echo $? to 1;
    //     exit(1);
    // }
    // curdir= our_pwd(); 

}

