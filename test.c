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

int handle_redir_in(t_redir *temp, int *input, int *output, t_cmd *curr)
{
    int pipefd[2];

	if(*input != STDIN_FILENO && *input != -1)
        close(*input);
    *input = open(temp->file, O_RDONLY);
    if(*input == -1)
    {
        perror(temp->file);
        pipe(pipefd);
        close(pipefd[1]);
        *input = pipefd[0];
        if(*output != STDOUT_FILENO && *output != -1)
        {
            close(*output);
            *output = -1; //without this caused ls output be printed in results.txt "ls >results.txt <er | ls | cat | wc -l"
        }
        curr->redir_out = 0;
        return (-1);
    }
    return (0);
}
