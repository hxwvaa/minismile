#include "../minishell.h"

void update_pwd(t_shell *data, char *pwd)
{
    t_list *current;

    current = data->envir;
    while(current)
    {
        if(ft_strncmp(current->content, "PWD=", 4) == 0)
        {
            //free(current->content);
            current->content = ft_strdup(pwd);
            free(pwd);
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
                //free(current->content);
                current->content = ft_strdup(oldpwd);
                found = 1;
                free(oldpwd);
            }
        current = current->next;
    }
    if(!found)
    {
        new = ft_lstnew(ft_strdup(oldpwd));
        if(!new)
        {
            write(2, "error malloc\n", 13);
            return ;
        }
        ft_lstadd_back(&data->envir, new);
        free(oldpwd);
    }
}



void change_dir(char * path, t_shell *data)
{
    int i;
    char *curdir;
    char *prevdir;
    char *pwd;
    char *oldpwd;

    i = 0;
    //maybe i need to move this down after chdir because i get stuck
    //inside a unfound directory
    prevdir = get_pwd();
    // if(!prevdir)
    //     return ; // or remove return
    printf("hrllo\n");
    i = chdir(path);
    if(i == -1)
    {
        write(2, "cd: ", 4);
        write(2, path, ft_strlen(path));
        write(2, ": No such file or directory\n", 28);
        // set variable to echo $? to 1;
        //exit(1);
    }
    curdir= get_pwd();
    printf("after\n");
    if(!curdir || !prevdir)
        return ;
    oldpwd = ft_strjoin("OLDPWD=", prevdir);
    pwd = ft_strjoin("PWD=", curdir);
    if(!pwd || !oldpwd)
        return ;
    free(curdir);
    free(prevdir);
    update_pwd(data, pwd);
    update_oldpwd(data, oldpwd);

}

void our_cdir(char *path, t_shell *data)
{
    int i;
    i = 0;
    //char    pwd[1024];

    if(!path)
    {
        path = getenv("HOME");
        if(!path)
        {
            write(2, "cd : HOME is not set\n", 21);
            //data->exit_code = 1;
            return ;
        }
    }
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

