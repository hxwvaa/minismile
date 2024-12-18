/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 22:21:14 by mshaheen          #+#    #+#             */
/*   Updated: 2024/12/18 16:28:50 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	our_free(char **str, int t)
{
	int	i;

	i = 0;
	while (i <= t)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (-1);
}

int	our_quote(char *str, int i, char quote)
{
	if (quote == '\'')
	{
		while (str[i] && str[i] != '\'')
			i++;
		return (i);
	}
	else
	{
		while (str[i] && str[i] != '\"')
			i++;
		return (i);
	}
}

int	our_help_wount(int *word, int *i, char *s)
{
	if (!s[*i])
		return (-1);
	if ((s[*i] == '<' || s[*i] == '>' || s[*i] == '|'))
	{
		(*word)++;
		(*i)++;
		return (-1);
	}
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
	return (0);
}

int	our_wount(char *s, int *i, int word)
{
	while (s[*i])
	{
		while (s[*i] && (s[*i] == ' ' || (s[*i] >= 9 && s[*i] <= 13)))
			(*i)++;
		if (s[*i] && s[*i] != ' ' && !(s[*i] >= 9 && s[*i] <= 13)
			&& !(s[*i] == '<' || s[*i] == '>' || s[*i] == '|'))
			word++;
		while (s[*i] && s[*i] != ' ' && !(s[*i] >= 9 && s[*i] <= 13))
		{
			if (our_help_wount(&word, i, s) == -1)
				break ;
			if (s[*i])
				(*i)++;
		}
	}
	return (word);
}

char	**our_tokenize(char *s)
{
	char	*r;
	char	**split;
	int		i;
	int		word;

	i = 0;
	word = 0;
	r = ft_strtrim(s, " ");
	if (r == NULL)
		return (NULL);
	word = our_wount(r, &i, word);
	split = ft_calloc(word + 1, sizeof(char *));
	if (!split)
		return (NULL);
	split[word] = 0;
	if (our_fill(r, split, word) == -1)
	{
		free(r);
		return (NULL);
	}
	free(r);
	return (split);
}
