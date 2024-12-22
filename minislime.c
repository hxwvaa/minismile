/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minislime.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbasheer <hbasheer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:10:36 by hbasheer          #+#    #+#             */
/*   Updated: 2024/12/19 15:10:36 by hbasheer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

int		g_signo = 0;

int	count_cargs(t_cmd *cmd)
{
	int		i;
	t_cmd	*temp;

	i = 0;
	temp = cmd;
	while (temp->cargs[i])
		i++;
	return (i);
}

void	init_pwd(t_shell *data)
{
	char	pwd[1024];

	if (getcwd(pwd, sizeof(pwd)) != NULL)
	{
		data->backup_pwd = ft_strdup(pwd);
		if (!data->backup_pwd)
		{
			perror("malloc");
			exit(1);
		}
	}
	else
	{
		perror("getcwd");
	}
}

void	init_shell_help(t_shell *data)
{
	data->envi = NULL;
	data->line = NULL;
	data->backup_pwd = NULL;
	data->envir = NULL;
	data->our_args = NULL;
	data->exit_code = 0;
	data->tokens = NULL;
	data->cmds = NULL;
	data->fd[0] = -1;
	data->fd[1] = -1;
	data->std[0] = -1;
	data->std[1] = -1;
	data->cmd_path = NULL;
	data->lpid = -1;
	data->pid = -1;
}

void	init_shell(t_shell *data, char **envp)
{
	t_list	*new_node;
	int		i;

	i = 0;
	init_shell_help(data);
	init_pwd(data);
	if (envp)
	{
		while (envp[i])
		{
			new_node = ft_lstnew(ft_strdup(envp[i]));
			if (!new_node)
			{
				write(2, "error malloc\n", 13);
				free_exec_fail(data, NULL, NULL, 12);
			}
			if (new_node)
				ft_lstadd_back(&data->envir, new_node);
			i++;
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell	data;

	(void)av;
	if (ac > 1)
		return (write(2, "minishell: too many arguments\n", 31), 1);
	init_shell(&data, envp);
	read_loop(&data);
	return (0);
}
