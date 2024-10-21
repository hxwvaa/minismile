#include "../minishell.h"

void our_cdir(char *path)
{
    int i;

    i = 0;
    char    pwd[1024];

 
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
