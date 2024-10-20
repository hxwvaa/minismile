/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbasheer <hbasheer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:15:22 by hbasheer          #+#    #+#             */
/*   Updated: 2024/06/26 15:15:23 by hbasheer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*newlst;

	if (!f || !lst)
		return (NULL);
	newlst = NULL;
	while (lst != NULL)
	{
		temp = malloc(sizeof(t_list));
		if (!temp)
		{
			ft_lstclear(&newlst, (*del));
			return (NULL);
		}
		temp->content = f(lst->content);
		temp->next = NULL;
		ft_lstadd_back(&newlst, temp);
		lst = lst->next;
	}
	return (newlst);
}
