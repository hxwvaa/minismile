/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_export_extend.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbasheer <hbasheer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:04:53 by hbasheer          #+#    #+#             */
/*   Updated: 2024/12/17 17:04:54 by hbasheer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*clone_list(t_list *o_list)
{
	t_list	*list;
	t_list	*temp;
	t_list	*new_l;

	list = o_list;
	new_l = NULL;
	while (list)
	{
		temp = ft_lstnew(ft_strdup(list->content));
		if (!temp)
			return (NULL);
		ft_lstadd_back(&new_l, temp);
		list = list->next;
	}
	return (new_l);
}

t_list	*sort_exp(t_list *list)
{
	t_list	*final;
	t_list	*n_list;
	void	*temp;

	n_list = clone_list(list);
	if (!n_list)
		return (NULL);
	final = n_list;
	while (n_list)
	{
		if (n_list->next && ft_strncmp((char *)n_list->content,
				(char *)n_list->next->content,
				ft_strlen((char *)n_list->content)) > 0)
		{
			temp = n_list->content;
			n_list->content = n_list->next->content;
			n_list->next->content = temp;
			n_list = final;
		}
		else
			n_list = n_list->next;
	}
	return (final);
}

void	our_expenv(t_shell *data)
{
	t_list	*tmp;
	t_list	*sorted;
	char	*equal;

	sorted = sort_exp(data->envir);
	tmp = sorted;
	if (!tmp)
	{
		perror("malloc");
		free_all(data);
		exit(1);
	}
	while (tmp)
	{
		equal = ft_strchr((char *)tmp->content, '=');
		if (equal)
		{
			printf("declare -x %.*s=\"%s\"\n", (int)(equal
					- (char *)tmp->content), (char *)tmp->content, equal + 1);
		}
		else
			printf("declare -x %s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	our_envlistclear(&sorted);
}
