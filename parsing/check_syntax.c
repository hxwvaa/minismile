/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 00:05:08 by mshaheen          #+#    #+#             */
/*   Updated: 2024/12/18 15:46:01 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_syntax_redirect(char **av, int i)
{
	if (ft_strncmp(av[i + 1], ">", 2) == 0 || ft_strncmp(av[i + 1], "<",
			2) == 0 || ft_strncmp(av[i + 1], ">>", 3) == 0
		|| ft_strncmp(av[i + 1], "<<", 3) == 0)
	{
		return (1);
	}
	return (0);
}

int	check_syntax_pipe(char **av, int i)
{
	if (ft_strncmp(av[i + 1], "|", 2) == 0)
	{
		write(2, "syntax error near unexpected token `|'\n", 39);
		//exit code = 258
		return (1);
	}
	return (0);
}

int	redirect_checker(char **av, int i)
{
	if (av[i + 1])
	{
		if (check_syntax_redirect(av, i) == 1)
		{
			write(2, "syntax error near unexpected token `>' or `<'\n", 46);
			//data->exit_code = 258;
			return (1);
		}
	}
	if (av[i + 1] && ft_strncmp(av[i +1], "|", 2) == 0)
	{
		write(2, "syntax error near unexpected token `|'\n", 39);
		//data->exit_code = 258
		return (1);
	}
	if (!av[i + 1])
	{
		write(2, "syntax error near unexpected token `newline'\n", 45);
		//data->exit_code = 258
		return (1);
	}
	return (0);
}

int	pipe_checker(char **av, int i)
{
	if (i == 0)
	{
		write(2, "syntax error near unexpected token `|'\n", 39);
		return (1);
	}
	if (av[i +1])
	{
		if (check_syntax_pipe(av, i) == 1)
			return (1);
	}
	else
	{
		write(2, "syntax error near unexpected token `|'\n", 39);
		return (1);
	}
	return (0);
}

int	check_syntax(char **av, int i, t_shell *data)
{
	int ret;

	ret = 0;
	i = 0;
	while (av[i])
	{
		if (ft_strncmp(av[i], "|", 2) == 0)
		{
			if (pipe_checker(av, i) == 1)
				ret = 1;
		}
		if (ft_strncmp(av[i], ">", 2) == 0 || ft_strncmp(av[i], "<", 2) == 0
			|| ft_strncmp(av[i], ">>", 3) == 0
			|| ft_strncmp(av[i], "<<", 3) == 0)
		{
			if (redirect_checker(av, i) == 1)
				ret = 1;
		}
		i++;
	}
	if(ret == 1)
	{
		free_arr(av);
		if(data->line)
			add_history(data->line);
		free(data->line);
		data->exit_code = 258;
	}
	return (ret);
}
