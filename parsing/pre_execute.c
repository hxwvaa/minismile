/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 22:47:41 by mshaheen          #+#    #+#             */
/*   Updated: 2024/12/19 03:12:30 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_token_type(char *token, int *first, int *file)
{
	if (ft_strncmp(token, "|", 2) == 0)
	{
		(*first) = 1;
		return (PIPE);
	}
	else if (ft_strncmp(token, "<", 2) == 0)
		return (*file = 1, REDIR_IN);
	else if (ft_strncmp(token, ">", 2) == 0)
		return (*file = 1, REDIR_OUT);
	else if (ft_strncmp(token, ">>", 3) == 0)
		return (*file = 1, APPEND);
	else if (ft_strncmp(token, "<<", 3) == 0)
		return (*file = 2, HERE_DOC);
	else if (token[0] == '-' && !*first)
		return (FLAG);
	else if (*file == 1)
		return (*file = 0, FILE_NAME);
	else if (*file == 2)
		return (*file = 0, LIMITER);
	else if (*first)
	{
		*first = 0;
		return (CMD);
	}
	return (ARGS);
}

t_toklist	*our_tlstlast(t_toklist *lst)
{
	t_toklist	*ptr;

	if (!lst)
		return (NULL);
	ptr = lst;
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

void	our_tlstadd_back(t_toklist **lst, t_toklist *new)
{
	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
		our_tlstlast(*lst)->next = new;
}

t_toklist	*our_tlstnew(char *token, int type)
{
	t_toklist	*list;

	if (!token)
	{
		return (NULL);
	}
	list = malloc(sizeof(t_toklist));
	if (list == NULL)
		return (NULL);
	list->token = token;
	list->type = type;
	list->q_type = 0;
	list->em_ex = 0;
	list->next = NULL;
	return (list);
}

t_toklist	*array_token_list(t_shell *data, char **split, int count)
{
	int			i;
	int			first;
	t_toklist	*new;
	int			file;

	file = 0;
	i = 0;
	first = 1;
	while (split[i] && i <= count)
	{
		new = our_tlstnew(ft_strdup(split[i]),
				set_token_type(split[i], &first, &file));
		if (!new)
		{
			perror("malloc");
			free_all(data);
			exit(12);
		}
		if (new)
			our_tlstadd_back(&data->tokens, new);
		i++;
	}
	free_args_set_null(data);
	return (data->tokens);
}
