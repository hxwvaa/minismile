/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbasheer <hbasheer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:52:20 by hbasheer          #+#    #+#             */
/*   Updated: 2024/12/17 18:52:21 by hbasheer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_value_env(char *var, t_shell *data)
{
	t_list	*current;
	char	*str;
	char	*res;

	current = data->envir;
	while (current)
	{
		if (ft_strncmp(current->content, var, (ft_strlen(var))) == 0)
		{
			str = ft_strdup(current->content + ft_strlen(var));
			if (!str)
				return (NULL);
			res = ft_strdup(str);
			free(str);
			if (!res)
				return (NULL);
			return (res);
		}
		current = current->next;
	}
	return (NULL);
}

char	*get_pwd_value(t_shell *data)
{
	char	*pwd;
	char	*res;

	pwd = get_value_env("PWD=", data);
	if (pwd)
	{
		res = ft_strdup(pwd);
		free(pwd);
		if (!res)
			return (NULL);
		return (res);
	}
	if (data->backup_pwd)
		return (ft_strdup(data->backup_pwd));
	return (NULL);
}

char	*get_curr_pwd(void)
{
	char	pwd[1024];

	if (getcwd(pwd, sizeof(pwd)) == NULL)
		return (NULL);
	return (ft_strdup(pwd));
}

char	*our_pwd_help(t_shell *data)
{
	char	pwd[1024];
	char	*env_pwd;
	char	*res;

	if (getcwd(pwd, sizeof(pwd)) != NULL)
	{
		if (data->backup_pwd)
			free(data->backup_pwd);
		data->backup_pwd = ft_strdup(pwd);
		if (!data->backup_pwd)
			return (NULL);
		return (ft_strdup(pwd));
	}
	env_pwd = get_value_env("PWD=", data);
	if (env_pwd)
	{
		res = ft_strdup(env_pwd);
		free(env_pwd);
		if (!res)
			return (NULL);
		return (res);
	}
	if (data->backup_pwd)
		return (ft_strdup(data->backup_pwd));
	return (NULL);
}

bool	our_pwd(t_shell *data)
{
	char	*pwd;

	pwd = our_pwd_help(data);
	if (!pwd)
	{
		if (errno == ENOMEM)
			write(2, "malloc error\n", 13);
		else
			write(2, "pwd: Path too long\n", 19);
		return (true);
	}
	if (write(STDOUT_FILENO, pwd, ft_strlen(pwd)) < 0)
		return (free(pwd), true);
	if (write(STDOUT_FILENO, "\n", 1) < 0)
		return (free(pwd), true);
	free(pwd);
	return (false);
}
