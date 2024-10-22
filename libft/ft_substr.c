/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbasheer <hbasheer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:16:18 by hbasheer          #+#    #+#             */
/*   Updated: 2024/06/26 15:16:19 by hbasheer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	str_len;
	char	*str;

	if (!s)
		return (0);
	str_len = ft_strlen(s);
	if (start > str_len)
		len = 0;
	if (len > str_len - start)
		len = str_len - start;
	str = malloc(len + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while ((start < str_len) && (i < len))
	{
		str[i] = s[start];
		start++;
		i++;
	}
	str[i] = '\0';
	return (str);
}
