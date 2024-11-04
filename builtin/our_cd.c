#include "../minishell.h"

void change_dir()

void our_cdir(char *path, t_shell *data)
{
    int i;
    char *curdir;
    char *prevdir;
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
    curdir = 
    i = chdir(path);
    if(i == -1)
    {
        write(2, "cd: ", 4);
        write(2, path, ft_strlen(path));
        write(2, ": No such file or directory\n", 28);
        // set variable to echo $? to 1;
        exit(1);
    }
}
