/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:44:56 by hbasheer          #+#    #+#             */
/*   Updated: 2024/12/18 18:32:56 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*export_var(char *arg)
{
	int		i;
	char	*new_s;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	new_s = malloc(i + 1);
	if (!new_s)
		return (NULL);
	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		new_s[i] = arg[i];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}

int	check_exp_ident(char *arg)
{
	int		i;
	char	*b_equal;
	int		flag;

	i = 0;
	flag = 0;
	b_equal = export_var(arg);
	if (!b_equal)
		return (write(2, "error malloc\n", 13), -1);
	if (!ft_isalpha(b_equal[i]) && b_equal[i] != '_')
		flag = 1;
	i++;
	while (b_equal[i] && flag == 0)
	{
		if (!ft_isalnum(b_equal[i]) && b_equal[i] != '_')
			flag = 1;
		i++;
	}
	if (flag == 1)
	{
		write(2, "minishell: `", 13);
		write(2, arg, ft_strlen(arg));
		return (write(2, "': not a valid identifier\n", 27), free(b_equal), 1);
	}
	return (free(b_equal), 0);
}

bool	if_equal(char *arg, t_list *current, int *found, t_shell *data)
{
	int	chevk;

	chevk = check_exp_ident(arg);
	if (chevk == 1 || chevk == -1)
	{
		data->exit_code = 1;
		return (false);
	}
	while (current)
	{
		if (ft_strncmp(current->content, arg, len_b4_eq(current->content)) == 0)
		{
			free(current->content);
			current->content = ft_strdup(arg);
			if (!current->content)
			{
				write(2, "error malloc\n", 13);
				(free_all(data), exit(12));
			}
			*found = 1;
			break ;
		}
		current = current->next;
	}
	return (true);
}

bool	if_not_equal(char *arg, t_list *current, int *found, t_shell *data)
{
	int	chevk;

	chevk = check_exp_ident(arg);
	if (chevk == 1 || chevk == -1)
	{
		data->exit_code = 1;
		return (false);
	}
	while (current)
	{
		if (ft_strncmp(current->content, arg, len_b4_eq(current->content)) == 0)
		{
			*found = 1;
			break ;
		}
		current = current->next;
	}
	return (true);
}
void add_not_found(int found, t_shell *data, char *arg)
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


bool	our_export(char **arg, t_shell *data, int i)
{
	t_list	*current;
	char	*key;
	int		found;

	if (!arg[1])
		return (our_expenv(data), true);
	while (arg[++i])
	{
		current = data->envir;
		found = 0;
		key = ft_strchr(arg[i], '=');
		if (key && !if_equal(arg[i], current, &found, data))
			continue ;
		else if (!key && !if_not_equal(arg[i], current, &found, data))
			continue ;
		add_not_found(found, data, arg[i]);
	}
	if(data->exit_code == 1)
		return (true);
	return (false);
}
