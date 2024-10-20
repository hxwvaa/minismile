/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbasheer <hbasheer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:16:14 by hbasheer          #+#    #+#             */
/*   Updated: 2024/06/26 15:16:15 by hbasheer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*temp;

	temp = NULL;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
			temp = (char *)s + i;
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s + i);
	return (temp);
}
