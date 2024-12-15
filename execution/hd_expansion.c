/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:24:31 by mshaheen          #+#    #+#             */
/*   Updated: 2024/12/15 18:25:26 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*exp_symb(char *res, char *line, int *len, char *bef_do)
{
	char	*temp;

	temp = ft_substr(line, ft_strlen(bef_do), *len - ft_strlen(bef_do));
	if (!temp)
	{
		free(res);
		return (NULL);
	}
	res = join_strs(res, bef_do, line);
	if (!res)
		return (NULL);
	res = join_strs(res, temp, line);
	if (!res)
		return (NULL);
	return (res);
}

char	*handle_expand(char *line, t_shell *data, int *len, char *res)
{
	char	*ex_str;
	char	*to_ex;
	char	*bef_do;

	bef_do = pre_dollar(line, NULL);
	if (!bef_do)
		return (free(res), NULL);
	to_ex = expand_what(line, (ft_strlen(bef_do) + 1), len);
	if (!to_ex)
		return (free(bef_do), free(res), NULL);
	if (!ft_isalnum(to_ex[0]) && to_ex[0] != '_' && to_ex[0] != '?')
		return (free(to_ex), exp_symb(res, line, len, bef_do));
	res = join_strs(res, bef_do, line);
	if (!res)
		return (NULL);
	ex_str = our_expand(to_ex, data);
	free(to_ex);
	if (!ex_str)
		return (free(res), NULL);
	res = join_strs(res, ex_str, line);
	if (!res)
		return (NULL);
	return (res);
}

char	*update_line(char *line, char *res, int len)
{
	char	*new;

	new = ft_strdup(line + len);
	free(line);
	if (!new)
	{
		perror("malloc");
		free(res);
		return (NULL);
	}
	return (new);
}

char	*final_string(char *line, char *res)
{
	char	*remains;

	remains = ft_strdup(line);
	free(line);
	if (!remains)
	{
		perror("malloc");
		free(res);
		return (NULL);
	}
	res = join_free(res, remains);
	if (!res)
	{
		perror("malloc");
		return (NULL);
	}
	return (res);
}

char	*expand_hd(char *line, t_shell *data, int len)
{
	char	*res;

	res = ft_strdup("");
	if (!res)
	{
		perror("malloc");
		return (NULL);
	}
	while (find_dollar(line))
	{
		res = handle_expand(line, data, &len, res);
		if (!res)
		{
			perror("malloc");
			return (NULL);
		}
		line = update_line(line, res, len);
		if (!line)
			return (NULL);
	}
	return (final_string(line, res));
}
