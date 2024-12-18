/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:23:12 by mshaheen          #+#    #+#             */
/*   Updated: 2024/12/18 20:23:13 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_oargs(char **our_args)
{
	int	i;

	i = 0;
	while (our_args[i])
	{
		i++;
	}
	i--;
	return (i);
}

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signo = SIGINT;
	}
}

void	read_loop(t_shell *data)
{
	while (1)
	{
		signal(SIGINT, &handle_signal);
		signal(SIGQUIT, SIG_IGN);
		data->line = readline("minishell♣ > ");
		if (g_signo == SIGINT)
		{
			data->exit_code = 1;
			g_signo = 0;
		}
		if (!data->line)
			(free_all(data), exit(0));
		data->our_args = our_tokenize(data->line);
		if (!data->our_args)
			(free_all(data), exit(12));
		if (check_syntax(data->our_args, 0, data) == 1)
			continue ;
		array_token_list(data, data->our_args, count_oargs(data->our_args));
		if (check_quotes(data->tokens, data) == -1)
			continue ;
		if (our_extok(data->tokens, data) == -1)
			(free_all(data), exit(1));
		our_toklist_cmdlist(data->tokens, data);
		pre_execute(data, STDIN_FILENO, STDOUT_FILENO);
	}
}
