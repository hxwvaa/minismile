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

void	exit_av_more_than_2(char **av, t_shell *data)
{
	if (is_digit_exit_code(av))
	{
		(printf("exit\n"), printf("shell: exit: too many arguments\n"));
		data->exit_code = 1;
		return ;
	}
	else
	{
		printf("exit\n");
		printf("shell: exit: %s: numeric argument required\n", av[1]);
		exit(255);
	}
}

void	exit_av_is_equal_2(char **av)
{
	bool				b;
	unsigned long long	n;

	b = false;
	n = 0;
	if (is_digit_exit_code(av))
	{
		if (av[1][0] == '-')
			b = is_num_very_small(av[1]);
		if (b == false)
		{
			if (av[1][0] != '-')
				n = ft_atoull(av[1]);
			if ((n <= LONG_MAX && b == false) || (av[1][0] == '-'
					&& b == false))
			{
				printf("exit\n");
				exit(ft_atol(av[1]) % 256);
			}
		}
	}
	printf("exit\n");
	printf("shell: exit: %s: numeric argument required\n", av[1]);
	exit(255);
}

void	exit_shell(char **av, t_shell *data)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	if (i == 1)
		(printf("exit\n"), exit(0));
	else if (i == 2)
		exit_av_is_equal_2(av);
	else
		exit_av_more_than_2(av, data);
}
