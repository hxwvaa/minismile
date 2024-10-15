#include "minishell.h"

// still doesnt function with quotes withing quotes "  ' ' " or the other way around
// check testing.txt if you want to see test results


int	empty_space(char *s, int len)
{
	int	i;

	i = 1;
	if (s[i] == '\0' || s[i] == s[0])
		return (1);
	while (i < len - 1)
	{
		if(s[i] != ' ')
			return(0);
		i++;
	}
	return (1);
}

int ft_is_quote(char *s, char q)
{
	int i;

	i = 1; // we skip first quote
	while(s[i])
	{
		//&& (s[i + 1] == ' ' || s[i + 1] == '\0')) i had this in the if statement below but it would count "hello"hello as 2 tokens if included
		if(s[i] == q)  // check if we found the closing quote, !!! it still doesnt work quotes in quotes i will add examples
		{
			if(empty_space(s, i + 1)) // then we check if the string within the quotes is null or just spaces
				return(0);
			i++; // count the closing quote
			return(i);
		}
		i++;
	}
	return(0);
}

int	ft_wount(char *s)
{
	int	i;
	int	word;
	int qlen;

	i = 0;
	word = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)))
			i++;
		if (s[i] && s[i] != ' ' && !(s[i] >= 9 && s[i] <= 13))
        {
            if (s[i] == '\'' || s[i] == '\"') // check for quotes
			{
                //printf("%d\n", i);
				//printf("%c\n", s[9]);
				qlen = ft_is_quote(&s[i], s[i]); // get the length of the quoted string
				if(qlen) // if its != 0 that means it not an empty string or a string with just spaces so we count it as token
				{
					word++;
					// if(s[i] == '\'')
					// i += ft_is_quote(&s[i], '\'');
					// else if(s[i] == '\"')
					// i += ft_is_quote(&s[i], '\"');
					i += qlen; 
				}
            }
			else
            	word++;
        }
		//printf("%d\n", i);
		while (s[i] && s[i] != ' ' && !(s[i] >= 9 && s[i] <= 13))
			i++;
	}
	//printf("%c\n", s[20]);
	return (word);
}

char **ft_tokenize(char *s)
{
    char *r;
    char **split;

    split = NULL;
    r = ft_strtrim(s, " ");
    int i = ft_wount(r);
    printf("%s\ntokens:%d\n", r, i);
    return(split);
}