#include "minishell.h"


int	our_quote(char *str, int i, char quote)
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

int our_help_wount(int *word, int *i, char *s)
{
	if(!s[*i])
		return(-1);
	if ((s[*i] == '<' || s[*i] == '>' || s[*i] == '|'))
	{
		(*word)++;
		(*i)++;
		return -1;
	}
	if(*i > 0) // we were decrementing -1 always
	{
		if ((s[*i] == '\'' || s[*i] == '\"')
		&& (s[*i - 1] == ' ' || (s[*i - 1] >= 9 && s[*i - 1] <= 13)))
			*i = our_quote(s, *i + 1, s[*i]);
		else if ((s[*i] == '\'' || s[*i] == '\"') && s[*i - 1] != ' '
		&& !(s[*i - 1] >= 9 && s[*i - 1] <= 13))
			*i = our_quote(s, *i + 1, s[*i]);
	}
	else
	{
		if ((s[*i] == '\'' || s[*i] == '\"'))
			*i = our_quote(s, *i + 1, s[*i]);
		else if ((s[*i] == '\'' || s[*i] == '\"'))
			*i = our_quote(s, *i + 1, s[*i]); // those two lines not needed ??!
	}
	return(0);
}

int	our_wount(char *s, int *i, int word)
{
	while (s[*i])
	{
		while (s[*i] && (s[*i] == ' ' || (s[*i] >= 9 && s[*i] <= 13)))
			(*i)++;
		if (s[*i] && s[*i] != ' ' && !(s[*i] >= 9 && s[*i] <= 13)
			&& !(s[*i] == '<' || s[*i] == '>' || s[*i] == '|'))
			word++;
		while (s[*i] && s[*i] != ' ' && !(s[*i] >= 9 && s[*i] <= 13))
		{
			if (our_help_wount(&word, i, s) == -1)
				break;
			if(s[*i])
				(*i)++; //we were incrementing always
		}
	}
	return (word);
}

int	our_free(char **str, int t)
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

void	our_strcpy(char *des, char *src, int j)
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

static int handle_operands(int *j, int *i, char *s)
{
	if ((s[*i] == '<' || s[*i] == '>' || s[*i] == '|'))
	{
		(*j) = (*i);
		(*i)++;
		if((s[(*i) - 1] == '<' && s[*i] == '<') 
			|| (s[(*i) - 1] == '>' && s[*i] == '>'))
			(*i)++;
		return (-1);
	}
	return (0);
}

static void quotes_handle(int *i, char *s)
{
	if(*i > 0)
	{
		if ((s[*i] == '\'' || s[*i] == '\"')
		&& (s[*i - 1] == ' ' || (s[*i - 1] >= 9 && s[*i - 1] <= 13)))
			*i = our_quote(s, *i + 1, s[*i]);
		else if ((s[*i] == '\'' || s[*i] == '\"') && s[*i - 1] != ' '
		&& !(s[*i - 1] >= 9 && s[*i - 1] <= 13))
			*i = our_quote(s, *i + 1, s[*i]);
	}
	else if ((s[*i] == '\'' || s[*i] == '\"'))
		*i = our_quote(s, *i + 1, s[*i]);
}

int our_help_fill(int *j, int *i, char *s)
{
	if(s[*i] == '\0')
		return(-1);
	if(handle_operands(j, i, s) == -1)
		return -1;
	quotes_handle(i, s);
	if(s[*i])
		(*i)++;
	if ((s[*i] == '<' || s[*i] == '>' || s[*i] == '|'))
		return -1;
	return(0);
}

// int our_help_fill(int *j, int *i, char *s)
// {
// 	if(s[*i] == '\0')
// 		return(-1);
// 	if ((s[*i] == '<' || s[*i] == '>' || s[*i] == '|'))
// 	{
// 		(*j) = (*i);
// 		(*i)++;
// 		if(s[(*i) - 1] == '<' && s[*i] == '<')
// 		{
// 			(*i)++;
// 			return -1;
// 		}
// 		else if(s[(*i) - 1] == '>' && s[*i] == '>')
// 		{
// 			(*i)++;
// 			return -1;
// 		}
// 		return -1;
// 	}

// 	if(*i > 0) // we were decrementing -1 always
// 	{
// 		if ((s[*i] == '\'' || s[*i] == '\"')
// 		&& (s[*i - 1] == ' ' || (s[*i - 1] >= 9 && s[*i - 1] <= 13)))
// 			*i = our_quote(s, *i + 1, s[*i]);
// 		else if ((s[*i] == '\'' || s[*i] == '\"') && s[*i - 1] != ' '
// 		&& !(s[*i - 1] >= 9 && s[*i - 1] <= 13))
// 			*i = our_quote(s, *i + 1, s[*i]);
// 	}
// 	else
// 	{
// 		if ((s[*i] == '\'' || s[*i] == '\"'))
// 			*i = our_quote(s, *i + 1, s[*i]);
// 		else if ((s[*i] == '\'' || s[*i] == '\"'))
// 			*i = our_quote(s, *i + 1, s[*i]);
// 	}
// 	if(s[*i])
// 		(*i)++; // we were incrementing always
// 	if ((s[*i] == '<' || s[*i] == '>' || s[*i] == '|'))
// 		return -1;
// 	return(0);
// }

int	our_fill(char *s, char **cmd, int count)
{
	int	i;
	int	word;
	int j;

	i = 0;
	word = 0;
	while (s[i] && word < count)
	{
		while (s[i] && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)))
			i++;
		if (s[i] && s[i] != ' ' && !(s[i] >= 9 && s[i] <= 13) && !(s[i] == '<'
				|| s[i] == '>' || s[i] == '|'))
			j = i;
		while (s[i] && s[i] != ' ' && !(s[i] >= 9 && s[i] <= 13))
		{
			if (our_help_fill(&j, &i, s) == -1)
				break;
		}
		cmd[word] = ft_calloc(((i - j) + 1), sizeof(char));
		if(!cmd[word])
			return(our_free(cmd, word));
		our_strcpy(cmd[word], s + j, i - j);
		word++;
	}
	return (0);
}

char	**our_tokenize(char *s)
{
	char *r;
	char **split;
	int i;
	int word;

	i = 0;
	word = 0;
	r = ft_strtrim(s, " "); //need to check if s is empty
	if(r == NULL)
		return NULL;
	printf("\nafter_trim - {%s}\n", r); //SAVE
	word = our_wount(r, &i, word);
	printf("\ntoken_count - %d\n", word); //SAVE
    split = ft_calloc(word + 1, sizeof(char *));
    if(!split)
        return(NULL);
    split[word] = 0;
    if(our_fill(r, split, word) == -1)
	{
		free(r);
        return(NULL);
	}
	free(r);
	return (split);
}
