/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_hd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 10:53:59 by mshaheen          #+#    #+#             */
/*   Updated: 2024/12/12 21:35:04 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//hamadan gnl
// char *get_file(int fd)
// {
// 	int i = 0;
// 	int byte;
// 	char c;
// 	char *line;
// 	int total;
// 	if (fd < 0)
// 		return (NULL);
// 	if(count_bytes(fd, &total) == -1)
// 		return(NULL);
// 	byte = read(fd, &c, 1);
// 	if (byte == -1)
// 	{
// 		perror("read");
// 		return (NULL);
// 	}
// 	line = ft_calloc(65537, 1);
// 	if (!line)
// 		return (NULL);
// 	while(byte > 0)
// 	{
// 		line[i] = c;
// 		i++;
// 		byte = read(fd, &c, 1);
// 	}
// 	if (byte == 0 && i == 0)
// 		return(free(line), NULL);
// 	return(line);
// }

char	*get_file(int fd, int i)
{
	char	*temp;
	char	*line;
	int		total;

	if (fd < 0)
		return (NULL);
	temp = ft_calloc(65536, 1);
	if (!temp)
		return (NULL);
	if (count_bytes(fd, temp, &total) == -1)
		return (free(temp), NULL);
	if (total == 0)
		return (NULL);
	line = ft_calloc(total + 1, 1);
	if (!line)
		return (free(temp), NULL);
	while (i < total)
	{
		line[i] = temp[i];
		i++;
	}
	line[i] = '\0';
	free(temp);
	return (line);
}

char	*hd_parent(int fd, int status)
{
	char	*input;

	input = NULL;
	if (WEXITSTATUS(status) == 130)
	{
		input = ft_strdup("ctrl");
		close(fd);
		return (input);
	}
	input = get_file(fd, 0);
	close(fd);
	printf("after while dasdasd\n");
	return (input);
}

char	*pre_heredoc(char *delimiter, t_shell *data)
{
	int	pid;
	int	pipefd[2];
	int	status;

	if (pipe(pipefd) == -1)
		hd_clean_exit(errno, 1, pipefd, data);
	pid = fork();
	if (pid == -1)
		hd_clean_exit(errno, 2, pipefd, data);
	signal(SIGINT, signal_hd);
	signal(SIGQUIT, SIG_IGN);
	if (pid == 0)
	{
		close(pipefd[0]);
		signal(SIGINT, handle_hd_sig);
		do_heredoc(pipefd[1], delimiter, data);
		close(pipefd[1]);
		exit(0);
	}
	waitpid(pid, &status, 0);
	data->exit_code = WEXITSTATUS(status);
	close(pipefd[1]);
	return (hd_parent(pipefd[0], status));
}

static int	handle_heredoc(t_redir *temp, t_shell *data)
{
	if (temp->flag == 2)
	{
		temp->hd_input = pre_heredoc(temp->file, data);
		if (!temp->hd_input)
		{
			if (errno == ENOMEM)
			{
				perror("malloc");
				return (errno);
			}
		}
		else if (ft_strncmp("ctrl", temp->hd_input, 5) == 0)
			return (-1);
	}
	else
		temp->hd_input = NULL;
	return (0);
}

int	process_heredoc(t_cmd *cmds, t_shell *data)
{
	t_cmd	*curr;
	t_redir	*temp;
	int		ret;

	curr = cmds;
	while (curr)
	{
		temp = curr->redirs;
		while (temp)
		{
			ret = handle_heredoc(temp, data);
			if (ret != 0)
				return (ret);
			temp = temp->next;
		}
		curr = curr->next;
	}
	return (0);
}
