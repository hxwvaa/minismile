#include "../minishell.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	i;

	str = (char *)malloc(ftb_strlen(s1) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}