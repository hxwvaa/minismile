#include "../minishell.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	ch;
	char	*st;

	ch = (char)c;
	st = (char *)s;
	i = 0;
	while (st[i])
	{
		if (st[i] == ch)
			return (&st[i]);
		i++;
	}
	if (st[i] == ch)
		return (&st[i]);
	return (NULL);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
	{
		i = ft_strlen(src);
		return (i);
	}
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*ns;

	i = 0;
	j = ft_strlen(s1);
	ns = 0;
	if (s1 != 0 && set != 0)
	{
		while (s1[i] && ft_strchr(set, s1[i]))
			i++;
		while (s1[j - 1] && ft_strchr(set, s1[j - 1]) && j > i)
			j--;
		ns = (char *)malloc(j - i + 1);
		if (!ns)
			return (NULL);
		ft_strlcpy(ns, &s1[i], j - i + 1);
	}
	return (ns);
}