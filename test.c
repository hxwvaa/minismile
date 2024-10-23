#include <stdio.h>
#include <stdbool.h>
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


size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}


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
	// while (str[i] >= '0' && str[i] <= '9')
	// 	i++;
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10 + *str - '0';
		str++;
	}
	if ((sign * nb) == 	LONG_MIN)
		return(LONG_MIN);
	return (sign * nb);
}


// long long	ft_atol(const char *str)
// {
// 	long long	nb;
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
// 	while (*str >= '0' && *str <= '9')
// 	{
// 		nb = nb * 10 + *str - '0';
// 		str++;
// 	}
// 	if ((sign * nb) == 	LONG_MIN);
// 		return(LONG_MIN);
// 	return (sign * nb);
// }

bool is_num_very_small(char *str)
{
    size_t i = 0;
    long long nb = 0;

	i = 0;
	nb = 0;
	if (ft_atol(str) == LONG_MIN)
		return(false);
	if (str[i] == '-')
		i++;
    if (ft_strlen(str) > 19)
        return(true);
	else if (ft_strlen(str) < 19)
		return(false);
	while (i < ft_strlen(str) && str[i] >= '0' && str[i] <= '9')
    	nb = nb * 10 + str[i++] - '0';
    if (nb * -1 < LONG_MIN)
        return(true);
    i = str[i] - '0';
    if (i > 8)
        return(true);
    return(false);
}

int main(void)
{
//      long long n = ft_atol("-9223372036854775808");
// 	// if (n > 9223372036854775807)
// 	// 	printf("1\n");
// 	// else
// 	// 	printf("0\n");
// 	printf("%lld", n);
	char *str = "-9223372036854775809";
	printf("%d", is_num_very_small(str));
}