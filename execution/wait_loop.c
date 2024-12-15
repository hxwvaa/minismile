/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:07:54 by mshaheen          #+#    #+#             */
/*   Updated: 2024/12/15 17:07:59 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_exit_code_last(t_shell *data, int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			data->exit_code = 130;
			g_signo = 0;
		}
		else if (WTERMSIG(status) == SIGSEGV)
		{
			write(2, "Segmentation fault: 11\n", 23);
			data->exit_code = 139;
		}
		else if (WTERMSIG(status) == SIGQUIT)
		{
			write(2, "Quit: 3\n", 8);
			data->exit_code = 131;
		}
	}
	else
		data->exit_code = WEXITSTATUS(status);
}

void	set_exit_code_others(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			g_signo = 0;
		}
		else if (WTERMSIG(status) == SIGSEGV)
		{
			write(2, "Segmentation fault: 11\n", 23);
		}
	}
}

void	wait_loop(t_shell *data, int status, pid_t pid)
{
	while (1)
	{
		pid = wait(&status);
		if (pid == -1)
			break ;
		set_exit_code_others(status);
		if (pid == data->lpid)
		{
			set_exit_code_last(data, status);
		}
	}
}
