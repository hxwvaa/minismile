#include "../minishell.h"

char *get_pwd(void)
{
    char    pwd[1024];

    if(getcwd(pwd, sizeof(pwd)) == NULL)
    {
        write(2, "pwd: Path too long\n", 19);
        return(NULL);
    }
    return(ft_strdup(pwd));
}

bool our_pwd(void)
{
    char    pwd[1024];

    if(getcwd(pwd, sizeof(pwd)) == NULL)
    {
        write(2, "pwd: Path too long\n", 19);
        return(false);
    }
    printf("%s\n", pwd);
    return(true);
}
