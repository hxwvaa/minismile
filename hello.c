void help_wount(int *word, int *i, char *s)
{
	if ((s[*i] == '<' || s[*i] == '>' || s[*i] == '|'))
	{
		(*word)++;
		(*i)++;
		return ;
	}
	if ((s[*i] == '\'' || s[*i] == '\"')
		&& (s[*i - 1] == ' ' || (s[*i - 1] >= 9 && s[*i - 1] <= 13)))
		*i = our_quote(s, *i + 1, s[*i]);
	else if ((s[*i] == '\'' || s[*i] == '\"') && s[*i - 1] != ' '
		&& !(s[*i - 1] >= 9 && s[*i - 1] <= 13))
		*i = our_quote(s, *i + 1, s[*i]);
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
			help_wount(&word, i, s);
			(*i)++;
		}
	}
	return (word);
}
