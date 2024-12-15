/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_ex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:25:42 by mshaheen          #+#    #+#             */
/*   Updated: 2024/12/15 18:26:05 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_what(char *line, int start, int *len)
{
	char	*to_expand;
	int		i;

	i = start;
	while (line[i] && line[i] != 32 && !(line[i] >= 9 && line[i] <= 13)
		&& line[i] != '\"' && line[i] != '\'' && line[i] != '$')
		i++;
	*len = i;
	to_expand = ft_substr(line, start, i - start);
	if (!to_expand)
	{
		perror("malloc");
		return (NULL);
	}
	return (to_expand);
}

char	*join_strs(char *s1, char *s2, char *line)
{
	char	*temp;

	temp = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	if (!temp)
	{
		perror("malloc");
		free(line);
		return (NULL);
	}
	return (temp);
}

int	count_bytes(int fd, char *temp, int *total)
{
	int		byte;
	char	c;

	*total = 0;
	byte = read(fd, &c, 1);
	if (byte == -1)
	{
		perror("read");
		return (-1);
	}
	while (byte > 0)
	{
		temp[(*total)] = c;
		(*total)++;
		if (*total > 65536)
		{
			write(2, "here_doc input too large\n", 26);
			return (-1);
		}
		byte = read(fd, &c, 1);
	}
	if (byte == 0 && *total == 0)
		return (-1);
	return (0);
}
