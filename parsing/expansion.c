/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 00:56:53 by mshaheen          #+#    #+#             */
/*   Updated: 2024/12/18 16:43:28 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*pre_dollar(char *str, char *bef_do)
{
	char	*dollar;
	int		i;
	int		j;
	int		doll;

	bef_do = ft_strdup("");
	if (!bef_do)
		return (NULL);
	dollar = ft_strchr(str, '$');
	doll = (int)(dollar - str);
	if (doll > 0)
	{
		free(bef_do);
		i = ft_strlen(str);
		j = ft_strlen(str + doll);
		bef_do = ft_substr(str, 0, (i - j));
		if (!bef_do)
			return (NULL);
	}
	return (bef_do);
}

int	find_dollar(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*handle_em_ex(char *str, char *res, int *i)
{
	char	*temp;

	temp = ft_substr(str, *i, 1);
	if (!temp)
	{
		free(res);
		return (NULL);
	}
	res = join_free(res, temp);
	if (!res)
		return (NULL);
	if (str[*i])
		(*i)++;
	return (res);
}

char	*handle_exit_code(char *res, int *i, t_shell *data)
{
	char	*temp;

	(*i) = (*i) + 2;
	temp = ft_itoa(data->exit_code);
	if (!temp)
	{
		free(res);
		return (NULL);
	}
	res = join_free(res, temp);
	if (!res)
		return (NULL);
	return (res);
}

char	*handle_ex(char *str, char *res, int *i, t_shell *data)
{
	int		start;
	char	*to_ex;
	char	*temp;

	if (str[*i + 1] == '?')
		return (handle_exit_code(res, i, data));
	if ((str[*i + 1] != '\'' && str[*i + 1] != '\"') && (str[*i + 1] != '_'
			&& !ft_isalnum(str[*i + 1])))
		return (handle_em_ex(str, res, i));
	start = ++(*i);
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	to_ex = ft_substr(str, start, (*i) - start);
	if (!to_ex)
		return (free(res), NULL);
	temp = our_expand(to_ex, data);
	free(to_ex);
	if (!temp)
		return (free(res), NULL);
	res = join_free(res, temp);
	if (!res)
		return (NULL);
	return (res);
}
