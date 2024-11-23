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


//was using before
// int input_file(t_cmd *curr, int *input)
// {
//     t_redir *n_inp;
//     if(*input != STDIN_FILENO && *input != -1)
//     {
//         close(*input);
//         *input = -1;
//     }
//     n_inp = curr->inputs;
//     while(n_inp) 
//     {
//         if(n_inp->hd_input)
//         {
//             int hdpipe[2];

//             if(*input != STDIN_FILENO && *input != -1)
//                 close(*input);
//             pipe(hdpipe);
//             write(hdpipe[1], n_inp->hd_input, ft_strlen(n_inp->hd_input));
//             close(hdpipe[1]);
//             //input = hdpipe[0];
//             free(n_inp->hd_input);
//             n_inp->hd_input = NULL;
//             *input = hdpipe[0];
//             //return (hdpipe[0]);
//             //return (0);
//         }
//         else if(!n_inp->hd_input) // else
//         {
//             if(*input != STDIN_FILENO && *input != -1)
//                 close(*input);
//             *input = open(n_inp->file, O_RDONLY, 0777);
//             if(*input == -1)
//             {
//                 input_invalid(n_inp->file);
//                 //input = open("/dev/null", O_RDONLY);
//                 int pipefd[2];
//                 pipe(pipefd);
//                 close(pipefd[1]);
//                 *input = pipefd[0];
//                 return (-1);
//                 //without this it would make the program hang cause it waits for input
//                 // mycommand line is < asd cat | wc -l, it will run forever because wc -l waits for
//                 // input
//                 //return (-1);
//             }
//         }
//         n_inp = n_inp->next;
//     }
//     //return (input);
//     return (0);
// }
