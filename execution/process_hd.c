/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_hd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 10:53:59 by mshaheen          #+#    #+#             */
/*   Updated: 2024/12/12 20:52:02 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// char *expand_what(char *line, int start, int *len)
// {
// 	char *to_expand;
// 	int i;

// 	i = start;
// 	while(line[i] && line[i] != 32 && !(line[i] >= 9 && line[i] <= 13) && line[i] != '\"' && line[i] != '\'' && line[i] != '$')
// 		i++;
// 	*len = i;
// 	to_expand = ft_substr(line, start, i - start);
// 	if(!to_expand)
// 		return(perror("malloc"), NULL);
// 	return(to_expand);
// }

// char *join_strs(char *s1, char *s2, char *line)
// {
// 	char *temp;

// 	temp = ft_strjoin(s1, s2);
// 	free(s1);
// 	free(s2);
// 	if(!temp)
// 		return(perror("malloc"), free(line), NULL);
// 	return (temp);
// }

// char *expand_hd(char *line, t_shell *data, char *bef_do, int len)
// {
// 	char *ex_str;
// 	char *remains;
// 	char *to_ex;
// 	char *res;
// 	char *new;

// 	res = ft_strdup("");
// 	if(!res)
// 		return(perror("malloc"), NULL);
// 	while(find_dollar(line))
// 	{
// 		bef_do = pre_dollar(line, bef_do);
// 		if(!bef_do)
// 			return(perror("malloc"), free(res), NULL);
// 		to_ex = expand_what(line, (ft_strlen(bef_do) + 1), &len); 
// 		if(!to_ex)
// 			return(perror("malloc"), free(bef_do), NULL);
// 		res = join_strs(res, bef_do, line);
// 		ex_str = our_expand(to_ex, data);
// 		free(to_ex);
// 		if(!ex_str)
// 			return(perror("malloc"), NULL);
// 		res = join_strs(res, ex_str, line);
// 		if(!res)
// 			return(perror("malloc"), NULL);
// 		new = ft_strdup(line + len);
// 		free(line);
// 		if (!new)
// 			return (perror("malloc"), free(res), NULL);
// 		line = new;
// 	}
// 	remains = ft_strdup(line);
// 	free(line);
// 	if(!remains)
// 		return(perror("malloc"), free(res), NULL);
// 	return(join_strs(res, remains, line));
// }

// int append_input(char **input, char *line)
// {
// 	char *temp;
// 	char *new_line;
// 	new_line = ft_strjoin(line, "\n");
// 	if(!new_line)
// 		return(perror("malloc"), -1);
// 	temp = ft_strjoin(*input, new_line);
// 	free(new_line);
// 	if(!temp)
// 		return(perror("malloc"), -1);
// 	free(*input);
// 	*input = temp;
// 	return(0);
// }

char *get_file(int fd)
{
	int i = 0;
	int byte;
	char c;
	char *line;
	
	if (fd < 0)
		return (NULL);
	byte = read(fd, &c, 1);
	if (byte == -1)
	{
		perror("read");
		return (NULL);
	}
	line = ft_calloc(65537, 1);
	if (!line)
		return (NULL);
	while(byte > 0)
	{
		line[i] = c;
		i++;
		byte = read(fd, &c, 1);
	}
	if (byte == 0 && i == 0)
		return(free(line), NULL);
	return(line);
}

void handle_hd_sig(int signo)
{
	if (signo == SIGINT)
	{
		g_signo = signo;
		close(STDIN_FILENO);
	}
}

char	*do_heredoc(char *input, char *limit, t_shell *data)
{
	char *line;
	//char *bef_do;
	int status;

	//bef_do = NULL;
	line = NULL;
	int pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (NULL);
	}
	// signal(SIGINT, SIG_IGN);
	int pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (NULL);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (pid == 0)
	{
		close(pipefd[0]);
		signal(SIGINT, handle_hd_sig);
		while (1)
		{	
			line = readline(">");
			// if (g_signo == SIGINT)
			// {
			// 	close(pipefd[1]);
			// 	if (line)
			// 		free(line);
			// 	if (input)
			// 		free(input);
			// 	exit(1);
			// }
			if(!line)
				break;
			if (ft_strncmp(limit, line, ft_strlen(limit) + 1) == 0)
			{
				(free(line), line = NULL);
				break ;
			}
			line = expand_hd(line, data, 0);
			if(!line)
				return (free(line), free(limit), NULL);
			if(append_input(&input, line) == -1)
				return (free(line), free(limit), NULL);
			free(line);
		}
		exit(0);
	}
	close(pipefd[1]);
	close(pipefd[0]);
	// waitpid(pid, &status, 0);
	wait(&status);
	printf("status: %d\n", status);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			printf("inside sigint\n");
			free(input);
			input = ft_strdup("ctrl");
			close(pipefd[1]);
			close(pipefd[0]);
			return(input);
		}
	}
	printf("after while dasdasd\n");
	// input = get_file(pipefd[0]);
	// close(pipefd[0]);
	return (input);
}

char	*pre_heredoc(char *delimiter, t_shell *data)
{
	char	*input;
	//char	*limit;
	//char	*temp;
	//char	*line;

	//line = NULL;
	//temp = NULL;
	input = ft_strdup("");
	if (!input)
		return (NULL);
	//input = NULL;
	//limit = delimiter;
	// limit = ft_strjoin(delimiter, "\n");
	// if (!limit)
	// 	return (free(input), NULL);
	return (do_heredoc(input, delimiter, data));
}

int process_heredoc(t_cmd *cmds, t_shell *data)
{
    t_cmd *curr;
    t_redir *temp;

    curr = cmds;
    while(curr)
    {
        temp = curr->redirs; // maybe check if curr->inputs is null before assigning
        while(temp)
        {
            if(temp->flag == 2)
            {
                temp->hd_input = pre_heredoc(temp->file, data);
				if (ft_strncmp("ctrl", temp->hd_input, 5) == 0)
				{
					return (-1);
				}
                if(!temp->hd_input)
                {
                    perror("malloc");
                    return errno;
                }
				// printf("hd_input: %s\n", temp->hd_input);
				// if(ft_strncmp(temp->hd_input, "ctrl", 5) == 0)
				// 	return(-1);
            }
            else
                temp->hd_input = NULL;
            temp = temp->next;
        }
        curr = curr->next;
    }
	return(0);
}
