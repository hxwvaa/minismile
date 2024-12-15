/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 22:21:26 by mshaheen          #+#    #+#             */
/*   Updated: 2024/12/15 22:37:11 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	our_strcpy(char *des, char *src, int j)
{
	int	i;

	i = 0;
	while (src[i] && i < j)
	{
		des[i] = src[i];
		i++;
	}
	des[i] = '\0';
}

static	int	handle_operands(int *j, int *i, char *s)
{
	if ((s[*i] == '<' || s[*i] == '>' || s[*i] == '|'))
	{
		(*j) = (*i);
		(*i)++;
		if ((s[(*i) - 1] == '<' && s[*i] == '<')
			|| (s[(*i) - 1] == '>' && s[*i] == '>'))
			(*i)++;
		return (-1);
	}
	return (0);
}

static	void	quotes_handle(int *i, char *s)
{
	if (*i > 0)
	{
		if ((s[*i] == '\'' || s[*i] == '\"')
			&& (s[*i - 1] == ' ' || (s[*i - 1] >= 9 && s[*i - 1] <= 13)))
			*i = our_quote(s, *i + 1, s[*i]);
		else if ((s[*i] == '\'' || s[*i] == '\"') && s[*i - 1] != ' '
			&& !(s[*i - 1] >= 9 && s[*i - 1] <= 13))
			*i = our_quote(s, *i + 1, s[*i]);
	}
	else if ((s[*i] == '\'' || s[*i] == '\"'))
		*i = our_quote(s, *i + 1, s[*i]);
}

int	our_help_fill(int *j, int *i, char *s)
{
	if (s[*i] == '\0')
		return (-1);
	if (handle_operands(j, i, s) == -1)
		return (-1);
	quotes_handle(i, s);
	if (s[*i])
		(*i)++;
	if ((s[*i] == '<' || s[*i] == '>' || s[*i] == '|'))
		return (-1);
	return (0);
}

int	our_fill(char *s, char **cmd, int count)
{
	int	i;
	int	word;
	int	j;

	i = 0;
	word = 0;
	while (s[i] && word < count)
	{
		while (s[i] && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)))
			i++;
		if (s[i] && s[i] != ' ' && !(s[i] >= 9 && s[i] <= 13) && !(s[i] == '<'
				|| s[i] == '>' || s[i] == '|'))
			j = i;
		while (s[i] && s[i] != ' ' && !(s[i] >= 9 && s[i] <= 13))
		{
			if (our_help_fill(&j, &i, s) == -1)
				break ;
		}
		cmd[word] = ft_calloc(((i - j) + 1), sizeof(char));
		if (!cmd[word])
			return (our_free(cmd, word));
		our_strcpy(cmd[word], s + j, i - j);
		word++;
	}
	return (0);
}
