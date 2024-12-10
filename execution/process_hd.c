/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_hd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 10:53:59 by mshaheen          #+#    #+#             */
/*   Updated: 2024/12/05 17:34:13 by mshaheen         ###   ########.fr       */
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

char	*do_heredoc(char *input, char *limit, t_shell *data)
{
	char *line;
	//char *bef_do;

	//bef_do = NULL;
	line = NULL;
	while (1)
	{
		line = readline(">");
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
	//(free(limit), limit = NULL); // it will get free'd inside cmdlistclear
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

void process_heredoc(t_cmd *cmds, t_shell *data)
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
                if(!temp->hd_input)
                {
                    perror("malloc");
                    return ;
                }
            }
            else
                temp->hd_input = NULL;
            temp = temp->next;
        }
        curr = curr->next;
    }
}
