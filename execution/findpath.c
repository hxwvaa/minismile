/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findpath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:24:30 by mshaheen          #+#    #+#             */
/*   Updated: 2024/12/18 17:14:28 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	accessible_p(char **array, char *fp)
{
	if (access(fp, F_OK & X_OK) == 0)
	{
		free_path_array(array);
		return (1);
	}
	return (0);
}

char	*find_in_path(char *cmd, int *input, int *output, t_shell *data)
{
	char	**paths;
	char	*full_path;
	char	*tmp;
	int		i;

	i = 0;
	paths = findsplit_path(data->envi);
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			free_exec_fail(data, input, output, 12);
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!full_path)
			free_exec_fail(data, input, output, 12);
		if (accessible_p(paths, full_path) == 1)
			return (full_path);
		free(full_path);
		i++;
	}
	free_path_array(paths);
	return (NULL);
}

char	*get_cmd_path(char *cmd, int *input, int *output, t_shell *data)
{
	char	*res;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
	}
	res = find_in_path(cmd, input, output, data);
	return (res);
}
