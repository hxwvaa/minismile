int	set_token_type(char *token, int *first, int *file)
{
	if (ft_strncmp(token, "|", 2) == 0)
	{
		(*first) = 1;
		return (PIPE);
	}
	else if (ft_strncmp(token, "<", 2) == 0)
		return (*file = 1, REDIR_IN);
	else if (ft_strncmp(token, ">", 2) == 0)
		return (*file = 1, REDIR_OUT);
	else if (ft_strncmp(token, ">>", 3) == 0)
		return (*file = 1, APPEND);
	else if (ft_strncmp(token, "<<", 3) == 0)
		return (*file = 2, HERE_DOC);
	else if (token[0] == '-' && !*first)
		return (FLAG);
	else if (*file == 1)
		return (*file = 0, FILE_NAME);
	else if (*file == 2)
		return (*file = 0, LIMITER);
	else if (*first)
	{
		*first = 0;
		return (CMD);
	}
	return (ARGS);
}
