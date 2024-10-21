#include <stdio.h>
#include <limits.h>

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

long long	ft_atol(const char *str)
{
	long long	nb;
	int					i;
	int					sign;

	sign = 1;
	nb = 0;
	i = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10 + *str - '0';
		str++;
	}
	if (nb > LONG_MAX || ((nb * sign) < LONG_MIN))
		return (LONG_MIN);
	return (sign * nb);
}

int main(int ac, char **av)
{
    printf("%lld", ft_atol("-9223372036854775808"));
}