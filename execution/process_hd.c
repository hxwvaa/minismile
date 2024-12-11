/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_hd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbasheer <hbasheer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 10:53:59 by mshaheen          #+#    #+#             */
/*   Updated: 2024/12/11 16:01:43 by hbasheer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*do_heredoc(char *input, char *limit, char *temp, char *line)
{
	while (1)
	{
		line = get_next_line(0);
		if (line)
		{
			if (ft_strncmp(limit, line, ft_strlen(limit)) == 0)
			{
				free(limit);
				free(line);
				break ;
			}
			temp = ft_strjoin(input, line);
			free(input);
			if (!temp)
				return (free(line), free(limit), NULL);
			input = temp;
			free(line);
		}
		else
		{
			free(limit);
			break ;
		}
	}
	return (input);
}

char	*pre_heredoc(char *delimiter)
{
	char	*input;
	char	*limit;
	char	*temp;
	char	*line;

	line = NULL;
	temp = NULL;
	input = ft_strdup("");
	if (!input)
		return (NULL);
	limit = ft_strjoin(delimiter, "\n");
	if (!limit)
		return (free(input), NULL);
	return (do_heredoc(input, limit, temp, line));
}

int process_heredoc(t_cmd *cmds)
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
                temp->hd_input = pre_heredoc(temp->file);
                if(!temp->hd_input)
                {
                    perror("malloc");
                    return errno;
                }
            }
            else
                temp->hd_input = NULL;
            temp = temp->next;
        }
        curr = curr->next;
    }
}
