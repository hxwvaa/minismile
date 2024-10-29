#include <stdio.h>
#include <limits.h>
#include "minishell.h"

// unsigned long long	ft_atol(const char *str)
// {
// 	unsigned long long	nb;
// 	int					i;
// 	int					sign;

// 	sign = 1;
// 	nb = 0;
// 	i = 0;
// 	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
// 		str++;
// 	if (*str == '-' || *str == '+')
// 	{
// 		if (*str == '-')
// 			sign *= -1;
// 		str++;
// 	}
// 	while (str[i] >= '0' && str[i] <= '9')
// 		i++;
// 	// if (i > 19) // 19
// 	// 	return (2147483649);
// 	while (*str >= '0' && *str <= '9')
// 	{
// 		nb = nb * 10 + *str - '0';
// 		str++;
// 	}
//     if (nb)
// 	return (sign * nb);
// }

void our_exeenvv(t_shell *data, char **env)
{
	int i;

	i = 0;
	while(env[i])
	{
		// write(1, "a", 1);
		data->envi[i] = ft_strdup(env[i]);
		i++;
	}
	data->envi[i] = NULL;
}

int main(int ac, char **av, char **env)
{
	t_shell data;
	data.envi = malloc(sizeof(env) + 1);
	// data.envi = NULL;
    our_exeenvv(&data, env);
	int i =0;
	while(data.envi[i])
	{
		printf("%s\n",data.envi[i]);
		i++;
	}
}