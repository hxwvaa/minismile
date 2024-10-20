#include "minishell.h"

//void	execute_cmd(char *cmd, char **env, int ifd, int fd[])
void	execute_cmd(char **cmd, char **env)
{
	//char	**cmd_av;
	char	*cmd_path;

	// if (only_space(cmd) == 1)
	// 	inv_string(ifd, fd);
	//cmd_av = ft_split(cmd, ' ');
	cmd_path = get_cmd_path(cmd[0], env);
	// if (!cmd_path)
	// 	inv_cmd(cmd_av[0], cmd_av);
	// if (ifd != STDIN_FILENO)
	// {
	// 	dup2(ifd, STDIN_FILENO);
	// 	close(ifd);
	// }
	// if (fd[1] != STDOUT_FILENO)
	// {
	// 	dup2(fd[1], STDOUT_FILENO);
	// 	close(fd[1]);
	// }
	execve(cmd_path, cmd, env);
// 	if (execve(cmd_path, cmd_av, env) == -1)
// 		inv_cmd(cmd_av[0], cmd_av);
 }

void    pre_execute_cmd(char **cmd, char **env)
{
	// char **ven;
	pid_t pid = fork ();
	if(pid == -1)
		write(2, "fork error\n", 11);
	if(pid == 0)
	{
		execute_cmd(cmd, env);
	}
	else
	{
		int status;
		wait(&status);
	}
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

int	our_fill(char *s, char **cmd)
{
	int	i;
	int	word;
	int j;
	int k;

	i = 0;
	word = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)))
			i++;
		j = 0;
		k = 0;
		if (s[i] && s[i] != ' ' && !(s[i] >= 9 && s[i] <= 13) && !(s[i] == '<'
				|| s[i] == '>' || s[i] == '|'))
			{
				j = i;
			}	
		while (s[i] && s[i] != ' ' && !(s[i] >= 9 && s[i] <= 13))
		{
			if ((s[i] == '<' || s[i] == '>' || s[i] == '|'))
			{
				k = i;
				i++;
				break ;
			}
			if ((s[i] == '\'' || s[i] == '\"') && (s[i- 1] == ' ' || (s[i
					- 1] >= 9 && s[i - 1] <= 13)))
				i = our_quote(s, i + 1, s[i]);
			else if ((s[i] == '\'' || s[i] == '\"') && s[i - 1] != ' ' && !(s[i
					- 1] >= 9 && s[i - 1] <= 13))
				i = our_quote(s, i + 1, s[i]);
			i++;
		}
		if(k == 0)
		{
			cmd[word] = ft_calloc(((i - j) + 1), sizeof(char));
			if(!cmd[word])
				return(our_free(cmd, word));
			our_strcpy(cmd[word], s + j, i - j);
		}
		else
		{	
			cmd[word] = ft_calloc(((i - k) + 1), sizeof(char));
			if(!cmd[word])
				return(our_free(cmd, word));
			our_strcpy(cmd[word], s + k, i - k);
		}
		word++;	
	}
	return (0);
}


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

int	our_wount(char *s)
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
				i = our_quote(s, i + 1, s[i]);
			else if ((s[i] == '\'' || s[i] == '\"') && s[i - 1] != ' ' && !(s[i
					- 1] >= 9 && s[i - 1] <= 13))
				i = our_quote(s, i + 1, s[i]);
			i++;
		}
	}
	return (word);
}

char	**our_tokenize(char *s)
{
	char *r;
	char **split;
	// char *cmd;
	int j = 0;

	r = ft_strtrim(s, " ");
	printf("\nafter_trim - {%s}\n", r);
	int i = our_wount(r);
	printf("\ntoken_count - %d\n", i);
    split = ft_calloc(i + 1, sizeof(char *));
    if(!split)
        return(NULL);
    split[i] = 0;
    if(our_fill(r, split) == -1)
        return(NULL);
	printf("{");
    while(j < i)
        printf("%s,", split[j++]);

	printf("}\n");
	free(r);
	return (split);
}