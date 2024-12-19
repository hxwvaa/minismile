/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unclosed_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 22:41:05 by mshaheen          #+#    #+#             */
/*   Updated: 2024/12/20 03:13:25 by mshaheen         ###   ########.fr       */
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

void	set_estat_syntax(char **av, t_shell *data, int ret)
{
	if (ret == 1)
	{
		free_arr(av);
		data->our_args = NULL;
		if (data->line)
			add_history(data->line);
		free(data->line);
		data->exit_code = 258;
	}
}

void	unclosed_free(t_shell *data)
{
	our_toklistclear(&data->tokens);
	if (data->line)
		add_history(data->line);
	free(data->line);
	data->exit_code = 1;
}

int	check_quotes(t_toklist *list, t_shell *data)
{
	t_toklist	*temp;
	char		quote;
	int			ret;

	ret = 0;
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
			ret = -1;
			break ;
		}
		temp = temp->next;
	}
	if (ret == -1)
		unclosed_free(data);
	return (ret);
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
