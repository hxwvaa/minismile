// void help_wount(int *word, int *i, char *s)
// {
// 	if ((s[*i] == '<' || s[*i] == '>' || s[*i] == '|'))
// 	{
// 		(*word)++;
// 		(*i)++;
// 		return ;
// 	}
// 	if ((s[*i] == '\'' || s[*i] == '\"')
// 		&& (s[*i - 1] == ' ' || (s[*i - 1] >= 9 && s[*i - 1] <= 13)))
// 		*i = our_quote(s, *i + 1, s[*i]);
// 	else if ((s[*i] == '\'' || s[*i] == '\"') && s[*i - 1] != ' '
// 		&& !(s[*i - 1] >= 9 && s[*i - 1] <= 13))
// 		*i = our_quote(s, *i + 1, s[*i]);
// }

// int	our_wount(char *s, int *i, int word)
// {
// 	while (s[*i])
// 	{
// 		while (s[*i] && (s[*i] == ' ' || (s[*i] >= 9 && s[*i] <= 13)))
// 			(*i)++;
// 		if (s[*i] && s[*i] != ' ' && !(s[*i] >= 9 && s[*i] <= 13)
// 			&& !(s[*i] == '<' || s[*i] == '>' || s[*i] == '|'))
// 			word++;
// 		while (s[*i] && s[*i] != ' ' && !(s[*i] >= 9 && s[*i] <= 13))
// 		{
// 			help_wount(&word, i, s);
// 			(*i)++;
// 		}
// 	}
// 	return (word);
// }
int	check_syntax_helper(char **av, int i)
{
	if (ft_strncmp(av[i + 1], ">", 2) == 0 || ft_strncmp(av[i + 1], "<",
			2) == 0)
	{
		if (av[i + 2])
		{
			if (ft_strncmp(av[i + 2], ">", 2) == 0 || ft_strncmp(av[i + 2], "<",
					2) == 0)
			{
				return (1);
				// write(2, "syntax error near unexpected token `>'\n", 39);
				// //exit code = 258 ?
				// return (1);
			}
		}
	}
	return (0);
}

int	check_syntax(char **av, int i)
{
	i = 0;
	while (av[i])
	{
		if (ft_strncmp(av[i], ">", 2) == 0 || ft_strncmp(av[i], "<", 2) == 0)
		{
			if (av[i + 1])
			{
				if (check_syntax_helper(av, i) == 1)
				{
					write(2, "syntax error near unexpected token `>'\n", 39);
					// exit code = 258 ?
					return (1);
				}
			}
		}
		i++;
	}
	return (0);
}
