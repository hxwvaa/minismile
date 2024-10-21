#include "../minishell.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void our_cdir(char *path)
{
    int i;

    i = 0;
    char    pwd[1024];

    if(getcwd(pwd, sizeof(pwd)) == NULL)
    {
        write(2, "pwd: Path too long\n", 19);
    
    }
    printf("%s\n", pwd);
    i = chdir(path);
    if(i == -1)
    {
        write(2, "cd: ", 4);
        write(2, path, ft_strlen(path));
        write(2, ": No such file or directory\n", 28);
        // set variable to echo $? to 1;
        exit(1);
    }
    if(getcwd(pwd, sizeof(pwd)) == NULL)
    {
        write(2, "pwd: Path too long\n", 19);
    }
    printf("%s\n", pwd);
}

int main(int ac, char **av)
{
    //(void)ac;
    //int i;

    if(ac > 2)
    {
        if(ft_strncmp(av[1], "cd", 2) == 0)
            our_cdir(av[2]);
    else
        printf("\n");
    }
    else
        printf("\n");
}
