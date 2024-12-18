/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:35:02 by hbasheer          #+#    #+#             */
/*   Updated: 2024/12/18 17:48:21 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	our_env(t_list *envir, char **arg, t_shell *data)
{
	t_list	*tmp;

	tmp = envir;
	if(arg[1])
	{
		write(2, "env: ", 5);
		write(2, arg[1], ft_strlen(arg[1]));
		write(2, "No such file or directory\n", 26);
		data->exit_code = 1;
		return (1);
	}
	while (tmp)
	{
		if (ft_strchr(tmp->content, '='))
			printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	return (0);
}

size_t	len_b4_eq(char *arg)
{
	size_t	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	return (i);
}
