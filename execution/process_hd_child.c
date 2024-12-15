/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_hd_child.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:27:57 by mshaheen          #+#    #+#             */
/*   Updated: 2024/12/15 18:28:13 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	hd_clean_exit(int exit_code, int flag, int pipefd[], t_shell *data)
{
	if (flag == 1)
	{
		perror("pipe");
		our_cmdlistclear(&data->cmds);
		our_envlistclear(&data->envir);
		our_toklistclear(&data->tokens);
	}
	if (flag == 2)
	{
		perror("fork");
		if (pipefd[0] != -1)
			close(pipefd[0]);
		if (pipefd[1] != -1)
			close(pipefd[1]);
		our_cmdlistclear(&data->cmds);
		our_envlistclear(&data->envir);
		our_toklistclear(&data->tokens);
	}
	exit(exit_code);
}

void	handle_hd_sig(int signo)
{
	if (signo == SIGINT)
	{
		g_signo = signo;
		close(STDIN_FILENO);
		return ;
	}
}

void	signal_hd(int signo)
{
	g_signo = signo;
}

void	hd_exit_child(char *line, int fd, int exit_code, t_shell *data)
{
	close(fd);
	if (line)
		free(line);
	if (data->backup_pwd)
	{
		free(data->backup_pwd);
		data->backup_pwd = NULL;
	}
	our_cmdlistclear(&data->cmds);
	our_envlistclear(&data->envir);
	our_toklistclear(&data->tokens);
	if (exit_code == 64)
	{
		write(2, "here_doc input too large\n", 26);
		exit(0);
	}
	if (exit_code == 130)
		g_signo = 0;
	exit(exit_code);
}

char	*do_heredoc(int fd, char *limit, t_shell *data)
{
	char	*line;
	int		i;

	i = 0;
	line = NULL;
	while (1)
	{
		line = readline(">");
		if (g_signo == SIGINT)
			hd_exit_child(line, fd, 130, data);
		if (!line)
			hd_exit_child(line, fd, 0, data);
		if (ft_strncmp(limit, line, ft_strlen(limit) + 1) == 0)
			hd_exit_child(line, fd, 0, data);
		line = expand_hd(line, data, 0);
		if (!line)
			hd_exit_child(line, fd, errno, data);
		i += ft_strlen(line) + 1;
		if (i > 65536)
			hd_exit_child(line, fd, 64, data);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	exit(0);
}
