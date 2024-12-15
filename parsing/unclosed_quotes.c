/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unclosed_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 22:41:05 by mshaheen          #+#    #+#             */
/*   Updated: 2024/12/16 00:27:42 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	opened_or_closed(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (quote == 0)
				quote = str[i];
			else if (quote == str[i])
				quote = 0;
		}
		i++;
	}
	if (quote != 0)
		return (quote);
	return (0);
}

int	check_quotes(t_toklist *list)
{
	t_toklist	*temp;
	char		quote;

	temp = list;
	quote = 0;
	while (temp)
	{
		quote = opened_or_closed(temp->token);
		if (quote != 0)
		{
			if (quote == '\'')
				ft_putendl_fd("syntax error unclosed quote \'", 2);
			else
				ft_putendl_fd("syntax error unclosed quote \"", 2);
			return (-1);
		}
		temp = temp->next;
	}
	return (0);
}

t_cmd	*our_clstlast(t_cmd *lst)
{
	t_cmd	*ptr;

	if (!lst)
		return (NULL);
	ptr = lst;
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}
