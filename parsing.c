/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbasheer <hbasheer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:43:31 by hbasheer          #+#    #+#             */
/*   Updated: 2024/11/07 17:21:21 by hbasheer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
// 			if ((s[*i] == '<' || s[*i] == '>' || s[*i] == '|'))
// 			{
// 				word++;
// 				(*i)++;
// 				break ;
// 			}
// 			if ((s[*i] == '\'' || s[*i] == '\"')
// 				&& (s[*i - 1] == ' ' || (s[*i - 1] >= 9 && s[*i - 1] <= 13)))
// 				*i = our_quote(s, *i + 1, s[*i]);
// 			else if ((s[*i] == '\'' || s[*i] == '\"') && s[*i - 1] != ' '
// 				&& !(s[*i - 1] >= 9 && s[*i - 1] <= 13))
// 				*i = our_quote(s, *i + 1, s[*i]);
// 			(*i)++;
// 		}
// 	}
// 	return (word);
// }

void	check_built_in(char **av, t_shell *data)
{
	int flag;

	flag = 0;
	if (ft_strncmp(av[0], "exit", 5) == 0)
		(flag = 1, exit_shell(av));
	else if (ft_strncmp(av[0], "env", 4) == 0)
		our_env(data->envir);
	else if (ft_strncmp(av[0], "unset", 6) == 0)
		our_unset(av[1], &data->envir);
	else if (ft_strncmp(av[0], "echo", 5) == 0)
		our_echo(av);
	else if (ft_strncmp(av[0], "export", 7) == 0)
		our_export(av, data);
	else if (ft_strncmp(av[0], "pwd", 4) == 0)
	{
		if (av[1] != NULL)
			write(2, "pwd: too many arguments\n", 24);
		// echo $?// data->exit_code = 1
		else
			our_pwd();
	}
	else if (ft_strncmp(av[0], "cd", 3) == 0)
		our_cdir(av[1], data);
}
