/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 10:20:13 by mshaheen          #+#    #+#             */
/*   Updated: 2024/12/15 18:11:15 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	empty_pipe_input(int *input)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	close(pipefd[1]);
	*input = pipefd[0];
	return (0);
}

int	handle_heredoc(t_redir *temp, int *input, int *output, t_shell *data)
{
	int	hdpipe[2];
	int	len;

	if (*input != STDIN_FILENO && *input != -1)
		close(*input);
	if (pipe(hdpipe) == -1)
		free_exec_fail(data, input, output, 1);
	if (temp->hd_input == NULL)
		return (close(hdpipe[1]), *input = hdpipe[0], 0);
	len = ft_strlen(temp->hd_input);
	if (len > 65536)
	{
		write(2, "hd input too large\n", 19);
		close(hdpipe[1]);
		*input = hdpipe[0];
	}
	else
	{
		write(hdpipe[1], temp->hd_input, len);
		close(hdpipe[1]);
	}
	free(temp->hd_input);
	temp->hd_input = NULL;
	*input = hdpipe[0];
	return (0);
}

int	handle_redir_in(t_redir *temp, int *input, int *output, t_cmd *curr)
{
	if (*input != STDIN_FILENO && *input != -1)
		close(*input);
	*input = open(temp->file, O_RDONLY);
	if (*input == -1)
	{
		perror(temp->file);
		if (empty_pipe_input(input) == -1)
			return (-2);
		if (*output != STDOUT_FILENO && *output != -1)
		{
			close(*output);
			*output = -1;
		}
		curr->redir_out = 0;
		return (-1);
	}
	return (0);
}

int	handle_redir_out(t_redir *temp, int *output, int *input, t_cmd *curr)
{
	if (*output != STDOUT_FILENO && *output != -1)
		close(*output);
	if (temp->flag == 1)
		*output = open(temp->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (temp->flag == 3)
		*output = open(temp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	curr->redir_out = 1;
	if (*output == -1)
	{
		perror(temp->file);
		if (*input != STDIN_FILENO && *input != -1)
			close(*input);
		curr->redir_out = 0;
		return (-1);
	}
	return (0);
}

int	process_redir(t_cmd *curr, int *input, int *output, t_shell *data)
{
	t_redir	*temp;
	int		i;

	i = 0;
	temp = curr->redirs;
	while (temp)
	{
		if (temp->flag == 2)
			handle_heredoc(temp, input, output, data);
		else if (temp->flag == 0)
		{
			i = handle_redir_in(temp, input, output, curr);
			if (i == -1)
				return (i);
			if (i == -2)
				free_exec_fail(data, input, output, 1);
		}
		else if (temp->flag == 1 || temp->flag == 3)
		{
			if (handle_redir_out(temp, output, input, curr) == -1)
				return (-1);
		}
		temp = temp->next;
	}
	return (0);
}
