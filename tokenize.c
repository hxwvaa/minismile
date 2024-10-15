#include "minishell.h"

int ft_quote

int	ft_wount(char *s)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)))
			i++;
		if (s[i] && s[i] != ' ' && !(s[i] >= 9 && s[i] <= 13))
        {
            if(s[i] == '\'' || s[i] == '\"')
			{
                
            }
            word++;
        }
		while (s[i] && s[i] != ' ' && !(s[i] >= 9 && s[i] <= 13))
			i++;
	}
	return (word);
}

char **ft_tokenize(char *s)
{
    char *r;
    char **split;

    split = NULL;
    r = ft_strtrim(s, " ");
    int i = ft_wount(r);
    printf("%s\n%d\n", r, i);
    return(split);
}