/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 23:41:05 by mshaheen          #+#    #+#             */
/*   Updated: 2024/12/16 00:43:05 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	our_clstadd_back(t_cmd **lst, t_cmd *new)
{
	if (!new)
		return (-1);
	if (!*lst)
		*lst = new;
	else
		our_clstlast(*lst)->next = new;
	return (0);
}

t_redir	*our_redirlast(t_redir *lst)
{
	t_redir	*ptr;

	if (!lst)
		return (NULL);
	ptr = lst;
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

t_redir	*our_redirnew(char *file, int flag)
{
	t_redir	*new;

	new = ft_calloc(1, sizeof(t_redir));
	if (!new)
		return (NULL);
	new->file = ft_strdup(file);
	if (!new->file)
	{
		free(new);
		return (NULL);
	}
	new->hd_input = NULL;
	new->flag = flag;
	new->next = NULL;
	return (new);
}

int	our_rediradd(t_redir **lst, char *file, int flag)
{
	t_redir	*new;

	new = our_redirnew(file, flag);
	if (!new)
		return (-1);
	if (!*lst)
		*lst = new;
	else
		our_redirlast(*lst)->next = new;
	return (0);
}

t_cmd	*our_clistnew(int count)
{
	t_cmd	*list;

	list = ft_calloc(1, sizeof(t_cmd));
	if (!list)
		return (NULL);
	list->cmd = NULL;
	list->cargs = ft_calloc((count + 1), sizeof(char *));
	if (!list->cargs)
	{
		free(list);
		return (NULL);
	}
	list->cargs[0] = NULL;
	list->redirs = NULL;
	list->redir_out = 0;
	list->em_expand = 0;
	list->next = NULL;
	return (list);
}
