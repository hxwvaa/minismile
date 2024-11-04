#include "../minishell.h"

char	*get_pwd(void)
{
	char	pwd[1024];

	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
		// write(2,
		// 	"cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n",
		// 	108);
		// write(2, "pwd: Path too long\n", 19);
		return (NULL);
	}
	return (ft_strdup(pwd));
}

bool	our_pwd(void)
{
	char	pwd[1024];

	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
		write(2, "pwd: Path too long\n", 19);
		return (false);
	}
	printf("%s\n", pwd);
	return (true);
}
