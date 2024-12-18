/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 10:20:06 by mshaheen          #+#    #+#             */
/*   Updated: 2024/12/18 20:21:43 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reset_stds(t_shell *data)
{
	if (dup2(data->std[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		free_all(data);
		exit(errno);
	}
	if (dup2(data->std[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		free_all(data);
		exit(errno);
	}
	if (data->std[0] != -1)
	{
		close(data->std[0]);
		data->std[0] = -1;
	}
	if (data->std[1] != -1)
	{
		close(data->std[1]);
		data->std[1] = -1;
	}
}

void	execute_one_builtin(t_cmd *curr, t_shell *data, int *input, int *output)
{
	set_redirection(curr, data, input, output);
	execute_one_cmd(curr, data);
}

void	our_execution(t_shell *data, int input, int output, t_cmd *curr)
{
	while (curr)
	{
		if (process_redir(curr, &input, &output, data) == -1)
		{
			data->exit_code = 1;
			curr = curr->next;
			continue ;
		}
		if (curr->em_expand)
		{
			data->exit_code = 0;
			curr = curr->next;
			continue ;
		}
		if (curr->next && pipe(data->fd) == -1)
			free_exec_fail(data, &input, &output, 1);
		if (is_builtin(curr->cmd) && only_one_cmd(data->cmds) == 1)
			execute_one_builtin(curr, data, &input, &output);
		else
			fork_execute_child(data, curr, &input, &output);
		curr = curr->next;
	}
	close_clean(data, input, output);
}

void	dup_std_envi(t_shell *data)
{
	data->std[0] = dup(STDIN_FILENO);
	data->std[1] = dup(STDOUT_FILENO);
	if (data->std[0] == -1 || data->std[1] == -1)
	{
		perror("dup");
		free_all(data);
		exit(errno);
	}
	data->envi = envlist_envarray(data->envir);
	if (!data->envi)
	{
		perror("malloc");
		free_all(data);
		exit(errno);
	}
}

void	free_lists_line(t_shell *data)
{
	if (data->line)
		add_history(data->line);
	if (data->tokens)
	{
		our_toklistclear(&data->tokens);
		data->tokens = NULL;
	}
	if (data->cmds)
	{
		our_cmdlistclear(&data->cmds);
		data->cmds = NULL;
	}
	free(data->line);
	data->line = NULL;
}

void	pre_execute(t_shell *data, int input, int output)
{
	int		status;
	int		check;
	pid_t	pid;
	t_cmd	*curr;

	curr = data->cmds;
	status = 0;
	pid = 0;
	check = process_heredoc(data->cmds, data);
	if (check == 12 || check == -1)
	{
		if (check == 12)
		{
			free_all(data);
			exit(errno);
		}
		data->exit_code = 130;
		g_signo = 0;
		return ;
	}
	dup_std_envi(data);
	our_execution(data, input, output, curr);
	wait_loop(data, status, pid);
	reset_stds(data);
	free_lists_line(data);
}
