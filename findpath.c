#include "minishell.h"

void	free_path_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	**findsplit_path(char **env)
{
	char	*pathy;
	char	**paths;
	int		i;

	i = 0;
	pathy = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			pathy = env[i] + 5;
			break ;
		}
		i++;
	}
	paths = ft_split(pathy, ':');
	return (paths);
}

int	only_space(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '\0')
		return (1);
	while (s[i] == 32 && s[i])
		i++;
	if (s[i] == '\0')
		return (1);
	return (0);
}

int	accessible_p(char **array, char *fp)
{   
	if (access(fp, X_OK) == 0)
	{
		free_path_array(array);
		return (1);
	}
	return (0);
}

char	*get_cmd_path(char *cmd, char **env)
{
	char	*full_path;
	char	**paths;
	char	*tmp;
	int		i;

	i = 0;
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
	}
	paths = findsplit_path(env);
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i++], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (accessible_p(paths, full_path) == 1)
			return (full_path);
		free(full_path);
	}
	free_path_array(paths);
	return (NULL);
}