/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbasheer <hbasheer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 10:19:55 by mshaheen          #+#    #+#             */
/*   Updated: 2024/12/17 16:43:54 by hbasheer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_clean(t_shell *data, int input, int output)
{
	if (input != STDIN_FILENO && input != -1)
		close(input);
	if (output != STDOUT_FILENO && output != -1)
		close(output);
	if (data->fd[0] != -1)
	{
		close(data->fd[0]);
		data->fd[0] = -1;
	}
	if (data->fd[1] != -1)
	{
		close(data->fd[1]);
		data->fd[1] = -1;
	}
	if (data->envi)
	{
		free_arr(data->envi);
		data->envi = NULL;
	}
}

void	set_redirection(t_cmd *curr, t_shell *data, int *input, int *output)
{
	if (*input != STDIN_FILENO && *input != -1)
	{
		if (dup2(*input, STDIN_FILENO) == -1)
			free_exec_fail(data, input, output, 1);
		close(*input);
		*input = -1;
	}
	if (*output != STDOUT_FILENO && *output != -1)
	{
		if (dup2(*output, STDOUT_FILENO) == -1)
			free_exec_fail(data, input, output, 1);
		close(*output);
		*output = -1;
		if (data->fd[1] != -1)
			close(data->fd[1]);
	}
	else if (curr->next && data->fd[1] != -1)
	{
		if (dup2(data->fd[1], STDOUT_FILENO) == -1)
			free_exec_fail(data, input, output, 1);
		if (data->fd[1] != -1)
			close(data->fd[1]);
		data->fd[1] = -1;
	}
}

void	cleanup_child(t_shell *data, int *input, int *output)
{
	if (data->backup_pwd)
		free(data->backup_pwd);
	if (data->std[0] != -1)
		close(data->std[0]);
	if (data->std[1] != -1)
		close(data->std[1]);
	if (*input != -1)
		close(*input);
	if (*output != -1)
		close(*output);
	if (data->fd[0] != -1)
		close(data->fd[0]);
	if (data->tokens)
		our_toklistclear(&data->tokens);
	if (data->envir)
		our_envlistclear(&data->envir);
	if (data->cmds)
		our_cmdlistclear(&data->cmds);
	if (data->envi)
		free_arr(data->envi);
}

void	execute_child(t_shell *data, t_cmd *curr, int *input, int *output)
{
	set_redirection(curr, data, input, output);
	if (curr->cmd)
	{
		if (data->std[0] != -1)
			close(data->std[0]);
		if (data->std[1] != -1)
			close(data->std[1]);
		if (is_builtin(curr->cmd))
			builtin_pipeline(curr, data);
		if (data->fd[0] != -1)
			close(data->fd[0]);
		if (ft_strchr(curr->cmd, '/') && check_if_directory(curr->cmd))
			invalid_cmd_dir(curr->cmd, input, output, data);
		data->cmd_path = get_cmd_path(curr->cmd, input, output, data);
		if (!data->cmd_path)
			invalid_lstcmd(curr->cmd, input, output, data);
		if (execve(data->cmd_path, curr->cargs, data->envi) == -1)
		{
			perror(data->cmd_path);
			free_exec_fail(data, input, output, 126);
		}
	}
	cleanup_child(data, input, output);
	exit(0);
}

void	fork_execute_child(t_shell *data, t_cmd *curr, int *input, int *output)
{
	signal(SIGINT, SIG_IGN);
	data->pid = fork();
	if (data->pid == -1)
	{
		perror("fork");
		free_exec_fail(data, input, output, 1);
	}
	if (data->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execute_child(data, curr, input, output);
	}
	prepare_fds(input, output, data, curr);
	if (!curr->next)
		data->lpid = data->pid;
}
