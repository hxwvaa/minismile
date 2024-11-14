/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:05:07 by mshaheen          #+#    #+#             */
/*   Updated: 2024/10/01 12:21:26 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*s;
	size_t			i;

	if (size && count > (SIZE_MAX / size))
		return (NULL);
	s = malloc(count * size);
	if (!s)
		return (NULL);
	i = 0;
	while (i < size * count)
	{
		s[i] = 0;
		i++;
	}
	return (s);
}

char	*ft_readline(int fd, char *buff, char *str)
{
	char	*tmp;
	int		rb;

	rb = 1;
	while (!ft_strchr(buff, '\n') && rb > 0)
	{
		rb = read(fd, buff, BUFFER_SIZE);
		if (rb == -1)
		{
			free(str);
			free(buff);
			return (NULL);
		}
		else if (rb == 0)
			break ;
		tmp = str;
		buff[rb] = '\0';
		str = ft_strjoin(str, buff);
		if (tmp)
			free(tmp);
	}
	free(buff);
	return (str);
}

char	*ft_getline(char *str)
{
	size_t	i;
	char	*s;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	s = ft_substr(str, 0, i);
	if (!s)
		return (NULL);
	return (s);
}

char	*ft_nextline(char *str)
{
	char	*s;
	size_t	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] && str[i] == '\n')
		i++;
	s = ft_strdup(str + i);
	if (!s)
	{
		free(str);
		return (NULL);
	}
	free(str);
	str = NULL;
	return (s);
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	buff = ft_calloc((size_t)(BUFFER_SIZE + 1), sizeof(char));
	if (!buff)
		return (NULL);
	str = ft_readline(fd, buff, str);
	if (!str)
		return (NULL);
	line = ft_getline(str);
	str = ft_nextline(str);
	if (!str)
		return (NULL);
	if (!*str)
	{
		free(str);
		str = NULL;
	}
	return (line);
}
