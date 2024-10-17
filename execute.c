#include "minishell.h"

void    execute_cmd(char *cmd, char **env);

int	t_quote(char *str, int i, char quote)
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

int	t_wount(char *s)
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
				i = t_quote(s, i + 1, s[i]);
			else if ((s[i] == '\'' || s[i] == '\"') && s[i - 1] != ' ' && !(s[i
					- 1] >= 9 && s[i - 1] <= 13))
				i = t_quote(s, i + 1, s[i]);
			i++;
		}
	}
	return (word);
}



int	t_free(char **str, int t)
{
	int	i;

	i = 0;
	while (i <= t)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (-1);
}

void	t_strcpy(char *des, char *src, int j)
{
	int	i;

	i = 0;
	while (src[i] && i < j)
	{
		des[i] = src[i];
		i++;
	}
	des[i] = '\0';
}
int	t_fill(char *s, char **cmd)
{
	int	i;
	int	word;
	int j;

	i = 0;
	word = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)))
			i++;
		if (s[i] && s[i] != ' ' && !(s[i] >= 9 && s[i] <= 13) && !(s[i] == '<'
				|| s[i] == '>' || s[i] == '|'))
			word++;
		j = 0;	
		while (s[i + j] && s[i + j] != ' ' && !(s[i + j] >= 9 && s[i + j] <= 13))
		{
			if ((s[i + j] == '<' || s[i + j] == '>' || s[i + j] == '|'))
			{
				word++;
				j++;
				break ;
			}
			if ((s[i + j] == '\'' || s[i + j] == '\"') && (s[(i +j)- 1] = ' ' || (s[(i + j)
					- 1] >= 9 && s[(i + j) - 1] <= 13)))
				j = t_quote(s, (i + j) + 1, s[i + j]);
			else if ((s[i] == '\'' || s[i] == '\"') && s[i - 1] != ' ' && !(s[i
					- 1] >= 9 && s[i - 1] <= 13))
				j = t_quote(s, (i + j) + 1, s[i + j]);
			i += j;
		}
		cmd[word] = ft_calloc((j + 1), sizeof(char));
		if(!cmd[word])
			return(t_free(cmd, word));
		t_strcpy(cmd[word], s + i, j);	
	}
	return (0);
}

char	**st_tokenize(char *s)
{
	char *r;
	char **split;
	char *cmd;

	//split = NULL;
	r = ft_strtrim(s, " ");
	printf("\nafter_trim - {%s}\n", r);
	int i = t_wount(r);
	printf("\ntoken_count - %d\n", i);
	printf("after token\n");
    split = ft_calloc(i + 1, sizeof(char *));
	printf("after calloc");
    if(!split)
        return(NULL);
    split[i] = 0;
    printf("hi");
    if(t_fill(r, split) == -1)
        return(NULL);
    //split = t_fill(r, split);
    while(i != 0)
        printf("{%s,}", split[i--]);
	free(r);
	return (split);
}