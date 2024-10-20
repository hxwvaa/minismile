/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbasheer <hbasheer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:14:36 by hbasheer          #+#    #+#             */
/*   Updated: 2024/06/26 15:14:37 by hbasheer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*s;
	size_t	total;

	if (size && nmemb > (SIZE_MAX / size))
		return (NULL);
	total = nmemb * size;
	s = malloc(total);
	if (s == NULL)
		return (NULL);
	ft_bzero(s, total);
	return (s);
}
