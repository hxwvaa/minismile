/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_exit_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbasheer <hbasheer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:50:44 by hbasheer          #+#    #+#             */
/*   Updated: 2024/12/17 16:50:45 by hbasheer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_digit_exit_code(char **av)
{
	int	n;

	n = 0;
	if (av[1][n] == '-' || av[1][n] == '+')
		n++;
	while (av[1][n])
	{
		if (ft_isdigit(av[1][n]))
			;
		else
			return (0);
		n++;
	}
	return (1);
}

bool	is_num_very_small(char *str)
{
	size_t		i;
	long long	nb;

	i = 0;
	nb = 0;
	if (ft_atol(str) == LONG_MIN)
		return (false);
	if (str[i] == '-')
		i++;
	if (ft_strlen(str) > 19)
		return (true);
	else if (ft_strlen(str) < 19)
		return (false);
	while (i < ft_strlen(str) && str[i] >= '0' && str[i] <= '9')
		nb = nb * 10 + str[i++] - '0';
	if (nb * -1 < LONG_MIN)
		return (true);
	i = str[i] - '0';
	if (i > 8)
		return (true);
	return (false);
}
