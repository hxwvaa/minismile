/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbasheer <hbasheer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:27:41 by hbasheer          #+#    #+#             */
/*   Updated: 2024/12/19 16:51:22 by hbasheer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_fd_data(t_shell *data)
{
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
	free(data->line);
}

void	free_exec_fail2(t_shell *data, int *input, int *output)
{
	if (data->cmds)
	{
		our_cmdlistclear(&data->cmds);
		data->cmds = NULL;
	}
	if (data->cmd_path)
	{
		free(data->cmd_path);
		data->cmd_path = NULL;
	}
	if (data->backup_pwd)
	{
		free(data->backup_pwd);
		data->backup_pwd = NULL;
	}
	if (input && *input != STDIN_FILENO && *input != -1)
	{
		close(*input);
		*input = -1;
	}
	if (output && *output != STDOUT_FILENO && *output != -1)
	{
		close(*output);
		*output = -1;
	}
}

void	free_exec_fail(t_shell *data, int *input, int *output, int exit_code)
{
	if (data->envi)
	{
		free_arr(data->envi);
		data->envi = NULL;
	}
	if (data->envir)
	{
		our_envlistclear(&data->envir);
		data->envir = NULL;
	}
	if (data->our_args)
	{
		free_arr(data->our_args);
		data->our_args = NULL;
	}
	if (data->tokens)
	{
		our_toklistclear(&data->tokens);
		data->tokens = NULL;
	}
	free_exec_fail2(data, input, output);
	close_fd_data(data);
	exit(exit_code);
}

void	free_all2(t_shell *data)
{
	if (data->cmds)
	{
		our_cmdlistclear(&data->cmds);
		data->cmds = NULL;
	}
	if (data->cmd_path)
	{
		free(data->cmd_path);
		data->cmd_path = NULL;
	}
	if (data->backup_pwd)
	{
		free(data->backup_pwd);
		data->backup_pwd = NULL;
	}
	close_fd_data(data);
}

void	free_all(t_shell *data)
{
	if (data->envi)
	{
		free_arr(data->envi);
		data->envi = NULL;
	}
	if (data->envir)
	{
		our_envlistclear(&data->envir);
		data->envir = NULL;
	}
	if (data->our_args)
	{
		free_arr(data->our_args);
		data->our_args = NULL;
	}
	if (data->tokens)
	{
		our_toklistclear(&data->tokens);
		data->tokens = NULL;
	}
	free_all2(data);
}
