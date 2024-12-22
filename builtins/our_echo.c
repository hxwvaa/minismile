/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:18:52 by hbasheer          #+#    #+#             */
/*   Updated: 2024/12/22 15:32:36 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	protected_write(char *error, int fd, t_shell *data)
{
	if (write(fd, error, ft_strlen(error)) == -1)
	{
		perror("write");
		free_all(data);
		exit(1);
	}
}

bool	check_non_n(char *arg)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

void	our_echo(char **arg, t_shell *data)
{
	int	flag_n;
	int	i;

	i = 1;
	flag_n = 1;
	if (!arg[i])
		;
	else
	{
		while (arg[i] && ft_strncmp(arg[i], "-n", 2) == 0
			&& check_non_n(arg[i]))
		{
			flag_n = 0;
			i++;
		}
		while (arg[i])
		{
			protected_write(arg[i], STDOUT_FILENO, data);
			if ((arg[i + 1]))
				protected_write(" ", STDOUT_FILENO, data);
			i++;
		}
	}
	if (flag_n)
		protected_write("\n", STDOUT_FILENO, data);
}
