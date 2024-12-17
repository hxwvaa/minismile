/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbasheer <hbasheer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:35:02 by hbasheer          #+#    #+#             */
/*   Updated: 2024/12/17 18:43:07 by hbasheer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	our_env(t_list *envir)
{
	t_list	*tmp;

	tmp = envir;
	while (tmp)
	{
		if (ft_strchr(tmp->content, '='))
			printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
}

size_t	len_b4_eq(char *arg)
{
	size_t	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	return (i);
}
