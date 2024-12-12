/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbasheer <hbasheer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:25:26 by mshaheen          #+#    #+#             */
/*   Updated: 2024/12/12 13:59:08 by hbasheer         ###   ########.fr       */
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

void error_message(char *file)
{
	if(ft_strchr(file, '/'))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	else
    {
		write(2, "minishell: command not found: ", 30);
    	ft_putstr_fd(file, 2);
    	write(2, "\n", 1);
	}
}

void invalid_lstcmd(char *file, int *input, int *output, t_shell *data)
{
	error_message(file);
	free(data->backup_pwd);
	if (data->cmd_path)
	{
		free(data->cmd_path);
		data->cmd_path = NULL;
	}
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
	exit(127);
}
void invalid_cmd_dir(char *file, int *input, int *output, t_shell *data)
{
	write(2, "shell: ", 7);
	ft_putstr_fd(file, 2);
	ft_putendl_fd(": Is a directory", 2);
	free(data->backup_pwd);
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
    data->exit_code = 126;
    //exit_shell(data->cmds->cargs, data);
	exit(126);
}

int check_if_directory(char *cmd)
{
	struct stat status;
	// printf("\033[32;1m%s\033[0m", cmd);
    // fprintf(stderr, "\033[32;1m%s\033[0m\n", cmd);
	if(stat(cmd, &status) != 0)
		return (0);
	return (S_ISDIR(status.st_mode)); // this returns 1, if its a directory or 0 if its not a directory

}
