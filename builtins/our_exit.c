/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbasheer <hbasheer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:55:12 by hbasheer          #+#    #+#             */
/*   Updated: 2024/12/17 16:55:12 by hbasheer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	num_arg_req(char *arg, t_shell *data)
{
	protected_write("exit\nshell: exit: ", 2, data);
	protected_write(arg, 2, data);
	protected_write(": numeric argument required\n", 2, data);
	free_all(data);
	exit(255);
}

void	exit_av_more_than_2(char **av, t_shell *data, int *exit_status)
{
	if (is_digit_exit_code(av))
	{
		protected_write("exit\n", 2, data);
		protected_write("shell: exit: too many arguments\n", 2, data);
		*exit_status = 1;
		return ;
	}
	else
		num_arg_req(av[1], data);
}

void	exit_av_is_equal_2(char **av, t_shell *data)
{
	bool				num_small;
	unsigned long long	n;

	num_small = false;
	n = 0;
	if (is_digit_exit_code(av))
	{
		if (av[1][0] == '-')
			num_small = is_num_very_small(av[1]);
		if (num_small == false)
		{
			if (av[1][0] != '-')
				n = ft_atoull(av[1]);
			if ((n <= LONG_MAX && num_small == false) || (av[1][0] == '-'
				&& num_small == false))
			{
				n = ft_atol(av[1]);
				printf("exit\n");
				(free_all(data), exit(n % 256));
			}
		}
	}
	num_arg_req(av[1], data);
}

void	exit_shell(char **av, t_shell *data, int *exit_status)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	if (!(i > 2 && is_digit_exit_code(av)))
	{
		if (data->std[0] != -1)
			close(data->std[0]);
		if (data->std[1] != -1)
			close(data->std[1]);
	}
	if (data->fd[0] != -1)
		close(data->fd[0]);
	if (i == 1)
	{
		write(2, "exit\n", 5);
		free_all(data);
		exit(0);
	}
	else if (i == 2)
		exit_av_is_equal_2(av, data);
	else
		exit_av_more_than_2(av, data, exit_status);
}
