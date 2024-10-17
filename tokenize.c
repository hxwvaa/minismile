#include "minishell.h"


int	ft_quote(char *str, int i, char quote)
{
	if (quote == '\'')
	{
		while (str[i] && str[i] != '\'')
			i++;
		return (i);
	}
	else
	{
		while (str[i] && str[i] != '\"')
			i++;
		return (i);
	}
}
/**
 * @brief this function counts how many tokens we have
 * @param s - this the command line after trimming
 * @return returns the token count
 * 
*/
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
		if (s[i] && s[i] != ' ' && !(s[i] >= 9 && s[i] <= 13) && !(s[i] == '<'
				|| s[i] == '>' || s[i] == '|'))
			word++;	
		while (s[i] && s[i] != ' ' && !(s[i] >= 9 && s[i] <= 13))
		{
			if ((s[i] == '<' || s[i] == '>' || s[i] == '|'))
			{
				word++;
				i++;
				break ;
			}
			if ((s[i] == '\'' || s[i] == '\"') && (s[i - 1] = ' ' || (s[i
					- 1] >= 9 && s[i - 1] <= 13)))
				i = ft_quote(s, i + 1, s[i]);
			else if ((s[i] == '\'' || s[i] == '\"') && s[i - 1] != ' ' && !(s[i
					- 1] >= 9 && s[i - 1] <= 13))
				i = ft_quote(s, i + 1, s[i]);
			i++;
		}
	}
	return (word);
}

char	**ft_tokenize(char *s)
{
	char *r;
	char **split;

	split = NULL;
	r = ft_strtrim(s, " ");
	printf("\nafter_trim - {%s}\n", r);
	int i = ft_wount(r);
	printf("\ntoken_count - %d\n", i);
	free(r);
	return (split);
}
