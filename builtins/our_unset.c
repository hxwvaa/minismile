/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbasheer <hbasheer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:59:47 by hbasheer          #+#    #+#             */
/*   Updated: 2024/12/18 17:36:21 by hbasheer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_loop(t_list **current, char *var, t_list *prev, t_list **envir)
{
	while ((*current))
	{
		if (ft_strncmp((*current)->content, var,
				len_b4_eq((*current)->content)) == 0)
		{
			if (prev == NULL)
				*envir = (*current)->next;
			else
				prev->next = (*current)->next;
			free((*current)->content);
			(*current)->content = NULL;
			free(*current);
			*current = NULL;
			return ;
		}
		prev = (*current);
		(*current) = (*current)->next;
	}
}

bool	our_unset(char **var, t_list **envir)
{
	t_list	*current;
	t_list	*prev;
	t_list	*temp;
	int		i;
	int		flag;

	if (!var[1])
		return (false);
	temp = *envir;
	current = *envir;
	prev = NULL;
	i = 0;
	while (var[++i])
	{
		flag = 0;
		if (check_exp_ident(var[i]) == 1)
			flag = 1;
		if (flag == 1)
			continue ;
		unset_loop(&current, var[i], prev, envir);
		prev = NULL;
		current = temp;
	}
	return (flag == 1);
}
