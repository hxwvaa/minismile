/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:25:26 by mshaheen          #+#    #+#             */
/*   Updated: 2024/11/24 11:27:57 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**envlist_envarray(t_list *env)
{
	char	**env_arr;
	t_list	*curr;
	int		i;

	i = ft_lstsize(env);
	env_arr = ft_calloc((i + 1), sizeof(char *));
	if (!env_arr)
		return (perror("malloc"), NULL);
	i = 0;
	curr = env;
	while (curr)
	{
		env_arr[i] = ft_strdup(curr->content);
		if (!env_arr[i])
		{
			while (i > 0)
				free(env_arr[i--]);
			free(env_arr);
			return (NULL);
		}
		i++;
		curr = curr->next;
	}
	return (env_arr);
}

void invalid_lstcmd(char *file, int *input, int *output, t_shell *data)
{
    write(2, "minishell: command not found: ", 30);
    ft_putstr_fd(file, 2);
    write(2, "\n", 1);
	//ft_putendl_fd(file, 2);
	//free_array(array);
    if (*input != -1)
	    close(*input);
    if (*output != -1)
	    close(*output);
    if (data->tokens)
        our_toklistclear(&data->tokens);
    if (data->envir)
        our_envlistclear(&data->envir);
    if (data->cmds) 
        our_cmdlistclear(&data->cmds);
    if (data->envi)
        free_arr(data->envi);
    data->exit_code = 127;
    //exit_shell(data->cmds->cargs, data);
	exit(1);
}