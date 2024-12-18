/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 01:09:07 by mshaheen          #+#    #+#             */
/*   Updated: 2024/12/19 01:09:22 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_not_found(int found, t_shell *data, char *arg)
{
	t_list	*new;

	if (!found)
	{
		new = ft_lstnew(ft_strdup(arg));
		if (!new)
		{
			write(2, "error malloc\n", 13);
			free_all(data);
			exit(12);
		}
		ft_lstadd_back(&data->envir, new);
	}
}
